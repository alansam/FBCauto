all: main

#CXX = clang++
CXX = g++
#override CXXFLAGS += -g -Wno-everything
override CXXFLAGS += -g -Wall -Wpedantic -Werror=vla -fsanitize=address -std=gnu++2b -static-libasan -pthread -lm
#-Wl,--print-memory-usage

SRCS = $(shell find . -name '.ccls-cache' -type d -prune -o -type f -name '*.cpp' -print | sed -e 's/ /\\ /g')
HEADERS = $(shell find . -name '.ccls-cache' -type d -prune -o -type f -name '*.h' -print)

main: $(SRCS) $(HEADERS)
	$(CXX) $(CXXFLAGS) $(SRCS) -o "$@"

main-debug: $(SRCS) $(HEADERS)
	$(CXX) $(CXXFLAGS) -O0 $(SRCS) -o "$@"

clean:
	rm -f main main-debug