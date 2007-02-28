// Author: zhengsh
// Date: 2005/10/03 01:30:35 
// $Id: EtherDataGram.cpp,v 1.10 2006/09/16 09:44:57 zhengsh Exp $

//---------------------------------------------------------------------------


#pragma hdrstop

#include "EtherDataGram.h"
#include "Constant.h"
#include "stdio.h"
#include "Global.h"
#include "Functions.h"
#include "MsgDialog.h"
#include "Language.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)


TEtherDataGram::TEtherDataGram()
{
    pHead = 0;
    pData = 0;
    nId = 0;
    pNext = 0;
    nSize = 0;
    AnsiString szFile = DIR_ROOT+DIR_CACHE+FILE_CACHE;
    //fp = fopen(szFile.c_str(),"ab");
}

void TEtherDataGram::Clear()
{
    if (pHead != 0)
        delete pHead;
    if (pData != 0)
        delete [] pData;
    pHead =0;
    pData = 0;
}

TEtherDataGram::~TEtherDataGram()
{
    Clear();
    //fclose(fp);
}

bool TEtherDataGram::SetBuffer(const struct pcap_pkthdr *header, const u_char *pkt_data,int size)
{
    pHead = new (struct pcap_pkthdr);
    if (pHead == 0)
        return false;
    memcpy(pHead,header,sizeof(struct pcap_pkthdr));

    if (pHead->caplen > BUFFER_SIZE)
    	return false;
    pData = new u_char[pHead->caplen];
    if (pData == 0)
        return false;
    memcpy(pData,pkt_data,pHead->caplen);
    if (size != 0)
    	nSize = size;
    else
    	nSize = pHead->caplen;
    return true;
}

AnsiString TEtherDataGram::GetSrcMac()
//get source mac  addr
{
    if (pData == 0)
        return "";
    TMacAddress *mac_addr = new TMacAddress;
    memcpy(mac_addr,pData+6,6);

    AnsiString tmp;
    tmp += To16(mac_addr->byte1)+":";
    tmp += To16(mac_addr->byte2)+":";
    tmp += To16(mac_addr->byte3)+":";
    tmp += To16(mac_addr->byte4)+":";
    tmp += To16(mac_addr->byte5)+":";
    tmp += To16(mac_addr->byte6);
    delete mac_addr;
    return AnsiString(tmp);
}

AnsiString TEtherDataGram::GetDestMac()
//get destination mac addr
{
    if (pData == 0)
        return "";
    TMacAddress *mac_addr = new TMacAddress;
    memcpy(mac_addr,pData,6);
    AnsiString tmp;
    tmp += To16(mac_addr->byte1)+":";
    tmp += To16(mac_addr->byte2)+":";
    tmp += To16(mac_addr->byte3)+":";
    tmp += To16(mac_addr->byte4)+":";
    tmp += To16(mac_addr->byte5)+":";
    tmp += To16(mac_addr->byte6);
    delete mac_addr;
    return AnsiString(tmp);
}

AnsiString TEtherDataGram::GetTypeName()
{//get protocol type
	u_char *p_type = new u_char[2];
	if (pData == 0 || p_type == 0 || pHead == 0)
	{
		//ShowMsg(AnsiString("pData:")+(int)pData+"\n" + "p_type:"+(int)p_type+"\n"+"pHead:"+(int)pHead);
		return "";
	}
	memcpy(p_type,pData+12,2);
    char buf[100];
    AnsiString tmp,byte1 = To16(*p_type),byte2 = To16(*(p_type+1));
    if (byte1=="08" && byte2 == "00")
        tmp = "IP";
    else if (byte1=="08" && byte2 == "06")
		tmp = "ARP";
    else if (byte1=="08" && byte2 == "35")
        tmp = "RARP";
    else tmp = "Unknown";
	delete []p_type;
    return tmp;
}


AnsiString TEtherDataGram::GetTimeStamp()
//get timestamp
{
    if (pHead == 0)
        return "";
    struct tm *ltime;
    char timestr[16],buf[100];
    /* convert the timestamp to readable format */
    ltime=localtime(&pHead->ts.tv_sec);
    if (ltime == 0)
    	return "";
    strftime( timestr, sizeof timestr, "%H:%M:%S", ltime);
    sprintf(buf,"%s.%.6d",timestr,pHead->ts.tv_usec);
    return AnsiString(buf);
}

