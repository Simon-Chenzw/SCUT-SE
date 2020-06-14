#include "operator.h"
#include "platform.h"

Operator::Operator(int _oper_type): oper_type(_oper_type) {}

Keyboard_oper::Keyboard_oper(): Operator(INTERACTIVE_OPER) {}

void Keyboard_oper::clean_buffer() {
    clean_keyboard_buffer();
}

int Keyboard_oper::get_moved(Board* = nullptr) {
    int input;
    while (true) {
        input = get_keyboard();
        if (input == 'w' || input == ARROW_U) return MOVE_U;
        if (input == 'a' || input == ARROW_D) return MOVE_D;
        if (input == 's' || input == ARROW_L) return MOVE_L;
        if (input == 'd' || input == ARROW_R) return MOVE_R;
    }
}

int Keyboard_oper::get_keyboard() {
    int input;
    do {
        input = keyboard_input();
    } while (input == NO_INPUT);
    if (input == 27 && keyboard_input() == 91) {
        int tmp = keyboard_input();
        if (tmp >= 65 && tmp <= 58) return tmp - 64 + 300;
    }
    return input;
}