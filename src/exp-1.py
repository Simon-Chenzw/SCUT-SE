import cv2
import numpy as np
from matplotlib import pyplot as plt
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
        Hhigh = 1 - Hlow
        return Hhigh

    img_log = np.log1p(img.astype(np.float_) / 255)
    img_fft = np.fft.fft2(img_log, (M, N))
    mask = np.fft.ifftshift(GaussianHighPass())
    result = img_fft * mask
    img_out_log = np.real(np.fft.ifft2(result))[0:rows, 0:cols]
    img_out: np.ndarray = np.expm1(img_out_log)

    # remove highlight
    # 考虑到图片中存在无用高光
    # 直接采取比例截取的方式
    highlight_remove_rate = 0.0005
    highlight_remove_pos = int(rows * cols * highlight_remove_rate)
    highlight_remove_val: float = np.partition(
        img_out.flat, -(highlight_remove_pos + 1))[-(highlight_remove_pos + 1)]

    img_clip = np.clip(img_out, img_out.min(), highlight_remove_val)
    remove_rate = ((img_clip.max() - img_out.min()) /
                   (img_out.max() - img_out.min()))

    print(f"{util.fname_var.get()} {highlight_remove_pos=} {remove_rate=:%}")

    return normalized(img_clip)


def solve(img: np.ndarray) -> np.ndarray:
    img = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)  # 灰度图
    img = cv2.medianBlur(img, 3)  # 中值滤波
    img = HomomorphicFiltering(img)  # 同态滤波

    if cfg.DEBUG:
        plt.hist(img.ravel(), 256, (0, 256))
        plt.savefig(
            str(util.output_dir_var.get() /
                f"{util.fname_var.get('tmp')}_hist.png"))
        plt.clf()

        cv2.imwrite(
            str(util.output_dir_var.get() /
                f"{util.fname_var.get('tmp')}_max_200.png"),
            (img > 200).astype(np.uint8) * 255,
        )

        cv2.imwrite(
            str(util.output_dir_var.get() /
                f"{util.fname_var.get('tmp')}_max_255.png"),
            (img == 255).astype(np.uint8) * 255,
        )

    return img


if __name__ == "__main__":
    util.runAll(
        solve,
        cfg.IMAGE_PREFIX,
        cfg.OUTPUT_DIR / "exp-1",
        clean=True,
    )

    # cfg.TMP_DIR.mkdir(exist_ok=True)
    # img = cv2.imread(str(cfg.IMAGE_PREFIX / "17_L_B.png"))
    # cv2.imwrite(str(cfg.TMP_DIR / "tmp.png"), solve(img))
