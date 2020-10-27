#include <iostream>

int main() {
    double a = 1;
    double b = 3;
    double eps = 1e-5;
    double now = a, ans = 0;
    while (now + eps < b) {
        ans += (now * now + 1) * eps;
        now += eps;
    }
    std::cout << ans << std::endl;
}