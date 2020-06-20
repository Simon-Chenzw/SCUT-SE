#pragma once

// 交互式输入
#define INTERACTIVE_OPER 1
// 非交互式自动输入
#define NON_INTERACTIVE_OPER 2

#define ARROW_U 301
#define ARROW_D 302
#define ARROW_L 304
#define ARROW_R 303

#include "gamecore.h"

class Operator {
  public:
    int oper_type;
    char name[20];

    Operator(int, char*);
    virtual int get_moved(Board*) = 0;
};

// 键盘输入
class Keyboard_oper: public Operator {
  public:
    Keyboard_oper();
    void clean_buffer();
    int get_moved(Board* = nullptr) override;
    int get_keyboard();
};