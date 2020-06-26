#pragma once

// 交互式输入
#define INTERACTIVE_OPER 1
// 非交互式自动输入
#define NON_INTERACTIVE_OPER 2

#include <string>
#include "gamecore.h"

// 纯虚基类 Operator的接口
class Operator {
  public:
    int oper_type;
    std::string name;

    Operator(int oper_type, std::string oper_name);
    virtual ~Operator() = 0;
    virtual int get_moved(Gamecore*) = 0;
};

// 键盘输入
class Keyboard_oper: public Operator {
  public:
    Keyboard_oper();
    ~Keyboard_oper();
    int get_moved(Gamecore*) override;
};

class Random_oper: public Operator {
  public:
    Random_oper();
    ~Random_oper();
    int get_moved(Gamecore*) override;
};