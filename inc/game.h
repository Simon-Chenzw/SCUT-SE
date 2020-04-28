#include "header.h"

// 1/n 的概率返回true (n<20)
inline bool rand_chance(int n) {
    static int check_list[] {
        RAND_MAX,      RAND_MAX,      RAND_MAX / 2,  RAND_MAX / 3,  RAND_MAX / 4,  RAND_MAX / 5,  RAND_MAX / 6,
        RAND_MAX / 7,  RAND_MAX / 8,  RAND_MAX / 9,  RAND_MAX / 10, RAND_MAX / 11, RAND_MAX / 12, RAND_MAX / 13,
        RAND_MAX / 14, RAND_MAX / 15, RAND_MAX / 16, RAND_MAX / 17, RAND_MAX / 18, RAND_MAX / 19,
    };
    return rand() <= check_list[n];
}

inline int get_state(const int& a, const int& b, const int& c, const int& d) {
    return (a << 12) + (b << 8) + (c << 4) + d;
}

inline void set_state(const int& i, int& a, int& b, int& c, int& d) {
    a = i >> 12 & 0b1111;
    b = i >> 8 & 0b1111;
    c = i >> 4 & 0b1111;
    d = i & 0b1111;
}

class move_states {
  public:
    int new_state;
    int step;
    int score;
};

//打表记录一行的每种情况 向左移动
vector<move_states> moving_map;

void make_moving_map(vector<move_states>& moving_map);

class Game {
  public:
    //初始化 赋初始值
    Game();

    //开始游戏 并添加两个数字
    void start();

    //添加一个数字
    void add_num();

    // 检查是不是lose
    void end();

    //获取棋盘状态
    State state();

    void set_state();

    void moving_up();
    void moving_down();
    void moving_left();
    void moving_right();

    //通过幂的形式记录地图
    int game_map[16];

    //记录分数
    int score;

    //记录移动步数
    int step;

    //记录比赛结束的标记
    bool lose;

    //本局游戏的srand代码
    clock_t seed;
};