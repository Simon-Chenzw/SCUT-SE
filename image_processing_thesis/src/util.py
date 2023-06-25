import contextlib
import contextvars
import os
import shutil
from pathlib import Path
from typing import Callable, Iterator, List, Literal, TypeVar, Union

import cv2
import numpy as np
from rich.progress import Progress

import cfg

SolveFunc = Callable[[np.ndarray], np.ndarray]

fname_var = contextvars.ContextVar('fname')  # without extension
fname_var.set('tmp')
output_dir_var = contextvars.ContextVar('output_dir')  # without extension
output_dir_var.set(cfg.TMP_DIR)

T = TypeVar('T')


@contextlib.contextmanager
def ctx_set(ctx: contextvars.ContextVar, var: T) -> Iterator[T]:
    token = ctx.set(var)
    try:
        yield var
    finally:
        ctx.reset(token)


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

    with ctx_set(output_dir_var, dst_dir):
        with Progress() as progress:
            names = fnameAll()
            task = progress.add_task("Solving...", total=len(names))

            for name in names:
                progress.update(task, description=f"Solving...   {name}")

                with ctx_set(fname_var, os.path.splitext(name)[0]):
                    run(func, src_dir / name, dst_dir / name)

                progress.update(task, advance=1)


def fname(
    num: int,
    side: Literal['LF', 'RF', 'LB', 'RB'],
) -> str:
    a, b = side[0], side[1]
    return f"{num}_{a}_{b}.png"


def fnameAll() -> List[str]:
    return [
        fname(i, s) for i in range(cfg.IMAGE_TOTAL)  # type: ignore
        for s in ['LB', 'LF', 'RB', 'RF']
    ]


if __name__ == "__main__":
    import os
    for name in fnameAll():
        print(name)
        assert os.path.isfile(cfg.IMAGE_PREFIX / name)
