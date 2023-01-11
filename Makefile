MAKEFLAGS+=--no-builtin-rules --no-builtin-variables

OUTPUT=bin/output

CXXFLAGS=-O0 -g -Wall -MMD -Wno-unused-function
CXXFLAGS+=-Iinclude
CFLAGS=$(CXXFLAGS)
CC=gcc
CXX=g++

LDLIBS=-Llib -lglfw -lGL -lGLU -ldl
SRCSC=$(wildcard src/*.c)
SRCSCXX=$(wildcard src/*.cpp)

OBJS=$(SRCSC:.c=.o)
OBJS+= $(SRCSCXX:.cpp=.o)

DEPS=$(OBJS:.o=.d)

all: $(OUTPUT)

-include $(DEPS)

%.o: %.c
	$(CC) -o $@ -c $< $(CFLAGS)

%.o: %.cpp
	$(CXX) -o $@ -c $< $(CXXFLAGS)

$(OUTPUT): $(OBJS)
	$(CXX) -o $@ $(LDFLAGS) $^ $(LDLIBS)
	
run: $(OUTPUT)
	./$<

clean:
	rm -f $(OBJS) $(DEPS) $(OUTPUT)
	
.PHONY: all clean run
