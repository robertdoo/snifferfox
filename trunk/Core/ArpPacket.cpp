//$Author: gourf $
//$Data$
//$Id: ArpPacket.cpp,v 1.2 2005/10/13 14:45:41 gourf Exp $
//---------------------------------------------------------------------------


#pragma hdrstop

#include "ArpPacket.h"

TArpPacket::TArpPacket()
{
     clear();
}

TArpPacket::~TArpPacket()
{
}

void TArpPacket::clear()
{
     memset(pBuf,0,BUFFER_SIZE);
     nLength=0;
     pArpRarpPacket=NULL;
}

void TArpPacket::SetBuffer(u_char *aBuf,int aLength)
{
    clear();
    nLength = aLength;
    if (nLength > BUFFER_SIZE)
        nLength = BUFFER_SIZE;
    memcpy(pBuf,aBuf,nLength);
    pArpRarpPacket = (TArpRarpPacket*)(pBuf);
}

AnsiString TArpPacket::GetSrcAddr()
{
    if (pArpRarpPacket != NULL)
        return AnsiString(iptos(pArpRarpPacket->source_ip_addr));
    return "";
}

AnsiString TArpPacket::GetDestAddr()
{
    if (pArpRarpPacket != NULL)
        return AnsiString(iptos(pArpRarpPacket->end_ip_addr));
    return "";
}

AnsiString TArpPacket::GetSrcMac()
{
    if (pArpRarpPacket == NULL)
        return "";
    //TMacAddress *mac_addr = new TMacAddress;
    AnsiString tmp;
    tmp += To16(pArpRarpPacket->source_mac_addr.byte1)+":";
    tmp += To16(pArpRarpPacket->source_mac_addr.byte2)+":";
    tmp += To16(pArpRarpPacket->source_mac_addr.byte3)+":";
    tmp += To16(pArpRarpPacket->source_mac_addr.byte4)+":";
    tmp += To16(pArpRarpPacket->source_mac_addr.byte5)+":";
    tmp += To16(pArpRarpPacket->source_mac_addr.byte6);
    return AnsiString(tmp);
}

AnsiString TArpPacket::GetDestMac()
{
    if (pArpRarpPacket == NULL)
        return "";
    //TMacAddress *mac_addr = new TMacAddress;
    AnsiString tmp;
    tmp += To16(pArpRarpPacket->end_mac_addr.byte1)+":";
    tmp += To16(pArpRarpPacket->end_mac_addr.byte2)+":";
    tmp += To16(pArpRarpPacket->end_mac_addr.byte3)+":";
    tmp += To16(pArpRarpPacket->end_mac_addr.byte4)+":";
    tmp += To16(pArpRarpPacket->end_mac_addr.byte5)+":";
    tmp += To16(pArpRarpPacket->end_mac_addr.byte6);
    return AnsiString(tmp);
}

short int TArpPacket::GetOpType()
{
    return  pArpRarpPacket->op_type;
}

//---------------------------------------------------------------------------

#pragma package(smart_init)
