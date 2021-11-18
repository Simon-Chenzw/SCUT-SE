test=imread('flower.tif');
whos test;
subplot(2,2,1),
imshow(test);title('原图');
inforTest=imfinfo('flower.tif');
imwrite(test,'filename.jpg','quality',20);
imwrite(test,'filename.bmp');
ImageOne=imread('Lenna.jpg');
ImageTwo=imread('camema.jpg');
inforOne=imfinfo('Lenna.jpg');
inforTwo=imfinfo('camema.jpg');
subplot(2,2,2);
imshow(ImageOne),title('第9步图');
subplot(2,2,3);
imshow(ImageTwo),title('第9步图');

TwoValueImage=im2bw(ImageOne);
subplot(2,2,4);
imshow(TwoValueImage),title('第10步图');
