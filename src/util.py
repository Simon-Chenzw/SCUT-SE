import shutil
from pathlib import Path
from typing import Callable, Iterator, Literal, Union

import cfg
import cv2
import numpy as np

SolveFunc = Callable[[np.ndarray], np.ndarray]


def run(
    func: SolveFunc,
    src_fname: Union[str, Path],
    dst_fname: Union[str, Path],
):
    src_img = cv2.imread(str(src_fname))
    dst_img = func(src_img)
    cv2.imwrite(str(dst_fname), dst_img)


def runAll(
    func: SolveFunc,
    src_dir: Path,
    dst_dir: Path,
    clean: bool = False,
):
    if clean and dst_dir.exists():
        shutil.rmtree(dst_dir)

    dst_dir.mkdir(parents=True, exist_ok=True)

    for name in fnameAll():  # TODO:progress bar
        print(name)
        run(func, src_dir / name, dst_dir / name)


def fname(
    num: int,
    side: Literal['LF', 'RF', 'LB', 'RB'],
) -> str:
    a, b = side[0], side[1]
    return f"{num}_{a}_{b}.png"


def fnameAll() -> Iterator[str]:
    for i in range(cfg.IMAGE_TOTAL):
        yield fname(i, 'LF')
        yield fname(i, 'RF')
        yield fname(i, 'LB')
        yield fname(i, 'RB')


if __name__ == "__main__":
    import os
    for name in fnameAll():
        print(name)
        assert os.path.isfile(cfg.IMAGE_PREFIX / name)
