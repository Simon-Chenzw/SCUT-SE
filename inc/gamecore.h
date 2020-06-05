#include <vector>

// 移动方向
#define MOVE_U 1
#define MOVE_D 2
#define MOVE_L 3
#define MOVE_R 4

// 4x4 棋盘
class Board {
  public:
    class line_change {
      public:
        int after[4];
        bool moved;
        int point;
    };

    // 预处理打表 向前移动
    static std::vector<line_change> mem;

    bool can_move(const int&) const;
    Board get_move(const int&) const;
    void moving(const int&) const;
    int number[4][4];
};

// 游戏核心 负责基本操作
class Gamecore {
  public:
    Gamecore();
    void start_game();
    void add_a_number();
    void moving(const int&);
    void can_move(const int&);

    int point;
    int step;
    Board board;
};
