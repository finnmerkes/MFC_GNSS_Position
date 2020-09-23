#pragma once

struct gnss_position 
{
	char verticalCD;			// cardinal direction
	char horizontalCD;
	float verticalDM;			// degree / minutes
	float horizontalDM;
};

class PosAverager
{
private:
	gnss_position* positions;
	gnss_position average;
	int lastAdded;
	int length = 16;
	bool filled = false;

public:

	PosAverager();
	PosAverager(unsigned int length);
	~PosAverager();
	bool filledUp();
	void insertPosition(gnss_position pos);
	void reset();
	bool toJson(CString path);
	gnss_position* getAverage();
};

