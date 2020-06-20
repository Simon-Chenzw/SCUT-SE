#pragma once

#include "gamecore.h"

/*
    clean_borad:    全黑

    以下基于clean_borad的基础上
    print_frame:    打印周围边框


    以下基于print_frame的基础上
    print_symbol:   2048 logo
    print_anykey:   "press any key to continue"
    select_option:  多选项选择

    print_state:    打印游戏state
    print_endint:   打印最终结算结果

    loading:    左下角加载 "loading..." 视最终版本时加载耗时决定是否添加
*/

void clean_board();

void print_frame();

void print_symbol();

void press_anykey();

int select_option(int option_size, char* options);

void print_state(const Gamecore&, int = 1);    //注意多线程

void print_ending(const Gamecore&);

// class loading {
//     loading(char*);
//     void start();
//     void end();
// };