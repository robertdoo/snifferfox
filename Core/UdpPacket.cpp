//$Author: zhengsh $
//$Date: 2005/11/15 15:53:09 $
//$Id: UdpPacket.cpp,v 1.10 2005/11/15 15:53:09 zhengsh Exp $
//---------------------------------------------------------------------------


#pragma hdrstop

#include "UdpPacket.h"

TUdpPacket::TUdpPacket()
{
    Clear();
}

void TUdpPacket::Clear()
{
    memset(pBuf,0,UDP_HEADER_SIZE);
    nLength=0;
    pUdpHeader=NULL;
}

void TUdpPacket::SetBuffer(u_char *aBuf,int aLength)
{
    Clear();
    nLength = aLength;
    if (nLength > BUFFER_SIZE)
        nLength = BUFFER_SIZE;
    memcpy(pBuf,aBuf,BUFFER_SIZE);
    pUdpHeader=(TUdpHeader *)pBuf;
}

AnsiString TUdpPacket::GetSrcPort()
{
    u_short temp;
    temp = ntohs( pUdpHeader->src_port );
    return (AnsiString)temp;
}

AnsiString TUdpPacket::GetDesPort()
{
    u_short temp;
    temp = ntohs( pUdpHeader->des_port );
    return (AnsiString)temp;
}

AnsiString TUdpPacket::GetDataLen()
{
    return (AnsiString)pUdpHeader->data_len;
}

AnsiString TUdpPacket::GetCheckSum()
{
    return (AnsiString)To16(pUdpHeader->check_sum);
}

AnsiString  TUdpPacket::GetAppProtocolName()
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

void TUdpPacket::GetAppData16(TStrings *Strs)
{
	AnsiString szTmp;
	int cnt;
    //u_char ch;
	for (cnt=0;cnt<nLength-UDP_HEADER_SIZE;cnt++)
	{
		u_char ch = pBuf[UDP_HEADER_SIZE+cnt];

		szTmp += To16(ch);
        //ShowMessage(To16(ch) + AnsiString(" ")+AnsiString(pBuf[BUFFER_SIZE+cnt])+ AnsiString(" ")+AnsiString(int(pBuf[BUFFER_SIZE+cnt])));
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

void TUdpPacket::GetAppDataAsc(TStrings *Strs)
{
	//TStringList Strs;
	AnsiString szTmp;
	//ShowMessage(nLength);
	int i;
	for(i=0;i<=(nLength-UDP_HEADER_SIZE);i++)
	{
		if (pBuf[UDP_HEADER_SIZE+i] == '\0' || pBuf[UDP_HEADER_SIZE+i] == '\n')
			szTmp += ".";
		else
			szTmp += pBuf[UDP_HEADER_SIZE+i];
		if ((i+1)%DATA_SHOW_LEN==0)
		{
			Strs->Add(szTmp);
			//ShowMessage(szTmp);
			szTmp = "";
		}
	}
}
//---------------------------------------------------------------------------
#pragma package(smart_init)
