// #include <termios.h>
// #include <cstdlib>
// #include <iostream>

// void init() {
//     //更改终端设定 实时读取键盘输入
//     struct termios settings;
//     tcgetattr(0, &settings);
//     settings.c_lflag &= (~ICANON);
//     settings.c_cc[VTIME] = 0;
//     settings.c_cc[VMIN] = 1;
//     tcsetattr(0, TCSANOW, &settings);
//     //关闭输入显示
//     system("stty -echo");
//     //清屏
//     printf("\033[2J");
//     //隐藏光标
//     printf("\033[?25l");
// }

// void release() {
//     //开启输入显示
//     system("stty echo");
//     //清屏
//     printf("\033[2J");
//     //恢复光标
//     printf("\33[?25h");
//     exit(0);
// }

// board test
#include <iostream>
#include <dbg_func>
#include "gamecore.h"
using namespace std;

int main() {
    Board board;
    board.num[0][0] = 1;
    board.num[3][2] = 3;
    board.num[1][1] = 2;
    board.num[1][2] = 1;
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++) cout << board.num[i][j] << " \n"[j == 3];
    while (true) {
        int dire;
        cin >> dire;
        board.moving(dire);
        for (int i = 0; i < 4; i++)
            for (int j = 0; j < 4; j++) cout << board.num[i][j] << " \n"[j == 3];
    }
    // while (true) {
    //     int a, b, c, d;
    //     cin >> a >> b >> c >> d;
    //     int num = a << 15 | b << 10 | c << 5 | d;
    //     auto tmp = Board::mem[num];
    //     dbg(a, b, c, d, num, tmp.after, tmp.moved, tmp.point);
    // }
}