
#include "stdafx.h"

#include "GlobalData.hpp"
#ifdef USE_MULTI_THREAD
#include <boost/thread/thread.hpp>
#endif

int GlobalData::numberCores = 0;

void GlobalData::setNumberPoints(int nPoints)
{

	#ifdef USE_MULTI_THREAD

		int n = boost::thread::hardware_concurrency();

		if(nPoints < n)
		{
	
			numberCores = nPoints;
	
		}else{

			numberCores = n;

		}

	#else

		numberCores = 1;

	#endif

}

int GlobalData::getNumberOfCores()
{

	return GlobalData::numberCores;

}
