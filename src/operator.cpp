#include "operator.h"
#include <chrono>     // for sleep
#include <cstdlib>    // for rand()
#include <string>
#include <thread>    // for sleep
#include <vector>
#include "gamecore.h"
#include "log.h"
#include "platform.h"    // for keyboard
using namespace std;

// generator 用于多态生成unique_ptr<Operator>
class generator_base {
  public:
    virtual unique_ptr<Operator> get() = 0;
};
template <typename T>
class generator: public generator_base {
  public:
    generator() {}
    unique_ptr<Operator> get() override {
        return make_unique<T>();
    }
};

// 由operator_list 构造vector<unique_ptr<generator_base>>
void make_generator(vector<unique_ptr<generator_base>>& vec) {
    return;
}
template <typename T, typename... Arg>
void make_generator(vector<unique_ptr<generator_base>>& vec, T a, Arg... arg) {
    vec.push_back(unique_ptr<generator_base>(new generator<T>));
    make_generator(vec, arg...);
}

// 储存了每个Oper类的名字(Keyboard除外)
vector<string> oper_name_list = {operator_list};

// 储存了每个Oper类的generator(Keyboard除外) 通过成员函数get便可返回一个unique_ptr<Operator>
vector<unique_ptr<generator_base>> oper_generator_list;

void operator_init() {
    // 初始化oper_generator_list
    make_generator(oper_generator_list, operator_list);
    log("oper_generator_list initialization done");
}

vector<unique_ptr<Operator>> oper_generator(int type, int number) {
    vector<unique_ptr<Operator>> list;
    if (type == -1) {
        for (int i = 0; i < number; i++) list.push_back(unique_ptr<Operator>(new Keyboard_oper));
    }
    else {
        for (int i = 0; i < number; i++) list.push_back(unique_ptr<Operator>(oper_generator_list[type]->get()));
    }
    log(number, " operator(s) created.");
    return list;
}

Operator::Operator(const std::string& oper_name, const int& oper_type): name(oper_name), type(oper_type) {}

Operator::~Operator() = default;

Operator::operator std::string() {
    return name;
}

Keyboard_oper::Keyboard_oper(): Operator("Keyboard", INTERACTIVE_OPER) {}

// Keyboard_oper::~Keyboard_oper() = default;

int Keyboard_oper::get_moved(const Board& board) {
    while (!end_flag) {
        int input = keyboard.get_blocking();
        if (IS_U(input)) return MOVE_U;
        if (IS_D(input)) return MOVE_D;
        if (IS_L(input)) return MOVE_L;
        if (IS_R(input)) return MOVE_R;
    }
}

Random_oper::Random_oper(): Operator("Random") {}

// Random_oper::~Random_oper() = default;

int Random_oper::get_moved(const Board& board) {
    this_thread::sleep_for(chrono::microseconds(100));
    return rand() % 4 + 1;
}