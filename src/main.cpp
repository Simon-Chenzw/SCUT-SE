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

// 单个游戏的核心循环 多线程主体
void game_loop(Operator& oper, int thread_num) {
    int running_cnt = 0;
    log("thread ", thread_num, " start.");
    while (!end_flag) {
        Gamecore core;
        core.start_game();
        print_state(core, thread_num);
        while (!end_flag && !core.is_ending()) {
            keyboard.clean_buffer();    //防止非交互式OPER时 无法触发QUIT 无法更新end_flag
            int move_dire = oper.get_moved(&core);
            if (!end_flag && core.can_move(move_dire)) {
                core.moving(move_dire);
                core.add_a_number();
                print_state(core, thread_num);
            }
        }
        print_ending(thread_num);
        save_result(core.max_element(), core.step, core.score, oper.name);
        if (oper.oper_type == INTERACTIVE_OPER)    //依据OPER是否是交互式 采取不同的行动
            keyboard.get_blocking();
        else
            this_thread::sleep_for(chrono::seconds(1));
        clean_ending(thread_num);
        running_cnt++;
        log("thread ", thread_num, " run ", running_cnt, " times.");
    }
    log("thread ", thread_num, " end.");
}

void game() {
    // greeting
    log("program start");
    print_symbol();
    print_greeting();
    keyboard.get_blocking();    // press any key to continue

    int game_form = 0, thread_num = 1;
    string oper_name = "keyboard";
    // 游戏形式选择
    game_form = select_option({"Start Game", "Automatic", "Multi-threaded Automatic"});
    log("game form selected: ", game_form);
    // AI选择
    const vector<string> ai_list = {"random"};
    if (game_form != 0) {
        oper_name = ai_list[select_option(ai_list, "Choose an algorithm")];
        log("operator name selected: ", oper_name);
    }
    // 线程数量选择
    if (game_form == 2) {
        thread_num = get_number("Please enter the number of threads");
        log("threads number get: ", thread_num);
    }

    // 启动游戏
    print_state_frame(oper_name == "keyboard" ? "" : oper_name, thread_num != 1);
    // 创建oper
    vector<Operator*> opers;
    for (int i = 0; i < thread_num; i++) {
        if (oper_name == "keyboard") opers.push_back(new Keyboard_oper);
        if (oper_name == "random") opers.push_back(new Random_oper);
        log("operator ", i, " created.");
    }
    // 开启多线程
    vector<thread> threads;
    for (int i = 0; i < thread_num; i++) {
        threads.push_back(thread(game_loop, ref(*opers[i]), i));
        log("thread ", i, " start.");
    }
    // join多线程 即等待游戏结束
    for (int i = 0; i < thread_num; i++) threads[i].join();
    log("all threads ended");
    // 销毁oper
    for (int i = 0; i < thread_num; i++) delete opers[i];
    log("all operators deleted");
    print_goodbye();
    log("goodbye message printed");
}

// 测试keyboard
void keyboard_test() {
    dbg("keyboard input test");
    while (!end_flag) {
        int input = keyboard.get_blocking();
        dbg(input, (char)input);
    }
}

// 测试打表数据的正确性
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

// 测试log是否正常运作
void log_test() {
    dbg("log test");
    log("log test");
}

int main() {
    game();
    // keyboard_test();
    // board_move_test();
    // log_test();
    log("program ended.");
}