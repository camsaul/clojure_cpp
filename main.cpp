#include <cstdlib>
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
    static int depth = 0;

    if (begin == end) {
        if (depth != 0) {
            depth = 0; // reset so it works next time
            throw runtime_error { "Mismatched parentheses : " + std::to_string(abs(depth)) + " too many " +
                    (depth > 0 ? "opening" : "closing") + " parens "};
        }
        return nullptr;
    }

    // slurp all whitespace
    while (begin != end && *begin == ' ') begin++;

    // read a token or delimiter
    
    string token = "";
    while (begin != end) {
        // handle escape sequence
        if (*begin == '\\') {
            begin++;
            if (begin == end) throw runtime_error { "Invalid escape token at end of input!" };
            token.push_back(*begin);
            begin++;
            continue;
        }

        if (*begin == ' ') {
            break; // end of token
        }
        else if (*begin == '(') {
            if (begin == end) {
                throw runtime_error { "unbalanced parentheses: unexpected '(' at end."};
            } else if (!token.empty()) {
                break; // end of token. next loop around will handle this paren as separate token
            } else {
                // cout << "PUSH PARENS" << endl;
                depth++;
                begin++;
                return MakeNode(Read(begin, end), Read(begin, end));
            }
        } else if (*begin == ')') {
            if (!token.empty()) break;
            else {
                begin++;
                depth--;
                // cout << "POP PARENS" << endl;
                return nullptr;                
            }
        }

        token.push_back(*begin);
        begin++;
    }
    
    if (token.empty()) return nullptr;

    // cout << "ACCEPT TOKEN: '" << token << "' @" << depth << endl;

    return MakeNode(token, Read(begin, end));
}

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








