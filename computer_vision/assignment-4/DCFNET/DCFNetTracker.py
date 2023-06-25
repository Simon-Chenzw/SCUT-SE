import numpy as np
import torch
from util import crop_chw, gaussian_shaped_labels,cxy_wh_2_bbox





    
#dcfnet跟踪器类
class DCFNetTracker(object):
    def __init__(self, save, net,config):
        self.min_sz = None
        self.max_sz = None
        self.target_sz = None
        self.target_pos = None
        self.patch_crop = None
        self.config =config
        self.net =net
        # self.net.load_param(args.model)
        self.net.load_param(save)
        
    #利用初始状态初始化跟踪器
    def init(self, im, target_pos, target_sz):

        self.min_sz = np.maximum(self.config.min_scale_factor * target_sz, 4)  # 最小大小长宽比中最小为4
        self.max_sz = np.minimum(im.shape[:2], self.config.max_scale_factor * target_sz)  # 最大大小长宽比最大为目标框长宽比大小的5倍
        self.target_pos = target_pos
        self.target_sz = target_sz
        self.net.eval().cuda()


        # config.padding=2，windows大小为目标框的3倍
        window_sz = target_sz * (1 + self.config.padding)
        # 根据window_sz 和目标中心点获取一个box
        bbox = cxy_wh_2_bbox(target_pos, window_sz)
        # 获取切片，通道变换为[3,125,125]
        patch = crop_chw(im, bbox, self.config.crop_sz)
        target = patch - self.config.net_average_image
        self.net.update(torch.Tensor(np.expand_dims(target, axis=0)).cuda())
        self.patch_crop = np.zeros((self.config.num_scale, patch.shape[0], patch.shape[1], patch.shape[2]), np.float32)

    def track(self, im):
        # 用不同的window size截取图片，并且后续会根据这个scale_factor来变换box的形状
        for i in range(self.config.num_scale):  # crop multi-scale search region
            window_sz = self.target_sz * (self.config.scale_factor[i] * (1 + self.config.padding))
            bbox = cxy_wh_2_bbox(self.target_pos, window_sz)
            self.patch_crop[i, :] = crop_chw(im, bbox, self.config.crop_sz)

        search = self.patch_crop - self.config.net_average_image
        # response为反应图
        response = self.net(torch.Tensor(search).cuda())
        # 找到最大反应以及其index
        peak, idx = torch.max(response.view(self.config.num_scale, -1), 1)
        peak = peak.data.cpu().numpy() * self.config.scale_penalties
        best_scale = np.argmax(peak)
        idx = idx.cpu()
        # 获取最大的索引
        r_max, c_max = np.unravel_index(idx[best_scale], self.config.net_input_size)

        # 更新target_pos的位置
        if r_max > self.config.net_input_size[0] / 2:
            r_max = r_max - self.config.net_input_size[0]
        if c_max > self.config.net_input_size[1] / 2:
            c_max = c_max - self.config.net_input_size[1]
        window_sz = self.target_sz * (self.config.scale_factor[best_scale] * (1 + self.config.padding))

        self.target_pos = self.target_pos + np.array([c_max, r_max]) * window_sz / self.config.net_input_size
        # target_sz 的大小由得分最高的mulitscale的数值来进行形变
        self.target_sz = np.minimum(np.maximum(window_sz / (1 + self.config.padding), self.min_sz), self.max_sz)

        # 模型更新
        window_sz = self.target_sz * (1 + self.config.padding)
        bbox = cxy_wh_2_bbox(self.target_pos, window_sz)
        patch = crop_chw(im, bbox, self.config.crop_sz)
        target = patch - self.config.net_average_image
        self.net.update(torch.Tensor(np.expand_dims(target, axis=0)).cuda(), lr=self.config.interp_factor)
        return self.target_pos, self.target_sz


