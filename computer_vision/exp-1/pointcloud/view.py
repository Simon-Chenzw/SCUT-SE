#!python3.9
import open3d as o3d

pcd = o3d.io.read_point_cloud("point.xyz")
o3d.visualization.draw_geometries([pcd])  # type: ignore
