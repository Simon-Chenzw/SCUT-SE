% 1.
RGB = imread('camera.bmp');
I=RGB;
%I = rgb2gray(RGB);
BW = edge(I,'canny');
[H,T,R] = hough(BW,'RhoResolution',0.5,'ThetaResolution',0.5);

subplot(121)
imshow(H,[],'InitialMagnification','fit'), axis on, axis normal
xlabel('\T'), ylabel('\R')
p = houghpeaks(H,5,'threshold',ceil(0.3*max(H(:)))); 

hold on
plot(T(p(:,2)),R(p(:,1)),'s','color','white');
lines = houghlines(BW,T,R,p,'FillGap',10,'MinLength',10); 
subplot(122), imshow(BW), hold on
for k = 1:length(lines)
	xy = [lines(k).point1; lines(k).point2];
	plot(xy(:,1),xy(:,2),'LineWidth',2,'Color','green');
end

% 2.
% (1)直方图阈值法
I=imread('car.bmp');
subplot(2,2,1);
imshow(I);
title('原图像');
I1=rgb2gray(I);
subplot(2,2,2);
imhist(I1);
title('直方图');
subplot(2,2,3);
I2=im2bw(I1,165/415);
imshow(I2);
title('分割后的图像');

% (2)Otsu算法
I=imread('car.bmp');
subplot(2,1,1);
imshow(I);
title('原图像');
subplot(2,1,2);
level=graythresh(I);
BW=im2bw(I,level);
imshow(BW);
title('分割后的图像');

% (3)分水岭分割算法
f=imread('car.bmp');
subplot(311),imshow(f);
g=im2bw(f, graythresh(f));
subplot(312),imshow(g);
gc=~g;
D=bwdist(gc);
L=watershed(-D);
w=L;
g2=g&~w;
subplot(313),imshow(g2);