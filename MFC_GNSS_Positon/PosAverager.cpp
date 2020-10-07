#include "stdafx.h"
#include "PosAverager.h"
#include <time.h>


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

gnss_position PosAverager::insertPosition(gnss_position pos)
{
	lastAdded++;
	positions[lastAdded] = pos;

	if (lastAdded == length - 1)
	{
		lastAdded = -1;
		filled = true;
	}

	gnss_position av;
	av.horizontalDM = 0.f;
	av.verticalDM = 0.f;

	if (filled) 
	{
		for (int i = 0; i < length; i++)
		{
			av.horizontalDM += positions[i].horizontalDM;
			av.verticalDM += positions[i].verticalDM;
		}

		av.horizontalDM /= length;
		av.verticalDM /= length;
	}
	else
	{
		for (int i = 0; i <= lastAdded; i++)
		{
			av.horizontalDM += positions[i].horizontalDM;
			av.verticalDM += positions[i].verticalDM;
		}

		av.horizontalDM /= lastAdded + 1;
		av.verticalDM /= lastAdded + 1;
	}

	average = &av;
	return av;
}

bool PosAverager::toJson(CString path)
{
	FILE* fp;

#pragma region FilePath

	time_t timestamp;
	tm* nun;
	
	timestamp = time(0);
	nun = localtime(&timestamp);
	
	CString filepath_string;
	CString tmp;
	filepath_string = path;
	filepath_string += "koordinate_vom{";

	tmp.Format(_T("%d"), nun->tm_mday);
	filepath_string += tmp;
	filepath_string += "_";
	tmp.Format(_T("%d"), nun->tm_mon + 1);
	filepath_string += tmp;
	filepath_string += "_";
	tmp.Format(_T("%d"), nun->tm_year + 1900);
	filepath_string += tmp;
	filepath_string += "(";
	tmp.Format(_T("%d"), nun->tm_hour);
	filepath_string += tmp;
	filepath_string += "-";
	tmp.Format(_T("%d"), nun->tm_min);
	filepath_string += tmp;
	filepath_string += "-";
	tmp.Format(_T("%d"), nun->tm_sec);
	filepath_string += tmp;
	filepath_string += ")}";

	filepath_string += ".gpx";

	CT2A filepath_cca(filepath_string);
	TRACE(_T("ASCII: %S\n"), filepath_cca.m_psz);

#pragma endregion
	
	fopen_s(&fp, filepath_cca, "w");

	fprintf_s(fp, "<?xml version =\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>\n<gpx version=\"1.1\">\n");


	CString lat;
	CString lon;
	CString iString;
	CString lines_string;

	if (filled)
	{
		for (int i = 0; i < length; i++)
		{
			lat.Format(_T("%.10f"), positions[i].horizontalDM);
			lon.Format(_T("%.10f"), positions[i].verticalDM);
			iString.Format(_T("%d"), i);

			lines_string = "<wpt lat=\"";
			lines_string += lat;
			lines_string += "\" lon=\"";
			lines_string += lon;
			lines_string += "\">\n<ele>137</ele>\n<name>WP";
			lines_string += iString;
			lines_string += "</name>\n</wpt>\n";

			CT2A lines_cca(lines_string);
			TRACE(_T("ASCII: %S\n"), lines_cca.m_psz);

			fprintf_s(fp, lines_cca);
		}
	}
	else 
	{
		for (int i = 0; i <= lastAdded; i++)
		{
			lat.Format(_T("%.10f"), positions[i].horizontalDM);
			lon.Format(_T("%.10f"), positions[i].verticalDM);
			iString.Format(_T("%d"), i);

			lines_string = "<wpt lat=\"";
			lines_string += lat;
			lines_string += "\" lon=\"";
			lines_string += lon;
			lines_string += "\">\n<ele>137</ele>\n<name>WP";
			lines_string += iString;
			lines_string += "</name>\n</wpt>\n";

			CT2A lines_cca(lines_string);
			TRACE(_T("ASCII: %S\n"), lines_cca.m_psz);

			fprintf_s(fp, lines_cca);
		}
	}

	lat.Format(_T("%.10f"), average->horizontalDM);
	lon.Format(_T("%.10f"), average->verticalDM);

	lines_string = "<wpt lat=\"";
	lines_string += lat;
	lines_string += "\" lon=\"";
	lines_string += lon;
	lines_string += "\">\n<ele>137</ele>\n<name>AVERAGE</name>\n</wpt>\n";

	CT2A ascii4(lines_string);
	TRACE(_T("ASCII: %S\n"), ascii4.m_psz);

	fprintf_s(fp, ascii4);
	fprintf_s(fp, "</gpx>");

	fclose(fp);
	OutputDebugStringA("File created!\n");

	return true;
}
