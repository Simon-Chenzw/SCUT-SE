import cv2 as cv
import numpy as np
import torch

myimg = cv.imread('1.jpg', cv.IMREAD_GRAYSCALE)  # 读取和代码位于同一目录下的图片
shape = myimg.shape
print(shape[0], shape[1])
length = 0
# if (len(shape) == 2): myimg = np.reshape(myimg, (shape[0], shape[1], 1))
if (shape[0] >= shape[1]):
    length = shape[1]
    cut = (shape[0] - shape[1]) // 2
    myimg = myimg[cut:(cut + length), :]
else:
    length = shape[0]
    cut = (shape[1] - shape[0]) // 2
    myimg = myimg[:, cut:(cut + length)]

cv.imwrite("img/image.jpg", myimg)
#print(myimg.shape)
myimg = cv.resize(myimg, (227, 227))
# print(myimg.shape)
myimg = np.reshape(myimg, (1, 1, 227, 227))
input = torch.tensor(myimg, dtype=torch.float32)
# input = 255-input
#print(input.shape)

def showPict(array, title, num=0, i=0, deal=False):
    name = title + str(num) + "_" + str(i)
    array = array.detach().numpy()
    shape = array.shape
    pict = array[0, 0, :, :]
    pict = np.reshape(pict, (shape[2], shape[3]))
    l = 454
    pict = cv.resize(pict, (l, l))
    print("pict:",name)
    #print(pict.shape)
    if (deal == True): # 二值化
        pict[pict > 0] = 255
        # aver = np.average(pict)
        # pict[pict < aver] = 0
        # pict[pict >= aver] = 255
    # cv.imshow(name, pict)
    # cv.waitKey(0)
    # cv.destroyAllWindows()
    cv.imwrite("img/" + name + ".jpg", pict)



relu = torch.nn.ReLU(inplace=True)
conv1 = torch.nn.Conv2d(1, 96, 11, stride=4)
deconv1 = torch.nn.ConvTranspose2d(96, 1, 11, stride=4)

conv2 = torch.nn.Conv2d(96, 256, 5, stride=1, padding=2, padding_mode='zeros')
deconv2 = torch.nn.ConvTranspose2d(256, 96, 5, stride=1, padding=2, padding_mode='zeros')

conv3 = torch.nn.Conv2d(256, 384, 3, stride=1, padding=1, padding_mode='zeros')
deconv3 = torch.nn.ConvTranspose2d(384, 256, 3, stride=1, padding=1, padding_mode='zeros')

conv4 = torch.nn.Conv2d(384, 384, 3, stride=1, padding=1, padding_mode='zeros')
deconv4 = torch.nn.ConvTranspose2d(384, 384, 3, stride=1, padding=1, padding_mode='zeros')

conv5 = torch.nn.Conv2d(384, 256, 3, stride=1, padding=1, padding_mode='zeros')
deconv5 = torch.nn.ConvTranspose2d(256, 384, 3, stride=1, padding=1, padding_mode='zeros')

maxpool = torch.nn.MaxPool2d(3, stride=2, return_indices=True)
unpool = torch.nn.MaxUnpool2d(3, stride=2)

# -----卷积部分------

vol1 = conv1(input)
vol1 = relu(vol1)
W1 = conv1.weight
b1 = conv1.bias
print("vol1", vol1.shape)
showPict(vol1, "conv", 1, 0)
# showPict(W1, "weight", 1, 0)

pool1, indices1 = maxpool(vol1)
print("pool1",pool1.shape)

vol2 = conv2(pool1)
vol2 = relu(vol2)
W2 = conv2.weight
b2 = conv2.bias
print("vol2", vol2.shape)
showPict(vol2, "conv", 2, 1)
# showPict(W2, "weight", 2, 1)

pool2, indices2 = maxpool(vol2)
print("pool2",pool2.shape)

vol3 = conv3(pool2)
vol3 = relu(vol3)
W3 = conv3.weight
b3 = conv3.bias
print("vol3", vol3.shape)
showPict(vol3, "conv", 3, 2)
# showPict(W3, "weight", 3, 2)

vol4 = conv4(vol3)
vol4 = relu(vol4)
W4 = conv4.weight
b4 = conv4.bias
print("vol4", vol4.shape)
showPict(vol4, "conv", 4, 2)
# showPict(W4, "weight", 4, 2)

