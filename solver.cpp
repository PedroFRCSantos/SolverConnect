#include "stdafx.h"

#include "solver.hpp"
#include "GlobalData.hpp"

SOLVER::SOLVER(int n, int in_n_lin, int in_n_col)
{

	int i;

	found = false;

	#ifdef USE_MULTI_THREAD

		launched = false;
		init_print =  false;

	#endif

	permutas.set_n(n);

	tabs_thr = new bool[GlobalData::getNumberOfCores()];

	for(i = 0; i < GlobalData::getNumberOfCores(); i++)
	{

		BOARD* novo_tab = new BOARD(in_n_lin, in_n_col);
		tabs.push_back(novo_tab);

		tabs_thr[i] = false;

	}

	lines1 = new int[n];
	columns1 = new int[n];
	lines2 = new int[n];
	columns2 = new int[n];
	designation = new char[n];

}

void SOLVER::set_lines_columns_id(int line1In, int column1In, int line2In, int column2In,int idIn, int indexIn)
{

	lines1[indexIn] = line1In;
	columns1[indexIn] = column1In;
	lines2[indexIn] = line2In;
	columns2[indexIn] = column2In;
	designation[indexIn] = idIn;

}

void SOLVER::launch_workers()
{

	#ifdef USE_MULTI_THREAD

		int i;

		// launches threads
		thrs = new boost::thread*[GlobalData::getNumberOfCores()];

		for(i = 0; i < GlobalData::getNumberOfCores(); i++)
		{

			thrs[i] = new boost::thread(boost::bind(&SOLVER::workers, this));
			//cout << "Thread " << i << " created!!!" << endl;

		}

		launched = true;

	#else

		workers();

	#endif

}

void SOLVER::workers()
{

	int i;

	int* ordem_teste;

	int id_tab;

	//cout << "I'm a worker!!!" << endl;

	id_tab = -1;

	// finds the index of table available
	#ifdef USE_MULTI_THREAD
	key_tabs_thr.lock();
	#endif

	for(i = 0; i < GlobalData::getNumberOfCores(); i++)
	{

		if(tabs_thr[i] == false)
		{

			tabs_thr[i] = true;
			id_tab = i;
			break;

		}

	}

	#ifdef USE_MULTI_THREAD
	key_tabs_thr.unlock();
	#endif

	if(id_tab == -1)
	{

		//cout << "I'm out of work!!!" << endl;
		return;

	}

	ordem_teste = permutas.get_order_of_try(id_tab);

	work_to_do(ordem_teste, id_tab);

}

void SOLVER::work_to_do(int* order, int id_tab)
{

	int i;

	tabs[id_tab]->reset_tab();

	// put marks in place
	for(i = 0; i < permutas.get_number_colors(); i++)
	{

		tabs[id_tab]->set_data(lines1[i], columns1[i], designation[i]);
		tabs[id_tab]->set_data(lines2[i], columns2[i], designation[i]);

	}

	// prints initial board
	#ifdef USE_MULTI_THREAD

		print_sol.lock();

		if(init_print == false)
		{

			cout << "Initial Board!!!" << endl;
			tabs[id_tab]->print_board(true);

		}

		init_print = true;

		print_sol.unlock();

	#else

		cout << "Initial Board!!!" << endl;
		tabs[id_tab]->print_board(true);

	#endif

	recursion_solver(lines1[order[0]-1], columns1[order[0]-1], id_tab, order, 0);

}

