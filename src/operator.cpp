#include "operator.h"
#include <chrono>     // for sleep
#include <cstdlib>    // for rand()
#include <string>
#include <thread>    // for sleep
#include <vector>
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

vector<string> oper_name_list = {operator_list};
vector<unique_ptr<generator_base>> oper_generator_list = []() {
    vector<unique_ptr<generator_base>> list;
    make_generator(list, operator_list);
    return list;
}();

vector<unique_ptr<Operator>> oper_generator(int type, int number) {
    vector<unique_ptr<Operator>> list;
    if (type == -1) {
        for (int i = 0; i < number; i++) list.push_back(unique_ptr<Operator>(new Keyboard_oper));
    }
    else {
        for (int i = 0; i < number; i++) list.push_back(unique_ptr<Operator>(oper_generator_list[type]->get()));
    }
    return list;
}

Operator::Operator(int _oper_type, string _name): oper_type(_oper_type), name(_name) {}

Operator::~Operator() = default;

Operator::operator std::string() {
    return name;
}

Keyboard_oper::Keyboard_oper(): Operator(INTERACTIVE_OPER, "Keyboard") {}

Keyboard_oper::~Keyboard_oper() = default;

int Keyboard_oper::get_moved(Gamecore* board) {
    while (!end_flag) {
        int input = keyboard.get_blocking();
        if (IS_U(input)) return MOVE_U;
        if (IS_D(input)) return MOVE_D;
        if (IS_L(input)) return MOVE_L;
        if (IS_R(input)) return MOVE_R;
    }
}

Random_oper::Random_oper(): Operator(NON_INTERACTIVE_OPER, "Random") {}

Random_oper::~Random_oper() = default;

int Random_oper::get_moved(Gamecore* board) {
    this_thread::sleep_for(chrono::microseconds(100));
    return rand() % 4 + 1;
}