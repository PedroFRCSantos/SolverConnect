#include "stdafx.h"

#include "tabuleiro.hpp"

TABULEIRO::TABULEIRO(int in_n_lin, int in_n_col)
{

	int i;

	n_lin = in_n_lin;
	n_col = in_n_col;

	dados = new char*[n_lin];

	for(i = 0; i < n_lin; i++)
	{

		dados[i] = new char[n_col];

	}

	reset_tab();

}

void TABULEIRO::set_dados(int i, int j, char data_in)
{

	dados[i][j] = data_in;

}

char TABULEIRO::get_dados(int i, int j)
{

	return dados[i][j];

}

void TABULEIRO::reset_tab()
{

	int i, j;

	for(i = 0; i < n_lin; i++)
	{

		for(j = 0; j < n_col; j++)
		{

			dados[i][j] = '\0';

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

TABULEIRO::~TABULEIRO()
{

	int i;

	for(i = 0; i < n_lin; i++)
	{

		delete dados[i];

	}

	delete dados;

}

