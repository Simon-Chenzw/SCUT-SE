// keyboard_demo in linux

#include <fcntl.h>
#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <bits/stdc++.h>
using namespace std;

void init() {
    //更改终端设定 实时读取键盘输入
    struct termios settings;
    tcgetattr(0, &settings);
    settings.c_lflag &= (~ICANON);
    settings.c_cc[VTIME] = 0;
    settings.c_cc[VMIN] = 1;
    tcsetattr(0, TCSANOW, &settings);

    //关闭输入显示
    // system("stty -echo");

    // 非阻塞
    int flags = fcntl(0, F_GETFL, 0);
    fcntl(0, F_SETFL, flags | O_NONBLOCK);
}

int x = 0;
int y = 0;
const int maxn = 10;
const int f[4][2] = {-1, 0, 1, 0, 0, 1, 0, -1};

void print() {
    printf("\033[2;1H");
    for (int i = 0; i < maxn; i++) {
        for (int j = 0; j < maxn; j++)
            if (i == x && j == y)
                cout << '@';
            else
                cout << '#';
        cout << '\n';
    }
}

// //测试函数
// int main() {
//     init();
//     printf("\033[2J");    //清屏
//     while (1) {
//         printf("\033[1;1Hinput:");    //定位光标
//         if (cin.get() != 27) continue;
//         if (cin.get() != 91) continue;
//         int moving = cin.get();
//         if (moving < 65 || moving > 68) continue;
//         x += f[moving - 65][0];
//         y += f[moving - 65][1];
//         if (x < 0) x = 0;
//         if (y < 0) y = 0;
//         if (x == maxn) x = maxn - 1;
//         if (y == maxn) y = maxn - 1;
//         print();
//     }
// }

auto init_func = []() {
    init();
    return 0;
}();

int main() {
    int cnt = 0;
    char tmp = '*';
    dbg(tmp, (int)tmp, cnt++);
    while (true) {
        tmp = cin.get();
        dbg(tmp, (int)tmp, cnt++);
        sleep(1);
    }
}