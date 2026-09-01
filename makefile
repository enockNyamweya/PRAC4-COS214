CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -g
TARGET = taskforge

SRCS = $(wildcard *.cpp)
OBJS = $(SRCS:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f *.o $(TARGET)

run: all
	./$(TARGET)

.PHONY: all clean run