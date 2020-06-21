#include "gamecore.h"
#include "log.h"
#include "operator.h"
#include "platform.h"
#include "ui.h"

void game_main(Operator& input, int thread_num) {
    Gamecore core;
    // 无AI的情况下 暂且这样
    core.start_game();
    print_state(core, thread_num);
    while (!core.is_ending()) {
        int move_dire = input.get_moved(&core.board);
        if (core.can_move(move_dire)) {
            core.moving(move_dire);
            core.add_a_number();
            print_state(core, thread_num);
        }
    }
    print_ending(core);
    print_result(core, input);
}

void starting() {
    terminal_init();
    Keyboard_oper keyboard;

    press_anykey();
    keyboard.get_keyboard();    // press any key to continue

    game_main(keyboard, 1);
}