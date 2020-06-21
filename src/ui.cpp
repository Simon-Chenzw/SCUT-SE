#include "ui.h"
#include <cstdio>
#include <iostream>
#include <dbg_func>
#warning UI not done yet

using std::cout;

void clean_board() {
    return;
}

void print_frame() {
    return;
}

void print_symbol() {
    return;
}

void press_anykey() {
    cout << "press any key to continue";
    return;
}

int select_option(const std::vector<std::string>& vec) {
    return 0;
}

//注意多线程
void print_state(const Gamecore& core, int thread_num) {
    dbg("state start", thread_num, core.step, core.point);
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++) cout << core.board.num[i][j] << " \n"[j == 3];
    cout << '\n';
}

void print_ending(const Gamecore&) {
    return;
}