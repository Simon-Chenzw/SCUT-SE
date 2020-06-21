#include "platform.h"
#ifdef IN_LINUX

#include <termios.h>
#include <cstdio>
#include <sys/ioctl.h>
// guide:
// termios https://blog.csdn.net/liuqz2009/article/details/51967763
// termios https://blog.csdn.net/leumber/article/details/80105295
// 窗口大小 https://www.cnblogs.com/sinpo828/p/10678945.html

struct termios initial_setting;

// 更改终端设定 做到非阻塞实时读取键盘输入
void terminal_init() {
    // 获取并保存设定
    struct termios setting;
    tcgetattr(0, &setting);
    initial_setting = setting;
    // 更改 local mode (关闭模式)
    // setting.c_lflag &= ~ISIG;      // 当输入INTR、QUIT、SUSP或DSUSP时，产生相应的信号
    setting.c_lflag &= ~ICANON;    // 使用标准输入模式
    setting.c_lflag &= ~ECHO;      // 显示输入字符
    // 更改 control characters
    setting.c_cc[VMIN] = 0;     // 最小读取字符 0为非阻塞
    setting.c_cc[VTIME] = 0;    // 读取延迟 单位百毫秒
    // 应用设定
    tcsetattr(0, TCSANOW, &setting);
}

// 还原终端设定
void terminal_uninit() {
    tcsetattr(0, TCSANOW, &initial_setting);
}

void clean_keyboard_buffer() {
    while (getchar() != -1)
        ;
}

int keyboard_input() {
    return getchar();
}

void get_screen_size(int& row, int& col) {
    struct winsize info;
    ioctl(0, TIOCGWINSZ, &info);
    row = info.ws_row;
    col = info.ws_col;
}

void set_cursor_position(int row, int col) {
    printf("\033[%d;%df", row, col);
}

int clr_code[] = {0, 30, 31, 32, 33, 34, 35, 36, 37, 40, 41, 42, 43, 44, 45, 46, 47};

void setcolor(const int& color) {
    if (color == CLR_RESET)
        resetcolor();
    else
        printf("\033[%dm", clr_code[color]);
}

void resetcolor() {
    printf("\033[m");
}

#endif    // IN_LINUX