#ifndef _TABULEIRO
#define _TABULEIRO

#include <stdio.h>
#include <iostream>

class TABULEIRO
{

	private:

		char** dados;
		int n_lin, n_col;

	public:

		TABULEIRO(int in_n_lin, int in_n_col);

		void set_dados(int i, int j, char data_in);

		char get_dados(int i, int j);

		void reset_tab();

		int get_n_linhas();

		int get_n_colunas();

		void print_tabuleiro();

		bool verifica_sol();

		~TABULEIRO();

};

#endif

