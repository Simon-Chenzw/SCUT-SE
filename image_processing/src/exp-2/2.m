s=imread('1.jpg');%读入原图像
i=rgb2gray(s);
i=double(i);
j=fft2(i); %傅里叶变换
k=fftshift(j); % 直流分量移到频谱中心
l=log(abs(k)); %对数变换
m=fftshift(j); %直流分量移到频谱中心
RR=real(m); %取傅里叶变换的实部
II=imag(m); %取傅里叶变换的虚部
A=sqrt(RR.^2+II.^2); %计算频谱府幅值
A=(A-min(min(A)))/(max(max(A)))*255; % 归一化
b=circshift(s,[800 450]); %对图像矩阵 im 中的数据进行移位操作
b=rgb2gray(b);
b=double(b);
c=fft2(b); %傅里叶变换
e=fftshift(c); % 直流分量移到频谱中心
l=log(abs(e)); %对数变换
f=fftshift(c); %直流分量移到频谱中心
WW=real(f); %取傅里叶变换的实部 B
ZZ=imag(f); %取傅里叶变换的虚部
B=sqrt(WW.^2+ZZ.^2); %计算频谱府幅值
B=(B-min(min(B)))/(max(max(B)))*255; % 归一化
subplot(2,2,1);imshow(s);title('原图像')
subplot(2,2,2);imshow(uint8(b));;title('平移图像')
subplot(2,2,3);imshow(A);title('离散傅里叶频谱');
subplot(2,2,4);imshow(B);title('平移图像离散傅里叶频谱')

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

s=imread('1.jpg');%读入原图像
i=rgb2gray(s);
i=double(i);
j=fft2(i); %傅里叶变换
k=fftshift(j); % 直流分量移到频谱中心
l=log(abs(k)); %对数变换
m=fftshift(j); %直流分量移到频谱中心
RR=real(m); %取傅里叶变换的实部
II=imag(m); %取傅里叶变换的虚部
A=sqrt(RR.^2+II.^2); %计算频谱府幅值
A=(A-min(min(A)))/(max(max(A)))*255; % 归一化
b=imrotate(s, -90); %对图像矩阵 im 中的数据进行移位操作
b=rgb2gray(b);
b=double(b);
c=fft2(b); %傅里叶变换
e=fftshift(c); % 直流分量移到频谱中心
l=log(abs(e)); %对数变换
f=fftshift(c); %直流分量移到频谱中心
WW=real(f); %取傅里叶变换的实部 B
ZZ=imag(f); %取傅里叶变换的虚部
B=sqrt(WW.^2+ZZ.^2); %计算频谱府幅值
B=(B-min(min(B)))/(max(max(B)))*255; % 归一化
subplot(2,2,1);imshow(s);title('原图像')
subplot(2,2,2);imshow(uint8(b));title('旋转图像')
subplot(2,2,3);imshow(A);title('离散傅里叶频谱');
subplot(2,2,4);imshow(B);title('平移图像离散傅里叶频谱') 