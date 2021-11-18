x=imread('cameraman.jpg');
x=imnoise(x,'gaussian');
subplot(131);imshow(x),title('噪声')


h=fspecial('average')
y=imfilter(x,h);
subplot(132);imshow(y),title('平滑滤波器')

w=wiener2(x);
subplot(133);imshow(w),title('维纳滤波器')

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

I = imread('flowers.jpg'); 
subplot(131);imshow(I);
title('Original Image');
LEN = 31;
THETA = 15;
PSF = fspecial('motion',LEN,THETA);
Blurred = imfilter(I,PSF,'circular','conv');
subplot(132);imshow(Blurred);
title('Blurred Image');

wnr1 = deconvwnr(Blurred,PSF);
subplot(133);imshow(wnr1);
title('Restored, True PSF');