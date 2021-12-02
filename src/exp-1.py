import cfg
import util

import cv2
import numpy as np


def normalized(img: np.ndarray) -> np.ndarray:
    img = (img - np.min(img)) / (np.max(img) - np.min(img))
    return (img * 255).astype(np.uint8)


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
    img_out = np.expm1(img_out_log)
    return normalized(img_out)


def solve(img: np.ndarray) -> np.ndarray:
    img = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)  # 灰度图
    img = cv2.medianBlur(img, 3)  # 中值滤波
    img = HomomorphicFiltering(img)  # 同态滤波
    return img


if __name__ == "__main__":
    # util.runAll(
    #     solve,
    #     cfg.IMAGE_PREFIX,
    #     cfg.OUTPUT_DIR / "exp-1",
    #     clean=True,
    # )

    cfg.TMP_DIR.mkdir(exist_ok=True)
    img = cv2.imread(cfg.EXAMPLE_IMAGE)
    cv2.imwrite(cfg.EXAMPLE_OUTPUT, solve(img))
