CC = g++
LDFLAGS = -lncurses
SRCS = main.cpp gameLogic.cpp makeMap.cpp
OBJS = $(SRCS:.cpp=.o)
EXECUTABLE = labirynth

all: $(EXECUTABLE)

$(EXECUTABLE):$(OBJS)
	$(CC) -o $(EXECUTABLE) $(OBJS) $(LDFLAGS)
	
run:
	./$(EXECUTABLE) $(ARGS)
	
clean:
	rm -f $(OBJS) $(EXECUTABLE)
