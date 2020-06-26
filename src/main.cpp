#include <chrono>
#include <functional>
#include <mutex>
#include <thread>
#include <dbg_func>
#include "gamecore.h"
#include "log.h"
#include "operator.h"
#include "platform.h"
#include "ui.h"

using namespace std;

void game_loop(Operator& oper, int thread_num) {
    while (!end_flag) {
        Gamecore core;
        core.start_game();
        clean_ending(thread_num);
        print_state(core, thread_num);
        while (!core.is_ending() && !end_flag) {
            keyboard.clean_buffer();
            int move_dire = oper.get_moved(&core);
            if (!end_flag && core.can_move(move_dire)) {
                core.moving(move_dire);
                core.add_a_number();
                print_state(core, thread_num);
            }
        }
        print_ending(thread_num);
        save_result(core.max_element(), core.step, core.score, oper.name);
        if (oper.oper_type == NON_INTERACTIVE_OPER) {
            this_thread::sleep_for(chrono::seconds(1));
        }
        else if (!end_flag)
            keyboard.get_blocking();
    }
}

void game() {
    // greeting
    print_symbol();
    print_greeting();
    keyboard.get_blocking();    // press any key to continue

    int game_form = 0, thread_num = 1;
    string oper_name = "keyboard";
    // 游戏形式选择
    game_form = select_option({"Start Game", "Automatic", "Multi-threaded Automatic"});
    // AI选择
    const vector<string> ai_list = {"random"};
    if (game_form != 0) oper_name = ai_list[select_option(ai_list, "Choose an algorithm")];
    // 线程数量选择
    if (game_form == 2) thread_num = get_number("Please enter the number of threads");

    // 启动游戏
    print_state_frame(oper_name == "keyboard" ? "" : oper_name, thread_num != 1);
    // 创建oper
    vector<Operator*> opers;
    for (int i = 0; i < thread_num; i++) {
        if (oper_name == "keyboard") opers.push_back(new Keyboard_oper);
        if (oper_name == "random") opers.push_back(new Random_oper);
    }
    // 开启多线程
    vector<thread> threads;
    for (int i = 0; i < thread_num; i++) threads.push_back(thread(game_loop, ref(*opers[i]), i));
    // join多线程
    for (int i = 0; i < thread_num; i++) threads[i].join();
    // 销毁oper
    for (int i = 0; i < thread_num; i++) delete opers[i];
    print_goodbye();
}

void keyboard_test() {
    dbg("keyboard input test");
    while (!end_flag) {
        int input = keyboard.get_blocking();
        dbg(input, (char)input);
    }
}

void board_move_test() {
    dbg("board move test");
    keyboard.~Keyboard();
    while (!end_flag) {
        Gamecore core;
        int& a = core.num[0][0];
        int& b = core.num[0][1];
        int& c = core.num[0][2];
        int& d = core.num[0][3];
        cin >> a >> b >> c >> d;
        core.moving(MOVE_L);
        int step = core.step;
        int score = core.score;
        dbg(a, b, c, d, step, score);
    }
}

void log_test() {
    dbg("log test");
    log("log test");
}

int main() {
    game();
    // keyboard_test();
    // board_move_test();
}