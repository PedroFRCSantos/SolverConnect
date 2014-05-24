#include "stdafx.h"

#include "solver.hpp"

SOLVER::SOLVER(int n, int in_n_lin, int in_n_col)
{

	int i;

	encontrada = false;
	lancadas = false;
	init_printado =  false;

	permutas.set_n(n);

	tabs_thr = new bool[numero_cores()];

	for(i = 0; i < numero_cores(); i++)
	{

		TABULEIRO* novo_tab = new TABULEIRO(in_n_lin, in_n_col);
		tabs.push_back(novo_tab);

		tabs_thr[i] = false;

	}

	linhas1 = new int[n];
	colunas1 = new int[n];
	linhas2 = new int[n];
	colunas2 = new int[n];
	designacao = new char[n];

}

void SOLVER::set_linhas_colunas_id(int linha1, int coluna1, int linha2, int coluna2,int id, int index)
{

	linhas1[index] = linha1;
	colunas1[index] = coluna1;
	linhas2[index] = linha2;
	colunas2[index] = coluna2;
	designacao[index] = id;

}

void SOLVER::lanca_trabalhadores()
{

	int i;

	// lança a threads
	thrs = new boost::thread*[numero_cores()];

	for(i = 0; i < numero_cores(); i++)
	{

		thrs[i] = new boost::thread(boost::bind(&SOLVER::trabalhador, this));
		//cout << "Thread " << i << " criada!!!" << endl;

	}

	lancadas = true;

}

void SOLVER::trabalhador()
{

	int i;

	int* ordem_teste;

	int id_tab;

	//cout << "Sou um trabalhador!!!" << endl;

	id_tab = -1;

	// encontra o indice de tabela disponivel
	key_tabs_thr.lock();

	for(i = 0; i < numero_cores() && i < permutas.get_numero_cores(); i++)
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

	ordem_teste = permutas.get_ordem_tentativa(id_tab);

	trabalho_realizar(ordem_teste, id_tab);

}

void SOLVER::trabalho_realizar(int* ordem, int id_tab)
{

	int i;

	tabs[id_tab]->reset_tab();

	// coloca as marcas no lugar
	for(i = 0; i < permutas.get_numero_cores(); i++)
	{

		tabs[id_tab]->set_dados(linhas1[i], colunas1[i], designacao[i]);
		tabs[id_tab]->set_dados(linhas2[i], colunas2[i], designacao[i]);

	}

	// imprime tabuleiro inicial
	print_sol.lock();

	if(init_printado == false)
	{

		cout << "Tabuleiro inicial!!!" << endl;
		tabs[id_tab]->print_tabuleiro();

	}

	init_printado = true;

	print_sol.unlock();

	recursao_solver(linhas1[ordem[0]-1], colunas1[ordem[0]-1], id_tab, ordem, 0);

}

