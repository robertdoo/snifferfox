//$Author: zhengsh $
//$Date: 2005/10/14 04:16:37 $
//$Id: IcmpPacket.cpp,v 1.4 2005/10/14 04:16:37 zhengsh Exp $
//---------------------------------------------------------------------------


#pragma hdrstop
#include "IcmpPacket.h"
#include "MsgDialog.h"


TIcmpPacket::TIcmpPacket()
{
    Clear();
}

void TIcmpPacket::Clear()
{
     memset(pBuf,0,BUFFER_SIZE);
     nLength=0;
     pIcmpHeader=NULL;
}

void TIcmpPacket::SetBuffer(u_char *aBuf)
{
    //TIcmpPacket *pIcmpPacket;
    Clear();
    memcpy(pBuf,aBuf,ICMP_HEADER_SIZE);

    pIcmpHeader=(TIcmpHeader *)pBuf;
}

AnsiString  TIcmpPacket::GetType()
{
    return AnsiString(pIcmpHeader->icmp_type);
}

AnsiString  TIcmpPacket::GetCode()
{
    return AnsiString(pIcmpHeader->code);
}

AnsiString  TIcmpPacket::GetCheckSum()
{
    return AnsiString(To16(pIcmpHeader->check_sum));
}

AnsiString TIcmpPacket::GetDescri()
{
	AnsiString  tmp;
	tmp=AnsiString("ICMP_DESCRIPTION_")+GetType()+"_"+GetCode();
	//ShowMsg(tmp
	return g_pLanguage->GetValue(tmp);
}

//---------------------------------------------------------------------------

#pragma package(smart_init)
