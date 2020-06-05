#include "gamecore.h"

using namespace std;

auto Board::mem = []() {
    vector<Board::line_change> ans;
    for (int num = 0; num < (1 << 20); num++) {
        Board::line_change val;
        val.after[0] = num & 0b00000000000000011111;
        val.after[1] = num & 0b00000000001111100000;
        val.after[2] = num & 0b00000111110000000000;
        val.after[3] = num & 0b11111000000000000000;
        val.moved = false;
        val.point = 0;
        for (int i = 1; i < 4; i++) {
            if (val.after[i] == 0) continue;
            int pos = i;
            while (pos && val.after[pos - 1] == 0) {
                swap(val.after[pos], val.after[pos - 1]);
                pos--;
                val.moved = true;
            }
            if (pos && val.after[pos - 1] == val.after[pos]) {
                val.after[pos - 1]++;
                val.after[pos] = 0;
                val.moved = true;
                val.point += val.after[pos - 1];
            }
        }
        ans.push_back(val);
    }
    return ans;
}();