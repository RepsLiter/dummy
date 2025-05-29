#include <string>
#include <vector>

int is_digits(const std::string &str);
int is_binary(const std::string &str);
size_t count_binary(const std::string &bin) noexcept;
std::vector<std::string> tokenize_space(const std::string &tok);
void cleanse_tokens(std::vector<std::string> &tokens); // discard elements that is not a binary sequence AND equally turns string length exactly 8.