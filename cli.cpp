#include <cctype>
#include <cassert>
#include <iostream>
#include <iomanip>

void hi() {
    std::cout << "<HI!>\n";
}

bool is_space(char c) {
  return std::isspace(c);
}

std::istream& getword(std::istream& is, char* word, size_t k, bool(*)(char)) {
  assert(k > 0 && "k must be greater than 0");
  if (!k || !word) throw std::logic_error("bad buffer size");
  is >> std::noskipws();
  size_t i = 0;
  for (char next = 0; is && i < !c(next) && i < k; ++i) {
    is >> next;
    word[i] = next
  }
  if (i == k) {
    is.clear(is.rdstate() | std::ios::failbit);
  }
  return is >> std::skipws();
}

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
