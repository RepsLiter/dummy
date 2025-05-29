#include <b2dec_utils.hpp>
#include <cmath>
#include <algorithm>

int is_digits(const std::string &str){
    return std::all_of(str.begin(), str.end(), ::isdigit);
}

int is_binary(const std::string &str){
    return is_digits(str) && str.find_first_of("23456789") == std::string::npos;
}

size_t count_binary(const std::string &bin) noexcept{
    size_t end_result = 0, exponent = 7;
    for(std::string::const_iterator binary_it = bin.begin(); binary_it != bin.end(); binary_it++){
        end_result += (*binary_it - '0') * std::pow(static_cast<size_t>(2), exponent--);
    }
    return end_result;
}

void cleanse_tokens(std::vector<std::string> &tokens){
    tokens.erase(std::remove_if(tokens.begin(), tokens.end(), [](std::string const &token){
        return !is_binary(token) || token.size() > 8;
    }), tokens.end());

    for(auto &x : tokens){
        std::size_t range = 8 - x.length();
        if(range != 0){
            x.insert(0, range, '0');
        }
    }
}
std::vector<std::string> tokenize_space(const std::string &tok){
    std::vector<std::string> tokens;
    size_t start = 0, end = tok.find(' ');
    while(end != std::string::npos){
        tokens.push_back(tok.substr(start, end - start));
        start = end + 1;
        end = tok.find(' ', start);
    }
    tokens.push_back(tok.substr(start));
    return tokens;
}