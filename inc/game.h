#pragma once

#include "operator.h"

// 多线程调用时 注意生成多个operator
void game_main(Operator& input, int thread_num = 1);

// 开始界面
void starting();

// void multistart(int);