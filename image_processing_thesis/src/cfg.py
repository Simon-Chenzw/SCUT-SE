from pathlib import Path

DEBUG = True

CFG_PATH = Path(__file__)
SRC_DIR = CFG_PATH.parent
PROJECT_DIR = SRC_DIR.parent

IMAGE_TOTAL = 47  # 0 ~ 46
IMAGE_PREFIX = PROJECT_DIR / "data" / "images"

EXP_2_BENCHMARK = PROJECT_DIR / "data" / "exp-2-benchmark"

OUTPUT_DIR = PROJECT_DIR / "dest"

TMP_DIR = PROJECT_DIR / "tmp"

EXAMPLE_IMAGE = str(IMAGE_PREFIX / "0_L_B.png")
EXAMPLE_OUTPUT = str(TMP_DIR / "0_L_B.png")