vol5 = conv5(vol4)
vol5 = relu(vol5)
W5 = conv5.weight
b5 = conv5.bias
print("vol5", vol5.shape)
showPict(vol5, "conv", 5, 2)
# showPict(W5, "weight", 5, 2)

pool3, indices3 = maxpool(vol5)
print("pool3",pool3.shape)

# -----反卷积部分------

# 一层卷积层
print("\n-----一层卷积层------")
print(vol1.shape)
res1 = relu(vol1)
res1 = deconv1(res1)
print(res1.shape)
showPict(res1, "deconv", 1, 0)

# 一层卷积层+一层池化层
print("\n--一层卷积层+一层池化层--")
print(pool1.shape)
res2 = unpool(pool1, indices1)
print(res2.shape)
res2 = relu(res2)
res2 = deconv1(res2)
print(res2.shape)
showPict(res2, "deconv", 1, 1)

# 两层卷积层+一层池化层
print("\n--两层卷积层+一层池化层--")
print(vol2.shape)
res3 = relu(vol2)
res3 = deconv2(res3)
print(res3.shape)
res3 = unpool(res3, indices1)
print(res3.shape)
res3 = relu(res3)
res3 = deconv1(res3)
print(res3.shape)
showPict(res3, "deconv", 2, 1)

# 两层卷积层+两层池化层
print("\n--两层卷积层+两层池化层--")
print(pool2.shape)
res4 = unpool(pool2, indices2)
print(res4.shape)
res4 = relu(res4)
res4 = deconv2(res4)
print(res4.shape)
res4 = unpool(res4, indices1)
print(res4.shape)
res4 = relu(res4)
res4 = deconv1(res4)
print(res4.shape)
showPict(res4, "deconv", 2, 2)

# 三层卷积层+两层池化层
print("\n--三层卷积层+两层池化层--")
print(vol3.shape)
res5 = relu(vol3)
res5 = deconv3(res5)
print(res5.shape)
res5 = unpool(res5, indices2)
print(res5.shape)
res5 = relu(res5)
res5 = deconv2(res5)
print(res5.shape)
res5 = unpool(res5, indices1)
print(res5.shape)
res5 = relu(res5)
res5 = deconv1(res5)
print(res5.shape)
showPict(res5, "deconv", 3, 2)

# 四层卷积层+两层池化层
print("\n--四层卷积层+两层池化层--")
print(vol4.shape)
res6 = relu(vol4)
res6 = deconv4(res6)
print(res6.shape)
res6 = relu(res6)
res6 = deconv3(res6)
print(res6.shape)
res6 = unpool(res6, indices2)
print(res6.shape)
res6 = relu(res6)
res6 = deconv2(res6)
print(res6.shape)
res6 = unpool(res6, indices1)
print(res6.shape)
res6 = relu(res6)
res6 = deconv1(res6)
print(res6.shape)
showPict(res6, "deconv", 4, 2)

# 五层卷积层+两层池化层
print("\n--五层卷积层+两层池化层--")
print(vol5.shape)
res7 = relu(vol5)
res7 = deconv5(res7)
print(res7.shape)
res7 = relu(res7)
res7 = deconv4(res7)
print(res7.shape)
res7 = relu(res7)
res7 = deconv3(res7)
print(res7.shape)
res7 = unpool(res7, indices2)
print(res7.shape)
res7 = relu(res7)
res7 = deconv2(res7)
print(res7.shape)
res7 = unpool(res7, indices1)
print(res7.shape)
res7 = relu(res7)
res7 = deconv1(res7)
print(res7.shape)
showPict(res7, "deconv", 5, 2)

# 五层卷积层+三层池化层
print("\n--五层卷积层+三层池化层--")
print(pool3.shape)
res8 = unpool(pool3, indices3)
print(res8.shape)
res8 = relu(res8)
res8 = deconv5(res8)
print(res8.shape)
res8 = relu(res8)
res8 = deconv4(res8)
print(res8.shape)
res8 = relu(res8)
res8 = deconv3(res8)
print(res8.shape)
res8 = unpool(res8, indices2)
print(res8.shape)
res8 = relu(res8)
res8 = deconv2(res8)
print(res8.shape)
res8 = unpool(res8, indices1)
print(res8.shape)
res8 = relu(res8)
res8 = deconv1(res8)
print(res8.shape)
showPict(res8, "deconv", 5, 3)