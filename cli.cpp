#include <iostream>

void hi() {
    std::cout << "<HI!>\n";
}

int main() {
    const size_t cmds_count = 1;
    size_t i = 0;
    void(*cmds[cmds_count])() = {hi};
    while (!(std::cin >> i).eof()) {
        if (std::cin.fail()) {
            std::cerr << "<INVALID COMMAND>\n";
            return 1;
        } else if (i < cmds_count) {
            cmds[i]();
        } else {
            std::cerr << "<UNIKNOWN COMMAND>\n";
        }
    }
}
