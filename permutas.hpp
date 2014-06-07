#ifndef _PERMUTAS
#define _PERMUTAS

#include <iostream>
#include <stdlib.h>

using namespace std;

class PERMUTAS
{

	private:

		int n; // numero de cores direntes
		int n_possibilities;

		bool* num; // numero que já foram usados
		int** parcial_tab;
	
	public:

		PERMUTAS();

		PERMUTAS(int n_in);

		void set_n(int n_in);

		int* get_order_of_try(int ind);

		int get_number_colors();

		~PERMUTAS();

	private:

		void estimate_possible_permutations();

		void calculate_number_combinations(); 

};

#endif

