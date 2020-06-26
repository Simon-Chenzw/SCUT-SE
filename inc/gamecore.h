#pragma once

// 移动方向
#define MOVE_U 1
#define MOVE_D 2
#define MOVE_L 4
#define MOVE_R 3

// 打表记录移动
class line_change {
  public:
    int after[4];
    bool moved;
    int score;
};
extern line_change mem[1 << 20];

// 游戏核心 负责基本操作
class Gamecore {
  public:
    Gamecore();
    void start_game();
    bool add_a_number();
    bool can_move(const int&) const;
    void moving(const int&);
    bool is_ending() const;
    int max_element() const;

    int step;
    int score;
    int num[4][4];
};
