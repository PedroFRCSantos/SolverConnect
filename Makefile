# -g -o para todos em vez de -o
libs = -lboost_thread -pthread
# DEBUG
#type = -g -c
#typeg = -g -o
# RELEASE
type = -c -O3
typeg = -o

all: SolverConnect

SolverConnect: SolverConnect.o permutas.o solver.o tabuleiro.o
	g++ $(typeg) SolverConnect SolverConnect.o permutas.o solver.o tabuleiro.o $(libs)

SolverConnect.o: SolverConnect.cpp solver.hpp  permutas.hpp
	g++ $(type) SolverConnect.cpp $(libs)

permutas.o: permutas.cpp permutas.hpp
	g++ $(type) permutas.cpp $(libs)

solver.o: solver.cpp solver.hpp permutas.hpp tabuleiro.hpp
	g++ $(type) solver.cpp $(libs)

tabuleiro.o: tabuleiro.cpp tabuleiro.hpp
	g++ $(type) tabuleiro.cpp $(libs)

clean:
	rm -f SolverConnect *.o
