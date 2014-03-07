P := clojure++

SOURCES := main.cpp
OBJECTS := $(SOURCES:.cpp=.o)
DEPS := $(SOURCES:.cpp=.d)

INCLUDES :=

CPPFLAGS :=

CXXFLAGS := -std=c++11 -Weverything -pipe -gfull -stdlib=libc++ -O0 -Werror -Wfatal-errors

LDFLAGS := -fatal_warnings

LIBS :=

COMPILER_FLAGS := $(INCLUDES) $(CPPFLAGS) $(CXXFLAGS)
LINKER_FLAGS := $(LDFLAGS) $(LIBS)


$(P): deps $(SOURCES) $(HEADERS)
	$(MAKE) all

deps: $(DEPS)

all : $(OBJECTS)
	$(CXX) $(COMPILER_FLAGS) $(OBJECTS) -o $(P) $(LINKER_FLAGS)

%.d : %.cpp
	$(CXX) $(COMPILER_FLAGS) -MF"$@" -MG -MM -MT"$(<:.cpp=.o)" "$<"

clean :
	$(RM) -f $(DEPS)
	$(RM) -f $(OBJECTS)
	$(RM) -f $(P)

check-syntax:
	$(CXX) $(COMPILER_FLAGS) -o nul -S $(CHK_SOURCES)
