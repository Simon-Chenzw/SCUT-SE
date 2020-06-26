#include "gamecore.h"
#include <cstdlib>
using namespace std;

line_change memory[1 << 20];

// 自动初始化memory
auto memory_init = []() {
    for (int i = 0; i < (1 << 20); i++) {
        bool is_new[4] = {false, false, false, false};
        memory[i].after[0] = i >> 15 & 0b11111;
        memory[i].after[1] = i >> 10 & 0b11111;
        memory[i].after[2] = i >> 5 & 0b11111;
        memory[i].after[3] = i & 0b11111;
        memory[i].moved = false;
        memory[i].score = 0;
        for (int j = 1; j < 4; j++) {
            if (memory[i].after[j] == 0) continue;
            int pos = j;
            while (pos && memory[i].after[pos - 1] == 0) {
                memory[i].after[pos - 1] = memory[i].after[pos];
                memory[i].after[pos] = 0;
                pos--;
                memory[i].moved = true;
            }
            if (pos && memory[i].after[pos - 1] == memory[i].after[pos] && !is_new[pos - 1]) {
                is_new[pos - 1] = true;
                memory[i].after[pos - 1]++;
                memory[i].after[pos] = 0;
                memory[i].moved = true;
                memory[i].score += 1 << memory[i].after[pos - 1];
            }
        }
    }
    return 0;
}();

// 1/n的概率返回true
inline bool rand_chance(int n) {
    static int check_list[] {
        RAND_MAX,      RAND_MAX,      RAND_MAX / 2,  RAND_MAX / 3,  RAND_MAX / 4,  RAND_MAX / 5,  RAND_MAX / 6,
        RAND_MAX / 7,  RAND_MAX / 8,  RAND_MAX / 9,  RAND_MAX / 10, RAND_MAX / 11, RAND_MAX / 12, RAND_MAX / 13,
        RAND_MAX / 14, RAND_MAX / 15, RAND_MAX / 16, RAND_MAX / 17, RAND_MAX / 18, RAND_MAX / 19,
    };
    return rand() <= check_list[n];
}

// 辅助宏

//获取mem的序号
#define line_u(i) mem_num(num[0][i], num[1][i], num[2][i], num[3][i])    //向上移动
#define line_d(i) mem_num(num[3][i], num[2][i], num[1][i], num[0][i])    //向下移动
#define line_l(i) mem_num(num[i][0], num[i][1], num[i][2], num[i][3])    //向左移动
#define line_r(i) mem_num(num[i][3], num[i][2], num[i][1], num[i][0])    //向右移动

// 判断是否移动
#define move_bool(a, b, c, d) (memory[a].moved || memory[b].moved || memory[c].moved || memory[d].moved)

//获取移动分数
#define score_get(a, b, c, d) (memory[a].score + memory[b].score + memory[c].score + memory[d].score)

#define can_move_u move_bool(line_u(0), line_u(1), line_u(2), line_u(3))    //向上移动
#define can_move_d move_bool(line_d(0), line_d(1), line_d(2), line_d(3))    //向下移动
#define can_move_l move_bool(line_l(0), line_l(1), line_l(2), line_l(3))    //向左移动
#define can_move_r move_bool(line_r(0), line_r(1), line_r(2), line_r(3))    //向右移动

Gamecore::Gamecore(): step(0), score(0) {
    for (int i = 0; i < 16; i++) board_num(i) = 0;
}

void Gamecore::start_game() {
    add_a_number();
    add_a_number();
}

bool Gamecore::add_a_number() {
    int pos = -1, cnt = 0;
    for (int i = 0; i < 16; i++)
        if (board_num(i) == 0)
            if (rand_chance(++cnt)) pos = i;
    if (pos != -1) {
        board_num(pos) = (rand_chance(10) ? 2 : 1);
        return true;
    }
    else
        return false;
}

bool Gamecore::can_move(const int& dire) const {
    if (dire == MOVE_U)
        return can_move_u;
    else if (dire == MOVE_D)
        return can_move_d;
    else if (dire == MOVE_L)
        return can_move_l;
    else if (dire == MOVE_R)
        return can_move_r;
}

void Gamecore::moving(const int& dire) {
    if (dire == MOVE_U) {
        if (can_move_u) {
            step++;
            score += score_get(line_u(0), line_u(1), line_u(2), line_u(3));
            for (int i = 0; i < 4; i++) {
                int ord = line_u(i);
                for (int j = 0; j < 4; j++) num[j][i] = memory[ord].after[j];
            }
        }
    }
    else if (dire == MOVE_D) {
        if (can_move_d) {
            step++;
            score += score_get(line_d(0), line_d(1), line_d(2), line_d(3));
            for (int i = 0; i < 4; i++) {
                int ord = line_d(i);
                for (int j = 0; j < 4; j++) num[3 - j][i] = memory[ord].after[j];
            }
        }
    }
    else if (dire == MOVE_L) {
        if (can_move_l) {
            step++;
            score += score_get(line_l(0), line_l(1), line_l(2), line_l(3));
            for (int i = 0; i < 4; i++) {
                int ord = line_l(i);
                for (int j = 0; j < 4; j++) num[i][j] = memory[ord].after[j];
            }
        }
    }
    else if (dire == MOVE_R) {
        if (can_move_r) {
            step++;
            score += score_get(line_r(0), line_r(1), line_r(2), line_r(3));
            for (int i = 0; i < 4; i++) {
                int ord = line_r(i);
                for (int j = 0; j < 4; j++) num[i][3 - j] = memory[ord].after[j];
            }
        }
    }
}

bool Gamecore::is_ending() const {
    return !can_move(MOVE_U) && !can_move(MOVE_D) && !can_move(MOVE_L) && !can_move(MOVE_R);
}

int Gamecore::max_element() const {
    int ans = 0;
    for (int i = 0; i < 16; i++)
        if (board_num(i) > ans) ans = board_num(i);
    return ans;
}