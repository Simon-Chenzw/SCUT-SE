#pragma once

#include <memory>
#include <string>
#include <vector>
#include "gamecore.h"

// 交互式输入
#define INTERACTIVE_OPER 1
// 非交互式输入
#define NON_INTERACTIVE_OPER 2

// 只需在此添加新增的operator。oper_name_list和oper_generator会自动生成新版本
#define operator_list Random_oper()

// 纯虚基类 Operator的接口
class Operator {
  public:
    int oper_type;
    std::string name;

    Operator(int oper_type, std::string oper_name);
    virtual ~Operator() = 0;
    virtual int get_moved(Gamecore*) = 0;
    operator std::string();
};

extern std::vector<std::string> oper_name_list;    // "Keyboard" not included
// 构造指定个数的Operator keyboard的type为-1
std::vector<std::unique_ptr<Operator>> oper_generator(int type, int number);

// 键盘输入
class Keyboard_oper: public Operator {
  public:
    Keyboard_oper();
    ~Keyboard_oper();
    int get_moved(Gamecore*) override;
};    // number -1

class Random_oper: public Operator {
  public:
    Random_oper();
    ~Random_oper();
    int get_moved(Gamecore*) override;
};    // number 0