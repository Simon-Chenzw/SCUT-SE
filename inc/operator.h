// 交互式输入
#define INTERACTIVE_OPER 1
// 非交互式自动输入
#define NON_INTERACTIVE_OPER 2

#include "gamecore.h"

class Operator {
  public:
    int oper_type;

    Operator(int);
    virtual int get_input(Board*) = 0;
};

#define filter_none 0

// 键盘输入
class Keyboard_oper: Operator {
  public:
    int filter_type;

    Keyboard_oper();
    int get_input(Board* = nullptr) override;
};