#include "gamecore.h"
#include "operator.h"

upmove_oper::upmove_oper(): Operator("moveUP", NON_INTERACTIVE_OPER) {}

int upmove_oper::get_moved(const Board& num) {
    int dire = MOVE_U;
    if (can_move(num, MOVE_U)) {
        if (can_move(num, MOVE_L) && can_move(num, MOVE_R)) {
            Gamecore core_lu;
            Gamecore core_ru;
            for (int i = 0; i < 4; i++)
                for (int j = 0; j < 4; j++) {
                    core_lu.num[i][j] = num[i][j];
                    core_ru.num[i][j] = num[i][j];
                }
            core_lu.moving(MOVE_L);
            core_lu.moving(MOVE_U);
            core_ru.moving(MOVE_R);
            core_ru.moving(MOVE_U);
            int cnt_lu = 0, cnt_ru = 0;
            for (int i = 0; i < 4; i++)
                for (int j = 0; j < 4; j++) {
                    if (core_lu.num[i][j] == 0) cnt_lu++;
                    if (core_ru.num[i][j] == 0) cnt_ru++;
                }
            if (cnt_lu > cnt_ru)
                dire = MOVE_L;
            else
                dire = MOVE_R;
        }
        else if (can_move(num, MOVE_L)) {
            dire = MOVE_L;
        }
        else if (can_move(num, MOVE_R)) {
            dire = MOVE_R;
        }
        else {
            dire = MOVE_D;
        }
    }
    return dire;
}
