
#ifndef CLOJURE_UTIL_H
#define CLOJURE_UTIL_H

#include <string>
#include <typeinfo>

namespace clojure {
    using namespace std;

    string DemangleName(const type_info& info);

    template <typename T>
    string ReadableName() {
        return DemangleName(typeid(T));        
    }
    
    template <typename T>
    string ReadableName(const T& t) {
        return DemangleName(typeid(t));
    }
}

#endif
