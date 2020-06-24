#include "ui.h"
// #include <cstdio>
#include <iostream>
#include <mutex>
#include <string>
#include "platform.h"
#warning UI not done yet

using namespace std;

const int row = 100;
const int col = 100;

class coloful_string {
  public:
    int clr_front, clr_back;
    string str;
    coloful_string(): clr_front(CLR_RESET), clr_back(CLR_RESET), str() {}
    coloful_string(const string& _str, const int& front = CLR_RESET, const int& back = CLR_RESET):
          clr_front(front),
          clr_back(back),
          str(_str) {}
    friend ostream& operator<<(ostream& out, const coloful_string& rhs) {
        if (rhs.clr_front != CLR_RESET) setcolor(rhs.clr_front);
        if (rhs.clr_back != CLR_RESET) setcolor(rhs.clr_back);
        out << rhs.str;
        resetcolor();
    }
};

const string heading[9] = {R"(      /\\\\\\\\\          /\\\\\\\                /\\\         /\\\\\\\\\             )",
                           R"(     /\\\///////\\\      /\\\/////\\\            /\\\\\       /\\\///////\\\          )",
                           R"(     \///      \//\\\    /\\\    \//\\\         /\\\/\\\      \/\\\     \/\\\         )",
                           R"(                /\\\/    \/\\\     \/\\\       /\\\/\/\\\      \///\\\\\\\\\/         )",
                           R"(              /\\\//      \/\\\     \/\\\     /\\\/  \/\\\       /\\\///////\\\       )",
                           R"(            /\\\//         \/\\\     \/\\\   /\\\\\\\\\\\\\\\\   /\\\      \//\\\     )",
                           R"(           /\\\/            \//\\\    /\\\   \///////////\\\//   \//\\\      /\\\     )",
                           R"(           /\\\\\\\\\\\\\\\   \///\\\\\\\/              \/\\\      \///\\\\\\\\\/     )",
                           R"(           \///////////////      \///////                \///         \/////////      )"};

void print_symbol() {
    clean_screen();
    for (int i = 0; i < 9; i++) {
        set_cursor_position(4 + i);
        cout << heading[i];
    }
}

void print_greeting() {
    print_symbol();
    set_cursor_position(21, 32);
    cout << coloful_string("press any key to continue", CLR_CYAN);
    set_cursor_position(26, 27);
    cout << coloful_string("Tips: Press esc to exit at any time", CLR_MAGENTA);
}

int select_option(const vector<string>& vec) {
    if (vec.size() == 0) return 0;
    print_symbol();
    keyboard.clean_buffer();
    int selected = 0;
    while (true) {
        for (int i = 0; i < (int)vec.size(); i++) {
            set_cursor_position(15 + i, 50 - vec[i].length() / 2);
            if (i == selected)
                cout << coloful_string(vec[i], CLR_BLACK, CLR_ON_WHITE);
            else
                cout << vec[i];
        }
        int input = keyboard.get_blocking();
        if (input == ENTER) {
            print_symbol();
            return selected;
        }
        if (IS_U(input) && selected != 0) selected--;
        if (IS_D(input) && selected != (int)vec.size() - 1) selected++;
    }
    return 0;
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

bool multi;
mutex print_state_mutex;

const int frame_row = 17, frame_col = 17;

void print_state_frame(bool multithread) {
    print_symbol();
    multi = multithread;
    if (!multi) {
        const string frame[] = {"┌───────┬───────┬───────┬───────┐",
                                "│       ‬│       │       │       │",
                                "│───────┼───────┼───────┼───────┤",
                                "│       ‬│       │       │       │",
                                "│───────┼───────┼───────┼───────┤",
                                "│       ‬│       │       │       │",
                                "│───────┼───────┼───────┼───────┤",
                                "│       ‬│       │       │       │",
                                "└───────┴───────┴───────┴───────┘"};
        for (int i = 0; i < 9; i++) {
            set_cursor_position(frame_row + i, frame_col);
            cout << frame[i];
        }
        set_cursor_position(frame_row + 3, frame_col + 40);
        cout << "steps:";
        set_cursor_position(frame_row + 5, frame_col + 40);
        cout << "score:";
    }
    else {
    }
}

string int2str(int val, int width = 0) {
    string ans = "";
    while (val) {
        ans = char(val % 10 + '0') + ans;
        val /= 10;
    }
    while ((int)ans.length() < width) ans = ' ' + ans;
    return ans;
}

//注意多线程
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
                cout << pow[core.board.num[i][j]];
            }
        set_cursor_position(frame_row + 3, frame_col + 46);
        cout << int2str(core.step, 4);
        set_cursor_position(frame_row + 5, frame_col + 46);
        cout << int2str(core.score, 4);
    }
    else {
        lock_guard<mutex> guard(print_state_mutex);
    }
    // cout << "state start" << ' ' << thread_num << ' ' << core.step << ' ' << core.point << '\n';
    // for (int i = 0; i < 4; i++)
    //     for (int j = 0; j < 4; j++) cout << core.board.num[i][j] << " \n"[j == 3];
    // cout << '\n';
}

void print_ending(const Gamecore&) {
    if (!multi) {
        set_cursor_position(28, 27);
        cout << coloful_string("Sorry, it seems you can't move anymore", CLR_RED);
        set_cursor_position(31, 34);
        cout << coloful_string("Press any key to try again", CLR_CYAN);
        set_cursor_position(34, 39);
        cout << coloful_string("Press esc to exit", CLR_MAGENTA);
    }
    else {
    }
}

void print_goodbye() {
    print_symbol();
    set_cursor_position(18, 34);
    cout << coloful_string("Have a great day!", CLR_BLUE);
    // set cursor when program ending
    set_cursor_position(22);
}