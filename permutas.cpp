#include "stdafx.h"

#include "permutas.hpp"

PERMUTAS::PERMUTAS()
{}

PERMUTAS::PERMUTAS(int n_in)
{

	set_n(n_in);

}

int* PERMUTAS::get_ordem_tentativa(int ind)
{

	return parcial_tab[ind];

}

void PERMUTAS::set_n(int n_in)
{

	n = n_in;

	calcula_numero_combinacoes();

	cout << "Numero de cores: " << n << endl;
	estima_permutacoes_possiveis();

}

int PERMUTAS::get_numero_cores()
{

	return n;

}

PERMUTAS::~PERMUTAS()
{

	int i;

	delete num;

	for(i = 0; i < numero_cores(); i++)
	{

		delete parcial_tab[i];

	}

	delete parcial_tab;

}

void PERMUTAS::estima_permutacoes_possiveis()
{

	int i, j, k, ind;
	bool dif_int, dif;

	num = new bool[n];

	parcial_tab = new int*[numero_cores()];

	for(i = 0; i < numero_cores() && i < n; i++)
	{

		parcial_tab[i] = new int[n];

	}

	// encontra permutações possiveis
	for(i = 0; i < numero_cores() && i < n; i++)
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

		// teste
		/*for(j = 0; j < n; j++)
		{

			parcial_tab[i][j] = n-j;
			cout << n-j << endl;

		}*/

	}

	// para teste
	/*cout << endl;
	for(i = 0; i < numero_cores() && i < n; i++)
	{

		for(j = 0; j < n; j++)
		{

			cout << parcial_tab[i][j] << " ";

		}

		cout << endl;

	}
	cout << endl;*/

}

int PERMUTAS::numero_cores()
{

	// para teste
	return 10;

	/*#ifdef WIN32
		SYSTEM_INFO sysinfo;
		GetSystemInfo(&sysinfo);
		return sysinfo.dwNumberOfProcessors;
	#elif MACOS
		int nm[2];
		size_t len = 4;
		uint32_t count;

		nm[0] = CTL_HW; nm[1] = HW_AVAILCPU;
		sysctl(nm, 2, &count, &len, NULL, 0);

		if(count < 1) {
			nm[1] = HW_NCPU;
			sysctl(nm, 2, &count, &len, NULL, 0);
			if(count < 1) { count = 1; }
		}
		return count;
	#else
		return sysconf(_SC_NPROCESSORS_ONLN);
	#endif*/

}

void PERMUTAS::calcula_numero_combinacoes()
{

	int resultado = 1;
	int i;

	for(i = n; i >= 1; i--)
	{

		resultado *= i;

	}

	n_possibilidades = resultado;

}

