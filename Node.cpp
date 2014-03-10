#include <iostream>

#include "node.h"

namespace clojure {
    std::ostream& operator<<(std::ostream& os, const sexp& rhs) {
        os << '(';
        for (auto item : rhs.items) {
            os << item << ' ';
        }
        os << ')';
        
        return os;
    }
}
