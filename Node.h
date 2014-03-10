#ifndef CLOJURE_NODE_H
#define CLOJURE_NODE_H

// #include <memory>
#include <string>
#include <vector>

namespace clojure {
    struct sexp;

    typedef boost::variant<boost::recursive_wrapper<sexp>,
                           std::string // todo - float, int, etc (other types)
                           > sexp_node;

    typedef std::vector<sexp_node> sexp_list;

    struct sexp {
    public:
        sexp_list items;

        friend std::ostream& operator<<(std::ostream& os, const sexp& rhs);
    };    
}

#endif
