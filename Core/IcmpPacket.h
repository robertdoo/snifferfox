//$Author: gourf $
//$Date: 2005/10/09 05:15:04 $
//$Id: IcmpPacket.h,v 1.2 2005/10/09 05:15:04 gourf Exp $
//---------------------------------------------------------------------------

#ifndef IcmpPacketH
#define IcmpPacketH

#include "Constant.h"
#include "Global.h"
#include "windows.h"
#include "Functions.h"
#include "IpDataGram.h"
#include "EtherDataGram.h"
//#include <time.h>

typedef struct TIcmpHeader{
    u_char      icmp_type;
    u_char      code;
    short int   check_sum;
}TIcmpHeader;


class TIcmpPacket//:public TIpDataGram,public TUdpDataGram
{
    private:
        char pBuf[BUFFER_SIZE];
        TIcmpHeader *pIcmpHeader;
        int nLength;

    public:
        void SetBuffer(u_char *aBuf);
        TIcmpPacket();
        void Clear();
        //~TIcmpPacket();
        AnsiString  GetType();
        AnsiString  GetCode();
        AnsiString  GetCheckSum();
        AnsiString  GetDescri();

};

//---------------------------------------------------------------------------
#endif
