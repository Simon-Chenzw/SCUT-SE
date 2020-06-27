#pragma once

#include <fstream>
#include <mutex>
#include <sstream>
#include <string>

void clean_file();

// log part
extern std::fstream log_file;
extern std::mutex log_mutex;

// 记录log 包含file line func等信息
// [bug] log()不要用于lambda和template中 也不要空参调用
#define log(arg...) save_log(log_head(__FILE__, __LINE__, __func__), ##arg)

// 内联函数 处理输出格式
inline std::string log_head(const std::string& file, const int& line, const std::string& func) {
    std::stringstream ss;
    ss << '[' << file << ':' << line << ' ' << '(' << func << ')' << ']' << ' ';
    return ss.str();
}

// 不定长函数递归终点
inline void log_print(std::fstream& fout) {
    fout << '\n';
}

// 不定长函数递归过程
template <typename T, typename... Arg>
void log_print(std::fstream& fout, T&& a, Arg&&... arg) {
    fout << a;
    log_print(fout, arg...);
}

// 通过不定长函数 保存参数至log.txt
template <typename... Arg>
void save_log(Arg&&... arg) {
    std::lock_guard<std::mutex> result_guard(log_mutex);
    log_file.open("log.txt", std::ios::app | std::ios::out);
    log_print(log_file, arg...);
    log_file.close();
}

// result part
extern std::fstream result_file;
extern std::mutex result_mutex;

// 不定长函数递归终点
template <typename T>
void result_print(std::fstream& fout, T&& a) {
    fout << a << '\n';
}

// 不定长函数递归过程
template <typename T, typename... Arg>
void result_print(std::fstream& fout, T&& a, Arg&&... arg) {
    fout << a << ',';
    result_print(fout, arg...);
}

// 通过不定长函数 保存参数为csv格式
template <typename... Arg>
void save_result(Arg&&... arg) {
    std::lock_guard<std::mutex> result_guard(result_mutex);
    result_file.open("result.csv", std::ios::app | std::ios::out);
    result_print(result_file, arg...);
    result_file.close();
}