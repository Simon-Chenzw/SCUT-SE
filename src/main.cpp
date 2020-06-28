#include <chrono>
#include <functional>
#include <iostream>
#include <memory>
#include <mutex>
#include <thread>
#include "gamecore.h"
#include "log.h"
#include "operator.h"
#include "platform.h"
#include "ui.h"
using namespace std;

// 单个游戏的核心循环 多线程主体 注意检查调用的函数是否会出意外
void game_loop(Operator& oper, const int& thread_num) {
    int running_cnt = 0;
    log("thread ", thread_num, " start.");
    while (!end_flag) {
        Gamecore core;
        core.start_game();
        print_state(core, thread_num);
        while (!end_flag && !core.is_ending()) {
            keyboard.clean_buffer();    //防止非交互式OPER时 无法触发QUIT 无法更新end_flag
            int move_dire = oper.get_moved(core.num);
            if (!end_flag && core.can_move(move_dire)) {
                log("thread: ", thread_num, " move ", move_dire);
                core.moving(move_dire);
                core.add_a_number();
                print_state(core, thread_num);
            }
        }
        print_ending(thread_num);
        if (oper.type == INTERACTIVE_OPER)    //依据OPER是否是交互式 采取不同的行动
            keyboard.get_blocking();
        else
            this_thread::sleep_for(chrono::seconds(1));
        clean_ending(thread_num);
        running_cnt++;
        log("thread ", thread_num, " run ", running_cnt, " times.");
        save_result(core.max_element(), core.step, core.score, oper.name);
    }
    log("thread ", thread_num, " end.");
}

void game() {
    // greeting
    log("game started");
    print_symbol();
    print_greeting();
    keyboard.get_blocking();    // press any key to continue

    int game_form = 0, oper_num = -1 /* -1 means keyboard */, thread_num = 1;
    // 游戏形式选择
    game_form = select_option({"Start Game", "Automatic", "Multi-threaded Automatic"});
    log("game form selected: ", game_form);
    // AI选择
    if (game_form != 0) {
        oper_num = select_option(oper_name_list, "Choose an algorithm");
        log("operator selected: ", oper_name_list[oper_num]);
    }
    // 线程数量选择
    if (game_form == 2) {
        thread_num = get_number("Please enter the number of threads");
        log("threads number get: ", thread_num);
    }
    if (end_flag) {
        print_goodbye();
        return;
    }

    // 启动游戏
    print_state_frame(oper_num == -1 ? "" : oper_name_list[oper_num], thread_num != 1);
    // 创建oper
    vector<unique_ptr<Operator>> opers = oper_generator(oper_num, thread_num);
    // 开启多线程
    vector<thread> threads;
    for (int i = 0; i < thread_num; i++) {
        threads.push_back(thread(game_loop, ref(*opers[i]), i));
        log("thread ", i, " start.");
    }
    // join多线程 即等待游戏结束
    for (int i = 0; i < thread_num; i++) threads[i].join();
    log("all threads ended");
    print_goodbye();
    log("game ended");
}

void init() {
    gamecore_init();
    operator_init();
    log("initialization done");
}

// test module 测试keyboard是否正常工作
void keyboard_test() {
    cout << "keyboard input test, press ESC to exit.\n"
         << "301~304 means arrow keys\n";
    while (!end_flag) {
        int input = keyboard.get_blocking();
        cout << "input = " << input << "   (char)input = " << (char)input << '\n';
    }
}

// test module 测试打表数据的正确性
void board_move_test() {
    cout << "board move test\n"
         << "give four numbers, they will move to the left.\n";
    keyboard.~Keyboard();
    while (!end_flag) {
        int a, b, c, d;
        cin >> a >> b >> c >> d;
        line_change tmp = move_chart[chart_num(a, b, c, d)];
        cout << tmp.after[0] << ' ' << tmp.after[1] << ' ' << tmp.after[2] << ' ' << tmp.after[3] << ' '
             << (tmp.moved ? "moved" : "unmoved") << ' ' << "score:" << tmp.score << '\n';
    }
}

int main() {
    clean_file();
    log("program started.");
    init();
    game();
    // keyboard_test();
    // board_move_test();
    log("program ended.");
}