CPPFLAGS += -Wall -Wextra -std=c++11
SRC = $(wildcard *.cpp)
SRC = $(filter-out cli.cpp, $(SRC))
OBJ = $(SRC:%.cpp=%.o)
paint: $(OBJ)
	$(CXX) $^ -o $@

clean:
	$(RM) -rf $(OBJ) paint
#paint: main.cpp
#	g++ main.cpp -o paint
