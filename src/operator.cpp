#include "operator.h"
#include <cstdlib>    //for rand()
#include "platform.h"

Operator::Operator(int _oper_type, char* _name): oper_type(_oper_type) {
    for (int i = 0; i < 20; i++) name[i] = _name[i];
}

Keyboard_oper::Keyboard_oper(): Operator(INTERACTIVE_OPER, (char*)"Keyboard") {}

void Keyboard_oper::clean_buffer() {
    clean_keyboard_buffer();
}

int Keyboard_oper::get_moved(Board* board) {
    int input;
    while (true) {
        input = get_keyboard();
        if (input == 'w' || input == ARROW_U) return MOVE_U;
        if (input == 's' || input == ARROW_D) return MOVE_D;
        if (input == 'a' || input == ARROW_L) return MOVE_L;
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

Random_oper::Random_oper(): Operator(NON_INTERACTIVE_OPER, (char*)"Random") {}

int Random_oper::get_moved(Board* board) {
    return rand() % 4 + 1;
}