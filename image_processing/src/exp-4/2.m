% 1.
f=imread('calculator.tif');
% figure,subplot(221),imshow(f),title('灰度级重构原图像');

f_obr=imreconstruct(imerode(f,ones(1,71)),f);
% subplot(222),imshow(f_obr),title('经开运算重构图');

f_o=imopen(f,ones(1,71));
% subplot(223),imshow(f_o),title('经开运算后图');

f_thr=imsubtract(f,f_obr);
% subplot(224),imshow(f_thr),title('顶帽运算重构图');

% 2.

f_th=imsubtract(f,f_o);
figure,subplot(221),imshow(f_th),title('经顶帽运算图');

g_obr=imreconstruct(imerode(f_thr,ones(1,11)),f_thr);
subplot(222),imshow(g_obr),title('用水平线对 f_thr 经开运算后重构图');

g_obrd=imdilate(g_obr,ones(1,2));
subplot(223),imshow(g_obrd),title('使用水平线对上图进行膨胀');

f2=imreconstruct(min(g_obrd,f_thr),f_thr);
subplot(224),imshow(f2),title('最后的重构结果');