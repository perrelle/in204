SOURCES := $(shell find $(SOURCEDIR) -name '*.c' -o -name '*.cpp')
TESTS := $(addsuffix .test,$(SOURCES))
CXXFLAGS := -std=c++23 -Wall -Wno-unused-variable -Wno-unused-but-set-variable
CFLAGS := -Wall -Wno-unused-variable -Wno-unused-but-set-variable

.PHONY: all $(TESTS)

all: $(filter-out %access.cpp.test,$(TESTS))

%.c.exe: %.c
	gcc -g $(CFLAGS) -o $@ $<

%.cpp.exe: %.cpp
	g++ -g $(CXXFLAGS) -o $@ $<

$(TESTS):%.test: %.exe
	@echo "$*"
	@valgrind --quiet --leak-check=full --track-origins=yes ./$<

constructor-order.cpp.exe: CXXFLAGS = -Wno-reorder
