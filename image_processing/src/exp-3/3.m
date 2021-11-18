% 1.
% (1)
RGB=imread('autumn.tif');
R=RGB(:,:,1);
G=RGB(:,:,2);
B=RGB(:,:,3);
hsv=rgb2hsv(RGB);
subplot(231),imshow(RGB),title('原图')
subplot(234),imshow(R),title('R分量')
subplot(235),imshow(G),title('G分量')
subplot(236),imshow(B),title('B分量')
subplot(232),imshow(hsv),title('hsv图像')

% (2)
RGB=imread('autumn.tif');
hsv=rgb2hsv(RGB);
R=RGB(:,:,1);subplot(231),imhist(R),title('原始 R 分量直方图');
G=RGB(:,:,2);subplot(232),imhist(G),title('原始 G 分量直方图');
B=RGB(:,:,3);subplot(233),imhist(B),title('原始 B 分量直方图');
R1=histeq(R);subplot(234),imhist(R1),title('均衡化 R 分量直方图');
G1=histeq(G);subplot(235),imhist(G1),title('均衡化 G 分量直方图');
B1=histeq(B);subplot(236),imhist(B1),title('均衡化 B 分量直方图');
RGB1=cat(3,R1,G1,B1);
hsv1=rgb2hsv(RGB1);
figure
subplot(221),imshow(RGB),title('原始图像');
subplot(222),imshow(hsv),title('原始 HSV 图像');
subplot(223),imshow(RGB1),title('均衡化后图像');
subplot(224),imshow(hsv1),title('均衡化后 hsv 图像')

% (3)
RGB=imread('autumn.tif');
[hsi,H,S,I]=rgb2hsi(RGB);
subplot(341),imshow(RGB),title('原始图像');
subplot(342),imshow(H),title('H 分量');
subplot(343),imshow(S),title('s 分量');
subplot(344),imshow(I),title('I 分量');
subplot(345),imshow(hsi),title('hsi 图像');
h=fspecial('prewitt');
H1=imfilter(H,h);
S1=imfilter(S,h);
I1=imfilter(I,h);
subplot(346),imshow(H1),title('H 分量锐化');
subplot(347),imshow(S1),title('s 分量锐化');
subplot(348),imshow(I1),title('I 分量锐化');
hsi1=cat(3,H1,S1,I1);
subplot(349),imshow(hsi1),title('新 hsi 图像');
RGB1=hsi2rgb(hsi1);
subplot(3,4,10),imshow(RGB1),title('新 RGB 图像'); 

% 2.
% (1)
RGB=imread('lenna_color.jpg');
I=rgb2gray(RGB);
J=grayslice(I,8);
subplot(231),imshow(RGB),title('原始彩色图像');
subplot(232),imshow(I),title('原始灰度图像');
subplot(233),imshow(J,[]),title('8 切片图像');

subplot(234),imshow(RGB),title('原始彩色图像');
subplot(235),imshow(J,hot(8)),title('hot 恢复彩色图像');
subplot(236),imshow(J,cool(8)),title('cool 恢复彩色图像');

% 3.
RGB=imread('flowers.tif');
H=ones(5,5)/25;
RGB1=imfilter(RGB,H);
subplot(1,2,1),imshow(RGB),title('滤波前图像')
subplot(1,2,2),imshow(RGB1),title('滤波后图像')

% 4.
[RGB]=imread('autumn.tif');
subplot(121),imshow(RGB),title('原始图像');
RGBnew(:,:,1)=RGB(:,:,3);RGBnew(:,:,2)=RGB(:,:,1);
RGBnew(:,:,3)=RGB(:,:,2);
subplot(122),imshow(RGBnew),title('假彩色变换后图像');