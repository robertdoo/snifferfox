// Author: zhengsh
// Date: 2005/10/03 06:40:20
// $Id: RecvThread.cpp,v 1.7 2005/10/12 03:18:25 zhengsh Exp $

//---------------------------------------------------------------------------

#include <vcl.h>
#include "winsock2.h"
#include "Global.h"
#include "Functions.h"
#include "IpDataGram.h"
#include "MainWin.h"

#pragma hdrstop



#include "RecvThread.h"
#pragma package(smart_init)
//---------------------------------------------------------------------------

//   Important: Methods and properties of objects in VCL can only be
//   used in a method called using Synchronize, for example:
//
//      Synchronize(UpdateCaption);
//
//   where UpdateCaption could look like:
//
//      void __fastcall TRecvThread::UpdateCaption()
//      {
//        Form1->Caption = "Updated in a thread";
//      }
//---------------------------------------------------------------------------

__fastcall TRecvThread::TRecvThread(bool CreateSuspended)
    : TThread(CreateSuspended)
{
    //m_Socket = 0;
    Priority = tpIdle;
    adhandle = 0;
    //if (CreateSuspended)
        //Suspend();
}

bool TRecvThread::Initialize(pcap_if_t * pDev,AnsiString &szError)
{
    char errbuf[PCAP_ERRBUF_SIZE];
    //select network card
	if ( (adhandle= pcap_open_live(pDev->name,
	              65536,   // portion of the packet to capture.
	                       // 65536 grants that the whole packet will be captured on all the MACs.
	              1,       // 混杂模式
	              1000,
	              errbuf   // error buffer
	              ) ) == NULL)
	{
	    szError = g_pLanguage->GetValue("ERROR_UNABLE_OPEN_NIC") + "\n";
	    szError += g_pLanguage->GetValue("ERROR_UNABLE_OPEN_NIC_ERROR_CODE") + "\n";
        szError += errbuf;
        return false;
    }
    return true;
}

/* prototype of the packet handler */
void packet_handler(u_char *param, const struct pcap_pkthdr *header, const u_char *pkt_data)
{
	if (frmMain->DataProcess(header,pkt_data))
		g_nSaveCount++;
	g_nTotalCount++;
}

void __fastcall TRecvThread::DataProcess()
{
    pcap_loop(adhandle, 0, packet_handler, NULL);
    //frmMain->DataProcess(pHead,pData);
}


//---------------------------------------------------------------------------
void __fastcall TRecvThread::Execute()
{
    while (true)
    {
        /* 开始捕获包 */
        pcap_loop(adhandle, 0, packet_handler, NULL);
        //Synchronize((TThreadMethod)&DataProcess);
	}
    //Synchronize((TThreadMethod)&DataProcess);
}
//---------------------------------------------------------------------------

bool TRecvThread::Close()
{
    //closesocket(m_Socket);
    adhandle = 0;
    //WSACleanup();
    return true;
}

bool TRecvThread::IsInitialized()
{
    if ( adhandle == 0 )
        return false;
    return true;
}




