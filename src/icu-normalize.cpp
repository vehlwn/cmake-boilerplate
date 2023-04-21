#include <iostream>

#include <unicode/errorcode.h>
#include <unicode/normalizer2.h>
#include <unicode/schriter.h>
#include <unicode/unistr.h>
#include <unicode/ustream.h>

namespace {
void print_codepoints(const icu::UnicodeString& text)
{
    icu::StringCharacterIterator it(text);
    icu::UnicodeString tmp;
    for(UChar32 c = it.first32(); c != icu::ForwardCharacterIterator::DONE;
        c = it.next32()) {
        tmp.remove();
        tmp += c;
        std::cout << "c = " << c << ", sub = \'" << tmp << "\'\n";
    }
}
} // namespace

int main(const int argc, const char* argv[])
{
    if(argc == 1) {
        std::cerr << "usage: " << argv[0] << " <string> " << std::endl;
        std::exit(1);
    }

    const icu::UnicodeString text = argv[1];
    std::cout << "text = \'" << text << "\'" << '\n';
    print_codepoints(text);

    icu::ErrorCode err;
    const icu::Normalizer2& nfkc = *icu::Normalizer2::getNFKCInstance(err);
    if(err.isFailure() != 0) {
        std::cerr << "icu::Normalizer2::getNFKCInstance failed: " << err.errorName()
                  << std::endl;
        std::exit(1);
    }
    const icu::UnicodeString normalized = nfkc.normalize(text, err);
    if(err.isFailure() != 0) {
        std::cerr << "nfkc.normalize failed: " << err.errorName() << std::endl;
        std::exit(1);
    }
    std::cout << "normalized = \'" << normalized << "\'" << '\n';
    print_codepoints(normalized);

    return 0;
}
