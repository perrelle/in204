SOURCES := $(shell find $(SOURCEDIR) -name '*.c' -o -name '*.cpp')
TESTS := $(addsuffix .test,$(SOURCES))

.PHONY: all $(TESTS)

all: $(TESTS)

%.c.exe: %.c
	gcc -o $@ $<

%.cpp.exe: %.cpp
	g++ -o $@ $<

$(TESTS):%.test: %.exe
	@echo "$*"
	@valgrind --quiet --leak-check=full --track-origins=yes ./$<
