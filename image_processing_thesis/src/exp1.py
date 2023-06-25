import cv2
import shutil
import numpy as np
from matplotlib import pyplot as plt
from numpy.core.defchararray import equal
from rich import print
import cfg
import util


def normalized(img: np.ndarray) -> np.ndarray:
    img = (img - np.min(img)) / (np.max(img) - np.min(img)) * 255
    return img.astype(np.uint8)


def HomomorphicFiltering(img: np.ndarray, sigma: int = 10) -> np.ndarray:
    """
    同态滤波 高斯高通滤波器
    https://stackoverflow.com/questions/24731810/segmenting-license-plate-characters#:~:text=Before%20I%20start,Python%E4%BB%A3%E7%A0%81
    """
    rows, cols = img.shape[0], img.shape[1]
    M, N = 2 * rows + 1, 2 * cols + 1

    def GaussianHighPass() -> np.ndarray:
        """
        高斯高通滤波器
        """
        X, Y = np.meshgrid(
            np.linspace(0, N - 1, N),
            np.linspace(0, M - 1, M),
        )
        centerX, centerY = np.ceil(N / 2), np.ceil(M / 2)
        gaussianNumerator = (X - centerX)**2 + (Y - centerY)**2
        Hlow = np.exp(-gaussianNumerator / (2 * sigma * sigma))
        Hhigh = 1 - Hlow  # type: ignore
        return Hhigh

    img_log = np.log1p(img.astype(np.float_) / 255)
    img_fft = np.fft.fft2(img_log, (M, N))
    mask = np.fft.ifftshift(GaussianHighPass())
    result = img_fft * mask
    img_out_log = np.real(np.fft.ifft2(result))[0:rows, 0:cols]
    img_out: np.ndarray = np.expm1(img_out_log)  # type:ignore
    return img_out


def clip(img: np.ndarray, rate: float) -> np.ndarray:
    """
    考虑到图片中存在无用高光
    直接采取比例截取的方式
    """
    hlr_pos = int(img.size * rate)
    hlr_val: float = np.partition(img.flat, -(hlr_pos + 1))[-(hlr_pos + 1)]
    return img.clip(img.min(), hlr_val)


def gammaCorrection(img: np.ndarray, gamma: float) -> np.ndarray:
    img = (img - np.min(img)) / (np.max(img) - np.min(img))
    return img**gamma  # type: ignore


def solve(img: np.ndarray) -> np.ndarray:
    def debug(suffix: str):
        if cfg.DEBUG and __name__ == "__main__":
            if hasattr(debug, 'cnt'):
                debug.cnt += 1
            else:
                debug.cnt = 1
            cv2.imwrite(
                str(util.output_dir_var.get() /
                    f"{util.fname_var.get()}_{debug.cnt}__{suffix}.png"),
                normalized(img),
            )

            plt.hist(normalized(img).ravel(), 256, (0, 256))
            plt.savefig(
                str(util.output_dir_var.get() /
                    f"{util.fname_var.get()}_{debug.cnt}_hist_{suffix}.png"))
            plt.clf()

    img = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)  # 灰度图
    debug('grey')

    img = cv2.medianBlur(img, 3)  # 中值滤波
    debug("median")

    img = HomomorphicFiltering(img)  # 同态滤波
    debug('gauss_high')

    img = clip(img, 0.001)  # 去除高光
    debug('clip')

    img = gammaCorrection(img, 0.7)  # 伽马校正
    debug("gamma")

    return normalized(img)


if __name__ == "__main__":
    util.runAll(
        solve,
        cfg.IMAGE_PREFIX,
        cfg.OUTPUT_DIR / "exp-1",
        clean=True,
    )

    # if cfg.TMP_DIR.exists():
    #     shutil.rmtree(cfg.TMP_DIR)
    # cfg.TMP_DIR.mkdir(exist_ok=True)
    # img = cv2.imread(str(cfg.IMAGE_PREFIX / "0_L_B.png"))
    # cv2.imwrite(str(cfg.TMP_DIR / "tmp.png"), solve(img))
