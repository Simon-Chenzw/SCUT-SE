#include <cmath>
#include "gamecore.h"
#include "operator.h"

// 声明并定义一个tmp，为old的copy
#define newBoard(tmp, old)                                                                                             \
    Board tmp {                                                                                                        \
        old[0][0], old[0][1], old[0][2], old[0][3], old[1][0], old[1][1], old[1][2], old[1][3], old[2][0], old[2][1],  \
            old[2][2], old[2][3], old[3][0], old[3][1], old[3][2], old[3][3]                                           \
    }

//  0  1  2  3
//  4  5  6  7
//  8  9 10 11
// 12 13 14 15
#define board_num(i) ()

blinkered_oper::blinkered_oper(): Operator("blinkered", NON_INTERACTIVE_OPER) {}

int evaluate(const Board& num, const int dire) {
    newBoard(new_num, num);
    fast_move(new_num, dire);
    // Evaluation =
    // 128 (Constant)
    double point = 128;
    // + (Number of Spaces x 128)
    for (int i = 0; i < 16; i++)
        if (*(&new_num[0][0] + i) == 0) point += 128;
    // + Sum of faces adjacent to a space { (1/face) x 4096 }
    // + Sum of other faces { log(face) x 4 }
    const int f[4][2] = {-1, 0, 0, -1, 1, 0, 0, 1};
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++) {
            if (new_num[i][j] == 0) continue;
            bool near_space = false;
            for (int k = 0; k < 4; k++) {
                int x = i + f[k][0];
                int y = j + f[k][1];
                if (x >= 0 && y >= 0 && x < 4 && y < 4 && new_num[x][y] == 0) {
                    near_space = true;
                    break;
                }
            }
            if (near_space)
                point += 4096.0 / (1 << new_num[i][j]);
            else
                point += 4 * new_num[i][j];
        }
    // + (Number of possible next moves x 256)
    for (int i = 1; i <= 4; i++)
        if (can_move(new_num, i)) point += 256;
    // + (Number of aligned values x 2)
    point += move_score(num, dire);
    return point;
}

int blinkered_oper::get_moved(const Board& num) {
    int ans = 0, max_eval = 0;
    for (int dire = 1; dire <= 4; dire++) {
        if (!can_move(num, dire)) continue;
        int val = evaluate(num, dire);
        if (val > max_eval) {
            max_eval = val;
            ans = dire;
        }
    }
    return ans;
}
