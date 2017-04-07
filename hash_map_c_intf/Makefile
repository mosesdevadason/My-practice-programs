CC=gcc
CXX=g++

CFLAGS=-g -Wall
CXXFLAGS=-std=c++11 -g -Wall

EXE=hash_map_exe
C_SOURCES=main.c
CXX_SOURCES=hash_map_ds.cpp
C_OBJS=main.o
CXX_OBJS=hash_map_ds.o
OBJS=$(C_OBJS) $(CXX_OBJS)

all:
	make compile

compile:
	make $(OBJS)
	make $(EXE)

$(EXE): $(OBJS)
	$(CXX) -o $(EXE) $(OBJS)

$(C_OBJS): $(C_SOURCES)
	$(CC) $(CFLAGS) -c -o $(C_OBJS) $(C_SOURCES)

$(CXX_OBJS): $(CXX_SOURCES)
	$(CXX) $(CXXFLAGS) -c -o $(CXX_OBJS) $(CXX_SOURCES)

clean:
	-rm -f $(OBJS) $(EXE)
