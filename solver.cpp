#include "stdafx.h"

#include "solver.hpp"
#include "GlobalData.hpp"

SOLVER::SOLVER(int n, int in_n_lin, int in_n_col)
{

	int i;

	found = false;
	launched = false;
	init_print =  false;

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

	int i;

	// lança a threads
	thrs = new boost::thread*[GlobalData::getNumberOfCores()];

	for(i = 0; i < GlobalData::getNumberOfCores(); i++)
	{

		thrs[i] = new boost::thread(boost::bind(&SOLVER::workers, this));
		//cout << "Thread " << i << " criada!!!" << endl;

	}

	launched = true;

}

void SOLVER::workers()
{

	int i;

	int* ordem_teste;

	int id_tab;

	//cout << "Sou um trabalhador!!!" << endl;

	id_tab = -1;

	// encontra o indice de tabela disponivel
	key_tabs_thr.lock();

	for(i = 0; i < GlobalData::getNumberOfCores(); i++)
	{

		if(tabs_thr[i] == false)
		{

			tabs_thr[i] = true;
			id_tab = i;
			break;

		}

	}

	key_tabs_thr.unlock();

	if(id_tab == -1)
	{

		//cout << "estou sem trabalho!!!" << endl;
		return;

	}

	ordem_teste = permutas.get_order_of_try(id_tab);

	work_to_do(ordem_teste, id_tab);

}

void SOLVER::work_to_do(int* order, int id_tab)
{

	int i;

	tabs[id_tab]->reset_tab();

	// coloca as marcas no lugar
	for(i = 0; i < permutas.get_number_colors(); i++)
	{

		tabs[id_tab]->set_data(lines1[i], columns1[i], designation[i]);
		tabs[id_tab]->set_data(lines2[i], columns2[i], designation[i]);

	}

	// imprime tabuleiro inicial
	print_sol.lock();

	if(init_print == false)
	{

		cout << "Initial Board!!!" << endl;
		tabs[id_tab]->print_board(true);

	}

	init_print = true;

	print_sol.unlock();

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

	// caso tenha chegado ao outro ponto
	if(lines2[order[id_order]-1] == i && columns2[order[id_order]-1] == j)
	{

		//cout << "cheguie ao outro ponto!!!" << endl;

		// passa para a proxima cor
		id_order++;

		if(id_order == permutas.get_number_colors())
		{

			// verifica se o tabuleiro é valido
			print_sol.lock();

			if(tabs[id_tab]->verify_sol() && found == false)
			{

				found = true;

				cout << "Solution founded:" << endl;
				tabs[id_tab]->print_board(true);

			}

			print_sol.unlock();

			return;

		}else{

			recursion_solver(lines1[order[id_order]-1], columns1[order[id_order]-1], id_tab, order, id_order);

		}

	}else{

		// caso não tenha atigido o outro tenta andar
		// para cima
		if(i > 0)
		{

			aux_i = i - 1;
			aux_j = j;

			ant = tabs[id_tab]->get_data(aux_i, aux_j);

			if(tabs[id_tab]->get_data(aux_i, aux_j) == '\0' || (tabs[id_tab]->get_data(aux_i, aux_j) == designation[order[id_order]-1] && lines2[order[id_order]-1] == aux_i && columns2[order[id_order]-1] == aux_j))
			{

				//cout << "cima" << endl;
				tabs[id_tab]->set_data(aux_i, aux_j, designation[order[id_order]-1]);
				tabs[id_tab]->setPreviousNode(i, j, aux_i, aux_j);
				recursion_solver(aux_i, aux_j, id_tab, order, id_order);

				// repoe caso seja possivel
				if(ant == '\0')
				{

					tabs[id_tab]->set_data(aux_i, aux_j, '\0');

				}

			}

		}

		// para baixo
		if(i < tabs[id_tab]->get_n_lines()-1)
		{

			aux_i = i + 1;
			aux_j = j;

			ant = tabs[id_tab]->get_data(aux_i, aux_j);

			if(tabs[id_tab]->get_data(aux_i, aux_j) == '\0' || (tabs[id_tab]->get_data(aux_i, aux_j) == designation[order[id_order]-1] && lines2[order[id_order]-1] == aux_i && columns2[order[id_order]-1] == aux_j))
			{

				//cout << "baixo" << endl;
				tabs[id_tab]->set_data(aux_i, aux_j, designation[order[id_order]-1]);
				tabs[id_tab]->setPreviousNode(i, j, aux_i, aux_j);
				recursion_solver(aux_i, aux_j, id_tab, order, id_order);

				// repoe caso seja possivel
				if(ant == '\0')
				{

					tabs[id_tab]->set_data(aux_i, aux_j, '\0');

				}

			}

		}

		// esquerda
		if(j > 0)
		{

			aux_i = i;
			aux_j = j - 1;

			ant = tabs[id_tab]->get_data(aux_i, aux_j);

			if(tabs[id_tab]->get_data(aux_i, aux_j) == '\0' || (tabs[id_tab]->get_data(aux_i, aux_j) == designation[order[id_order]-1] && lines2[order[id_order]-1] == aux_i && columns2[order[id_order]-1] == aux_j))
			{

				//cout << "esquerda" << endl;
				tabs[id_tab]->set_data(aux_i, aux_j, designation[order[id_order]-1]);
				tabs[id_tab]->setPreviousNode(i, j, aux_i, aux_j);
				recursion_solver(aux_i, aux_j, id_tab, order, id_order);

				// repoe caso seja possivel
				if(ant == '\0')
				{

					tabs[id_tab]->set_data(aux_i, aux_j, '\0');

				}

			}

		}

		//direita
		if(j < tabs[id_tab]->get_n_columns()-1)
		{

			aux_i = i;
			aux_j = j + 1;

			ant = tabs[id_tab]->get_data(aux_i, aux_j);

			if(tabs[id_tab]->get_data(aux_i, aux_j) == '\0' || (tabs[id_tab]->get_data(aux_i, aux_j) == designation[order[id_order]-1] && lines2[order[id_order]-1] == aux_i && columns2[order[id_order]-1] == aux_j))
			{

				//cout << "direita" << endl;
				tabs[id_tab]->set_data(aux_i, aux_j, designation[order[id_order]-1]);
				tabs[id_tab]->setPreviousNode(i, j, aux_i, aux_j);
				recursion_solver(aux_i, aux_j, id_tab, order, id_order);

				// repoe caso seja possivel
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
