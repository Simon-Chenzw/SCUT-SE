#include "log.h"
#include <fstream>
#include <mutex>
#include <sstream>
#include <string>
using namespace std;

void log_format(const std::string& file, const int& line, const string& func, const std::string& mess) {
    stringstream ss;
    ss << '[' << file << ':' << line << ' ' << '(' << func << ')' << ']' << ' ' << mess << '\n';
    print_log(ss.str());
}

fstream log_file;
mutex log_mutex;

void print_log(const string& str) {
    lock_guard<mutex> log_guard(log_mutex);
    log_file.open("log.txt", ios::app | ios::out);
    log_file << str;
    log_file.close();
}

fstream result_file;
mutex result_mutex;

void print_result(const Gamecore& core, const Operator& oper) {
    lock_guard<mutex> result_guard(result_mutex);
    result_file.open("result.csv", ios::app | ios::out);
    // max_element, step, point, oper.name
    result_file << core.board.max_element() << ',' << core.step << ',' << core.score << ',' << oper.name << '\n';
    result_file.close();
}