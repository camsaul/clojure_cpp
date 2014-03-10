#ifndef CLOJURE_READER_H
#define CLOJURE_READER_H

#include <string>

#include "node.h"

namespace clojure {
    sexp Read (std::string& input);
}

#endif
