//$Author: gourf $
//$Date: 2005/10/09 05:15:03 $
//$Id: ArpPacket.h,v 1.2 2005/10/09 05:15:03 gourf Exp $
//---------------------------------------------------------------------------

#ifndef ArpPacketH
#define ArpPacketH
#include "Constant.h"
#include "windows.h"
#include "Functions.h"
#include "IpDataGram.h"
#include "EtherDataGram.h"

typedef struct TArpRarpPacket{
	short int			hardware_type;			    // 1������̫����ַ
	short int			protocol_type;				// 0x0800����IP��ַ
	u_char			    hardware_addr_len;			// 6�ֽ�
	u_char			    protocol_addr_len;			// 4�ֽ�
    short int			op_type;					// 1��arp����2��arpӦ��
										            // 3��rarp����4��rarpӦ��
	TMacAddress	        source_mac_addr;
	unsigned long    	source_ip_addr;
	TMacAddress	        end_mac_addr;
	unsigned long   	end_ip_addr;
}TArpRarpPacket;	                                // ARP����




class TArpPacket
{
    public:
        void SetBuffer(u_char *aBuf,int aLength);
        TArpPacket();
        ~TArpPacket();
        void clear();

        AnsiString GetSrcAddr();
        //get source ip addr
        AnsiString GetDestAddr();
        //get destination ip addr

        AnsiString GetSrcMac();
        //get source mac  addr
        AnsiString GetDestMac();
        //get destination mac addr

        short int  GetOpType();
        //get the type of protocol

    private:
        char pBuf[BUFFER_SIZE];
        TArpRarpPacket *pArpRarpPacket;
        int nLength;

};
//---------------------------------------------------------------------------
#endif
