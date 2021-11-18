% 1. 8*8
I=imread('lenna_color.jpg');
K=rgb2gray(I);
I=im2double(K);
imshow(I);
T=dctmtx(8);
B=blkproc(I,[8 8],'P1*x*P2',T,T');
mask=[1 1 1 1 0 0 0 0 
 1 1 1 0 0 0 0 0
 1 1 0 0 0 0 0 0 
 1 0 0 0 0 0 0 0
 0 0 0 0 0 0 0 0 
 0 0 0 0 0 0 0 0
 0 0 0 0 0 0 0 0 
 0 0 0 0 0 0 0 0 ];
B2=blkproc(B,[8 8],'P1.*x',mask);
I2=blkproc(B2,[8 8],'P1*x*P2',T',T);
I=imread('lenna_color.jpg');
subplot(2,2,1);
imshow(I);
title('原始图像');
subplot(2,2,2);
imshow(K);
title('灰度图');
subplot(2,2,3);
imshow(B2);
title('压缩图');
subplot(2,2,4);
imshow(I2);
title('复原图');

% 16*16
I=imread('lenna_color.jpg');
K=rgb2gray(I);
I=im2double(K);
imshow(I);
T=dctmtx(16);
B=blkproc(I,[16 16],'P1*x*P2',T,T');
mask=[1 1 1 1 1 1 1 1 0 0 0 0 0 0 0 0
1 1 1 1 1 1 1 0 0 0 0 0 0 0 0 0
1 1 1 1 1 1 0 0 0 0 0 0 0 0 0 0
1 1 1 1 1 0 0 0 0 0 0 0 0 0 0 0
1 1 1 1 0 0 0 0 0 0 0 0 0 0 0 0
1 1 1 0 0 0 0 0 0 0 0 0 0 0 0 0
1 1 0 0 0 0 0 0 0 0 0 0 0 0 0 0
1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 ];
B2=blkproc(B,[16 16],'P1.*x',mask);
I2=blkproc(B2,[16 16],'P1*x*P2',T',T);
I=imread('lenna_color.jpg');
subplot(2,2,1);
imshow(I);
title('原始图像');
subplot(2,2,2);
imshow(K);
title('灰度图');
subplot(2,2,3);
imshow(B2);
title('压缩图');
subplot(2,2,4);
imshow(I2);
title('复原图');

