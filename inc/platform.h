#pragma once

// windows macro
#ifdef _WIN32
#define IN_WINDOWS
#endif

// linux macro
#ifdef __linux__
#define IN_LINUX
#endif

#ifdef linux
#define IN_LINUX
#endif

// determine wrong
#if defined(IN_LINUX) && defined(IN_WINDOWS)
#error Detected on two different platforms
#endif
// platform determine end

void get_screen_size(int& row, int& col);

// origin row = 1 col = 1
void set_cursor_position(int row, int col);

// key macro
#define NO_INPUT -1
#define ESC 27
#define ARROW_U 301
#define ARROW_D 302
#define ARROW_L 304
#define ARROW_R 303

class Keyboard {
  public:
    Keyboard();
    ~Keyboard();
    int get();
    int get_blocking();
    void clean_buffer();
};

// color macro
#define CLR_RESET 0

#define CLR_BLACK 1
#define CLR_RED 2
#define CLR_GREEN 3
#define CLR_YELLOW 4
#define CLR_BLUE 5
#define CLR_MAGENTA 6
#define CLR_CYAN 7
#define CLR_WHITE 8

#define CLR_ON_BLACK 9
#define CLR_ON_RED 10
#define CLR_ON_GREEN 11
#define CLR_ON_YELLOW 12
#define CLR_ON_BLUE 13
#define CLR_ON_MAGENTA 14
#define CLR_ON_CYAN 15
#define CLR_ON_WHITE 16

void setcolor(const int&);

void resetcolor();