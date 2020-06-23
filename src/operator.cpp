#include "operator.h"
#include <cstdlib>    //for rand()
#include <dbg_func>
#include "platform.h"

using namespace std;

Operator::Operator(int _oper_type, string _name): oper_type(_oper_type), name(_name) {}

Keyboard_oper::Keyboard_oper(Keyboard& _keyboard): Operator(INTERACTIVE_OPER, "Keyboard"), keyboard(_keyboard) {}

int Keyboard_oper::get_moved(Board* board) {
    int input = keyboard.get_blocking();
    if (input == 'w' || input == ARROW_U) return MOVE_U;
    if (input == 's' || input == ARROW_D) return MOVE_D;
    if (input == 'a' || input == ARROW_L) return MOVE_L;
    if (input == 'd' || input == ARROW_R) return MOVE_R;
}

Random_oper::Random_oper(): Operator(NON_INTERACTIVE_OPER, "Random") {}

int Random_oper::get_moved(Board* board) {
    return rand() % 4 + 1;
}