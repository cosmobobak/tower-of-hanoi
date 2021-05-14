#include <cassert>
#include <iostream>
#include <sstream>
#include <stack>
#include <vector>

using Disc = uint_fast8_t;

const char PEG_SYMBOLS[] = {'A', 'B', 'C'};

enum Peg {
    A,
    B,
    C
};

auto peg_to_string(Peg p) -> std::string {
    return std::string(1, PEG_SYMBOLS[p]);
}

class Move {
    Peg from;
    Peg to;

   public:
    Move(Peg from, Peg to) {
        this->from = from;
        this->to = to;
    }

    auto to_string() -> std::string {
        return "Move piece from peg " + peg_to_string(from) + " to " + peg_to_string(to) + ".";
    }
};

class HanoiState {
   private:
    std::stack<Disc> peg_a;
    std::stack<Disc> peg_b;
    std::stack<Disc> peg_c;
    std::vector<Move> moves;
    int solve_counter = 0;
    int num_discs;

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

    auto get_peg_pointer(Peg p) -> std::stack<Disc>* {
        switch (p) {
            case Peg::A:
                return &peg_a;
            case Peg::B:
                return &peg_b;
            case Peg::C:
                return &peg_c;

            default:
                __builtin_unreachable();
        }
    }

    auto disc_count_even() -> bool {
        return (num_discs & 1) == 0;
    }

    auto move(Peg from, Peg to) -> bool {
        // get pointers to the stacks that we're manipulating
        std::stack<Disc>* source = get_peg_pointer(from);
        std::stack<Disc>* target = get_peg_pointer(to);

        // a move is invalid if we're trying to move from an empty stack or
        // if we're trying to put a big thing on a small thing.
        // short-circuit eval is important here because we can't take the "top" of an empty stack
        if (source->empty() || (!target->empty() && source->top() > target->top())) {
            // illegal move.
            return false;
        }

        // put the top of the source on the top of the target
        target->push(source->top());

        // remove the top of the source
        source->pop();

        // success!
        return true;
    }

   public:
    HanoiState(Disc biggest_disc) {
        num_discs = biggest_disc;
        for (Disc d = biggest_disc; d >= 1; d--) {
            peg_a.push(d);
        }
        moves.reserve(num_steps_required());
    }

    auto num_steps_required() -> int {
        return (1 << num_discs) - 1;
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
        std::ostringstream builder;
        builder << "\n";
        builder << generate_disc_symbol(0);
        builder << generate_disc_symbol(0);
        builder << generate_disc_symbol(0);
        builder << "\n";
        for (int row = 0; row < num_discs; row++) {
            builder << generate_disc_symbol(copy_a.top());
            builder << generate_disc_symbol(copy_b.top());
            builder << generate_disc_symbol(copy_c.top());
            builder << "\n";
            copy_a.pop();
            copy_b.pop();
            copy_c.pop();
        }
        std::cout << builder.str();
    }

    auto get_solve_counter() -> int {
        return solve_counter;
    }

    auto is_solved() -> bool {
        // the tower is solved when all the discs are on peg C.
        return peg_c.size() == num_discs;
    }

    void perform_solve_step() {
        if (disc_count_even()) {
            switch (solve_counter % 3) {
                case 0:
                    // 1. make the legal move between pegs A and B (in either direction)
                    if (!move(A, B)) {
                        move(B, A);
                        moves.emplace_back(B, A);
                    } else {
                        moves.emplace_back(A, B);
                    }
                    break;
                case 1:
                    // 2. make the legal move between pegs A and C (in either direction)
                    if (!move(A, C)) {
                        move(C, A);
                        moves.emplace_back(C, A);
                    } else {
                        moves.emplace_back(A, C);
                    }
                    break;
                case 2:
                    // 3. make the legal move between pegs B and C (in either direction)
                    if (!move(C, B)) {
                        move(B, C);
                        moves.emplace_back(B, C);
                    } else {
                        moves.emplace_back(C, B);
                    }
                    break;
            }
        } else {
            switch (solve_counter % 3) {
                case 0:
                    // 1. make the legal move between pegs A and C (in either direction)
                    if (!move(A, C)) {
                        move(C, A);
                        moves.emplace_back(C, A);
                    } else {
                        moves.emplace_back(A, C);
                    }
                    break;
                case 1:
                    // 2. make the legal move between pegs A and B (in either direction)
                    if (!move(A, B)) {
                        move(B, A);
                        moves.emplace_back(B, A);
                    } else {
                        moves.emplace_back(A, B);
                    }
                    break;
                case 2:
                    // 3. make the legal move between pegs B and C (in either direction)
                    if (!move(C, B)) {
                        move(B, C);
                        moves.emplace_back(B, C);
                    } else {
                        moves.emplace_back(C, B);
                    }
                    break;
            }
        }
        solve_counter++;
    }

    void print_move_stack() {
        std::ostringstream ss;
        int i = 0;
        for (auto&& move : moves) {
            ss << ++i << ". " << move.to_string() << "\n";
        }
        std::cout << ss.str();
    }
};

auto ask_question(std::string q) -> bool {
    std::cout << q;
    char ans;
    std::cin >> ans;
    if (ans == 'Y' || ans == 'y') {
        return true;
    }
    return false;
}

int main(int argc, char const* argv[]) {
    std::cout << "How many discs should the Tower of Hanoi have? \n--> ";
    int num_discs;
    std::cin >> num_discs;

    bool printing = false;
    if (ask_question("Would you like the program to print the Tower as it is solved? [Yy/Nn]\n--> ")) {
        printing = true;
    }

    HanoiState state = HanoiState(num_discs);

    std::cout << "Trying to solve it in " << state.num_steps_required() << " steps!\n";

    if (printing) {
        state.show();
    }

    while (!state.is_solved()) {
        state.perform_solve_step();
        if (printing) {
            state.show();
        }
    }
    std::cout << "Solved in " << state.get_solve_counter() << " steps!\n";

    if (ask_question("Would you like to get a printout of the moves to make in order? [Yy/Nn]\n--> ")) {
        state.print_move_stack();
    }

    return 0;
}
