
#ifndef CLOJURE_READER_H
#define CLOJURE_READER_H

#include <string>

#include "Node.h"

namespace clojure {
    using namespace std;

    /// \param begin Tokens that have already been read
    /// \param end remaining text to parse
    NodePtr Read(string::iterator& begin, string::iterator& end);
}

#endif
