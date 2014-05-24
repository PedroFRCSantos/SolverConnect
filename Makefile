# -g -o para todos em vez de -o
libs = -lboost_thread -pthread
# DEBUG
#type = -g -c
#typeg = -g -o
# RELEASE
type = -c -O3
typeg = -o

all: SolverConnect

SolverConnect: GlobalData.o SolverConnect.o permutas.o solver.o tabuleiro.o
	g++ $(typeg) SolverConnect GlobalData.o SolverConnect.o permutas.o solver.o tabuleiro.o $(libs)

SolverConnect.o: SolverConnect.cpp solver.hpp  permutas.hpp GlobalData.hpp stdafx.h
	g++ $(type) SolverConnect.cpp $(libs)

permutas.o: permutas.cpp permutas.hpp GlobalData.hpp stdafx.h
	g++ $(type) permutas.cpp $(libs)

solver.o: solver.cpp solver.hpp permutas.hpp tabuleiro.hpp GlobalData.hpp stdafx.h
	g++ $(type) solver.cpp $(libs)

tabuleiro.o: tabuleiro.cpp tabuleiro.hpp stdafx.h
	g++ $(type) tabuleiro.cpp $(libs)
	
GlobalData.o: GlobalData.cpp GlobalData.hpp stdafx.h
	g++ $(type) GlobalData.cpp $(libs)

clean:
	rm -f SolverConnect *.o
