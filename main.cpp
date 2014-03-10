#include <complex>
#include <functional>
#include <iostream>

using std::complex;

template <typename Iterator>
bool parse_complex(Iterator first, Iterator last, complex<double>& c)
{
    using boost::spirit::ascii::space;
    using boost::phoenix::ref;
    using boost::spirit::qi::double_;
    using boost::spirit::qi::phrase_parse;
    using boost::spirit::qi::_1;

    double rN = 0.0f;
    double iN = 0.0f;

    bool r = phrase_parse(first, last,
                          // begin grammar
                          (
                           '(' >> double_[ref(rN) = _1]
                           >> -(',' >> double_[ref(iN) = _1]) >> ')'
                           | double_[ref(rN) = _1]
                           ),
                          // end grammar
                          space);

    if (!r || first != last) // fail if we didn't get a full match
        return false;

    c = complex<double>(rN, iN);
    return r;
}

int main() {
    std::cout << "Type [q or Q] to quit\n\n";

    std::string str;
    while (getline(std::cin, str))
    {
        if (str.empty() || str[0] == 'q' || str[0] == 'Q') break;

        complex<double> c {};
        parse_complex(str.begin(), str.end(), c);
        std::cout << "Read: " << c.real() << ", " << c.imag() << std::endl;
        std::cout << "> " << std::endl;
    }

    return 0;
}

// #include "Node.h"
// #include "Reader.h"

// using namespace clojure;

// void Print(NodePtr node) {
//     cout << node->ToString() << endl;
// }

// NodePtr Eval(NodePtr node) {
//     return node; // placeholder
// }

// int main() {
//     auto RP = [](string s) {
//         auto begin = s.begin();
//         auto end = s.end();
//         auto node = Read(begin, end);
//         node = Eval(node);
//         Print(node);
//     };

//     RP("12");
//     RP("12 abcde 1997");
//     RP("12 ab\\ cde 1997");
//     RP("12 ab cd (ef gf) 12");
    
//     return 0;
// }








