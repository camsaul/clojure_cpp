
#include <cstdlib>
#include <cxxabi.h>
#include <regex>
#include <utility>
#include <vector>

#include "Util.h"

namespace clojure {
    string DemangleName(const type_info& info) {
        auto mangled_name = info.name();
        int status ;
        char *temp = __cxxabiv1::__cxa_demangle(mangled_name, nullptr, nullptr, &status);
        if(temp) {
            string result{temp};
            free(temp);

            // filter out std::, __1, etc
            static const vector<pair<string, string>> replacements {
                {"std::__1::", ""},
                {"basic_string<char, char_traits<char>, allocator<char> >", "string"},
                {"shared_ptr<clojure::BaseNode>", "NodePtr"}
            };

            for (auto replacement : replacements) {
                regex rx {replacement.first};
                result = regex_replace(result, rx, replacement.second);
            }
            return result;
        }
        else return mangled_name;   
    }
}
