#include <exception>
#include <functional>
#include <iostream>
#include <memory>
#include <regex>
#include <string>

#include "Node.h"

using namespace clojure;

/// \param begin Tokens that have already been read
/// \param end remaining text to parse
NodePtr Read(string::iterator& begin, string::iterator& end) {
    if (begin == end) {
        return nullptr;
    }

    // slurp all whitespace
    while (begin != end && *begin == ' ') begin++;

    // a '(' pushes a new node, ')' returns null
    if (begin != end) {
        if (*begin == '(') {
            begin++;
            if (begin == end) {
                throw runtime_error { "unbalanced parentheses: unexpected '(' at end."};
            }
            return MakeNode(Read(begin, end), Read(begin, end));
        } else if (*begin == ')') {
            return nullptr;
        }
    }

    // read a token
    bool escape = false;
    string token = "";
    while (begin != end) {
        if (!escape && *begin == ' ') break;
        escape = *begin == '\\';
        token.push_back(*begin);
        begin++;
    }
    if (token.empty()) return nullptr;

    return MakeNode(token, Read(begin, end));
}

// template <>
// string Node<string>::ToString() const {
//     return "STRING";
// }

void Print(NodePtr node) {
    cout << node->ToString() << endl;
}

int main() {
    auto RP = [](string s) {
        auto begin = s.begin();
        auto end = s.end();
        auto node = Read(begin, end);
        Print(node);
    };

    RP("12");
    RP("12 abcde 1997");
    RP("12 ab\\ cde 1997");
    RP("12 ab cd (ef gf) 12");
    
    return 0;
}








