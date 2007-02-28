// Author: zhengsh
// Date: 2005/10/03 06:40:20
// $Id: RecvThread.h,v 1.4 2005/10/07 13:28:15 zhengsh Exp $

//---------------------------------------------------------------------------

#ifndef RecvThreadH
#define RecvThreadH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <pcap.h>
#include "Constant.h"
#include <ws2tcpip.h>
#include <mstcpip.h>
//---------------------------------------------------------------------------
class TRecvThread : public TThread
{
private:
    //SOCKET m_Socket;
    pcap_t *adhandle;    
protected:
    void __fastcall Execute();
public:
    __fastcall TRecvThread(bool CreateSuspended = true);
    bool IsInitialized();
    bool Initialize(pcap_if_t * pDev,AnsiString &szError);
    //初始化指定网卡,成功则返回true,否则返回false
    bool Close();
    void  __fastcall DataProcess();
    void __fastcall ShowMsg(void);
    //void packet_handler(u_char *param, const struct pcap_pkthdr *header, const u_char *pkt_data);

};
//---------------------------------------------------------------------------
#endif
