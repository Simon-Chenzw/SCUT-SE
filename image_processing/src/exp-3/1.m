% 1.
i=imread('flower.jpg');
figure,
subplot(2,2,1),imshow(i),title('原图');
j=imresize(i,2,'nearest');
subplot(2,2,2),imshow(j),title('最近邻插值');
k=imresize(i,2,'bilinea');
subplot(2,2,3),imshow(k),title('双线性插值');
j=imresize(i,2,'bicubic');
subplot(2,2,4),imshow(k),title('三次立方插值');

% 2.
i=imread('flower.jpg');
figure,
subplot(2,2,1),imshow(i);title('原图');
j=imrotate(i,45,'nearest');
subplot(2,2,2),imshow(j);title('最近邻插值法旋转 45 度');
j=imrotate(i,45,'bilinear');
subplot(2,2,3),imshow(j);title('双线性插值法旋转 45 度');
j=imrotate(i,45,'bicubic');
subplot(2,2,4),imshow(j);title('三次立方插值法旋转 45 度');

% 3.
i=imread('flower.jpg');
i=rgb2gray(i);
[x,y]=size(i);
p=1:x;q=1:y;
m(x-p+1,y-q+1)=i(p,q);
figure,
subplot(1,2,1),imshow(i);title('原图')
subplot(1,2,2),imshow(m);title('先水平镜像后垂直镜像')

% 4.
i = imread('flower.jpg');
j=translate(strel(1),[25,50]);
j=imdilate(i,j);
figure,
subplot(1,2,1),imshow(i),title('原图');
subplot(1,2,2),imshow(j),title('向下25像素，向右50像素');
