#include <functional>
#include <iostream>

#include "Node.h"
#include "Reader.h"

using namespace clojure;

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








