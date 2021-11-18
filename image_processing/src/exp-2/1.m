I=imread('electric.jpg');
subplot(3,3,1);imshow(I),title('ԭͼ');

J = I;

% J = imnoise(I,'gauss',0.02); %��Ӹ�˹����
% subplot(3,3,2);imshow(J),title('��˹����');

% J = imnoise(I,'salt & pepper',0.02); %��ӽ�������
% subplot(3,3,2);imshow(J),title('��������');

ave1=fspecial('average',3); %���� 3��3 �ľ�ֵģ��
K1 = imfilter(J,ave1);
subplot(3,3,4);imshow(K1),title('��ֵ�˲� 3��3');

ave2=fspecial('average',5); %���� 5��5 �ľ�ֵģ��
K2 = imfilter(J,ave2);
subplot(3,3,5);imshow(K2),title('��ֵ�˲� 5��5');

ave3=[-1,-1,-1;-1,9,-1;-1,-1,-1];
K3 = imfilter(J,ave3);
subplot(3,3,6);imshow(K3),title('��ֵ�˲� �Զ���');


M = medfilt2(rgb2gray(J),[3 3]); 
subplot(3,3,7);imshow(M),title('��ֵ�˲� 3��3');

N = medfilt2(rgb2gray(J),[4 4]); 
subplot(3,3,8);imshow(N),title('��ֵ�˲� 4��4');
