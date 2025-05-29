#include <iostream>
#include <b2dec_utils.hpp>
#include <algorithm>
#include <unordered_map>

enum SpecialSequence{
    CommandNewLine,
    CommandCarriageReturn
};

template<class T>
std::ostream &operator<<(std::ostream &os, std::vector<T> const &vect){
    for(T i : vect)
        os << i << " ";
    return os;
}

int main(void){
    std::cout << std::boolalpha;
    std::ios_base::sync_with_stdio(0);
    static std::string binaries_literal;
    static std::unordered_map<size_t, SpecialSequence> special; // template: position and sequence identifier.

    std::cout << "bin: ";
    std::getline(std::cin, binaries_literal);
    std::vector<std::string> binaries = tokenize_space(binaries_literal);
    // filter out special sequence and copy their position in hashmap.
    for(std::size_t i = 0; i < binaries.size(); i++){
        if(binaries[i].find("x00") != std::string::npos)
            special[i] = CommandNewLine;
        else if(binaries[i].find("x01") != std::string::npos)
            special[i] = CommandCarriageReturn;
    }

    cleanse_tokens(binaries);
    if(binaries.size() == 0){
        std::cout << "empty." << std::endl;
        return 0;
    }

    std::cout 
    << "Options: \n"
    << "1. Hex (WIP)\n"
    << "2. Decimal (Default)\n"
    << "3. Printable\n"
    << "4. All (WIP)\n"
    << "(Printable control: x00 = new line, x01 = carriage return)\n"
    << ": ";
    int c;
    std::cin >> c;
    switch(c){
        case 1:
        break;

        case 3:
        {
            size_t indicator = 0;
            for(std::vector<std::string>::const_iterator it = binaries.begin(); it != binaries.end(); it++){
                if(special.find(indicator) != special.end()){
                    SpecialSequence sp_char = special[indicator];
                    std::cout << (sp_char == CommandNewLine ? '\n' : '\r');
                }
                std::size_t decimal = count_binary(*it);
                char print = static_cast<char>(decimal);
                std::cout << print;
                indicator++;
            }
        }
        break;

        case 4:
        break;

        default:
        case 2:
        {
            size_t i = 1;
            for(std::vector<std::string>::const_iterator it = binaries.begin(); it != binaries.end(); it++){
                std::cout << i << ". " << count_binary(*it) << "\n";
                i++;
            }
        }
        break;
    }
    std::cout << std::endl;
    return 0;
}
