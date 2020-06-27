#include "ui.h"
#include <iostream>
#include <mutex>
#include <string>
#include "platform.h"

using namespace std;

const int row = 50;
const int col = 83;

// 彩色字符串 operator<< 时会自动处理颜色设定
class colorful_string {
  public:
    int clr_front, clr_back;
    string str;
    colorful_string(): clr_front(CLR_RESET), clr_back(CLR_RESET), str() {}
    colorful_string(const string& _str, const int& front = CLR_RESET, const int& back = CLR_RESET):
          clr_front(front),
          clr_back(back),
          str(_str) {}
    friend ostream& operator<<(ostream& out, const colorful_string& rhs) {
        if (rhs.clr_front != CLR_RESET) setcolor(rhs.clr_front);
        if (rhs.clr_back != CLR_RESET) setcolor(rhs.clr_back);
        out << rhs.str;
        resetcolor();
    }
};

inline void middle_print(const string& str, const int& line) {
    set_cursor_position(line, col / 2 - str.length() / 2);
    cout << str;
}

inline void middle_print(const colorful_string& cstr, const int& line) {
    set_cursor_position(line, col / 2 - cstr.str.length() / 2);
    cout << cstr;
}

string int2str(int val, int width = 0) {
    string ans = val ? "" : "0";
    while (val) {
        ans = char(val % 10 + '0') + ans;
        val /= 10;
    }
    while ((int)ans.length() < width) ans = ' ' + ans;
    return ans;
}

const string heading[9] = {R"(    /\\\\\\\\\          /\\\\\\\                /\\\         /\\\\\\\\\           )",
                           R"(   /\\\///////\\\      /\\\/////\\\            /\\\\\       /\\\///////\\\        )",
                           R"(   \///      \//\\\    /\\\    \//\\\         /\\\/\\\      \/\\\     \/\\\       )",
                           R"(              /\\\/    \/\\\     \/\\\       /\\\/\/\\\      \///\\\\\\\\\/       )",
                           R"(            /\\\//      \/\\\     \/\\\     /\\\/  \/\\\       /\\\///////\\\     )",
                           R"(          /\\\//         \/\\\     \/\\\   /\\\\\\\\\\\\\\\\   /\\\      \//\\\   )",
                           R"(         /\\\/            \//\\\    /\\\   \///////////\\\//   \//\\\      /\\\   )",
                           R"(         /\\\\\\\\\\\\\\\   \///\\\\\\\/              \/\\\      \///\\\\\\\\\/   )",
                           R"(         \///////////////      \///////                \///         \/////////    )"};

void print_symbol() {
    clean_screen();
    for (int i = 0; i < 9; i++) {
        set_cursor_position(4 + i);
        cout << heading[i];
    }
}

void print_greeting() {
    print_symbol();
    middle_print(colorful_string("press any key to continue", CLR_CYAN), 21);
    middle_print(colorful_string("Tips: Press esc to exit at any time", CLR_MAGENTA), 26);
}

int select_option(const vector<string>& vec, const std::string& message) {
    const int srow = 21;
    if (vec.size() == 0) return 0;
    print_symbol();
    keyboard.clean_buffer();
    int selected = 0;
    if (message != "") middle_print(message, srow - 2);
    while (!end_flag) {
        for (int i = 0; i < (int)vec.size(); i++)
            middle_print(i == selected ? colorful_string(vec[i], CLR_GREEN) : vec[i], srow + i);
        int input = keyboard.get_blocking();
        if (IS_U(input) && selected != 0) selected--;
        if (IS_D(input) && selected != (int)vec.size() - 1) selected++;
        if (input == ENTER) {
            print_symbol();
            return selected;
        }
    }
    return 0;    //触发了end_flag
}

int get_number(const std::string& message) {
    print_symbol();
    int num = 0;
    middle_print(message, 21);
    while (!end_flag) {
        string line = num ? int2str(num) : "";
        while (line.length() < 10) line = line + '_';
        middle_print(line, 23);
        int input = keyboard.get_blocking();
        if (input >= '0' && input <= '9') num = num * 10 + input - '0';
        if (input == BACKSPACE) num /= 10;
        if (input == ENTER && num != 0) return num;
    }
    return 0;    //触发了end_flag
}

// ┌┬┐├┼┤└┴┘─│      131072
// ┌───────┬───────┬───────┬───────┐
// │ 65536 ‬│ 32768 │ 16384 │  8192 │
// │───────┼───────┼───────┼───────┤
// │  4096 ‬│  2048 │  1024 │   512 │
// │───────┼───────┼───────┼───────┤
// │   256 ‬│   128 │    64 │    32 │
// │───────┼───────┼───────┼───────┤
// │    16 ‬│     8 │     4 │     2 │
// └───────┴───────┴───────┴───────┘

