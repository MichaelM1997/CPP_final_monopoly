CXX = clang++
CXXFLAGS = -std=c++14 -Wall
# SFML libraries
LIBS = -lsfml-graphics -lsfml-window -lsfml-system

SRCS = main.cpp Board.cpp Player.cpp Property.cpp
OBJS = $(SRCS:.cpp=.o)
EXEC = monopoly_game

# Default target
all: $(EXEC)

# Rule to create the executable
$(EXEC): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(EXEC) $(OBJS) $(LIBS)

# Rule to create object files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $<

# Clean target to remove object files and the executable
clean:
	rm -f $(OBJS) $(EXEC)
