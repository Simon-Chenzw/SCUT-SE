f=imread('room.jpg');
f=rgb2gray(f);
F=fft2(f); %对图像进行傅立叶变换
%对变换后图像进行队数变化，并对其坐标平移，使其中心化
S=fftshift(log(1+abs(F)));
S=gscale(S); %将频谱图像标度在 0-256 的范围内，需要加入 gscale.m 文件
subplot(3,3,1);imshow(S),title('频谱图像'); %显示频谱图像
h=fspecial('sobel'); %产生空间‘sobel’模版
freqz2(h) %查看相应频域滤波器的图像
PQ=paddedsize(size(f)); %产生滤波时所需大小的矩阵，需要加入 paddedsize.m 文件
H=freqz2(h,PQ(1),PQ(2)); %产生频域中的‘sobel’滤波器
H1=ifftshift(H); %重排数据序列，使得原点位于频率矩阵的左上角
subplot(3,3,2);imshow(abs(H),[]),title('显示滤波器'); %以图形形式显示滤波器
subplot(3,3,3);imshow(abs(H1),[]),title('重排数据序列');
gs=imfilter(double(f),h); %用模版 h 进行空域滤波
gf=dftfilt(f,H1); %用滤波器对图像进行频域滤波，需要加入 dftfilt.m 文件
subplot(3,3,4);imshow(gs,[]),title('空域滤波');
subplot(3,3,5);imshow(gf,[]),title('频域滤波');
subplot(3,3,6);imshow(abs(gs),[]),title('空域滤波-abs');
subplot(3,3,7);imshow(abs(gf),[]),title('频域滤波-abs');
f=imread('number.jpg'); %读取图片
f=rgb2gray(f);
PQ=paddedsize(size(f)); %产生滤波时所需大小的矩阵
D0=0.05*PQ(1); %设定高斯高通滤波器的阈值
H=hpfilter2('gaussian',PQ(1),PQ(2),D0); %产生高斯高通滤波器，需要加入 hpfilter2.m 和 lpfilter.m
g=dftfilt(f,H); %对图像进行滤波
subplot(3,3,8);imshow(f),title('原图像') %显示原图像
subplot(3,3,9);imshow(g,[]),title('滤波后图像') %显示滤波后图像
