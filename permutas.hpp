#ifndef _PERMUTAS
#define _PERMUTAS

#include <boost/thread/mutex.hpp>
#include <boost/thread/thread.hpp>
#include <iostream>
#include <stdlib.h>

using namespace std;

class PERMUTAS
{

	private:

		int n; // numero de cores direntes
		int n_possibilidades;

		bool* num; // numero que já foram usados
		int** parcial_tab;
	
	public:

		PERMUTAS();

		PERMUTAS(int n_in);

		void set_n(int n_in);

		int* get_ordem_tentativa(int ind);

		int get_numero_cores();

		~PERMUTAS();

	private:

		void estima_permutacoes_possiveis();

		void calcula_numero_combinacoes(); 

};

#endif

