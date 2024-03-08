CXX = g++
CXXFLAGS = -g -std=c++11
SRC = main.cpp record.cpp register.cpp
OBJ = $(SRC:.cpp=.o)
EXEC = DB.out

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^

clean:
	rm -f $(OBJ) $(EXEC)

run: all
	./$(EXEC)

.PHONY: all clean run