#pragma once

// 移动方向
#define MOVE_U 1
#define MOVE_D 2
#define MOVE_L 4
#define MOVE_R 3

// 移动后的结果，初始状态由move_chart的编号决定
class line_change {
  public:
    int after[4];
    bool moved;
    int score;
};

#define mem_num(a, b, c, d) (a << 15 | b << 10 | c << 5 | d)    // 获取move_chart的序号
// 打表记录移动： a, b, c, d 向左移动的结果为 move_chart[mem_num(a,b,c,d)]
extern line_change move_chart[1 << 20];

// 游戏核心 负责基本操作
class Gamecore {
  public:
    Gamecore();
    void start_game();                  // 开始游戏 即添加两个数字
    bool add_a_number();                // 添加数字 成功返回true
    bool can_move(const int&) const;    // 能否向指定方向移动
    void moving(const int&);            // 向指定方向移动 内含能否移动的判断
    bool is_ending() const;             // 游戏是否结束 即四个方向都无法移动
    int max_element() const;            // 返回num[4][4]中的最大值

    int step;
    int score;
    int num[4][4];
};