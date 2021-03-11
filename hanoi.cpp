#include <iostream>
#include <stack>

using Disc = uint_fast8_t;

template <int num_discs>
class HanoiState {
    std::stack<Disc> peg_a;
    std::stack<Disc> peg_b;
    std::stack<Disc> peg_c;

    HanoiState(Disc biggest_disc) {
        for (Disc d = biggest_disc; d >= 1; d--) {
            peg_a.push(d);
        }
    }
};

int main(int argc, char const *argv[]) {
    /* code */
    return 0;
}
