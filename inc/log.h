#pragma once

#include <fstream>
#include <mutex>
#include <sstream>
#include <string>

#define log(mess) save_log(log_format(__FILE__, __LINE__, __func__, mess))

inline std::string log_format(const std::string& file,
                              const int& line,
                              const std::string& func,
                              const std::string& mess) {
    std::stringstream ss;
    ss << '[' << file << ':' << line << ' ' << '(' << func << ')' << ']' << ' ' << mess << '\n';
    return ss.str();
}

void save_log(const std::string& str);

extern std::fstream result_file;
extern std::mutex result_mutex;

template <typename T>
void file_print(std::fstream& fout, T a) {
    fout << a << '\n';
}

template <typename T, typename... Args>
void file_print(std::fstream& fout, T a, Args... arg) {
    fout << a << ',';
    file_print(fout, arg...);
}

template <typename... Args>
void save_result(Args... arg) {
    std::lock_guard<std::mutex> result_guard(result_mutex);
    result_file.open("result.csv", std::ios::app | std::ios::out);
    file_print(result_file, arg...);
    result_file.close();
}