#pragma once

#include <string>
#include "gamecore.h"
#include "operator.h"

#define log(mess) log_format(__FILE__, __LINE__, __func__, mess)

void log_format(const std::string& file, const int& line, const std::string& func, const std::string& mess);

void print_log(const std::string& str);

void print_result(const Gamecore&, const Operator&);