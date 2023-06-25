#!python3.9
import cv2
import numpy as np
import open3d as o3d

f1 = "left.jpg"
f2 = "right.jpg"
DIS_RATE = 0.8

# cameraMatrix = np.array([
K = np.array([
    [5.87102498e+03, 0.00000000e+00, 4.10177695e+03],
    [0.00000000e+00, 5.90495848e+03, 3.11299521e+03],
    [0.00000000e+00, 0.00000000e+00, 1.00000000e+00],
])

# distCoeffs = np.array([[
DIST = np.array([[
    0.01472018,
    0.0222051,
    0.0004129,
    -0.00171301,
    -0.05730478,
]])


def match(img1, img2):
    f2d = cv2.ORB_create(nfeatures=100000)
    kp1, des1 = f2d.detectAndCompute(img1, None)
    kp2, des2 = f2d.detectAndCompute(img2, None)
    print("kp1:", len(kp1))
    print("kp2:", len(kp2))

    FLANN_INDEX_LSH = 6
    index_params = dict(
        algorithm=FLANN_INDEX_LSH,
        table_number=6,  # 12
        key_size=12,  # 20
        multi_probe_level=1,
    )  #2
    search_params = dict(checks=50)
    matcher = cv2.FlannBasedMatcher(index_params, search_params)
    all_matches = matcher.knnMatch(des1, des2, 2)
    matches = np.array([
        m[0] for m in all_matches if m[0].distance < DIS_RATE * m[1].distance
    ])
    print("matches:", len(matches))

    p1 = np.array([kp1[m.queryIdx].pt for m in matches])
    p2 = np.array([kp2[m.trainIdx].pt for m in matches])

    F, mask = cv2.findFundamentalMat(p1, p2)  # type: ignore
    p1 = p1[mask.ravel() == 1]
    p2 = p2[mask.ravel() == 1]
    matches = matches[mask.ravel() == 1]

    E, mask = cv2.findEssentialMat(p1, p2, K, cv2.RANSAC, 0.999, 1.0)
    p1 = p1[mask.ravel() == 1]
    p2 = p2[mask.ravel() == 1]
    matches = matches[mask.ravel() == 1]

    match_img = cv2.drawMatches(img1, kp1, img2, kp2, matches, None)
    cv2.imwrite("matches.jpg", match_img, [cv2.IMWRITE_JPEG_QUALITY, 85])

    R1, R2, T = cv2.decomposeEssentialMat(E)
    print("R1:\n", R1)
    print("R2:\n", R2)
    print("T:\n", T)

    def get_point(R):
        M1 = np.concatenate((np.eye(3, 3), np.zeros((3, 1))), axis=1)
        M2 = np.concatenate((R, T), axis=1)

        p1u = cv2.undistortPoints(p1, K, DIST, None, None)  # type: ignore
        p2u = cv2.undistortPoints(p2, K, DIST, None, None)  # type: ignore

        points_4d_hom = cv2.triangulatePoints(M1, M2, p1u, p2u)
        points_4d = points_4d_hom / np.tile(points_4d_hom[-1, :], (4, 1))
        points_3d = points_4d[:3, :].T
        points_3d *= np.array([1, 1, -1])  # mirror

        return points_3d

    return get_point(R1), get_point(R2)


def save_point(fname: str, xyz):
    with open(fname, 'w') as fp:
        for p in xyz:
            print(p[0], p[1], p[2], file=fp)


def show_point_cloud(xyz):
    pcd = o3d.geometry.PointCloud()
    pcd.points = o3d.utility.Vector3dVector(xyz)
    o3d.visualization.draw_geometries([pcd])  # type: ignore


p1, p2 = match(cv2.imread(f1), cv2.imread(f2))
save_point("point.xyz", p1)
# save_point("point.xyz", p2)

# print("build point set 1 (", p1.shape[0], "points )")
# show_point_cloud(p1)
# print("build point set 2 (", p2.shape[0], "points )")
# show_point_cloud(p2)
