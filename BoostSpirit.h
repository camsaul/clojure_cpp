// #ifndef CLOJURE_BOOSTSPIRIT_H
// #define CLOJURE_BOOSTSPIRIT_H

//***** WRAPPER PCH HEADER FOR BOOST SPIRIT INCLUDES *****//

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wundef"
#pragma clang diagnostic ignored "-Wdisabled-macro-expansion"
#pragma clang diagnostic ignored "-Wdocumentation-unknown-command"
#pragma clang diagnostic ignored "-Wdocumentation"
#pragma clang diagnostic ignored "-Wunknown-pragmas"
#pragma clang diagnostic ignored "-Wunused-parameter"
#pragma clang diagnostic ignored "-Wshadow"
#pragma clang diagnostic ignored "-Wglobal-constructors"
#pragma clang diagnostic ignored "-Wmissing-noreturn"
#pragma clang diagnostic ignored "-Wextra-semi"
#pragma clang diagnostic ignored "-Wsign-conversion"
#pragma clang diagnostic ignored "-Wpadded"
#pragma clang diagnostic ignored "-Wswitch-enum"
#pragma clang diagnostic ignored "-Wcovered-switch-default"
#pragma clang diagnostic ignored "-Wweak-vtables"
#include <boost/config/warning_disable.hpp>
#include <boost/spirit/include/qi.hpp>
/* #include <boost/spirit/include/phoenix_core.hpp> */
/* #include <boost/spirit/include/phoenix_object.hpp> */
/* #include <boost/spirit/include/phoenix_operator.hpp> */
/* #include <boost/spirit/include/phoenix_stl.hpp> */
#include <boost/spirit/include/phoenix.hpp>
#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/fusion/include/io.hpp>
#include <boost/variant/recursive_variant.hpp>
#include <boost/foreach.hpp>
#pragma clang diagnostic pop

// #endif
