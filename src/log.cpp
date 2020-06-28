#include "log.h"
#include <fstream>
#include <mutex>
using namespace std;

fstream log_file;
mutex log_mutex;

// "save_log" old version
// void save_log(const string& str) {
//     lock_guard<mutex> log_guard(log_mutex);
//     log_file.open("log.txt", ios::app | ios::out);
//     log_file << str;
//     log_file.close();
// }

fstream result_file;
mutex result_mutex;

// "save_result" old version
// void save_result(const Gamecore& core, const Operator& oper) {
//     lock_guard<mutex> result_guard(result_mutex);
//     result_file.open("result.csv", ios::app | ios::out);
//     // max_element, step, point, oper.name
//     result_file << core.board.max_element() << ',' << core.step << ',' << core.score << ',' << oper.name << '\n';
//     result_file.close();
// }

void clean_file() {
    log_file.open("log.txt", ios::trunc | ios::out);
    result_file.open("result.csv", ios::trunc | ios::out);
    log_file.close();
    result_file.close();
}