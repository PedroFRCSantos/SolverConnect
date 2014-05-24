
#include "stdafx.h"

#include "GlobalData.hpp"
#include <boost/thread/thread.hpp>

int GloabalData::numberCores = 0;

void GloabalData::setNumberPoints(int nPoints)
{

	int n = boost::thread::hardware_concurrency();

	if(nPoints < n)
	{
	
		numberCores = nPoints;
	
	}else{

		numberCores = n;

	}

}

int GloabalData::getNumberOfCores()
{

	return GloabalData::numberCores;

}