const int frame_row = 20, frame_col = 15;
const string frame[9] = {"┌───────┬───────┬───────┬───────┐",
                         "│       ‬│       │       │       │",
                         "│───────┼───────┼───────┼───────┤",
                         "│       ‬│       │       │       │",
                         "│───────┼───────┼───────┼───────┤",
                         "│       ‬│       │       │       │",
                         "│───────┼───────┼───────┼───────┤",
                         "│       ‬│       │       │       │",
                         "└───────┴───────┴───────┴───────┘"};
bool multi;
void print_state_frame(const string& oper_name, bool multithread) {
    print_symbol();
    multi = multithread;
    if (!multi) {
        for (int i = 0; i < 9; i++) {
            set_cursor_position(frame_row + i, frame_col);
            cout << frame[i];
        }
        if (oper_name != "") {
            set_cursor_position(frame_row + 1, frame_col + 40);
            cout << "algorithm: " << oper_name;
        }
        set_cursor_position(frame_row + 3, frame_col + 40);
        cout << "steps:";
        set_cursor_position(frame_row + 5, frame_col + 40);
        cout << "score:";
    }
    else {
        if (oper_name != "") {
            set_cursor_position(frame_row - 4, frame_col - 2);
            cout << "algorithm: " << oper_name;
        }
    }
}

// print时共用的锁 防止多线程冲突
mutex print_mutex;

int running_time = 0, max_num = 1;
void print_state(const Gamecore& core, int thread_num) {
    if (!multi) {
        const string pow[] = {
            "       ", "     2 ", "     4 ", "     8 ", "    16 ", "    32 ", "    64 ",
            "   128 ", "   256 ", "   512 ", "  1024 ", "  2048 ", "  4096 ", "  8192 ",
            " 16384 ", " 32768 ", " 65536 ", "131072 ", "262144 ", "524288 ", "1048576",
        };
        for (int i = 0; i < 4; i++)
            for (int j = 0; j < 4; j++) {
                set_cursor_position(frame_row + 2 * i + 1, frame_col + 8 * j + 1);
                cout << pow[core.num[i][j]];
            }
        set_cursor_position(frame_row + 3, frame_col + 46);
        cout << int2str(core.step, 4);
        set_cursor_position(frame_row + 5, frame_col + 46);
        cout << int2str(core.score, 4);
    }
    else {
        lock_guard<mutex> guard(print_mutex);
        int cnt[25] = {};
        for (int i = 0; i < 4; i++)
            for (int j = 0; j < 4; j++) cnt[core.num[i][j]]++;
        if (cnt[max_num + 1]) {
            max_num++;
            set_cursor_position(frame_row - 3, frame_col - 2);
            cout << "maximum: " << (1 << max_num);
        }
        set_cursor_position(frame_row + thread_num, frame_col);
        for (int i = 20; i > 0; i--) {
            const char ch[20] = "0123456789ABCDEFGHI";
            cout << ch[cnt[i]];
            if (i % 5 == 1) cout.put(' ');
        }
    }
}

//注意多线程
void print_ending(const int& thread_num) {
    if (!multi) {
        middle_print(colorful_string("Sorry, it seems it can't move anymore", CLR_RED), frame_row + 10);
        middle_print(colorful_string("Press any key to try again", CLR_CYAN), frame_row + 12);
        middle_print(colorful_string("Press esc to exit", CLR_MAGENTA), frame_row + 14);
    }
    else {
        lock_guard<mutex> guard(print_mutex);
        running_time++;
        set_cursor_position(frame_row - 2, frame_col - 2);
        cout << "running times: " << running_time;
        set_cursor_position(frame_row + thread_num, frame_col + 40);
        cout << colorful_string("Dead", CLR_RED);
    }
}

//注意多线程
void clean_ending(const int& thread_num) {
    if (!multi) {
        middle_print("                                     ", frame_row + 10);
        middle_print("                          ", frame_row + 12);
        middle_print("                 ", frame_row + 14);
    }
    else {
        lock_guard<mutex> guard(print_mutex);
        set_cursor_position(frame_row + thread_num, frame_col + 40);
        cout << "    ";
    }
}

void print_goodbye() {
    print_symbol();
    middle_print(colorful_string("Have a great day!", CLR_BLUE), 18);
    // set cursor when program ending
    set_cursor_position(22);
}