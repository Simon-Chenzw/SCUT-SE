import cfg
import util

import cv2
import numpy as np


def solve(img: np.ndarray) -> np.ndarray:
    img = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
    return cv2.medianBlur(img, 3)


if __name__ == "__main__":
    util.runAll(
        solve,
        cfg.IMAGE_PREFIX,
        cfg.OUTPUT_DIR / "exp-1",
        clean=True,
    )

    # solve(util.fname(0, 'LB'))
