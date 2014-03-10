P := clojure++

HEADERS := $(shell find . -name "*.h" -and -not -name "*flymake*")
SOURCES := $(shell find . -name "*.cpp" -and -not -name "*flymake*")
OBJECTS := $(SOURCES:.cpp=.o)
DEPS := $(SOURCES:.cpp=.d)

PCH_SOURCES := BoostSpirit.h
PCH := $(PCH_SOURCES:.h=.pch)
PCH_FLAGS := -Ivendor -x c++-header 

INCLUDES := -Ivendor $(patsubst %,-include %,$(PCH_SOURCES))
CPPFLAGS :=

WARNING_FLAGS := -Weverything -Werror -Wfatal-errors -Wno-c++98-compat -Wno-missing-prototypes \
		 -Wno-exit-time-destructors -Winline -Wno-c++98-compat-pedantic
DIAGNOSTIC_OPTS := -fdiagnostics-show-template-tree -fno-elide-type
COMPILER_FLAGS := -std=c++11 -pipe -gfull -stdlib=libc++ -O0
CXXFLAGS := $(INCLUDES) $(WARNING_FLAGS) $(DIAGNOSTIC_OPTS) $(COMPILER_FLAGS)

LDFLAGS := -fatal_warnings
LIBS :=


$(P): $(PCH) deps $(SOURCES) $(HEADERS)
	$(MAKE) all

deps: $(DEPS)

all : $(OBJECTS)
	$(CXX) $(OBJECTS) -o $(P)

%.d : %.cpp
	$(CXX) $(CXXFLAGS) -MF"$@" -MG -MM -MT"$(<:.cpp=.o)" "$<"

%.pch : %.h
	$(CXX) $(WARNING_FLAGS) $(COMPILER_FLAGS) $(PCH_FLAGS) $< -o $@

clean :
	$(RM) -f $(DEPS)
	$(RM) -f $(OBJECTS)
	$(RM) -f $(P)
	$(RM) -f $(PCH)

check-syntax:
	$(CXX) $(INCLUDES) $(WARNING_FLAGS) $(COMPILER_FLAGS) -Weverything -o nul -S $(CHK_SOURCES)
