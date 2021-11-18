I=imread('electric.jpg');
subplot(3,3,1);imshow(I),title('原图');

J = I;

% J = imnoise(I,'gauss',0.02); %添加高斯噪声
% subplot(3,3,2);imshow(J),title('高斯噪声');

% J = imnoise(I,'salt & pepper',0.02); %添加椒盐噪声
% subplot(3,3,2);imshow(J),title('椒盐噪声');

ave1=fspecial('average',3); %产生 3×3 的均值模版
K1 = imfilter(J,ave1);
subplot(3,3,4);imshow(K1),title('均值滤波 3×3');

ave2=fspecial('average',5); %产生 5×5 的均值模版
K2 = imfilter(J,ave2);
subplot(3,3,5);imshow(K2),title('均值滤波 5×5');

ave3=[-1,-1,-1;-1,9,-1;-1,-1,-1];
K3 = imfilter(J,ave3);
subplot(3,3,6);imshow(K3),title('均值滤波 自定义');


M = medfilt2(rgb2gray(J),[3 3]); 
subplot(3,3,7);imshow(M),title('中值滤波 3×3');

N = medfilt2(rgb2gray(J),[4 4]); 
subplot(3,3,8);imshow(N),title('中值滤波 4×4');
