#include "stdafx.h"

#include "permutas.hpp"
#include "GlobalData.hpp"

PERMUTAS::PERMUTAS()
{}

PERMUTAS::PERMUTAS(int n_in)
{

	set_n(n_in);

}

int* PERMUTAS::get_order_of_try(int ind)
{

	return parcial_tab[ind];

}

void PERMUTAS::set_n(int n_in)
{

	n = n_in;

	calculate_number_combinations();

	cout << "Number of colors: " << n << endl;
	estimate_possible_permutations();

}

int PERMUTAS::get_number_colors()
{

	return n;

}

PERMUTAS::~PERMUTAS()
{

	int i;

	delete num;

	for(i = 0; i < GlobalData::getNumberOfCores(); i++)
	{

		delete parcial_tab[i];

	}

	delete parcial_tab;

}

void PERMUTAS::estimate_possible_permutations()
{

	int i, j, k, ind;
	bool dif_int, dif;

	num = new bool[n];

	parcial_tab = new int*[GlobalData::getNumberOfCores()];

	for(i = 0; i < GlobalData::getNumberOfCores(); i++)
	{

		parcial_tab[i] = new int[n];

	}

	// encontra permutações possiveis
	for(i = 0; i < GlobalData::getNumberOfCores(); i++)
	{

		// reset num
		for(j = 0; j < n; j++)
		{

			num[j] = false;

		}

		for(j = 0; j < n; j++)
		{

			ind = rand()%n;
			while(num[ind] == true)
			{

				ind = rand()%n;

			}

			num[ind] = true;
			parcial_tab[i][j] = ind + 1;

		}

		if(i != 0)
		{

			dif = true;

			for(k = 0; k < i; k++)
			{

				dif_int = false;

				for(j = 0; j < i; j++)
				{

					if(parcial_tab[i][j] != parcial_tab[k][j])
					{

						dif_int = true;

					}

				}

				if(dif_int == false)
				{

					dif = false;

				}

			}

			// verifica se todos começam com cores diferentes
			for(k = 0; k <= i; k++)
			{

				for(j = 0; j <= i; j++)
				{

					if(j != k && parcial_tab[k][0] == parcial_tab[j][0])
					{

						dif = false;

					}

				}

			}

			if(dif == false)
			{

				i--;

			}

		}

	}

}

void PERMUTAS::calculate_number_combinations()
{

	int resultado = 1;
	int i;

	for(i = n; i >= 1; i--)
	{

		resultado *= i;

	}

	n_possibilities = resultado;

}

