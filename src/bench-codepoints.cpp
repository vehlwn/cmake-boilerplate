#include <algorithm>
#include <array>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <iterator>
#include <string_view>

#include <boost/regex/icu.hpp>

std::string copyToString(std::istream& is)
{
    constexpr std::size_t BUF_SIZE = 4096;
    std::array<char, BUF_SIZE> buf;
    is.read(buf.begin(), buf.size());
    std::streamsize n = is.gcount();
    std::string ret;
    while(n > 0) {
        ret.append(buf.begin(), static_cast<std::size_t>(n));
        if(is) {
            is.read(buf.begin(), buf.size());
            n = is.gcount();
        } else {
            n = 0;
        }
    }
    return ret;
}

int main(const int argc, const char* argv[])
{
    if(argc == 1) {
        std::cerr << "usage: " << argv[0] << " <file name> " << std::endl;
        std::exit(1);
    }

    std::string text;
    const auto re = boost::make_u32regex(".");
    if(std::ifstream f{argv[1]}) {
        text = copyToString(f);
    } else {
        std::cerr << "failed to open file" << std::endl;
        std::exit(1);
    }

    std::cout << "text.size = " << text.size() << std::endl;

    using CharIterator = std::string::const_iterator;
    using RegexIterator = boost::u32regex_iterator<CharIterator>;
    const auto it = boost::make_u32regex_iterator(text, re);
    std::cout << "distance = " << std::distance(it, RegexIterator()) << std::endl;
    return 0;
}
