CXXFLAGS := -Wall -Wextra -pedantic -std=c++17 -g
SFML_LIBS := -lsfml-graphics -lsfml-window -lsfml-system -lGL
IMGUI_INCLUDE := -I./include
IMGUI_SRCS := $(wildcard ./include/*.cpp)
OBJS := $(patsubst %.cpp,%.o,$(IMGUI_SRCS))
APPLICATION_OBJ = application.o
TILES_OBJ := tiles.o

all: main.exe

main.exe: main.cpp $(OBJS) $(APPLICATION_OBJ) $(TILES_OBJ) 
	$(CXX) $(CXXFLAGS) $^ -o $@ $(SFML_LIBS) $(IMGUI_INCLUDE)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@ $(IMGUI_INCLUDE)

application.o: application.cpp application.hpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

tiles.o: tiles.cpp tiles.hpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

.PHONY: clean all

clean:
	rm -vf *.exe *.out.txt *.o


