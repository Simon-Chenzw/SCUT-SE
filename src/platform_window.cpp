#include "platform.h"
#ifdef IN_WINDOWS

// guide:
// _kbhit https://docs.microsoft.com/en-us/cpp/c-runtime-library/reference/kbhit?view=vs-2019

#include <conio.h>
#include <windows.h>
#include <cstdlib>
#include "log.h"

void clean_screen() {
    system("cls");
}

void get_screen_size(int& row, int& col) {
    CONSOLE_SCREEN_BUFFER_INFO scr;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &scr);
    row = scr.srWindow.Bottom + 1;
    col = scr.srWindow.Right + 1;
}

void set_cursor_position(const int& row, const int& col) {
    // 设置控制台光标坐标(设备句柄, 光标坐标)
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), COORD {(SHORT)col - 1, (SHORT)row - 1});
}

// keyboard
Keyboard keyboard;

bool end_flag = false;

Keyboard::Keyboard() {
    // 隐藏光标
    CONSOLE_CURSOR_INFO cur {1, 0};
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cur);
}

Keyboard::~Keyboard() {}

int Keyboard::get() {
    if (!_kbhit()) return NO_INPUT;
    int input = _getch();
    if (input == 224 && _kbhit()) {
        int tmp = _getch();
        if (tmp == 72) input = ARROW_U;
        if (tmp == 80) input = ARROW_D;
        if (tmp == 75) input = ARROW_L;
        if (tmp == 77) input = ARROW_R;
    }
    if (IS_QUIT(input)) {
        log("Triggered QUIT. end_flag set to True");
        end_flag = true;
    }
    return input;
}

int Keyboard::get_blocking() {
    int input = get();
    while (input == NO_INPUT && !end_flag) {
        input = get();
    }
    return input;
}

void Keyboard::clean_buffer() {
    int input;
    do {
        input = get();
    } while (input != NO_INPUT);
}

// color
const uint16_t clr[] = {
    0,                                                                             // CLR_RESET
    FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED,                           // CLR_BLACK 1
    FOREGROUND_RED | FOREGROUND_INTENSITY,                                         // CLR_RED
    FOREGROUND_GREEN | FOREGROUND_INTENSITY,                                       // CLR_GREEN
    FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY,                      // CLR_YELLOW
    FOREGROUND_BLUE | FOREGROUND_INTENSITY,                                        // CLR_BLUE
    FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_INTENSITY,                       // CLR_MAGENTA
    FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY,                     // CLR_CYAN
    FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY,    // CLR_WHITE
    BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED,                           // CLR_ON_BLACK
    BACKGROUND_RED /*| BACKGROUND_INTENSITY*/,                                     // CLR_ON_RED
    BACKGROUND_GREEN | BACKGROUND_INTENSITY,                                       // CLR_ON_GREEN
    BACKGROUND_GREEN | BACKGROUND_RED | BACKGROUND_INTENSITY,                      // CLR_ON_YELLOW
    BACKGROUND_BLUE /*| BACKGROUND_INTENSITY*/,                                    // CLR_ON_BLUE
    BACKGROUND_BLUE | BACKGROUND_RED /*| BACKGROUND_INTENSITY*/,                   // CLR_ON_MAGENTA
    BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_INTENSITY,                     // CLR_ON_CYAN
    BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED | BACKGROUND_INTENSITY,    // CLR_ON_WHITE
};

void setcolor(const int& color) {
    static const uint16_t initial_attributes = [] {
        CONSOLE_SCREEN_BUFFER_INFO buffer_info;
        GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &buffer_info);
        return buffer_info.wAttributes;
    }();
    static uint16_t background = initial_attributes & 0x00F0;
    static uint16_t foreground = initial_attributes & 0x000F;
    if (color == CLR_RESET) {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), initial_attributes);
    }
    else {
        uint16_t clr_code = clr[color];
        if (clr_code & 0x00F0)
            background = clr_code;
        else if (clr_code & 0x000F)
            foreground = clr_code;
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), background | foreground);
    }
}

void resetcolor() {
    setcolor(CLR_RESET);
}

#endif    // IN_WINDOWS