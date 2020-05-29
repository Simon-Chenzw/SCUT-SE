// 移动方向
#define MOVE_U 1
#define MOVE_D 2
#define MOVE_L 3
#define MOVE_R 4

class Gamecore {
  public:
    Gamecore();
    void start_game();
    void add_number();
    void moving(const int&);

  private:
    int state[4][4];
};