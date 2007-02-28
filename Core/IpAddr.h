//$Author: gourf $
//$Date: 2005/10/13 16:02:50 $
//$Id: IpAddr.h,v 1.5 2005/10/13 16:02:50 gourf Exp $
//---------------------------------------------------------------------------

#ifndef IpAddrH
#define IpAddrH

#include "Constant.h"
#include "Global.h"
#include "windows.h"
#include "Functions.h"
#include "IpDataGram.h"
#include "EtherDataGram.h"
#include <string.h>

class TIpAddr
{
    private:
        //AnsiString ipTemp;
        AnsiString FillStr(AnsiString sIp);
        bool JudgeValue(char *str);
        AnsiString ipBuf;
    public:
		TIpAddr(AnsiString ip);
		TIpAddr();
		bool IsValid();

		bool operator >(const TIpAddr &Ip);
		bool operator <(const TIpAddr &Ip);
        bool operator == (const TIpAddr &Ip);
		TIpAddr & operator=(AnsiString sIp);
};
//---------------------------------------------------------------------------
#endif
