P := clojure++

HEADERS := $(shell find . -name "*.h" -and -not -name "*flymake*" -and -not -name "*\#*")
SOURCES := $(shell find . -name "*.cpp" -and -not -name "*flymake*" -and -not -name "*\#*")
OBJECTS := $(SOURCES:.cpp=.o)
DEPS := $(SOURCES:.cpp=.d)

INCLUDES :=
CPPFLAGS := $(INCLUDES)

WARNING_FLAGS := -Weverything -Werror -Wfatal-errors -Wno-c++98-compat -Wno-missing-prototypes \
		 -Wno-exit-time-destructors
DIAGNOSTIC_OPTS := -fdiagnostics-show-template-tree -fno-elide-type
COMPILER_FLAGS := -std=c++11 -pipe -gfull -stdlib=libc++ -O0
CXXFLAGS := $(WARNING_FLAGS) $(DIAGNOSTIC_OPTS) $(COMPILER_FLAGS)

LDFLAGS := -fatal_warnings
LIBS :=


$(P): deps $(SOURCES) $(HEADERS)
	$(MAKE) all

deps: $(DEPS)

all : $(OBJECTS)
	$(CXX) $(OBJECTS) -o $(P)

%.d : %.cpp
	$(CXX) $(COMPILER_FLAGS) -MF"$@" -MG -MM -MT"$(<:.cpp=.o)" "$<"

clean :
	$(RM) -f $(DEPS)
	$(RM) -f $(OBJECTS)
	$(RM) -f $(P)

check-syntax:
	$(CXX) $(COMPILER_FLAGS) -o nul -S $(CHK_SOURCES)
