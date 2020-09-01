// Serial.cpp: Implementierung der Klasse CSerial.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Serial.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Konstruktion/Destruktion
//////////////////////////////////////////////////////////////////////



CSerial::CSerial()
{
	hCom = NULL;
}

CSerial::~CSerial()
{

}

 

int CSerial::Open_Port(int PORT_NR) 
{ 
  BOOL fSuccess;
  DCB dcb;

  
  CString Com,Nr;
  Nr.Format(_T("%d"),PORT_NR);
  Com=_T("COM")+Nr;

  CWnd* p_Win;
  p_Win = AfxGetApp()->m_pMainWnd;  //Zeiger zur Benutzung der Fkt. MessageBox!
  p_Win->MessageBox(Com);
 

  hCom = CreateFile(Com,
      GENERIC_READ, //| GENERIC_WRITE,
      0,    /* comm devices must be opened w/exclusive-access */
      NULL, /* no security attrs */
      OPEN_EXISTING, /* comm devices must use OPEN_EXISTING */
      0,    /* not overlapped I/O */
      NULL  /* hTemplate must be NULL for comm devices */
      );

  if (hCom == INVALID_HANDLE_VALUE) 
  {
		CWnd* p_Win;
		p_Win=AfxGetApp()->m_pMainWnd;  //Zeiger zur Benutzung der Fkt. MessageBox!
		p_Win->MessageBox(_T("Com-Schnittstelle nicht geoeffnet\n"));
		return 1;
  }

  fSuccess = GetCommState(hCom, &dcb);

  if (!fSuccess) {
						//Handle the error. 
	  CWnd* p_Win;
	  p_Win=AfxGetApp()->m_pMainWnd;  //Zeiger zur Benutzung der Fkt. MessageBox!
	  p_Win->MessageBox(_T("Fehler: Kein Status\n"));
	  return 1;
	}
  return 0;
} 


int CSerial::Close_Port() 
{ 
	if (NULL == hCom)
	{
		return 0;
	}

    CloseHandle(hCom);
	hCom=NULL;
    return 0; 
} 

int CSerial::SetDTR(bool mode) 
{ 
    
    if(mode==ON) 
    {   
        EscapeCommFunction(hCom, SETDTR);  // setzen 
    } 
    else 
    { 
        EscapeCommFunction(hCom, CLRDTR);  // Loeschen   
    } 

    return 0; 
} 

int CSerial::SetRTS(bool mode) 
{ 
    if(mode==ON) 
    {   
        EscapeCommFunction(hCom, SETRTS);  // setzen 
    } 
    else 
    { 
        EscapeCommFunction(hCom, CLRRTS);  // Loeschen       
    } 
    return 0; 
} 

int CSerial::SetTXD(bool mode) 
{ 
    if(mode==ON) 
    {   
        EscapeCommFunction(hCom, SETBREAK);  // setzen 
    } 
    else 
    { 
        EscapeCommFunction(hCom, CLRBREAK);  // Loeschen     
    } 
    return 0; 
} 



bool CSerial::GetCTS() 
{ 
    GetCommModemStatus(hCom, &COMStatus);   
    if(COMStatus & MS_CTS_ON) 
    { 
        return ON; 
    } 
    return OFF; 
} 

bool CSerial::GetDSR() 
{ 
    GetCommModemStatus(hCom, &COMStatus);   
    if(COMStatus & MS_DSR_ON) 
    { 
        return ON; 
    } 
    return OFF; 
} 

bool CSerial::GetRI()
{
    GetCommModemStatus(hCom, &COMStatus);   
    if(COMStatus & MS_RING_ON) 
    { 
        return ON; 
    } 
    return OFF; 
}

bool CSerial::GetDCD()
{
    GetCommModemStatus(hCom, &COMStatus);   
    if(COMStatus & MS_RLSD_ON) 
    { 
        return ON; 
    } 
    return OFF; 
}

int  CSerial::SetAll (bool mode) 
{ 
    SetRTS(mode); 
    SetTXD(mode); 
    SetDTR(mode); 
	return 0;
}

int CSerial::ReadDataWaiting(void)
{

	if (NULL == hCom)
	{
		return(0);
	}

	DWORD dwErrorFlags;
	COMSTAT ComStat;

	ClearCommError(hCom, &dwErrorFlags, &ComStat);

	return((int)ComStat.cbInQue);

}

int CSerial::Read(char * buf, int buflen)
{
	DWORD       dwBytesTransferred;

	if (NULL == hCom)
	{
		return 0;
	}
    
	ReadFile(hCom, buf, buflen, &dwBytesTransferred, 0);  //read 1

	return dwBytesTransferred;
}

void CSerial::wait(int milli_sek)
{
  clock_t start;
  start = clock();
  while( clock() < start + milli_sek)
    ;
}