u_char* TEtherDataGram::GetDataHeader()
{
    //ze = pHead->caplen;
    return pData + 14;
}

int TEtherDataGram::GetActLen()
{
    return nSize-14;
}

int TEtherDataGram::GetCapLen()
{
    return pHead->caplen-14;
}

AnsiString TEtherDataGram::GetTypeValue()
//get value of protocol
{
	if (pData == 0)
    	return "";
    u_char *p_type = new u_char[2];
    memcpy(p_type,pData+12,2);
    char buf[100];
    int nType = *p_type*256+*(p_type);
    AnsiString tmp = "0x",byte1 = To16(*p_type),byte2 = To16(*(p_type+1));
    delete []p_type;
    tmp += byte1 + byte2;
    return tmp;
}


bool TEtherDataGram::SaveToCache(FILE *fp)
{
    //static int cnt = 0;

    //FILE *fp;
    AnsiString szFile = DIR_ROOT+DIR_CACHE+FILE_CACHE;
    if (!fp)
        fp = fopen(szFile.c_str(),"ab");

    if (WaitForSingleObject(ghCacheFileMutex,INFINITE) == WAIT_FAILED)
        return false;

    if (!fp)
    {
        //ShowMessage(AnsiString("error:")+id);
        return false;
    }
    fseek(fp,0,SEEK_END);
    //ShowMessage(ftell(fp));

    int offset = 2*sizeof(int)+sizeof(struct pcap_pkthdr)+GetCapLen();
    fwrite(&nId,sizeof(nId),1,fp);//id
    fwrite(&offset,sizeof(offset),1,fp);//offset
    fwrite(pHead,sizeof(struct pcap_pkthdr),1,fp);
    fwrite(pData,GetCapLen(),1,fp);
    fflush(fp);
    //ShowMessage(ftell(fp));
    //fclose(fp);
    ReleaseMutex(ghCacheFileMutex);
    return true;
}

bool TEtherDataGram::LoadFromCache(FILE *fp,int &nOffset)
{
     //FILE *fp;
    //ShowMessage(AnsiString("id")+id);
    //AnsiString szFile = DIR_ROOT+DIR_CACHE+FILE_CACHE;
    if (WaitForSingleObject(ghCacheFileMutex,INFINITE) == WAIT_FAILED)
    {
        ShowMessage("error load file");
        return false;
    }
    if (!fp)
        return false;

    int id,offset;
    rewind(fp);
    AnsiString msg;
    Clear();
    fread(&id,sizeof(int),1,fp);
    nId = id;
    fread(&offset,sizeof(int),1,fp);
    nOffset = offset;
    msg = AnsiString("id:")+AnsiString(id)+AnsiString("\nlength:")+offset;
    //ShowMsg(msg);
    int nDataLength = offset-2*sizeof(int)-sizeof(struct pcap_pkthdr);
    pHead = new (struct pcap_pkthdr);
    pData = new u_char[nDataLength];
    fread(pHead,sizeof(struct pcap_pkthdr),1,fp);
    fread(pData,nDataLength,1,fp);
    //fclose(fp);
    ReleaseMutex(ghCacheFileMutex);
    return true;
}

TEtherDataGram &TEtherDataGram::operator=(const TEtherDataGram &src)
{
    this->SetBuffer(src.pHead,src.pData);
    nId = src.nId;
    return *this;
}

int TEtherDataGram::GetId()
{
    return nId;
}

void TEtherDataGram::SetId(int id)
{
    nId = id;
}

int TEtherDataGram::GetDataSize()
{
    return nSize - 14;
}

TEtherDataGram::TEtherDataGram(TEtherDataGram &rhv)
{
	this->SetBuffer(rhv.pHead,rhv.pData);
}

