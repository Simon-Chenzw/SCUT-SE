#include "gamecore.h"
#include <cstdlib>
#include <vector>

using namespace std;

class line_change {
  public:
    int after[4];
    bool moved;
    int point;
} mem[1 << 20];

auto mem_init = []() {
    for (int i = 0; i < (1 << 20); i++) {
        mem[i].after[0] = i >> 15 & 0b11111;
        mem[i].after[1] = i >> 10 & 0b11111;
        mem[i].after[2] = i >> 5 & 0b11111;
        mem[i].after[3] = i & 0b11111;
        mem[i].moved = false;
        mem[i].point = 0;
        for (int i = 1; i < 4; i++) {
            if (mem[i].after[i] == 0) continue;
            int pos = i;
            while (pos && mem[i].after[pos - 1] == 0) {
                swap(mem[i].after[pos], mem[i].after[pos - 1]);
                pos--;
                mem[i].moved = true;
            }
            if (pos && mem[i].after[pos - 1] == mem[i].after[pos]) {
                mem[i].after[pos - 1]++;
                mem[i].after[pos] = 0;
                mem[i].moved = true;
                mem[i].point += mem[i].after[pos - 1];
            }
        }
    }
    return 0;
}();

inline bool rand_chance(int n) {
    static int check_list[] {
        RAND_MAX,      RAND_MAX,      RAND_MAX / 2,  RAND_MAX / 3,  RAND_MAX / 4,  RAND_MAX / 5,  RAND_MAX / 6,
        RAND_MAX / 7,  RAND_MAX / 8,  RAND_MAX / 9,  RAND_MAX / 10, RAND_MAX / 11, RAND_MAX / 12, RAND_MAX / 13,
        RAND_MAX / 14, RAND_MAX / 15, RAND_MAX / 16, RAND_MAX / 17, RAND_MAX / 18, RAND_MAX / 19,
    };
    return rand() <= check_list[n];
}

// 辅助宏
#define four2one(a, b, c, d) (a << 15 | b << 10 | c << 5 | d)    //获取mem的序号

//获取mem的序号
#define line_u(i) four2one(num[0][i], num[1][i], num[2][i], num[3][i])    //向上移动
#define line_d(i) four2one(num[3][i], num[2][i], num[1][i], num[0][i])    //向下移动
#define line_l(i) four2one(num[i][0], num[i][1], num[i][2], num[i][3])    //向左移动
#define line_r(i) four2one(num[i][3], num[i][2], num[i][1], num[i][0])    //向右移动

Board::Board() {
    for (int i = 0; i < 16; i++) *(&num[0][0] + i) = 0;
}

int Board::get_point(const int& dire) const {
    bool point = 0;
    if (dire == MOVE_U)
        for (int i = 0; i < 4; i++) point += mem[line_u(i)].point;
    else if (dire == MOVE_D)
        for (int i = 0; i < 4; i++) point += mem[line_d(i)].point;
    else if (dire == MOVE_L)
        for (int i = 0; i < 4; i++) point += mem[line_l(i)].point;
    else if (dire == MOVE_R)
        for (int i = 0; i < 4; i++) point += mem[line_r(i)].point;
    return point;
}

bool Board::can_move(const int& dire) const {
    bool can_move = false;
    if (dire == MOVE_U)
        for (int i = 0; i < 4; i++) can_move |= mem[line_u(i)].moved;
    else if (dire == MOVE_D)
        for (int i = 0; i < 4; i++) can_move |= mem[line_d(i)].moved;
    else if (dire == MOVE_L)
        for (int i = 0; i < 4; i++) can_move |= mem[line_l(i)].moved;
    else if (dire == MOVE_R)
        for (int i = 0; i < 4; i++) can_move |= mem[line_r(i)].moved;
    return can_move;
}

Board Board::get_move(const int& dire) const {
    Board ans(*this);
    ans.moving(dire);
    return ans;
}

void Board::moving(const int& dire) {
    int point = 0;
    if (dire == MOVE_U)
        for (int i = 0; i < 4; i++) {
            int ord = line_u(i);
            for (int j = 0; j < 4; j++) num[j][i] = mem[ord].after[j];
        }
    else if (dire == MOVE_D)
        for (int i = 0; i < 4; i++) {
            int ord = line_d(i);
            for (int j = 0; j < 4; j++) num[3 - j][i] = mem[ord].after[j];
        }
    else if (dire == MOVE_L)
        for (int i = 0; i < 4; i++) {
            int ord = line_l(i);
            for (int j = 0; j < 4; j++) num[i][j] = mem[ord].after[j];
        }
    else if (dire == MOVE_R)
        for (int i = 0; i < 4; i++) {
            int ord = line_r(i);
            for (int j = 0; j < 4; j++) num[3 - j][i] = mem[ord].after[j];
        }
}

#define board_num(i) (*(&board.num[0][0] + i))

Gamecore::Gamecore(): step(0), point(0), board() {}

void Gamecore::start_game() {
    step = 0;
    point = 0;
    board = Board();
    add_a_number();
    add_a_number();
}

bool Gamecore::have_empty() const {
    for (int i = 0; i < 16; i++)
        if (board_num(i) == 0) return true;
    return false;
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
    return board.can_move(dire);
}

bool Gamecore::moving(const int& dire) {
    if (board.can_move(dire)) {
        step++;
        point += board.get_point(dire);
        board.moving(dire);
        return true;
    }
    else
        return false;
}