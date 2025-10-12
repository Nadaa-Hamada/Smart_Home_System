CC ?= ${CXX}
CXX ?= g++
CFLAGS = -std=c++20 -Wall -g

SRC = gpio.cpp main.cpp recieve.cpp serial.cpp
OBJ = $(SRC:.cpp=.o)
TARGET = smartsensors

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(CFLAGS) -o $@ $(OBJ)

%.o: %.cpp
	$(CXX) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)

