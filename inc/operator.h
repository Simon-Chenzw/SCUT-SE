#pragma once

#include <memory>
#include <string>
#include <vector>

// 只需在此添加新增的operator。oper_name_list和oper_generator会自动生成新版本
#define operator_list Random_oper()

/** 添加自定义Operator派生类教程：
 *
 *  文件：
 *    新增AI时建议另起额外的cpp文件，
 *    再在本头文件的末尾include你新建的cpp文件，
 *    然后修改本头文件中define的operator_list，
 *    在其后面添加新增派生类的默认构造函数。
 *
 *
 *   派生类必须包含以下函数：
 *      1)默认构造函数
 *          基类的构造函数为：
 *            Operator(const string& oper_name, const int& oper_type = NON_INTERACTIVE_OPER);
 *              oper_name为UI中显示的名字
 *              oper_type为 INTERACTIVE_OPER 或 NON_INTERACTIVE_OPER 标志着是否是交互式Operator
 *
 *      2)int get_moved(const Board&);
 *          board为int[4][4]
 *          返回值为MOVE_U MOVE_D MOVE_L MOVE_R define于gamecore.h
 *
 *    *** 注意Operator类会存在多个实例，且也会被include进多个文件 ***
 *
 */

using Board = int[4][4];

// 交互式输入
#define INTERACTIVE_OPER 1
// 非交互式输入
#define NON_INTERACTIVE_OPER 2

// 纯虚基类 Operator的接口
class Operator {
  public:
    const std::string name;
    const int type;

    Operator(const std::string& oper_name, const int& oper_type = NON_INTERACTIVE_OPER);
    virtual ~Operator() = 0;
    virtual int get_moved(const Board&) = 0;
    operator std::string();
};

// 除keyboard外所有operator的名字
extern std::vector<std::string> oper_name_list;    // "Keyboard" not included

// 构造指定个数的Operator keyboard的type为-1
std::vector<std::unique_ptr<Operator>> oper_generator(int type, int number);

void operator_init();

// 键盘输入
class Keyboard_oper: public Operator {
  public:
    Keyboard_oper();
    // ~Keyboard_oper() override;
    int get_moved(const Board&) override;
};    // number -1

class Random_oper: public Operator {
  public:
    Random_oper();
    // ~Random_oper() override;
    int get_moved(const Board&) override;
};    // number 0