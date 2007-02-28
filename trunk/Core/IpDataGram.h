// Author: zhengsh
// Date: 2005/10/03 01:30:35 
// $Id: IpDataGram.h,v 1.7 2005/10/09 13:32:57 zhengsh Exp $
// IP Êý¾Ý±¨
//---------------------------------------------------------------------------

#ifndef IpDataGramH
#define IpDataGramH
#include "Constant.h"
#include "windows.h"
#include "Functions.h"
#include "EtherDataGram.h"
//---------------------------------------------------------------------------


// the Defination of IP Header
typedef struct TIpHeader {
	UCHAR   iph_verlen;  // Version and length
	UCHAR   iph_tos;  // Type of service
	USHORT  iph_length;  // Total datagram length
	USHORT  iph_id;  // Identification
	USHORT  iph_offset;  // Flags, fragment offset
	UCHAR   iph_ttl;  // Time to live
	UCHAR   iph_protocol;  // Protocol
	USHORT  iph_xsum;  // Header checksum
	ULONG   iph_src;  // Source address
	ULONG   iph_dest;  // Destination address
} TIpHeader;

// the Defination of  class IP DataGram

class TIpDataGram
{
    private:
        u_char pBuf[BUFFER_SIZE+10];
        TIpHeader *pIpHeader;
        int nLength;
    public:
        void SetBuffer(u_char *aBuf,int aLength);
        TIpDataGram();
        void Clear();
        TIpDataGram(TEtherDataGram &idg);
        TIpDataGram &operator=(TEtherDataGram &idg);
        // the following is get method list
        AnsiString GetProtocol();
        //get protocol name
        int GetProtocolValue();
        int GetTimeToLive();
        //get ttl
        AnsiString GetSrcAddr();
        //get source ip addr
        AnsiString GetDestAddr();
        //get destination ip addr
        u_char *GetDataHeader();
        int GetDataSize();
        int GetHeaderLength();
        AnsiString GetVersion();
        AnsiString GetTos();
        int GetTotalLength();
        int GetIdentification();
        AnsiString GetFlags();
        int GetOffset();
        AnsiString GetChecksum();
        int GetIpHeaderLen();
};

#endif
