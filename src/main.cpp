#include "algo.h"

int main() {
    std::cout << "Enter your stacks of cards in the following format: 1 - for six, 2 - for seven, ... 9 - for ace" << std::endl;
    std::cout << "Print each stack in one line without space (new stack - new line), starting from the bottom of the stack to the top" << std::endl;
    std::string starting_state = ""; 
    for (int i = 0; i < 8; i++) {
        std::string stack;
        std::cin >> stack;
        starting_state += stack;
        if (i < 7) {
            starting_state += '|';
        }
    }
    auto ans = find_solution(normalize(starting_state));
    if (ans.first) {
        std::cout << "Your configuration has solution, it can be achieved with " << ans.second << " steps"; 
    } else {
        std::cout << "Your configuration doesn't have solution";
    }
}