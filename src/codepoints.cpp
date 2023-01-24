#include <algorithm>
#include <cstdlib>
#include <iostream>

#include <boost/regex/icu.hpp>

int main(const int argc, const char *argv[]) {
  if (argc == 1) {
    std::cerr << "usage: " << argv[0] << " <string> " << std::endl;
    std::exit(1);
  }

  const auto re = boost::make_u32regex(".");
  const auto text = argv[1];
  std::cout << "text = \'" << text << "\'" << '\n';

  using CharIterator = const char *;
  using RegexIterator = boost::u32regex_iterator<CharIterator>;
  const RegexIterator it = boost::make_u32regex_iterator(text, re);
  std::for_each(
      it, RegexIterator(), [](const boost::match_results<CharIterator> &m) {
        const std::string sub(m[0].first, m[0].second);
        std::cout << "length = " << m.length() << ", sub = \'" << sub << "\'\n";
      });
  return 0;
}
