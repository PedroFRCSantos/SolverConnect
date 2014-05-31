#include "stdafx.h"

#include "tabuleiro.hpp"

TABULEIRO::TABULEIRO(int in_n_lin, int in_n_col)
{

	int i;

	n_lin = in_n_lin;
	n_col = in_n_col;

	dados = new char*[n_lin];
	prevNode = new matixIndex*[n_lin];

	for(i = 0; i < n_lin; i++)
	{

		dados[i] = new char[n_col];
		prevNode[i] = new matixIndex[n_col];

	}

	reset_tab();

}

void TABULEIRO::set_dados(int i, int j, char data_in)
{
	
	// verify limits
	if(!(i >= 0 && j >= 0 && i < n_lin && j < n_col))
	{
	
		throw("Board out of range in set_dados!!!");

	}

	dados[i][j] = data_in;

}

void TABULEIRO::setPreviousNode(int iAnt, int jAnt, int iAct, int jAct)
{

	// verify limits
	if(!(iAnt >= 0 && jAnt >= 0 && iAnt < n_lin && jAnt < n_col && iAct >= 0 && jAct >= 0 && iAct < n_lin && jAct < n_col))
	{
	
		throw("Board out of range in setPreviousNode!!!");

	}

	matixIndex antNode;
	antNode.indI = iAnt; antNode.indJ = jAnt;

	prevNode[iAct][jAct] = antNode;

}

char TABULEIRO::get_dados(int i, int j)
{

	return dados[i][j];

}

void TABULEIRO::reset_tab()
{

	int i, j;

	matixIndex emptyVal;
	emptyVal.indI = -1;
	emptyVal.indJ = -1;

	for(i = 0; i < n_lin; i++)
	{

		for(j = 0; j < n_col; j++)
		{

			dados[i][j] = '\0';
			prevNode[i][j] = emptyVal;

		}

	}

}

bool TABULEIRO::verifica_sol()
{

	int i, j;

	// caso tenha algum espaço vazio
	for(i = 0 ; i < n_lin; i++)
	{

		for(j = 0; j < n_col; j++)
		{

			if(dados[i][j] == '\0')
			{

				return false;

			}

		}

	}

	return true;

}

int TABULEIRO::get_n_linhas()
{

	return n_lin;

}

int TABULEIRO::get_n_colunas()
{

	return n_col;

}

void TABULEIRO::print_tabuleiro()
{

	int i, j;

	// inicio da tabela
	for(i = 0; i < 2*n_col+1; i++)
	{

		printf("_");

	}

	printf("\n");

	for(i = 0; i < n_lin; i++)
	{

		for(j = 0; j < n_col; j++)
		{

			if(dados[i][j] == '\0')
			{

				printf("| ");

			}else{

				printf("|%c", dados[i][j]);

			}

			if(j+1 == n_col)
			{

				printf("|");

			}

		}

		printf("\n");

	}

	// fim da tabela
	for(i = 0; i < 2*n_col+1; i++)
	{

		printf("_");

	}

	printf("\n");

}

void TABULEIRO::print_tabuleiro(bool write2File)
{

	print_tabuleiro();

	if(write2File)
	{
	
		ofstream resultFile("result.txt");
		int i, j;

		for(i = 0; i < n_lin; i++)
		{

			for(j = 0; j < n_col; j++)
			{

				if(dados[i][j] != '\0')
				{

					resultFile << i << " " << j << " " << dados[i][j] << " " << prevNode[i][j].indI << " " << prevNode[i][j].indJ << endl;
				
				}

			}

		}
	
	}

}

TABULEIRO::~TABULEIRO()
{

	int i;

	for(i = 0; i < n_lin; i++)
	{

		delete dados[i];
		delete prevNode[i];

	}

	delete dados;
	delete prevNode;

}

