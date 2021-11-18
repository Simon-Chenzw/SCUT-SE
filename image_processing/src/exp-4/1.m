% 1.
I=imread('Plane2.jpg');
level = graythresh(I);
bw = im2bw(I,level);
SE = strel('square',3);
BW1 = imdilate(bw,SE);
SE1 = strel('arbitrary',eye(5));
BW2 = imerode(bw,SE1);
BW3 = bwmorph(bw, 'open');
BW4 = bwmorph(bw, 'close');
subplot(231),imshow(I),title('原图');
subplot(232),imshow(bw),title('二值化图像');
subplot(233),imshow(BW1),title('膨胀');
subplot(234),imshow(BW2),title('腐蚀');
subplot(235),imshow(BW3),title('开运算');
subplot(236),imshow(BW4),title('闭运算');

% 2.
I=imread('noisy.jpg'); %注意图片的路径要设置正确
subplot(231),imshow(I),title('噪声图像');

SE=strel('square',3);
BW=imerode(I,SE);
subplot(232),imshow(BW),title('腐蚀后的图像');

BW1=imopen(I,SE);
subplot(233),imshow(BW1),title('使用square(3)开操作后的图像');

BW2=imclose(I,SE);
subplot(234),imshow(BW2),title('使用square(3)闭操作后的图像');

BW3=imclose(BW1,SE);
subplot(235),imshow(BW3),title('使用square(3)先开后闭操作后的图像');

BW4=imopen(BW2,SE);
subplot(236),imshow(BW4),title('使用square(3)先闭后开操作后的图像');

