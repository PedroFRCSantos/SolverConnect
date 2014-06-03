#include "stdafx.h"

#include "board.hpp"

BOARD::BOARD(int in_n_lin, int in_n_col)
{

	int i;

	n_lin = in_n_lin;
	n_col = in_n_col;

	data = new char*[n_lin];
	prevNode = new matixIndex*[n_lin];

	for(i = 0; i < n_lin; i++)
	{

		data[i] = new char[n_col];
		prevNode[i] = new matixIndex[n_col];

	}

	reset_tab();

}

void BOARD::set_data(int i, int j, char data_in)
{
	
	// verify limits
	if(!(i >= 0 && j >= 0 && i < n_lin && j < n_col))
	{
	
		throw("Board out of range in set_dados!!!");

	}

	data[i][j] = data_in;

}

void BOARD::setPreviousNode(int iAnt, int jAnt, int iAct, int jAct)
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

char BOARD::get_data(int i, int j)
{

	return data[i][j];

}

void BOARD::reset_tab()
{

	int i, j;

	matixIndex emptyVal;
	emptyVal.indI = -1;
	emptyVal.indJ = -1;

	for(i = 0; i < n_lin; i++)
	{

		for(j = 0; j < n_col; j++)
		{

			data[i][j] = '\0';
			prevNode[i][j] = emptyVal;

		}

	}

}

bool BOARD::verify_sol()
{

	int i, j;

	// caso tenha algum espaço vazio
	for(i = 0 ; i < n_lin; i++)
	{

		for(j = 0; j < n_col; j++)
		{

			if(data[i][j] == '\0')
			{

				return false;

			}

		}

	}

	return true;

}

int BOARD::get_n_lines()
{

	return n_lin;

}

int BOARD::get_n_columns()
{

	return n_col;

}

void BOARD::print_board()
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

			if(data[i][j] == '\0')
			{

				printf("| ");

			}else{

				printf("|%c", data[i][j]);

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

void BOARD::print_board(bool write2File)
{

	print_board();

	if(write2File)
	{
	
		ofstream resultFile("result.txt");
		int i, j;

		for(i = 0; i < n_lin; i++)
		{

			for(j = 0; j < n_col; j++)
			{

				if(data[i][j] != '\0')
				{

					resultFile << i << " " << j << " " << data[i][j] << " " << prevNode[i][j].indI << " " << prevNode[i][j].indJ << endl;
				
				}

			}

		}
	
	}

}

BOARD::~BOARD()
{

	int i;

	for(i = 0; i < n_lin; i++)
	{

		delete data[i];
		delete prevNode[i];

	}

	delete data;
	delete prevNode;

}

