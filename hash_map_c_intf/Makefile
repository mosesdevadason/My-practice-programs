CC=gcc
CXX=g++

CFLAGS=-g -Wall
CXXFLAGS=-std=c++11 -g -Wall

EXE=hash_map_exe
OBJ=main hash_map_ds 
OBJS=$(addsuffix .o, $(OBJ))

all:
	make compile

compile:
	make $(OBJS)
	make $(EXE)

$(EXE): $(OBJS)
	$(CXX) -o $(EXE) $(OBJS)

main.o: main.c
	$(CC) $(CFLAGS) -c -o main.o main.c

hash_map_ds.o: hash_map_ds.cpp
	$(CXX) $(CXXFLAGS) -c -o hash_map_ds.o hash_map_ds.cpp

clean:
	-rm -f $(OBJS) $(EXE)