void SOLVER::recursao_solver(int i, int j, int id_tab, int* ordem, int id_ordem)
{

	int aux_i, aux_j;
	char ant;

	//cout << "i: " << i << " j: " << j << endl;

	if(encontrada)
	{

		return;

	}

	// caso tenha chegado ao outro ponto
	if(linhas2[ordem[id_ordem]-1] == i && colunas2[ordem[id_ordem]-1] == j)
	{

		//cout << "cheguie ao outro ponto!!!" << endl;

		// passa para a procima cor
		id_ordem++;

		if(id_ordem == permutas.get_numero_cores())
		{

			// verifica se o tabuleiro é valido
			if(tabs[id_tab]->verifica_sol() && encontrada == false)
			{

				encontrada = true;

				print_sol.lock();
				cout << "Solução encontrada:" << endl;
				tabs[id_tab]->print_tabuleiro();
				print_sol.unlock();

			}

			return;

		}else{

			recursao_solver(linhas1[ordem[id_ordem]-1], colunas1[ordem[id_ordem]-1], id_tab, ordem, id_ordem);

		}

	}else{

		// caso não tenha atigido o outro tenta andar
		// para cima
		if(i > 0)
		{

			aux_i = i - 1;
			aux_j = j;

			ant = tabs[id_tab]->get_dados(aux_i, aux_j);

			if(tabs[id_tab]->get_dados(aux_i, aux_j) == '\0' || (tabs[id_tab]->get_dados(aux_i, aux_j) == designacao[ordem[id_ordem]-1] && linhas2[ordem[id_ordem]-1] == aux_i && colunas2[ordem[id_ordem]-1] == aux_j))
			{

				//cout << "cima" << endl;
				tabs[id_tab]->set_dados(aux_i, aux_j, designacao[ordem[id_ordem]-1]);
				recursao_solver(aux_i, aux_j, id_tab, ordem, id_ordem);

				// repoe caso seja possivel
				if(ant == '\0')
				{

					tabs[id_tab]->set_dados(aux_i, aux_j, '\0');

				}

			}

		}

		// para baixo
		if(i < tabs[id_tab]->get_n_linhas()-1)
		{

			aux_i = i + 1;
			aux_j = j;

			ant = tabs[id_tab]->get_dados(aux_i, aux_j);

			if(tabs[id_tab]->get_dados(aux_i, aux_j) == '\0' || (tabs[id_tab]->get_dados(aux_i, aux_j) == designacao[ordem[id_ordem]-1] && linhas2[ordem[id_ordem]-1] == aux_i && colunas2[ordem[id_ordem]-1] == aux_j))
			{

				//cout << "baixo" << endl;
				tabs[id_tab]->set_dados(aux_i, aux_j, designacao[ordem[id_ordem]-1]);
				recursao_solver(aux_i, aux_j, id_tab, ordem, id_ordem);

				// repoe caso seja possivel
				if(ant == '\0')
				{

					tabs[id_tab]->set_dados(aux_i, aux_j, '\0');

				}

			}

		}

		// esquerda
		if(j > 0)
		{

			aux_i = i;
			aux_j = j - 1;

			ant = tabs[id_tab]->get_dados(aux_i, aux_j);

			if(tabs[id_tab]->get_dados(aux_i, aux_j) == '\0' || (tabs[id_tab]->get_dados(aux_i, aux_j) == designacao[ordem[id_ordem]-1] && linhas2[ordem[id_ordem]-1] == aux_i && colunas2[ordem[id_ordem]-1] == aux_j))
			{

				//cout << "esquerda" << endl;
				tabs[id_tab]->set_dados(aux_i, aux_j, designacao[ordem[id_ordem]-1]);
				recursao_solver(aux_i, aux_j, id_tab, ordem, id_ordem);

				// repoe caso seja possivel
				if(ant == '\0')
				{

					tabs[id_tab]->set_dados(aux_i, aux_j, '\0');

				}

			}

		}

		//direita
		if(j < tabs[id_tab]->get_n_colunas()-1)
		{

			aux_i = i;
			aux_j = j + 1;

			ant = tabs[id_tab]->get_dados(aux_i, aux_j);

			if(tabs[id_tab]->get_dados(aux_i, aux_j) == '\0' || (tabs[id_tab]->get_dados(aux_i, aux_j) == designacao[ordem[id_ordem]-1] && linhas2[ordem[id_ordem]-1] == aux_i && colunas2[ordem[id_ordem]-1] == aux_j))
			{

				//cout << "direita" << endl;
				tabs[id_tab]->set_dados(aux_i, aux_j, designacao[ordem[id_ordem]-1]);
				recursao_solver(aux_i, aux_j, id_tab, ordem, id_ordem);

				// repoe caso seja possivel
				if(ant == '\0')
				{

					tabs[id_tab]->set_dados(aux_i, aux_j, '\0');

				}

			}

		}

	}

}

void SOLVER::espra_por_threads()
{

	int i;

	if(lancadas)
	{

		for(i = 0; i < numero_cores(); i++)
		{

			thrs[i]->join();
			delete thrs[i];

		}

		delete thrs;

	}

}

SOLVER::~SOLVER()
{

	int i;

	for(i = 0; i < tabs.size(); i++)
	{

		delete tabs[i];

	}

	delete tabs_thr;

	delete linhas1;
	delete colunas1;
	delete linhas2;
	delete colunas2;
	delete designacao;

}

int SOLVER::numero_cores()
{

	// para teste
	return 1;

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

