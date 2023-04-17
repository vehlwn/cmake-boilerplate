#include <algorithm>
#include <array>
#include <chrono>
#include <cstddef>
#include <cstdlib>
#include <exception>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <iterator>
#include <string_view>

#include <boost/regex/icu.hpp>
#include <unicode/schriter.h>
#include <unicode/umachine.h>
#include <unicode/unistr.h>

std::string readFileToString(const std::filesystem::path& path)
{
    std::ifstream in(path, std::ios::binary);
    in.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    std::ostringstream ret;
    ret << in.rdbuf();
    return ret.str();
}

int main(const int argc, const char* argv[])
try {
    if(argc == 1) {
        std::cerr << "usage: " << argv[0] << " <file name> " << std::endl;
        std::exit(1);
    }

    const std::string text = readFileToString(argv[1]);

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
} catch(const std::exception& ex) {
    std::cerr << "Error: " << ex.what() << std::endl;
}
