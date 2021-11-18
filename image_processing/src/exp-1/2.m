% 1、图像的加法运算
ImageOne=imread('2_1(a).tif');
ImageTwo=imread('2_1(b).tif');
AddImage=imadd(ImageOne,ImageTwo);
subplot(4,4,1);
imshow(AddImage);title('加法运算截图');

RGB = imread('flower2.tif');
RGB2 = imadd(RGB,50);
RGB3 = imadd(RGB,-50);
subplot(4,4,2);imshow(RGB);title('原图');
subplot(4,4,3);imshow(RGB2);title('+50图');
subplot(4,4,4);imshow(RGB3);title('-50图');

% 2、图像的减法运算
camema=imread('camema.jpg');
background=imopen(camema,strel('disk',15));
output=imsubtract(camema, background);
subplot(4,4,5);imshow(camema);title('原图');
subplot(4,4,6);imshow(output);title('减去背景图');

% 3、图像的乘法运算
I = imread('room.tif');
J = immultiply(I,1.2);
subplot(4,4,9);imshow(I);title('原图');
subplot(4,4,10);imshow(J);title('乘以因子1.2图');

% 4、图像的除法运算
Image1 = imread('camema.jpg');
Ip = imdivide(Image1, output);
Ipim=mat2gray(Ip);
subplot(4,4,13);
imshow(Ipim, []);title('原图和减背景后的图像相除的图像效果');
