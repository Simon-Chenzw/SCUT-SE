// 移动方向
#define MOVE_U 1
#define MOVE_D 2
#define MOVE_L 3
#define MOVE_R 4

// 4x4 棋盘
// number[i][j] 第i行第j个 左上角为源点
class Board {
  public:
    Board();
    int get_point(const int&) const;
    bool can_move(const int&) const;
    Board get_move(const int&) const;
    void moving(const int&);
    int num[4][4];
};

// 游戏核心 负责基本操作
class Gamecore {
  public:
    Gamecore();
    void start_game();
    bool have_empty() const;
    bool add_a_number();
    bool can_move(const int&) const;
    bool moving(const int&);

    int step;
    int point;
    Board board;
};