AnsiString TEtherDataGram::GetHint()
{
    AnsiString szHint;
    szHint += FillSpace(g_pLanguage->GetValue("TEXT_MAINWIN_DATALIST_NUMBER"));
    szHint += AnsiString(nId) + "\n";
    szHint += FillSpace(g_pLanguage->GetValue("FRMMAIN_ETHERNET_HEADER_SRCMAC"));
    szHint += GetSrcMac() + "\n";
    szHint += FillSpace(g_pLanguage->GetValue("FRMMAIN_ETHERNET_HEADER_DESTMAC"));
    szHint += GetDestMac() + "\n";
    szHint += FillSpace(g_pLanguage->GetValue("FRMMAIN_ETHERNET_HEADER_TYPE"));
    szHint += GetTypeName() + "\n";
    szHint += FillSpace(g_pLanguage->GetValue("FRMMAIN_ETHERNET_HEADER_TIMESTAMP"));
    szHint += GetTimeStamp() + "\n";

    szHint += FillSpace(g_pLanguage->GetValue("FRMMAIN_ETHERNET_HEADER_ACT_LEN"));
    szHint += AnsiString(GetActLen()) + "\n";
    szHint += FillSpace(g_pLanguage->GetValue("FRMMAIN_ETHERNET_HEADER_CAP_LEN"));
    szHint += AnsiString(GetCapLen()) + "\n";
/*
	if (GetTypeName() == "IP")
    {
        //IP header
        szHint = "\n";
        TIpDataGram IpDataGram;
        IpDataGram = *this;

        szHint += FillSpace(g_pLanguage->GetValue("FRMMAIN_IP_HEADER_VERSION"));
        szHint += AnsiString(IpDataGram.GetVersion()) + "\n";
        szHint += FillSpace(g_pLanguage->GetValue("FRMMAIN_IP_HEADER_TOS"));
        szHint += AnsiString(IpDataGram.GetTos()) + "\n";
        szHint += FillSpace(g_pLanguage->GetValue("FRMMAIN_IP_HEADER_IHL"));
        szHint += AnsiString(IpDataGram.GetHeaderLength()) + "\n";
        szHint += FillSpace(g_pLanguage->GetValue("FRMMAIN_IP_HEADER_SRCADDR"));
        szHint += AnsiString(IpDataGram.GetSrcAddr()) + "\n";
        szHint += FillSpace(g_pLanguage->GetValue("FRMMAIN_IP_HEADER_DESTADDR"));
        szHint += AnsiString(IpDataGram.GetDestAddr()) + "\n";
        szHint += FillSpace(g_pLanguage->GetValue("FRMMAIN_IP_HEADER_ID"));
        szHint += AnsiString(IpDataGram.GetIdentification()) + "\n";
        szHint += FillSpace(g_pLanguage->GetValue("FRMMAIN_IP_HEADER_TOTAL_LEN"));
        szHint += AnsiString(IpDataGram.GetTotalLength()) + "\n";
        szHint += FillSpace(g_pLanguage->GetValue(""));
        szHint += AnsiString(IpDataGram.GetFlags()) + "\n";
        szHint += FillSpace(g_pLanguage->GetValue("FRMMAIN_IP_HEADER_FLAGS"));
        szHint += AnsiString(IpDataGram.GetOffset()) + "\n";
        szHint += FillSpace(g_pLanguage->GetValue(""));
        szHint += AnsiString(IpDataGram.GetTimeToLive()) + "\n";
        szHint += FillSpace(g_pLanguage->GetValue(""));
        szHint += AnsiString(IpDataGram.GetProtocol()) + "\n";
        szHint += FillSpace(g_pLanguage->GetValue("FRMMAIN_IP_HEADER_PROTOCOL"));
        szHint += AnsiString(IpDataGram.GetChecksum()) + "\n";
        szHint += FillSpace(g_pLanguage->GetValue("FRMMAIN_IP_HEADER_CRC"));
        szHint += AnsiString() + "\n";
    }
		//ICMP
		if (IpDataGram.GetProtocolValue() == IPPROTO_ICMP)
		{
			TIcmpPacket Icmp;
			Icmp.SetBuffer(IpDataGram.GetDataHeader());
			edtIcmpType->Text = Icmp.GetType();
			edtIcmpCode->Text = Icmp.GetCode();
			edtIcmpCrc->Text = Icmp.GetCheckSum();
			edtIcmpDesc->Text = Icmp.GetDescri();
			if (!tsIpHeader->TabVisible)
				tsIpHeader->TabVisible = true;
			if (tsTcp->TabVisible)
				tsTcp->TabVisible = false;
			if (tsUdp->TabVisible)
				tsUdp->TabVisible = false;
			if (!tsIcmp->TabVisible)
				tsIcmp->TabVisible = true;
			if (tsArpHeader->TabVisible)
				tsArpHeader->TabVisible = false;
			if (tsData->TabVisible)
				tsData->TabVisible = false;
		}
		else if (IpDataGram.GetProtocolValue() == IPPROTO_TCP)
		{
			TTcpPacket TcpPacket;
			TcpPacket.SetBuffer(IpDataGram.GetDataHeader(),IpDataGram.GetDataSize());

			if (tsIcmp->TabVisible)
				tsIcmp->TabVisible = false;
			if (tsUdp->TabVisible)
				tsUdp->TabVisible = false;
			if (tsArpHeader->TabVisible)
				tsArpHeader->TabVisible = false;
			if (!tsTcp->TabVisible)
				tsTcp->TabVisible = true;
            if (!tsData->TabVisible)
            	tsData->TabVisible = true;
            if (!tsIpHeader->TabVisible)
            	tsIpHeader->TabVisible = true;

			edtTcpSrcPort->Text = TcpPacket.GetSrcPort();
			edtTcpDestPort->Text = TcpPacket.GetDesPort();
			edtTcpWinSize->Text = TcpPacket.GetWindowSize();
			edtTcpSeqNum->Text = TcpPacket.GetSeqNum();
			edtAckSeq->Text = TcpPacket.GetAckNum();
			edtTcpProtoName->Text = TcpPacket.GetAppProtocolName();
            tsData->Visible = false;
			mmoBin->Lines->Clear();
			TcpPacket.GetAppData16(mmoBin->Lines);

			mmoText->Lines->Clear();
			TcpPacket.GetAppDataAsc(mmoText->Lines);
            tsData->Visible = true;
			//mmoText->Lines = StrList;
		}
		else if (IpDataGram.GetProtocolValue() == IPPROTO_UDP)
		{
			TUdpPacket UdpPacket;
			UdpPacket.SetBuffer(IpDataGram.GetDataHeader(),IpDataGram.GetDataSize());

			if (tsIcmp->TabVisible)
				tsIcmp->TabVisible = false;
			if (!tsUdp->TabVisible)
				tsUdp->TabVisible = true;
			if (tsTcp->TabVisible)
				tsTcp->TabVisible = false;
			if (!tsIpHeader->TabVisible)
				tsIpHeader->TabVisible = true;
            if (!tsIpHeader->TabVisible)
            	tsIpHeader->TabVisible = true;

			edtUdpSrcPort->Text = UdpPacket.GetSrcPort();
			edtUdpDestPort->Text = UdpPacket.GetDesPort();
			edtUdpLength->Text = UdpPacket.GetDataLen();
			edtUdpCrc->Text = UdpPacket.GetCheckSum();
			edtUdpProtoName->Text = UdpPacket.GetAppProtocolName();

            tsData->Visible = false;
			mmoBin->Lines->Clear();
			UdpPacket.GetAppData16(mmoBin->Lines);

			mmoText->Lines->Clear();
			UdpPacket.GetAppDataAsc(mmoText->Lines);
            tsData->Visible = true;
			//mmoText->l

		}
		else
		{//igmp, wait for extend
		}
	}
	else if (Ether.GetTypeName() == "ARP" || Ether.GetTypeName() == "RARP")
	{//ARP or RARP
		TArpPacket Arp;
		Arp.SetBuffer(Ether.GetDataHeader(),Ether.GetDataSize());
		edtArpDestAddr->Text = Arp.GetDestAddr();
		edtArpSrcAddr->Text = Arp.GetSrcAddr();
		edtArpDestMac->Text = Arp.GetDestMac();
		edtArpSrcMac->Text =  Arp.GetSrcMac();
		//if ( Arp.GetOpType() == 1 || Arp.GetOpType() == 2)
		edtProtocolType->Text = Ether.GetTypeName();
		if (tsIpHeader->TabVisible)
			tsIpHeader->TabVisible = false;
		if (tsTcp->TabVisible)
			tsTcp->TabVisible = false;
		if (tsUdp->TabVisible)
			tsUdp->TabVisible = false;
		if (!tsArpHeader->TabVisible)
			tsArpHeader->TabVisible = true;
		if (tsIcmp->TabVisible)
			tsArpHeader->TabVisible = false;
        if (tsData->TabVisible)
            tsData->TabVisible = false;

	}
	else
	{//unkown protocol
		if (tsIpHeader->TabVisible)
			tsIpHeader->TabVisible = false;
		if (tsTcp->TabVisible)
			tsTcp->TabVisible = false;
		if (tsUdp->TabVisible)
			tsUdp->TabVisible = false;
		if (tsArpHeader->TabVisible)
			tsArpHeader->TabVisible = false;
		if (tsIcmp->TabVisible)
			tsIcmp->TabVisible = false;
	}

*/
    return szHint;
}
