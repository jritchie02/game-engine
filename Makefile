CXX := g++

CXXFLAGS := -Wall -Wextra -pedantic -std=c++17 -g

sfml_flags := -lsfml-graphics -lsfml-window -lsfml-system

all: main.exe

main.exe: main.cpp
	$(CXX) $(CXXFLAGS) $^ -o $@ $(sfml_flags)

.PHONY: clean all
clean:
	rm -vf *.exe *.out.txt

