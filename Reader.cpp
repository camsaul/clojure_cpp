#include <exception>
#include <iostream>
#include <string>
#include <vector>

#include "Reader.h"

namespace qi = boost::spirit::qi;
namespace ascii = boost::spirit::ascii;
namespace phoenix = boost::phoenix;
namespace fusion = boost::fusion;

namespace clojure {
    struct symbol_table_ : qi::symbols<char, sexp_node>
    {
        symbol_table_()
        {
            add
                ("TEST", sexp_node{"test"})
            ;
        }
    } symbol_table;
    
    template <typename Iterator>
    struct grammar : qi::grammar<Iterator, sexp(), ascii::space_type>
    {
        grammar() : grammar::base_type(list)
        {
            using qi::lexeme;
            using qi::char_;
            using namespace qi::labels;
            // using qi::string;

            token %= +(char_ -'(' -')' -'#' -'"' -qi::space);

            node %= (symbol_table|token|list);

            list %= '('
                >> *node
                >> ')'
                ;

            // special forms

            // on_success(token,
            //            std::cout << "Parsed token: "
            //            << phoenix::construct<std::string>(_3, _2)
            //            << std::endl);
        }

        qi::rule<Iterator, std::string()> token;
        qi::rule<Iterator, sexp_node(), ascii::space_type> node;
        qi::rule<Iterator, sexp(), ascii::space_type> list;
    };
}

BOOST_FUSION_ADAPT_STRUCT(clojure::sexp,
                          (std::vector<clojure::sexp_node>, items));

namespace clojure {
    sexp Read (std::string& input) {
        static grammar<std::string::const_iterator> grammar;

        std::string::const_iterator itr = input.begin();
        std::string::const_iterator end = input.end();

        sexp output;

        bool r = qi::phrase_parse(itr, end, grammar, ascii::space, output);

        if (r && itr == end) {
            return output; 
        } else {
            throw std::runtime_error { "Parse error near: " + std::string(itr, end) };
        }
    }
}
