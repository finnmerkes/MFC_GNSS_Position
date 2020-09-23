#include "stdafx.h"
#include "PosAverager.h"


PosAverager::PosAverager()
{
	positions = new gnss_position[16]();
	lastAdded = -1;
	length = 16;
}

PosAverager::PosAverager(unsigned int length)
{
	positions = new gnss_position[length];
	lastAdded = -1;
	this->length = length;
}

PosAverager::~PosAverager()
{
	delete positions;
}

bool PosAverager::filledUp()
{
	return filled;
}

void PosAverager::insertPosition(gnss_position pos)
{
	lastAdded++;
	positions[lastAdded] = pos;

	if (lastAdded == length - 1)
	{
		lastAdded = -1;
		filled = true;
	}

	if (filled == true) 
	{
		gnss_position av;
		av.horizontalDM = 0;
		av.verticalDM = 0;

		for (int i = 0; i < length; i++)
		{
			av.horizontalDM += positions[i].horizontalDM;
			av.verticalDM += positions[i].verticalDM;
		}

		av.horizontalDM /= length;
		av.verticalDM /= length;

		average = av;
	}
}

gnss_position * PosAverager::getAverage()
{
	return &average;
}
