CXXFLAGS := -Wall -Wextra -pedantic -std=c++17 -g
SFML_LIBS := -lsfml-graphics -lsfml-window -lsfml-system -lGL
IMGUI_INCLUDE := -I./include
IMGUI_SRCS := $(wildcard ./include/*.cpp)
OBJS := $(patsubst %.cpp, %.o, $(IMGUI_SRCS))
APPLICATION_OBJ = src/application.o
SPRITE_OBJ := src/spritesheet.o
BOARD_OBJ := src/board.o

all: main.exe

main.exe: src/main.cpp $(OBJS) $(APPLICATION_OBJ) $(SPRITE_OBJ) $(BOARD_OBJ)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(SFML_LIBS) $(IMGUI_INCLUDE)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@ $(IMGUI_INCLUDE)

src/application.o: src/application.cpp src/application.hpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

src/spritesheet.o: src/spritesheet.cpp src/spritesheet.hpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

src/board.o: src/board.cpp src/board.hpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

test: src/spritesheet_tests.exe
	./src/spritesheet_tests.exe

src/spritesheet_tests.exe: src/spritesheet.cpp src/spritesheet_tests.cpp
	$(CXX) $(CXXFLAGS) $^ -o $@ $(SFML_LIBS) $(IMGUI_INCLUDE)

.PHONY: clean all

clean:
	rm -vf *.exe *.out.txt *.o
	rm -vf src/*.o

