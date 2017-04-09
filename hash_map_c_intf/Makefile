CC=gcc
CXX=g++

CFLAGS=-g -Wall
CXXFLAGS=-std=c++11 -g -Wall

PROGRAM=hash_map
C_SOURCES=main.c
CXX_SOURCES=hash_map_ds.cpp

C_OBJS=$(C_SOURCES:c=o)
CXX_OBJS=$(CXX_SOURCES:cpp=o)
OBJS=$(C_OBJS) $(CXX_OBJS)

all:
	make compile

compile:
	make $(OBJS)
	make $(PROGRAM)

$(PROGRAM): $(OBJS)
	$(CXX) -o $(PROGRAM) $(OBJS)

clean:
	-rm -f $(OBJS) $(PROGRAM)
