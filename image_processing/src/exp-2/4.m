i1=imread('statBlur.png');
i2=imread('s1.bmp');
i3=imread('picassoBlurImage.png');
i4=imread('nvblurImage.png');
o1=fftshift(fft2(rgb2gray(i1)));o2=fftshift(fft2(rgb2gray(i2)));
o3=fftshift(fft2(rgb2gray(i3)));o4=fftshift(fft2(rgb2gray(i4)));
subplot(421),imshow(i1),subplot(422),imshow(o1);
subplot(423),imshow(i2),subplot(424),imshow(o2);
subplot(425),imshow(i3),subplot(426),imshow(o3);
subplot(427),imshow(i4),subplot(428),imshow(o4);

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

im=imread('statBlur.png');[m,n,h]=size(im);
f11=ones(190,162,3);f22=ones(130,130,3);f33=ones(100,100,3);f44=ones(70,70,3);
for i=1:190
for j=1:162
for k=1:3
f11(i,j,k)=im(i,j,k);
end
end
end
for i=1:130
for j=501:630
for k=1:3
f22(i,j-500,k)=im(i,j,k);
end
end
end
for i=721:870
for j=11:170
for k=1:3
f33(i-720,j-10,k)=im(i,j,k);
end
end
end
for i=761:830
for j=561:630
for k=1:3
f44(i-760,j-560,k)=im(i,j,k);
end
end
end
figure,subplot(221),hist(f11,100),subplot(222),hist(f22,100),subplot(223),hist(f33,100),subplot(224),hist(f44,100);

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

%对输入的图像进行大气湍流处理
img=imread('statBlur.png'); % 输入的待处理图像
k=0.00011;% 大气湍流模型常数
subplot(121);imshow(img),title('原始图像');

i=fft2(double(img));
G=fftshift(i);[m, n, h] = size(i);
H=zeros(m,n);
for i=1:m
for j=1:n
if sqrt((i-m/2)^2+(j-n/2)^2)<100
H(i,j)=exp(-k*(i^2+j^2)^(5/6));
end
end
end
for i=1:3
out(:,:,i) = G(:,:,i).*H;
end
out = real(ifft2(ifftshift(out)));
subplot(122),imshow(out),title('大气湍流复原图像');

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

img=imread('nvblurImage.png');
subplot(131);imshow(img),title('原始图像');
PSF = fspecial('motion',9,0);
fr1 = double(deconvwnr(img,PSF,0.3));
[m,n,h]=size(fr1);
for i=1:m
for j=1:n
for k=1:3
fr1(i,j,k)=(fr1(i,j,k))^1.06;
end
end
end
subplot(132);imshow(uint8(fr1)),title('估计PSF运动复原');
k=0.00105;
i=fft2(double(img));
G=fftshift(i);[m, n, h] = size(i);
H=zeros(m,n);
for i=1:m
for j=1:n
if sqrt((i-m/2)^2+(j-n/2)^2)<100
H(i,j)=exp(-k*(i^2+j^2)^(5/6));
end
end
end
for i=1:3
out(:,:,i) = G(:,:,i).*H;
end
out = real(ifft2(ifftshift(out)));
subplot(133);imshow(out),title('大气湍流复原');

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

im = imread('s1.bmp'); 
[m,n,h]=size(im); 
%f1=zeros(m,n);f2=zeros(m,n);f3=zeros(m,n);... 
f11=ones(40,30,3);f22=ones(20,16,3);f33=ones(46,31,3);f44=ones(30,27,3); 
for i=61:100 
for j=21:50 
for k=1:3 
f11(i-60,j-20,k)=im(i,j,k); 
end 
end 
end 
for i=71:90 
for j=121:136 
for k=1:3 
f22(i-70,j-120,k)=im(i,j,k); 
end 
end 
end 
for i=211:256 
for j=25:55 
for k=1:3 
f33(i-210,j-24,k)=im(i,j,k); 
end 
end 
end 
for i=201:230 
for j=145:171 
for k=1:3 
f44(i-200,j-144,k)=im(i,j,k); 
end
end 
end 
figure,subplot(221),hist(f11,100),subplot(222),hist(f22,100),subplot(223),... 
hist(f33,100),subplot(224),hist(f44,100); 
w1=fspecial('gaussian'); 
im2=imfilter(im,w1,'conv' ,'replicate'); 
PSF = fspecial('motion',1.5,40); 
fr1 = deconvwnr(im,PSF);fr2 = deconvwnr(im,PSF,0.3); 
figure,subplot(121),imshow(fr1),title('直接估计维纳复原'),subplot(122),... 
imshow(fr2),title('高斯去噪后复原'); 

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

image=imread('picassoBlurImage.png');k=0.000185; 
i=fft2(double(image)); 
G=fftshift(i); 
[m, n, h] = size(i); 
H=zeros(m,n); 
for i=1:m 
for j=1:n
if sqrt((i-m/2)^2+(j-n/2)^2)<40 
H(i,j)=exp(-k*(i^2+j^2)^(5/6)); 
end 
end 
end 
for i=1:3 
out(:,:,i) = G(:,:,i).*H; 
end 
out = real(ifft2(ifftshift(out))); 
figure,subplot(121),imshow(image),title('原始图像'),... 
subplot(122),imshow(out,[]),title('频域半径为40复原图像'); 
PSF = fspecial('motion',1.5,40); 
fr1 = deconvwnr(image,PSF);fr2 = deconvwnr(image,PSF,0.3); 
figure,subplot(121),imshow(fr1),title('直接估计维纳复原'),subplot(122),... 
imshow(fr2),title('高斯去噪后复原'); 