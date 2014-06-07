
#include "stdafx.h"

#ifndef GLOBAL_DATA_HPP
#define GLOBAL_DATA_HPP

#define USE_MULTI_THREAD

class GlobalData
{

	private:

		static int numberCores;

	public:

		static void setNumberPoints(int nPoints);

		static int getNumberOfCores();

};

#endif
