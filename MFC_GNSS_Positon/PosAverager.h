#pragma once

struct gnss_position 
{
	char verticalCD;			// cardinal direction
	char horizontalCD;
	double verticalDM;			// degree / minutes
	double horizontalDM;
};

class PosAverager
{
private:
	gnss_position* positions;
	int lastAdded;
	int length = 16;
	bool filled = false;
	gnss_position average;

public:

	PosAverager();
	PosAverager(unsigned int length);
	~PosAverager();
	bool filledUp();
	gnss_position insertPosition(gnss_position pos);
	void reset();
	bool toJson(CString path);
};