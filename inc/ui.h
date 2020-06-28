#pragma once

#include <string>
#include <vector>
#include "gamecore.h"

/*
 *  以下函数调用时会清除除logo之外的东西：
 *      print_greeting
 *      select_option
 *      get_number
 *      print_state_frame
 *      print_goodbye
 *
 *  以下函数可以多线程调用：
 *      print_state
 *      print_ending
 *      clean_ending
 */

// 2048 logo
void print_symbol();

// 打印问候语
void print_greeting();

// 通过上下选择选项 返回vector中的序号
int select_option(const std::vector<std::string>&, const std::string& message = "");

// 获取一个从键盘中键入的数字
int get_number(const std::string& message);

// 打印游戏的基础框架 依据是否是多线程 有不同的形式
void print_state_frame(const std::string& oper_name, bool multithread = false);

// 打印Gamecore的状况 依据是否是多线程 有不同的形式
void print_state(const Gamecore&, int thread_num = 1);    //注意多线程

// 打印死亡时的结束语 依据是否是多线程 有不同的形式
void print_ending(const int& thread_num);    //注意多线程

// 清除死亡时的结束语 依据是否是多线程 有不同的形式
void clean_ending(const int& thread_num);    //注意多线程

// 打印触发QUIT时的结束语 并且设定光标至一个合理的位置 防止结束后终端乱码
void print_goodbye();