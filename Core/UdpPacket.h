//$Author: zhengsh $
//$Date: 2005/10/14 04:16:38 $
//$Id: UdpPacket.h,v 1.4 2005/10/14 04:16:38 zhengsh Exp $
//---------------------------------------------------------------------------

#ifndef UdpPacketH
#define UdpPacketH

#include "Constant.h"
#include "Global.h"
#include "windows.h"
#include "Functions.h"
#include "IpDataGram.h"
#include "EtherDataGram.h"

typedef struct TUdpHeader{
    u_short src_port;
    u_short des_port;
    u_short data_len;
    u_short check_sum;
}TUdpHeader;

class TUdpPacket
{
    private:
        char pBuf[BUFFER_SIZE];
        TUdpHeader *pUdpHeader;
        int nLength;
    public:
        TUdpPacket();
        void Clear();
        void SetBuffer(u_char *aBuf,int aLength);

        AnsiString  GetSrcPort();
        AnsiString  GetDesPort();
        AnsiString  GetDataLen();
        AnsiString  GetCheckSum();

        AnsiString  GetAppProtocolName();
		void GetAppData16(TStrings *Strs);
		void GetAppDataAsc(TStrings *Strs);
};
//---------------------------------------------------------------------------
#endif
