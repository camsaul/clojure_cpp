#include <iostream>

#include "node.h"

using clojure::sexp;

std::ostream& operator<<(std::ostream& os, const sexp& rhs) {
    os << '(';
    for (auto item : rhs.items) {
        os << item << ' ';
    }
    os << ')';
    
    return os;
}
