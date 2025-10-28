CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra
LIBS = -lraylib -ldl -lm -lpthread -lGL -lrt -lX11

TARGET = OPLK
SRCS = $(wildcard *.cpp)
OBJS = $(SRCS:.cpp=.o)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS) $(LIBS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f *.o $(TARGET)

.PHONY: clean
