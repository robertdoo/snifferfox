// Author: zhengsh
// Date: 2005/10/03 01:30:35 
// $Id: IpDataGram.cpp,v 1.8 2005/10/14 04:16:38 zhengsh Exp $
//---------------------------------------------------------------------------


#pragma hdrstop

#include "IpDataGram.h"
#include "Functions.h"
#include "Global.h"
#include "MsgDialog.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)


TIpDataGram::TIpDataGram()
{
    Clear();
}

void TIpDataGram::Clear()
{
    memset(pBuf,0,BUFFER_SIZE);
    nLength = 0;
    pIpHeader = 0;
}

void TIpDataGram::SetBuffer(u_char *aBuf,int aLength)
{
    Clear();
    nLength = aLength;
    if (nLength > BUFFER_SIZE)
        nLength = BUFFER_SIZE;

    try
    {
        memcpy(pBuf,aBuf,nLength);
    }
    catch(...)
    {
        ShowMsg((int)aBuf);
        ShowMsg(AnsiString("length:")+nLength);
    }
    pIpHeader = (TIpHeader*) (pBuf);
}


AnsiString TIpDataGram::GetProtocol()
//get protocol name
{
    if (pIpHeader != 0)
        return AnsiString(GetProtocolName(pIpHeader->iph_protocol));
    return "";
}

int TIpDataGram::GetTimeToLive()
//get ttl
{
    if (pIpHeader != 0)
        return pIpHeader->iph_ttl;
    return 0;
}
AnsiString TIpDataGram::GetSrcAddr()
//get source ip addr
{
    if (pIpHeader != 0)
        return AnsiString(iptos(pIpHeader->iph_src));
    return "";
}
AnsiString TIpDataGram::GetDestAddr()
//get destination ip addr
{
    if (pIpHeader != 0)
        return AnsiString(iptos(pIpHeader->iph_dest));
    return "";
}

int TIpDataGram::GetProtocolValue()
{
    return pIpHeader->iph_protocol;
}

u_char *TIpDataGram::GetDataHeader()
{
	return (u_char *)(pBuf + GetHeaderLength());
}

int TIpDataGram::GetDataSize()
{
	return nLength - GetHeaderLength();
}

AnsiString TIpDataGram::GetVersion()
{
    u_char ch;
	ch = *pBuf;
    ch = ch & 0xF0;
    if (ch == 0x40)
        return "IPv4";
    return g_pLanguage->GetValue("IP_VERSION_UNKNOWN");

}

int TIpDataGram::GetHeaderLength()
{
	//u_char ch;
	//ch = (u_char)*pBuf;
	//ch = 0x0f & ch;
	//return (int)ch*4;
	return (pIpHeader->iph_verlen & 0xf) * 4;
}



AnsiString TIpDataGram::GetTos()
{
    u_char *pChar;
    pChar = (u_char*)(pBuf+1);
    return AnsiString("0x")+To16(*pChar);
}

int TIpDataGram::GetTotalLength()
{
	return pIpHeader->iph_length;
}

int TIpDataGram::GetIdentification()
{
    unsigned short nId;
    memcpy(&nId,pBuf+4,2);
    return nId;
}

AnsiString TIpDataGram::GetChecksum()
{
    short checksum;
    memcpy(&checksum,pBuf+10,2);
    return AnsiString("0x") + To16(checksum);
}

TIpDataGram::TIpDataGram(TEtherDataGram &idg)
{
    SetBuffer(idg.GetDataHeader(),idg.GetDataSize());
}

TIpDataGram &TIpDataGram::operator=(TEtherDataGram &idg)
{
    SetBuffer(idg.GetDataHeader(),idg.GetDataSize());
    return *this;
}

int TIpDataGram::GetIpHeaderLen()
{
    return (pIpHeader->iph_verlen & 0xf) * 4;
}

AnsiString TIpDataGram::GetFlags()
{
    short flag;
    memcpy(&flag,pBuf+6,2);
    flag = flag >> 13;
    return AnsiString(flag);
}

int TIpDataGram::GetOffset()
{
    short flag;
    memcpy(&flag,pBuf+6,2);
    flag = flag & 0x1fff;
    return flag;

}
