#ifndef _TABULEIRO
#define _TABULEIRO

#include <stdio.h>
#include <iostream>
#include <fstream>

#define VERTICAL 'V'
#define HORIZONTAL 'H'
#define DOWN2LEFT 'Q'
#define DOWN2RIGTH 'R'
#define UP2LEFT 'S'
#define UP2RIGTH 'A'

using namespace std;

typedef struct _matixIndex {

	int indI;
	int indJ;

}matixIndex;

class TABULEIRO
{

	private:

		char** dados;
		matixIndex** prevNode;
		int n_lin, n_col;

	public:

		TABULEIRO(int in_n_lin, int in_n_col);

		void set_dados(int i, int j, char data_in);

		void setPreviousNode(int iAnt, int jAnt, int iAct, int jAct);

		char get_dados(int i, int j);

		void reset_tab();

		int get_n_linhas();

		int get_n_colunas();

		void print_tabuleiro();

		void print_tabuleiro(bool write2File);

		bool verifica_sol();

		~TABULEIRO();

};

#endif

