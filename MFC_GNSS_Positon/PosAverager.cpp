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

}

gnss_position* PosAverager::insertPosition(gnss_position pos)
{
	lastAdded++;
	positions[lastAdded];

	if (lastAdded == length - 1) lastAdded = -1;

	int count;
	for (int i = 0; i < length; i++)
	{
		if (positions->verticalCD == '\0') count == i;
	}

	gnss_position av;
	for (int i = 0; i < count; i++)
	{
		av.horizontalDM += positions[i].horizontalDM;
		av.verticalDM += positions[i].verticalDM;
	}

	av.horizontalDM /= count;
	av.verticalDM /= count;

	char output[16];

	gcvt(av.horizontalDM, 9, output);

	OutputDebugStringA(output);
	return &av;
}