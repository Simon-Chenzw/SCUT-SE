import os

import torch.utils.data as data
from os.path import join
import cv2
import json
import numpy as np
from util import cxy_wh_2_bbox, crop_hwc



#个人数据集
class OTB(data.Dataset):
    def __init__(self, root_path = "", range=10, train=True):
        self.domain2nseq = json.load(open(os.path.join(root_path,"OTB100.json"), 'r'))
        self.domain_list = list(self.domain2nseq.keys())
        self.root_path = root_path
        self.range = range
        self.train = train
        self.mean = np.expand_dims(np.expand_dims(np.array([109, 120, 119]), axis=1), axis=1).astype(np.float32)


    def __getitem__(self, item):
        # 随机抽取名字
        domain_name = np.random.choice(self.domain_list, size=1)[0]
        # 随机抽取两个idx
        target_id, search_id = self.getnewtwoframes(domain_name)
        
        # 获取frame_name、gt和img——name
        frame_name = self.domain2nseq[domain_name]['name']
        imgs_name = self.domain2nseq[domain_name]['image_files']
        imgs_gt = self.domain2nseq[domain_name]['gt_rect']

        target_gt = [imgs_gt[target_id][0], imgs_gt[target_id][1],imgs_gt[target_id][2], imgs_gt[target_id][3]]
        search_gt = [imgs_gt[search_id][0], imgs_gt[search_id][1], imgs_gt[search_id][2], imgs_gt[search_id][3]]

        #加载target和search图像
        target = cv2.imread(os.path.join(self.root_path, "OTB100", frame_name, "img", imgs_name[target_id]))
        search = cv2.imread(os.path.join(self.root_path, "OTB100", frame_name, "img", imgs_name[search_id]))

        #利用gt裁剪target和search图像
        target = self.crop_image(target,target_gt)
        search = self.crop_image(search,search_gt)


        target = np.transpose(target, (2, 0, 1)).astype(np.float32) - self.mean
        search = np.transpose(search, (2, 0, 1)).astype(np.float32) - self.mean

        return target, search
    def crop_image(self,image ,bbox):
        target_pos = [bbox[0] + (bbox[2])/2-1, bbox[1] + (bbox[3])/2-1]
        target_sz = np.array([bbox[2] , bbox[3]])
        window_sz = target_sz * 3
        crop_bbox = cxy_wh_2_bbox(target_pos, window_sz)
        patch = crop_hwc(image, crop_bbox, 125)
        return patch
    def getnewtwoframes(self, domain_name):
        # 获得帧列表
        num_frames = self.domain2nseq[domain_name]['image_files']
        # 随机抽取两帧并排序,两帧之间的间隔不大于100帧
        z_frame_nos = np.random.choice(range(0, len(num_frames) - 2), size=1, replace=False)
        x_frame_nos = np.random.choice(range(z_frame_nos[0], min(len(num_frames)-1, z_frame_nos[0] + self.range)), size=1,
                                 replace=False)
        return z_frame_nos[0], x_frame_nos[0]
    def __len__(self):
        if self.train:
            return 64000
        else:
            return 1280
