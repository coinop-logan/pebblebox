CXX = g++
CXXFLAGS = -g -Wall -std=c++17

INC=-I/usr/include -I../common -I./
LIB=-lsfml-graphics -lsfml-system -lsfml-window -lode -lpthread -lGL -lGLU

all: pre-build main-build

main-build: bin/main

clean:
	rm -f cpp/obj/*
	rm -rf bin/*
	rm -rf dist/*

pre-build:
	mkdir -p cpp/obj
	mkdir -p bin/
	mkdir -p dist/

cpp/obj/%.o: cpp/src/%.cpp
	$(CXX) $(CXXFLAGS) -c $^ -o $@ $(INC)

bin/main: cpp/obj/main.o cpp/obj/entities.o cpp/obj/graphics.o cpp/obj/utils.o cpp/obj/interface.o
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LIB)