void SOLVER::recursion_solver(int i, int j, int id_tab, int* order, int id_order)
{

	int aux_i, aux_j;
	char ant;

	//cout << "i: " << i << " j: " << j << endl;

	if(found)
	{

		return;

	}

	// in case to arrive to another point
	if(lines2[order[id_order]-1] == i && columns2[order[id_order]-1] == j)
	{

		//cout << "arrived to another point!!!" << endl;

		// passes to the next color
		id_order++;

		if(id_order == permutas.get_number_colors())
		{

			// checks if the board is valid
			#ifdef USE_MULTI_THREAD
			print_sol.lock();
			#endif

			if(tabs[id_tab]->verify_sol() && found == false)
			{

				found = true;

				cout << "Solution founded:" << endl;
				tabs[id_tab]->print_board(true);

			}

			#ifdef USE_MULTI_THREAD
			print_sol.unlock();
			#endif

			return;

		}else{

			recursion_solver(lines1[order[id_order]-1], columns1[order[id_order]-1], id_tab, order, id_order);

		}

	}else{

		// case has not reached the other tries to walk
		// up
		if(i > 0)
		{

			aux_i = i - 1;
			aux_j = j;

			ant = tabs[id_tab]->get_data(aux_i, aux_j);

			if(tabs[id_tab]->get_data(aux_i, aux_j) == '\0' || (tabs[id_tab]->get_data(aux_i, aux_j) == designation[order[id_order]-1] && lines2[order[id_order]-1] == aux_i && columns2[order[id_order]-1] == aux_j))
			{

				//cout << "up" << endl;
				tabs[id_tab]->set_data(aux_i, aux_j, designation[order[id_order]-1]);
				tabs[id_tab]->setPreviousNode(i, j, aux_i, aux_j);
				recursion_solver(aux_i, aux_j, id_tab, order, id_order);

				// Resets if possible
				if(ant == '\0')
				{

					tabs[id_tab]->set_data(aux_i, aux_j, '\0');

				}

			}

		}

		// down
		if(i < tabs[id_tab]->get_n_lines()-1)
		{

			aux_i = i + 1;
			aux_j = j;

			ant = tabs[id_tab]->get_data(aux_i, aux_j);

			if(tabs[id_tab]->get_data(aux_i, aux_j) == '\0' || (tabs[id_tab]->get_data(aux_i, aux_j) == designation[order[id_order]-1] && lines2[order[id_order]-1] == aux_i && columns2[order[id_order]-1] == aux_j))
			{

				//cout << "down" << endl;
				tabs[id_tab]->set_data(aux_i, aux_j, designation[order[id_order]-1]);
				tabs[id_tab]->setPreviousNode(i, j, aux_i, aux_j);
				recursion_solver(aux_i, aux_j, id_tab, order, id_order);

				// Resets if possible
				if(ant == '\0')
				{

					tabs[id_tab]->set_data(aux_i, aux_j, '\0');

				}

			}

		}

		// left
		if(j > 0)
		{

			aux_i = i;
			aux_j = j - 1;

			ant = tabs[id_tab]->get_data(aux_i, aux_j);

			if(tabs[id_tab]->get_data(aux_i, aux_j) == '\0' || (tabs[id_tab]->get_data(aux_i, aux_j) == designation[order[id_order]-1] && lines2[order[id_order]-1] == aux_i && columns2[order[id_order]-1] == aux_j))
			{

				//cout << "left" << endl;
				tabs[id_tab]->set_data(aux_i, aux_j, designation[order[id_order]-1]);
				tabs[id_tab]->setPreviousNode(i, j, aux_i, aux_j);
				recursion_solver(aux_i, aux_j, id_tab, order, id_order);

				// Resets if possible
				if(ant == '\0')
				{

					tabs[id_tab]->set_data(aux_i, aux_j, '\0');

				}

			}

		}

		// right
		if(j < tabs[id_tab]->get_n_columns()-1)
		{

			aux_i = i;
			aux_j = j + 1;

			ant = tabs[id_tab]->get_data(aux_i, aux_j);

			if(tabs[id_tab]->get_data(aux_i, aux_j) == '\0' || (tabs[id_tab]->get_data(aux_i, aux_j) == designation[order[id_order]-1] && lines2[order[id_order]-1] == aux_i && columns2[order[id_order]-1] == aux_j))
			{

				//cout << "right" << endl;
				tabs[id_tab]->set_data(aux_i, aux_j, designation[order[id_order]-1]);
				tabs[id_tab]->setPreviousNode(i, j, aux_i, aux_j);
				recursion_solver(aux_i, aux_j, id_tab, order, id_order);

				// Resets if possible
				if(ant == '\0')
				{

					tabs[id_tab]->set_data(aux_i, aux_j, '\0');

				}

			}

		}

	}

}

void SOLVER::wait_for_threads()
{

	#ifdef USE_MULTI_THREAD

	int i;

	if(launched)
	{

		for(i = 0; i < GlobalData::getNumberOfCores(); i++)
		{

			thrs[i]->join();
			delete thrs[i];

		}

		delete thrs;

	}

	#endif

}

SOLVER::~SOLVER()
{

	unsigned int i;

	for(i = 0; i < tabs.size(); i++)
	{

		delete tabs[i];

	}

	delete tabs_thr;

	delete lines1;
	delete columns1;
	delete lines2;
	delete columns2;
	delete designation;

}
