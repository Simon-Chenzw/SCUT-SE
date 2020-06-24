#pragma once

#include <string>
#include <vector>
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

void print_symbol();

void print_greeting();

int select_option(const std::vector<std::string>&);

int get_number(const std::string& message);

void print_state_frame(const std::string& oper_name, bool multithread = false);

void print_state(const Gamecore&, int thread_num = 1);    //注意多线程

void print_ending(int thread_num);    //注意多线程

void clean_ending(int thread_num);    //注意多线程

void print_goodbye();