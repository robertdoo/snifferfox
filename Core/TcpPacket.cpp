//$Author: zhengsh $
//$Date: 2005/11/15 15:53:09 $
//$Id: TcpPacket.cpp,v 1.9 2005/11/15 15:53:09 zhengsh Exp $
//---------------------------------------------------------------------------


#pragma hdrstop

#include "TcpPacket.h"
#include "MsgDialog.h"

TTcpPacket::TTcpPacket()
{
    Clear();
}

void TTcpPacket::Clear()
{
    nLength = 0;
    pTcpPacket = NULL;
    memset(pBuf,0,BUFFER_SIZE);
}

void TTcpPacket::SetBuffer(u_char *aBuf,int aLength)
{
    Clear();
	nLength = aLength;
	if (nLength > BUFFER_SIZE)
		nLength = BUFFER_SIZE;
	memcpy(pBuf,aBuf,BUFFER_SIZE);
	//ShowMsg(aLength);
    pTcpPacket=(TTcpHeader *)pBuf;	
}

AnsiString  TTcpPacket::GetSrcPort()
{
		u_short temp;
    temp = ntohs( pTcpPacket->src_port );
    return (AnsiString)temp;	
}

AnsiString  TTcpPacket::GetDesPort()
{
	u_short temp;
	temp = ntohs( pTcpPacket->des_port );
    return (AnsiString)temp;
}

AnsiString  TTcpPacket::GetWindowSize()
{
		return (AnsiString)pTcpPacket->win_size;	
}

AnsiString  TTcpPacket::GetSeqNum()
{
		return (AnsiString)To16(pTcpPacket->seq_num);
}

AnsiString  TTcpPacket::GetAckNum()
{
		return (AnsiString)To16(pTcpPacket->ack_seq_num);
}

AnsiString  TTcpPacket::GetAppProtocolName()
{
	AnsiString  tmp,proto1,proto2;

	tmp="PROTOCOL_PORT_"+GetDesPort();
	proto1 = g_pLanguage->GetValue(tmp);
	tmp="PROTOCOL_PORT_"+GetSrcPort();
	proto2 = g_pLanguage->GetValue(tmp);
	tmp = proto1;
	if (tmp == "")
		tmp = proto2;
	if (tmp == "")
		return g_pLanguage->GetValue("PROTOCOL_APPLICATION_UNKNOWN");
	return tmp;
}

void  TTcpPacket::GetAppData16(TStrings *Strs)
{
	AnsiString szTmp;
	int cnt;
	for (cnt=0;cnt<nLength-TCP_HEADER_SIZE;cnt++)
	{
		u_char ch = pBuf[TCP_HEADER_SIZE+cnt];
		szTmp += To16(ch);
		if ((cnt+1)%DATA_SHOW_LEN == 0)
		{
			Strs->Add(szTmp);
			szTmp = "";
		}
		else
			szTmp += " ";
	}
   //	return Strs;
}

void TTcpPacket::GetAppDataAsc(TStrings *Strs)
{
	//TStringList Strs;
	AnsiString szTmp;
	//ShowMessage(nLength);
	for(int i=0;i<=(nLength-TCP_HEADER_SIZE);i++)
	{
		if (pBuf[TCP_HEADER_SIZE+i] == '\0' || pBuf[TCP_HEADER_SIZE+i] == '\n')
			szTmp += ".";
		else
			szTmp += pBuf[TCP_HEADER_SIZE+i];
		if ((i+1)%DATA_SHOW_LEN==0)
		{
			Strs->Add(szTmp);
			//ShowMessage(szTmp);
			szTmp = "";
		}
	}
	//return Strs;
}

//---------------------------------------------------------------------------

#pragma package(smart_init)
 