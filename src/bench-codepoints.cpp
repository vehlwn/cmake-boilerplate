#include <algorithm>
#include <array>
#include <chrono>
#include <cstddef>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <iterator>
#include <string_view>

#include <boost/regex/icu.hpp>
#include <unicode/schriter.h>
#include <unicode/umachine.h>
#include <unicode/unistr.h>

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
    if(std::ifstream f{argv[1]}) {
        text = copyToString(f);
    } else {
        std::cerr << "failed to open file" << std::endl;
        std::exit(1);
    }

    std::cout << "text.size = " << text.size() << std::endl;

    auto t1 = std::chrono::system_clock::now();
    const auto re = boost::make_u32regex(".");
    using CharIterator = std::string::const_iterator;
    using RegexIterator = boost::u32regex_iterator<CharIterator>;
    const auto it = boost::make_u32regex_iterator(text, re);
    std::cout << "distance = " << std::distance(it, RegexIterator()) << std::endl;
    auto t2 = std::chrono::system_clock::now();
    std::cout << std::chrono::duration<double>(t2 - t1).count() << " s" << std::endl;

    t1 = std::chrono::system_clock::now();
    icu::UnicodeString utext = text.c_str();
    icu::StringCharacterIterator it2(utext);
    std::size_t distance2 = 0;
    for(UChar32 c = it2.first32(); c != icu::ForwardCharacterIterator::DONE;
        c = it2.next32()) {
        distance2++;
    }
    std::cout << "distance2 = " << distance2 << '\n';
    t2 = std::chrono::system_clock::now();
    std::cout << std::chrono::duration<double>(t2 - t1).count() << " s" << std::endl;
    return 0;
}
