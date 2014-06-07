#ifndef _SOLVER
#define _SOLVER

#include <iostream>
#include <vector>
#include <stdlib.h>

#include "permutas.hpp"
#include "board.hpp"
#include "GlobalData.hpp"

#ifdef USE_MULTI_THREAD
#include <boost/thread/mutex.hpp>
#include <boost/thread/thread.hpp>
#endif

using namespace std;


class SOLVER
{

	private:

		PERMUTAS permutas;

		vector<BOARD*> tabs;
		bool* tabs_thr;
		int* lines1;
		int* columns1;
		int* lines2;
		int* columns2;
		char* designation;

		bool found;

		#ifdef USE_MULTI_THREAD

			boost::mutex key_tabs_thr;
			boost::thread** thrs;
			bool launched;
			boost::mutex print_sol;
			bool init_print;

		#endif

	public:

		SOLVER(int n, int in_n_lin, int in_n_col);

		void set_lines_columns_id(int line1In, int column1In, int line2In, int column2In,int idIn, int indexIn);

		void launch_workers();

		void work_to_do(int* order, int id_tab);

		void recursion_solver(int i, int j, int id_tab, int* order, int id_order);

		void wait_for_threads();

		~SOLVER();

	private:

		void workers();

};

#endif

