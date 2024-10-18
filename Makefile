CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17

# List of source files
SRCS = main.cpp webserver.cpp request.cpp loadbalancer.cpp utils.cpp

# Output executable
TARGET = loadbalancer

all: $(TARGET)

$(TARGET): $(SRCS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRCS)

clean:
	rm -f $(TARGET)

