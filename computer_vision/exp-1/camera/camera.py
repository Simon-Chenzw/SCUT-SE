#!python3.9
import cv2
import numpy as np
import glob

CORNERS_SIZE = (6, 9)

data_path = r".\data\[012][0-9].jpg"

objp = np.array(
    [[j, i, 0] for i in range(CORNERS_SIZE[1])
     for j in range(CORNERS_SIZE[0])],
    dtype=np.float32,
)

image_size = None
success_fnames = []
objpoints = []
imgpoints = []

for fname in glob.glob(data_path):
    img = cv2.imread(fname)
    # img = cv2.resize(img, (960, 720))
    # cv2.imwrite(fname[:-4] + "_small.jpg", img)
    gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
    if image_size is None:
        image_size = gray.shape
    else:
        assert image_size == gray.shape

    retval, corners = cv2.findChessboardCorners(
        gray,
        CORNERS_SIZE,
        None,
        cv2.CALIB_CB_FAST_CHECK,
    )
    if retval:
        corners = cv2.cornerSubPix(
            gray,
            corners,
            (11, 11),
            (-1, -1),
            (cv2.TermCriteria_EPS | cv2.TermCriteria_EPS, 30, 0.001),
        )
        # cv2.drawChessboardCorners(img, CORNERS_SIZE, corners, retval)
        # cv2.imwrite(fname[:-4] + "_chess.jpg", img)

        success_fnames.append(fname)
        objpoints.append(objp)
        imgpoints.append(corners)

(
    retval,
    cameraMatrix,
    distCoeffs,
    rvecs,
    tvecs,
) = cv2.calibrateCamera(objpoints, imgpoints, image_size, None, None)
print(f"{retval=}")
print(f"{cameraMatrix=}")
print(f"{distCoeffs=}")

total_error = 0.0
for i, fname in enumerate(success_fnames):
    imgpoints2, jacobian = cv2.projectPoints(
        objpoints[i],
        rvecs[i],
        tvecs[i],
        cameraMatrix,
        distCoeffs,
    )
    error = cv2.norm(imgpoints[i], imgpoints2, cv2.NORM_L2) / len(imgpoints2)
    print(f"{fname=} {error=}")
    total_error += error

    # img = cv2.imread(fname)
    # img = cv2.resize(img, (960, 720))
    # img_undistort = cv2.undistort(img, cameraMatrix, distCoeffs)
    # cv2.imwrite(fname[:-4] + "_undistort.jpg", img_undistort)
print("total error: ", total_error / len(objpoints))

# retval=2.1111453346084796
# cameraMatrix=array([[5.87102498e+03, 0.00000000e+00, 4.10177695e+03],
#        [0.00000000e+00, 5.90495848e+03, 3.11299521e+03],
#        [0.00000000e+00, 0.00000000e+00, 1.00000000e+00]])
# distCoeffs=array([[ 0.01472018,  0.0222051 ,  0.0004129 , -0.00171301, -0.05730478]])
# fname='.\\data\\01.jpg' error=0.2019165737826066
# fname='.\\data\\02.jpg' error=0.31272823096514807
# fname='.\\data\\03.jpg' error=0.27782529015090024
# fname='.\\data\\04.jpg' error=0.31966092829801696
# fname='.\\data\\05.jpg' error=0.25487041715413183
# fname='.\\data\\06.jpg' error=0.2723983300427374
# fname='.\\data\\07.jpg' error=0.252928449924089
# fname='.\\data\\08.jpg' error=0.24889960845363948
# fname='.\\data\\09.jpg' error=0.212614150359957
# fname='.\\data\\10.jpg' error=0.2884010818300946
# fname='.\\data\\11.jpg' error=0.2847657532583736
# fname='.\\data\\12.jpg' error=0.3065100318673028
# fname='.\\data\\13.jpg' error=0.2970454019447103
# fname='.\\data\\14.jpg' error=0.27222893102452045
# fname='.\\data\\15.jpg' error=0.27802302619749025
# fname='.\\data\\16.jpg' error=0.2815481604347288
# fname='.\\data\\17.jpg' error=0.33594548455070344
# fname='.\\data\\18.jpg' error=0.3587383827190461
# fname='.\\data\\19.jpg' error=0.3041542108380157
# fname='.\\data\\20.jpg' error=0.3336116776047058
# total error:  0.2847407060700459