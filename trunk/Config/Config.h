//---------------------------------------------------------------------------

#ifndef ConfigH
#define ConfigH
#include "vcl.h"
//---------------------------------------------------------------------------
bool GetSystemVariable(AnsiString Section,AnsiString Key,AnsiString &Value);
//获得系统设置

bool SetSystemVariable(AnsiString Section,AnsiString Key,AnsiString Value);
//设置系统设置

bool SetAutoRun();
//set auto run
bool UnsetAutoRun();
//Disable Auto Run
#endif
