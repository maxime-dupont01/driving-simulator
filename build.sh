#!/bin/bash

CC=g++
LDFLAGS="-lm -lglut -lGL -lGLU"

$CC driving-simulator.cpp library.cpp $LDFLAGS -o main
