//---------------------------------------------------------------------------

#ifndef ConfigH
#define ConfigH
#include "vcl.h"
//---------------------------------------------------------------------------
bool GetSystemVariable(AnsiString Section,AnsiString Key,AnsiString &Value);
//���ϵͳ����

bool SetSystemVariable(AnsiString Section,AnsiString Key,AnsiString Value);
//����ϵͳ����

bool SetAutoRun();
//set auto run
bool UnsetAutoRun();
//Disable Auto Run
#endif
