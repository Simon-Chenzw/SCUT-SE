% 1.
rgb_image=imread('flower.jpg');
fR=rgb_image(:,:,1);
fG=rgb_image(:,:,2);
fB=rgb_image(:,:,3);
figure,
subplot(231),imshow(fR)
subplot(232),imshow(fG)
subplot(233),imshow(fB)

yiq_image=rgb2ntsc(rgb_image); 
fY=yiq_image(:,:,1);
fI=yiq_image(:,:,2);
fQ=yiq_image(:,:,3);
subplot(234),imshow(fY)
subplot(235),imshow(fI)
subplot(236),imshow(fQ)

% 2.
rgb_image=imread('flower.jpg');

fR=rgb_image(:,:,1);
subplot(421),imhist(fR),title('R分量');
fR=histeq(fR,256);
subplot(422),imhist(fR),title('均衡化R分量');

fG=rgb_image(:,:,2);
subplot(423),imhist(fR),title('G分量');
fG=histeq(fG,256);
subplot(424),imhist(fG),title('均衡化G分量');

fB=rgb_image(:,:,3);
subplot(425),imhist(fR),title('B分量');
fB=histeq(fB,256);
subplot(426),imhist(fB),title('均衡化B分量');

RGB_image=cat(3,fR,fG,fB);
subplot(427),imshow(RGB_image);

% 3.
f1=imread('v1_red.jpg');
f2=imread('v1_green.jpg'); 
f3=imread('v1_blue.jpg');
ture_color=cat(3,f1,f2,f3);
figure,imshow(ture_color)

% 4.
f=imread('lenna_gray.jpg');
cut_1=imadjust(f,[0.0925 0.5],[0.0925 0.5]);
cut_2=imadjust(f,[0.5 1],[0.5 1]);
subplot(121),imshow(cut_1),colormap(hot)
subplot(122),imshow(cut_2),colormap(cool)