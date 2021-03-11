#include <iostream>
#include <stack>

using Disc = uint_fast8_t;

class HanoiState {
    std::stack<Disc> peg_a;
    std::stack<Disc> peg_b;
    std::stack<Disc> peg_c;
    int solve_counter = 0;
    int num_discs;

   public:
    HanoiState(Disc biggest_disc) {
        num_discs = biggest_disc;
        for (Disc d = biggest_disc; d >= 1; d--) {
            peg_a.push(d);
        }
    }

    auto num_steps_required() -> int {
        return (1 << num_discs) - 1;
    }

    auto generate_disc_symbol(Disc disc) -> std::string {
        std::string builder;
        for (int i = 0; i < num_discs - disc; i++) {
            builder.push_back(' ');
        }
        for (int i = 0; i < disc; i++) {
            builder.push_back('*');
        }
        builder.push_back('|');
        for (int i = 0; i < disc; i++) {
            builder.push_back('*');
        }
        for (int i = 0; i < num_discs - disc; i++) {
            builder.push_back(' ');
        }
        return builder;
    }

    void show() {
        std::stack<Disc> copy_a = peg_a;
        std::stack<Disc> copy_b = peg_b;
        std::stack<Disc> copy_c = peg_c;

        while (copy_a.size() < num_discs) {
            copy_a.push(0);
        }
        while (copy_b.size() < num_discs) {
            copy_b.push(0);
        }
        while (copy_c.size() < num_discs) {
            copy_c.push(0);
        }

        for (int row = 0; row < num_discs; row++) {
            std::cout << generate_disc_symbol(copy_a.top());
            std::cout << generate_disc_symbol(copy_b.top());
            std::cout << generate_disc_symbol(copy_c.top());
            std::cout << "\n";
            copy_a.pop();
            copy_b.pop();
            copy_c.pop();
        }
    }

    void move(int from, int to) {
        auto &source = from == 0 ? peg_a : (from == 1 ? peg_b : peg_c);
        auto &target = to == 0 ? peg_a : (to == 1 ? peg_b : peg_c);
        std::cout << "made it here!";
        if (source.top() > target.top()) {
            std::cout << "invalid move passed to move function.\n";
        } else {
            Disc moving_disc = source.top();
            source.pop();
            target.push(moving_disc);
        }
    }

    auto is_solved() -> bool {
        return peg_c.top() == 1 && peg_a.size() == 0 && peg_b.size() == 0;
    }
};

int main(int argc, char const *argv[]) {
    int num_discs;
    std::cout << "How many discs should the Tower of Hanoi have? \n--> ";
    std::cin >> num_discs;
    HanoiState state = HanoiState(num_discs);
    std::cout << "Trying to solve it in " << state.num_steps_required() << " steps!\n";
    state.show();
    while (1) {
        int from, to;
        std::cin >> from;
        std::cin >> to;
        state.move(from - 1, to - 1);
        state.show();
    }

    return 0;
}
