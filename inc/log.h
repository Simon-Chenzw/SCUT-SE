#pragma once

#include <fstream>
#include <mutex>
#include <sstream>
#include <string>

void clean_file();

// log part
extern std::fstream log_file;
extern std::mutex log_mutex;

// need to given when compiling
#ifndef __MY__FILE__
#define __MY__FILE__ __FILE__
#endif

// 记录log 包含file line func等信息
#define log(arg...) save_log(log_head(__MY__FILE__, __LINE__, __func__), ##arg)

// 内联函数 处理输出格式
inline std::string log_head(const std::string& file, const int& line, const std::string& func) {
    std::stringstream ss;
    ss << '[' << file << ':' << line << ' ' << '(' << func << ')' << ']' << ' ';
    return ss.str();
}

// 不定长函数递归终点
inline void log_print() {
    log_file << '\n';
}

// 不定长函数递归过程
template <typename T, typename... Arg>
void log_print(T&& a, Arg&&... arg) {
    log_file << a;
    log_print(arg...);
}

// 通过不定长函数 保存参数至log.txt
template <typename... Arg>
void save_log(Arg&&... arg) {
    std::lock_guard<std::mutex> result_guard(log_mutex);
    log_file.open("log.txt", std::ios::app | std::ios::out);
    log_print(arg...);
    log_file.close();
}

// result part
extern std::fstream result_file;
extern std::mutex result_mutex;

// 不定长函数递归终点
template <typename T>
void result_print(T&& a) {
    result_file << a << '\n';
}

// 不定长函数递归过程
template <typename T, typename... Arg>
void result_print(T&& a, Arg&&... arg) {
    result_file << a << ',';
    result_print(arg...);
}

// 通过不定长函数 保存参数为csv格式
template <typename... Arg>
void save_result(Arg&&... arg) {
    std::lock_guard<std::mutex> result_guard(result_mutex);
    result_file.open("result.csv", std::ios::app | std::ios::out);
    result_print(arg...);
    result_file.close();
}