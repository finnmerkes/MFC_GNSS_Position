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
	int lastAdded;
	int length;

public:

	PosAverager();
	PosAverager(unsigned int length);
	~PosAverager();
	bool filledUp();
	gnss_position* insertPosition(gnss_position pos);
	void reset();
	bool toJson(CString path);
};

