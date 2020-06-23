#pragma once

// 交互式输入
#define INTERACTIVE_OPER 1
// 非交互式自动输入
#define NON_INTERACTIVE_OPER 2

#include <string>
#include "gamecore.h"
#include "platform.h"

class Operator {
  public:
    int oper_type;
    std::string name;

    Operator(int, std::string);
    virtual int get_moved(Board*) = 0;
};

// 键盘输入
class Keyboard_oper: public Operator {
  private:
    Keyboard& keyboard;

  public:
    Keyboard_oper(Keyboard&);
    int get_moved(Board* = nullptr) override;
};

class Random_oper: public Operator {
  public:
    Random_oper();
    int get_moved(Board*) override;
};