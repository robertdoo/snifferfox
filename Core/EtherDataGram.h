// Author: zhengsh
// Date: 2005/10/03 01:30:35 
// $Id: EtherDataGram.h,v 1.8 2006/09/16 09:44:57 zhengsh Exp $
//  classs TEherDataGram
//---------------------------------------------------------------------------

#ifndef EtherDataGramH
#define EtherDataGramH
//---------------------------------------------------------------------------
//EherDataGram
#include <pcap.h>
#include <vcl.h>
#include <stdio.h>

/*6 BIT的MAC地址头定义*/
typedef struct TMacAddress{
	u_char byte1;
	u_char byte2;
	u_char byte3;
	u_char byte4;
	u_char byte5;
	u_char byte6;
}TMacAddress;

/* 4 BIT的IP头定义 */
typedef struct TIpAddress{
  u_char byte1;
  u_char byte2;
  u_char byte3;
  u_char byte4;
}TIpAddress;

class TEtherDataGram
{
	public:
		TEtherDataGram();
		TEtherDataGram(TEtherDataGram &rhv);
        ~TEtherDataGram();
        bool SetBuffer(const struct pcap_pkthdr *header, const u_char *pkt_data,int size=0);
        bool SaveToCache(FILE *fp);
        bool LoadFromCache(FILE *fp,int &nOffset);
        AnsiString GetSrcMac();
        //get source mac  addr
        AnsiString GetDestMac();
        //get destination mac addr
        AnsiString GetTypeName();
        //get protocol type
        AnsiString GetTypeValue();
        //get value of protocol
        AnsiString GetTimeStamp();
        //get timestamp
        u_char *GetDataHeader();
        int GetDataSize();
        int GetActLen();
        int GetCapLen();
        TEtherDataGram &operator=(const TEtherDataGram &src);
        void SetId(int id);
        int GetId();
        TEtherDataGram *pNext;
        AnsiString GetHint();
        //get decription about this packet
    private:
        struct pcap_pkthdr *pHead;
        u_char  *pData;
        void Clear();
        //FILE *fp;
        int nId;
        int nSize;

}; //class TEtherDataGram
#endif
