
#include "stdafx.h"

#include <iostream>
#include <fstream>
#include <string>
#include <boost/thread/thread.hpp>

#include "solver.hpp"
#include "GlobalData.hpp"

int main(int argc, char* argv[])
{

	int n_cores, n_col, n_lin, n_col2, n_lin2;
	int i;
	char desig;
	bool usedFile = false;

	ifstream configFile;

	if(argc == 1)
	{

		cout << "Insira o numero de cores:" << endl;
		cin >> n_cores;

		cout << "Insira o numero de linhas:" << endl;
		cin >> n_lin;

		cout << "Insira o numero de colunas:" << endl;
		cin >> n_col;

	} else{
	
		// open to read config file
		configFile.open(argv[1]);

		if(configFile.is_open())
		{
		
			usedFile = true;

			configFile >> n_lin;
			configFile >> n_col;

			configFile >> n_cores;

		}
	
	}

	GlobalData::setNumberPoints(n_cores);

	SOLVER solver(n_cores, n_lin, n_col);

	if(!usedFile)
	{

		for(i = 0; i < n_cores; i++)
		{

			cout << "Insira a linha1(1-n) da cor "<< i+1 << ":" << endl;
			cin >> n_lin;

			cout << "Insira a coluna1(1-n) da cor "<< i+1 << ":" << endl;
			cin >> n_col;

			cout << "Insira a linha2(1-n) da cor "<< i+1 << ":" << endl;
			cin >> n_lin2;

			cout << "Insira a coluna2(1-n) da cor "<< i+1 << ":" << endl;
			cin >> n_col2;

			cout << "Insira a designacao:" << endl;
			cin >> desig;

			solver.set_linhas_colunas_id(n_lin-1, n_col-1, n_lin2-1, n_col2-1,desig, i);

		}

	} else{
	
		// read final definitions
		for(i = 0; i < n_cores; i++)
		{
		
			configFile >> n_lin;
			configFile >> n_col;
			configFile >> desig;

			configFile >> n_lin2;
			configFile >> n_col2;
			configFile >> desig;

			solver.set_linhas_colunas_id(n_lin-1, n_col-1, n_lin2-1, n_col2-1,desig, i);
		
		}

	}

	std::clock_t start;
	start = std::clock();

	solver.lanca_trabalhadores();
	solver.espra_por_threads();

	cout << "Time: " << (std::clock() - start) / (double)(CLOCKS_PER_SEC / 1000) << " ms" << endl;
	//cout << "Press enter to continue...." << endl;
	//cin >> desig;

	return 0;

}
