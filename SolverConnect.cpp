
#include "stdafx.h"

#include <iostream>
#include <boost/thread/thread.hpp>

#include "solver.hpp"
#include "GlobalData.hpp"

int main(int argc, char* argv[])
{

	int n_cores, n_col, n_lin, n_col2, n_lin2;
	int i;
	char desig;

	cout << "Insira o numero de cores:" << endl;
	cin >> n_cores;

	cout << "Insira o numero de linhas:" << endl;
	cin >> n_lin;

	cout << "Insira o numero de colunas:" << endl;
	cin >> n_col;

	GloabalData::setNumberPoints(n_cores);

	SOLVER solver(n_cores, n_lin, n_col);

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

	solver.lanca_trabalhadores();
	solver.espra_por_threads();

	cout << "Press enter to continue...." << endl;
	cin >> desig;

	return 0;

}
