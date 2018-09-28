CC=g++
CFLAGS = -std=c++14
OPENCV=`pkg-config --libs --cflags opencv`

DEPS = src/*.h

SRCS = $(shell find -name *.cpp)
OBJS := $(addsuffix .o,$(basename $(SRCS)))

all: run

src/%.o: src/%.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS) $(OPENCV)

run: $(OBJS)
	$(CC) -o $@ $^ $(OPENCV)

clean: 
	rm -rf src/*.o
