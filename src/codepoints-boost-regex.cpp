#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <string_view>

#include <boost/regex/icu.hpp>

int main(const int argc, const char* argv[])
try {
    if(argc == 1) {
        std::cerr << "usage: " << argv[0] << " <string> " << std::endl;
        std::exit(1);
    }

    const auto re = boost::make_u32regex(".");
    const auto text = argv[1];
    std::cout << "text = \'" << text << "\'" << '\n';

    using CharIterator = const char*;
    using RegexIterator = boost::u32regex_iterator<CharIterator>;
    const RegexIterator it = boost::make_u32regex_iterator(text, re);
    std::for_each(
        it,
        RegexIterator(),
        [](const boost::match_results<CharIterator>& m) {
            const auto sub
                = std::string_view(m[0].first, static_cast<std::size_t>(m.length()));
            std::cout << "length = " << m.length() << ", sub = \'" << sub << "\'\n";
        });
    return 0;
} catch(const std::exception& ex) {
    std::cerr << "Error: " << ex.what() << std::endl;
}
