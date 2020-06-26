#include "operator.h"
#include <chrono>
#include <cstdlib>    //for rand()
#include <thread>
#include <dbg_func>
#include "platform.h"

using namespace std;

Operator::Operator(int _oper_type, string _name): oper_type(_oper_type), name(_name) {}

Operator::~Operator() = default;

Keyboard_oper::Keyboard_oper(): Operator(INTERACTIVE_OPER, "Keyboard") {}

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

int Random_oper::get_moved(Gamecore* board) {
    this_thread::sleep_for(chrono::microseconds(100));
    return rand() % 4 + 1;
}