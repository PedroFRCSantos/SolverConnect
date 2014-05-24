#ifndef _SOLVER
#define _SOLVER

#include <boost/thread/mutex.hpp>
#include <boost/thread/thread.hpp>
#include <iostream>
#include <vector>
#include <stdlib.h>

#include "permutas.hpp"
#include "tabuleiro.hpp"

using namespace std;


class SOLVER
{

	private:

		PERMUTAS permutas;

		vector<TABULEIRO*> tabs;
		bool* tabs_thr;
		int* linhas1;
		int* colunas1;
		int* linhas2;
		int* colunas2;
		char* designacao;

		boost::mutex key_tabs_thr;
		boost::thread** thrs;
		bool lancadas;
		bool encontrada;
		boost::mutex print_sol;
		bool init_printado;

	public:

		SOLVER(int n, int in_n_lin, int in_n_col);

		void set_linhas_colunas_id(int linha1, int coluna1, int linha2, int coluna2,int id, int index);

		void lanca_trabalhadores();

		void trabalho_realizar(int* ordem, int id_tab);

		void recursao_solver(int i, int j, int id_tab, int* ordem, int id_ordem);

		void espra_por_threads();

		~SOLVER();

	private:

		void trabalhador();

};

#endif

