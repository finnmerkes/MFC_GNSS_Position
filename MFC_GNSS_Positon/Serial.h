// Serial.h: Schnittstelle für die Klasse CSerial.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SERIAL_H__D1BCF972_5ECC_4272_8C2A_896D342F227E__INCLUDED_)
#define AFX_SERIAL_H__D1BCF972_5ECC_4272_8C2A_896D342F227E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define ON  true 
#define OFF false 



//////////////////////////////////////////////////////////////////////////////
//																			//
//	Die Klasse CSerial dient zur Steuerung der Kommunikation über die		// 
//	serielle Schnittstelle													//
//	Erstellt: A. John 12.09. 2004											//
//																			//
//////////////////////////////////////////////////////////////////////////////


class CSerial  
{
public:
	HANDLE hCom;			//Handel auf den Com-Port
    DWORD COMStatus;		//Word zum Speichern des Status 

public:
	CSerial();
	virtual ~CSerial();	

	int   Open_Port (int PORT_NR);	//Öffnet den Com-Port mit der Nr. "PORT_NR" 
    int   Close_Port (void);		//Schließt den geöffneten COM-Port

    int   SetDTR    (bool mode);	//Setzen des Pins DTR auf 0 (false) oder 1 (true)
    int   SetRTS    (bool mode);	//Setzen des Pins RTS auf 0 oder 1
    int   SetTXD    (bool mode);	//Setzen des Pins TXD auf 0 oder 1
    int   SetAll    (bool mode);	//Setzen aller Ausgänge
	
    bool  GetCTS();					//Einlesen des Zustands am Pin CTS
    bool  GetDSR();					//Einlesen des Zustands am Pin DSR	
	bool  GetRI();					//Einlesen des Zustands am Pin RI				
	bool  GetDCD();					//Einlesen des Zustands am Pin DCD

	void wait(int milli_sek);		//Warteschleife mit einer Verzögerung von "milli_sek" ms
};


#endif // !defined(AFX_SERIAL_H__D1BCF972_5ECC_4272_8C2A_896D342F227E__INCLUDED_)
