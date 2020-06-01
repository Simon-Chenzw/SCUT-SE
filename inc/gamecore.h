// 移动方向
#define MOVE_U 1
#define MOVE_D 2
#define MOVE_L 3
#define MOVE_R 4

// 4x4 棋盘
class Board {
  public:
};

// 游戏核心 负责基本操作
class Gamecore {
  public:
    Gamecore();
    void start_game();
    void add_number();
    void moving(const int&);

  private:
    Board board;
};
