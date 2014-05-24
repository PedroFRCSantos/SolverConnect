
#include "stdafx.h"

#include "GlobalData.hpp"
#include <boost/thread/thread.hpp>

int GlobalData::numberCores = 0;

void GlobalData::setNumberPoints(int nPoints)
{

	int n = boost::thread::hardware_concurrency();

	if(nPoints < n)
	{
	
		numberCores = nPoints;
	
	}else{

		numberCores = n;

	}

}

int GlobalData::getNumberOfCores()
{

	return GlobalData::numberCores;

}
