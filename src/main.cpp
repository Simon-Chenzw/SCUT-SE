#include <termios.h>
#include "game.h"
#include "header.h"

void init() {
    //更改终端设定 实时读取键盘输入
    struct termios settings;
    tcgetattr(0, &settings);
    settings.c_lflag &= (~ICANON);
    settings.c_cc[VTIME] = 0;
    settings.c_cc[VMIN] = 1;
    tcsetattr(0, TCSANOW, &settings);
    //关闭输入显示
    system("stty -echo");
    //清屏
    printf("\033[2J");
    //隐藏光标
    printf("\033[?25l");
}

void release() {
    //开启输入显示
    system("stty echo");
    //清屏
    printf("\033[2J");
    //恢复光标
    printf("\33[?25h");
    exit(0);
}

int main() {}