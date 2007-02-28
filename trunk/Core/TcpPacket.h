//$Author: zhengsh $
//$Date: 2005/10/14 04:16:38 $
//$Id: TcpPacket.h,v 1.3 2005/10/14 04:16:38 zhengsh Exp $
//---------------------------------------------------------------------------

#ifndef TcpPacketH
#define TcpPacketH

#include "Constant.h"
#include "Global.h"
#include "windows.h"
#include "Functions.h"
#include "IpDataGram.h"
#include "EtherDataGram.h"
#include "vcl.h"

typedef struct TTcpHeader{
    u_short src_port;
    u_short des_port;
    int     seq_num;        //���
    int     ack_seq_num;    //ȷ�����
    u_short hlen_sign;
    u_short win_size;       //16λ���ڴ�С
    u_short check_sum;
    u_short urg_point;      //16λ����ָ��
}TTcpHeader;


class TTcpPacket
{
    private:
        TTcpHeader   *pTcpPacket;
        int          nLength;
        char         pBuf[BUFFER_SIZE];
    public:
        TTcpPacket();
        void Clear();
        void SetBuffer(u_char *aBuf,int aLength);

        AnsiString  GetSrcPort();
        AnsiString  GetDesPort();
        AnsiString  GetWindowSize();
        AnsiString  GetSeqNum();
        AnsiString  GetAckNum();
        AnsiString  GetAppProtocolName();
		void  GetAppData16(TStrings *Strs);
		void  GetAppDataAsc(TStrings *Strs);
};
//---------------------------------------------------------------------------
#endif
