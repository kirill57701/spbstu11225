#include <cctype>
#include <iostream>

void hi() {
    std::cout << "<HI!>\n";
}

std::istream& getword(std::istream& is, char* word, size_t k, bool(*)(char));
size_t match(const char * word, size_t bsize, const char * const * words, size_t k);

int main() {
    const size_t cmds_count = 1;
    size_t i = 0;
    void(*cmds[cmds_count])() = {hi};
    const char * const cmds_text[] = {"hi"};
    constexpr size_t bsize = 255;
    char word[bsize + 1] = {};
    while (!(getword(std::cin, word, bsize, is_space)).eof()) {
        if (std::cin.fail()) {
            std::cerr << "<INVALID COMMAND>\n";
            return 1;
        } else if (size_t i = match(word, cmds_text, cmds_count); i < cmds_count) {
            cmds[i]();
        } else {
            std::cerr << "<UNIKNOWN COMMAND>\n";
        }
    }
}
