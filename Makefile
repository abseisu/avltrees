#
# Makefile for Pset 5: AVL Tree
#
# CPSC 223
# Spring 2023
# Adnan Bseisu
# dab262
# CPSC 223
# PSET 5
# 04/17
#

CXX      = g++
CXXFLAGS = -std=c++17 -g -Wall -Wextra
LDFLAGS  = -g
EXE      = avlt

${EXE}: main.o AVLTree.o pretty_print.o
	${CXX} ${LDFLAGS} -o $@ $^

main.o: main.cpp AVLTree.h 
AVLTree.o: AVLTree.cpp AVLTree.h
pretty_print.o: pretty_print.cpp AVLTree.h

clean:
	${RM} ${EXE} *.o *.dSYM
