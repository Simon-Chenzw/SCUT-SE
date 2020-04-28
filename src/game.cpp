#include "game.h"

void make_moving_map(vector<move_states>& moving_map) {
    moving_map = vector<move_states>(1 << 16);
    for (int i = 0; i < 1 << 16; i++) {
        int val[4];
        set_state(i, val[0], val[1], val[2], val[3]);
        int score = 0, step = 0;
        for (int i = 1; i < 4; i++) {
            if (val[i] == 0) continue;
            for (int j = i; j > 0; j--) {
                if (val[j - 1] == 0) {
                    val[j - 1] = val[j];
                    val[j] = 0;
                    step = 1;
                }
                else if (val[j - 1] == val[j]) {
                    val[j - 1]++;
                    val[j] = 0;
                    step = 1;
                    score += (1 << val[j - 1]);
                }
                else
                    break;
            }
        }
        int new_state = get_state(val[0], val[1], val[2], val[3]);
        moving_map[i] = move_states {new_state, step, score};
    }
}

Game::Game() {
    if (moving_map.size() == 0) make_moving_map(moving_map);
    memset(game_map, 0, sizeof(game_map));
    lose = false;
    step = 0;
    score = 0;
    seed = clock();
    srand(seed);
}

void Game::start() {
    add_num();
    add_num();
}

void Game::add_num() {
    int pos = -1;
    int cnt = 0;
    for (int i = 0; i < 16; i++)
        if (game_map[i] == 0 && rand_chance(++cnt)) pos = i;
    if (pos != -1)
        game_map[pos] = rand_chance(10) ? 2 : 1;
    else
        lose = true;
}

void Game::check() {
    for (int i = 0; i < 16; i++)
        if (game_map[i] != 0) return;
    lose = true;
    return;
}

State Game::state() {
    State ans = 0;
    for (int i = 0; i < 16; i++) ans = (ans << 4) + game_map[i];
    return ans;
}

void Game::moving_up() {
    int tmp_step = 0;
    for (int i = 0; i < 4; i++) {
        move_states tmp = moving_map[get_state(game_map[i], game_map[i + 4], game_map[i + 8], game_map[i + 12])];
        set_state(tmp.new_state, game_map[i], game_map[i + 4], game_map[i + 8], game_map[i + 12]);
        tmp_step = tmp_step | tmp.step;
        score += tmp.score;
    }
    if (tmp_step) {
        step++;
        add_num();
    }
    else
        check();
}

void Game::moving_down() {
    int tmp_step = 0;
    for (int i = 0; i < 4; i++) {
        move_states tmp = moving_map[get_state(game_map[i + 12], game_map[i + 8], game_map[i + 4], game_map[i])];
        set_state(tmp.new_state, game_map[i + 12], game_map[i + 8], game_map[i + 4], game_map[i]);
        tmp_step = tmp_step | tmp.step;
        score += tmp.score;
    }
    if (tmp_step) {
        step++;
        add_num();
    }
    else
        check();
}

void Game::moving_left() {
    int tmp_step = 0;
    for (int i = 0; i < 16; i += 4) {
        move_states tmp = moving_map[get_state(game_map[i], game_map[i + 1], game_map[i + 2], game_map[i + 3])];
        set_state(tmp.new_state, game_map[i], game_map[i + 1], game_map[i + 2], game_map[i + 3]);
        tmp_step = tmp_step | tmp.step;
        score += tmp.score;
    }
    if (tmp_step) {
        step++;
        add_num();
    }
    else
        check();
}

void Game::moving_right() {
    int tmp_step = 0;
    for (int i = 0; i < 16; i += 4) {
        move_states tmp = moving_map[get_state(game_map[i + 3], game_map[i + 2], game_map[i + 1], game_map[i])];
        set_state(tmp.new_state, game_map[i + 3], game_map[i + 2], game_map[i + 1], game_map[i]);
        tmp_step = tmp_step | tmp.step;
        score += tmp.score;
    }
    if (tmp_step) {
        step++;
        add_num();
    }
    else
        check();
}
