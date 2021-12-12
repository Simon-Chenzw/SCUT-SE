import math
import shutil
from itertools import product
from queue import SimpleQueue
from typing import List, Tuple

import cv2
import numpy as np
import scipy.stats

import cfg
import exp1
import util


# 众数
def mode(arr: np.ndarray) -> int:
    ret = scipy.stats.mode(arr, axis=None)
    return ret.mode[0]


WHITE = 255
BLACK = 0


# 输入一个二值化的图像
def selectHand(
    img: np.ndarray,
    LIMIT_LR_UP_MOVE: float = 0.05,
    LIMIT_LR_DN_MOVE: float = 0.05,
):
    FRONT = BLACK
    BACK = WHITE
    LIMIT_rate = 0.05

    n, m = img.shape[0], img.shape[1]
    LIMIT_SIZE = img.size * LIMIT_rate
    LIMIT_X_LOW = int(n * LIMIT_LR_UP_MOVE)
    LIMIT_X_HIGH = n - int(n * LIMIT_LR_DN_MOVE)

    vis: np.ndarray = np.full_like(img, False, np.bool_)  # type: ignore

    # x靠边时 不能左右移动
    def fill(sx: int, sy: int) -> List[Tuple[int, int]]:
        lst: List[Tuple[int, int]] = []
        q: 'SimpleQueue[Tuple[int, int]]' = SimpleQueue()
        f = [[0, 1], [1, 0], [0, -1], [-1, 0]]
        lim_f = [[1, 0], [-1, 0]]

        vis[sx, sy] = True
        q.put((sx, sy))

        while not q.empty():
            x, y = q.get()
            lst.append((x, y))

            for dx, dy in (f if LIMIT_X_LOW < x < LIMIT_X_HIGH else lim_f):
                nx, ny = x + dx, y + dy
                if not (0 <= nx < n and 0 <= ny < m):
                    continue
                if not vis[nx, ny] and img[nx, ny] == FRONT:
                    vis[nx, ny] = True
                    q.put((nx, ny))

        return lst

    def toCenter(l: List[Tuple[int, int]]) -> float:
        if not l:
            return 1e100
        center = n // 2, m // 2
        lst = list(map(
            lambda tp: math.dist(tp, center),
            l,
        ))
        return sum(lst) / len(lst)

    # select hand
    hand: List[Tuple[int, int]] = []
    handVal = 1e100
    for i, j in product(range(n), range(m)):
        if not vis[i, j] and img[i, j] == FRONT:
            cur = fill(i, j)
            val = toCenter(cur)
            if len(cur) >= LIMIT_SIZE and handVal > val:
                hand = cur
                handVal = val

    img.fill(BACK)
    for i, j in hand:
        img[i, j] = FRONT


# 输入一个二值化的图像
# 填充不与边界联通的黑块
def fillHole(img: np.ndarray):
    FRONT = BLACK
    BACK = WHITE

    n, m = img.shape[0], img.shape[1]
    vis: np.ndarray = np.full_like(img, False, np.bool_)  # type: ignore

    def fill(sx: int, sy: int):
        bo = True
        lst: List[Tuple[int, int]] = []
        q: 'SimpleQueue[Tuple[int, int]]' = SimpleQueue()
        f = [[0, 1], [1, 0], [0, -1], [-1, 0]]

        vis[sx, sy] = True
        q.put((sx, sy))

        while not q.empty():
            x, y = q.get()
            lst.append((x, y))
            for dx, dy in f:
                nx, ny = x + dx, y + dy
                if not (0 <= nx < n and 0 <= ny < m):
                    bo = False
                    continue
                if not vis[nx, ny] and img[nx, ny] == BACK:
                    vis[nx, ny] = True
                    q.put((nx, ny))

        if bo:
            for i, j in lst:
                img[i, j] = FRONT

    for i, j in product(range(n), range(m)):
        if not vis[i, j] and img[i, j] == BACK:
            fill(i, j)


