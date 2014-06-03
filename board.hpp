#ifndef _BOARD
#define _BOARD

#include <stdio.h>
#include <iostream>
#include <fstream>

#define VERTICAL 'V'
#define HORIZONTAL 'H'
#define DOWN2LEFT 'Q'
#define DOWN2RIGTH 'R'
#define UP2LEFT 'S'
#define UP2RIGTH 'A'

using namespace std;

typedef struct _matixIndex {

	int indI;
	int indJ;

}matixIndex;

class BOARD
{

	private:

		char** data;
		matixIndex** prevNode;
		int n_lin, n_col;

	public:

		BOARD(int in_n_lin, int in_n_col);

		void set_data(int i, int j, char data_in);

		void setPreviousNode(int iAnt, int jAnt, int iAct, int jAct);

		char get_data(int i, int j);

		void reset_tab();

		int get_n_lines();

		int get_n_columns();

		void print_board();

		void print_board(bool write2File);

		bool verify_sol();

		~BOARD();

};

#endif
