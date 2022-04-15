SRC = $(shell find src -name *.cpp)
OBJ = $(patsubst %.cpp,%.o,$(SRC))
CC = g++
FLAGS = -g -O0
TARGET = bin/main.bin

all: $(OBJ)
	$(CC) $(FLAGS) src/main.cpp -o bin/main.bin -lsfml-graphics -lsfml-window -lsfml-system

%.o: %.cpp
	$(CC) -c $(FLAGS) $^ -o $@

run_main: all
	$(TARGET)

clean:
	rm -rf $(OBJ) $(TARGET)