def cannySolve(img: np.ndarray) -> np.ndarray:
    def debug(suffix: str):
        if cfg.DEBUG and __name__ == "__main__":
            if hasattr(debug, 'cnt'):
                debug.cnt += 1
            else:
                debug.cnt = 1
            cv2.imwrite(
                str(util.output_dir_var.get() /
                    f"{util.fname_var.get()}_{debug.cnt}__{suffix}.png"),
                img,
            )

    if cfg.DEBUG:
        cfg.DEBUG = False
        img = exp1.solve(img)
        cfg.DEBUG = True
    else:
        img = exp1.solve(img)
    debug("origin")

    img = cv2.GaussianBlur(img, (3, 3), 5)
    debug("gauss")

    img = cv2.Canny(img, 15, 50)
    debug("canny")

    img = cv2.morphologyEx(
        img,
        cv2.MORPH_CLOSE,
        cv2.getStructuringElement(cv2.MORPH_RECT, (31, 31)),
    )
    debug("close")

    selectHand(img, 0.20)
    debug("select")

    return img


def threshSolve(img: np.ndarray) -> np.ndarray:
    def debug(suffix: str):
        if cfg.DEBUG and __name__ == "__main__":
            if hasattr(debug, 'cnt'):
                debug.cnt += 1
            else:
                debug.cnt = 1
            cv2.imwrite(
                str(util.output_dir_var.get() /
                    f"{util.fname_var.get()}_{debug.cnt}__{suffix}.png"),
                img,
            )

    cfg.DEBUG = False
    img = exp1.solve(img)
    cfg.DEBUG = True
    debug("origin")

    img = cv2.GaussianBlur(img, (3, 3), 5)
    debug("gauss")

    th, img = cv2.threshold(img, mode(img) - 1, 255, cv2.THRESH_BINARY_INV)
    debug("thresh")

    selectHand(img)
    debug("select")

    fillHole(img)
    debug("fill")

    return img


def solve(img: np.ndarray) -> np.ndarray:
    img = cannySolve(img)
    # img = threshSolve(img)
    if 1 - img.mean() / 255 > 0.4:
        print(f"warning {util.fname_var.get()}")
    return img


def benchmark():
    if cfg.TMP_DIR.exists():
        shutil.rmtree(cfg.TMP_DIR)
    cfg.TMP_DIR.mkdir(exist_ok=True)

    SELECT = WHITE

    def iou(a: np.ndarray, b: np.ndarray) -> float:
        union: np.ndarray = ((a == SELECT) | (b == SELECT))  # type:ignore 并集
        inter: np.ndarray = ((a == SELECT) & (b == SELECT))  # type:ignore 交集
        return inter.sum() / union.sum()

    total_benchmark = 9
    tot_score = 0
    for i in range(total_benchmark):
        src = cv2.imread(str(cfg.EXP_2_BENCHMARK / f"{i}.png"))
        tgt = cv2.imread(str(cfg.EXP_2_BENCHMARK / f"{i}_alp.png"))

        if cfg.DEBUG:
            cfg.DEBUG = False
            ans = 255 - solve(src)  # inv
            cfg.DEBUG = True
        else:
            ans = 255 - solve(src)  # inv
        cv2.imwrite(str(cfg.TMP_DIR / f"{i}_ans.png"), ans)

        tgt = cv2.cvtColor(tgt, cv2.COLOR_BGR2GRAY)
        _, tgt = cv2.threshold(tgt, 128, 255, cv2.THRESH_BINARY)

        score = iou(ans, tgt)
        tot_score += score
        print(f"{i}: IOU = {score:.2%}")
    print(f"tot = {tot_score/total_benchmark:.2%}")


if __name__ == '__main__':
    # benchmark()

    util.runAll(
        solve,
        cfg.IMAGE_PREFIX,
        cfg.OUTPUT_DIR / "exp-2",
        clean=True,
    )

    # if cfg.TMP_DIR.exists():
    #     shutil.rmtree(cfg.TMP_DIR)
    # cfg.TMP_DIR.mkdir(exist_ok=True)
    # img = cv2.imread(str(cfg.EXP_2_BENCHMARK / "5.png"))
    # cv2.imwrite(str(cfg.TMP_DIR / "tmp.png"), solve(img))
