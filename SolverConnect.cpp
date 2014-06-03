
#include "stdafx.h"

#include <iostream>
#include <fstream>
#include <string>
#include <boost/thread/thread.hpp>

#include "solver.hpp"
#include "GlobalData.hpp"

int main(int argc, char* argv[])
{

	int n_color, n_col, n_lin, n_col2, n_lin2;
	int i;
	char desig;
	bool usedFile = false;

	ifstream configFile;

	if(argc == 1)
	{

		cout << "Insert number of pairs of points:" << endl;
		cin >> n_color;

		cout << "Insert number of lines:" << endl;
		cin >> n_lin;

		cout << "Insert number of colomns:" << endl;
		cin >> n_col;

	} else{
	
		// open to read config file
		configFile.open(argv[1]);

		if(configFile.is_open())
		{
		
			usedFile = true;

			configFile >> n_lin;
			configFile >> n_col;

			configFile >> n_color;

		}
	
	}

	GlobalData::setNumberPoints(n_color);

	SOLVER solver(n_color, n_lin, n_col);

	if(!usedFile)
	{

		for(i = 0; i < n_color; i++)
		{

			cout << "Insert the line1(1-n) associated to color "<< i+1 << ":" << endl;
			cin >> n_lin;

			cout << "Insert the column1(1-n) associated to color "<< i+1 << ":" << endl;
			cin >> n_col;

			cout << "Insert the line2(1-n) associated to color "<< i+1 << ":" << endl;
			cin >> n_lin2;

			cout << "Insert the column1(1-n) associated to color "<< i+1 << ":" << endl;
			cin >> n_col2;

			cout << "Insert the designation:" << endl;
			cin >> desig;

			solver.set_lines_columns_id(n_lin-1, n_col-1, n_lin2-1, n_col2-1,desig, i);

		}

	} else{
	
		// read final definitions
		for(i = 0; i < n_color; i++)
		{
		
			configFile >> n_lin;
			configFile >> n_col;
			configFile >> desig;

			configFile >> n_lin2;
			configFile >> n_col2;
			configFile >> desig;

			solver.set_lines_columns_id(n_lin-1, n_col-1, n_lin2-1, n_col2-1,desig, i);
		
		}

	}

	std::clock_t start;
	start = std::clock();

	solver.launch_workers();
	solver.wait_for_threads();

	cout << "Time: " << (std::clock() - start) / (double)(CLOCKS_PER_SEC / 1000) << " ms" << endl;
	//cout << "Press enter to continue...." << endl;
	//cin >> desig;

	return 0;

}
