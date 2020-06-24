#include <thread>
#include <dbg_func>
#include "gamecore.h"
#include "log.h"
#include "operator.h"
#include "platform.h"
#include "ui.h"

using namespace std;

void game_main(Operator& input, int thread_num) {
    Gamecore core;
    // 无AI的情况下 暂且这样
    core.start_game();
    print_state_frame();
    print_state(core, thread_num);
    while (!core.is_ending() && !end_flag) {
        int move_dire = input.get_moved(&core.board);
        if (!end_flag && core.can_move(move_dire)) {
            core.moving(move_dire);
            core.add_a_number();
            print_state(core, thread_num);
        }
    }
    print_ending(core);
    print_result(core, input);
}

void starting() {
    Keyboard_oper keyboard_oper(keyboard);

    print_symbol();
    print_greeting();
    keyboard.get_blocking();    // press any key to continue

    game_main(keyboard_oper, 1);
}

void keyboard_test() {
    while (!end_flag) {
        int input = keyboard.get_blocking();
        dbg(input, (char)input);
    }
}

void board_move_test() {
    keyboard.~Keyboard();
    while (!end_flag) {
        int a, b, c, d;
        cin >> a >> b >> c >> d;
        Board board;
        board.num[0][0] = a;
        board.num[0][1] = b;
        board.num[0][2] = c;
        board.num[0][3] = d;
        board.moving(MOVE_L);
        cout << board.num[0][0] << ' ' << board.num[0][1] << ' ' << board.num[0][2] << ' ' << board.num[0][3] << "\n\n";
    }
}

int main() {
    starting();
    print_goodbye();
    // keyboard_test();
    // board_move_test();
}