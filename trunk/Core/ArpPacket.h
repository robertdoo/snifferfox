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
	short int			hardware_type;			    // 1代表以太网地址
	short int			protocol_type;				// 0x0800代表IP地址
	u_char			    hardware_addr_len;			// 6字节
	u_char			    protocol_addr_len;			// 4字节
    short int			op_type;					// 1：arp请求；2：arp应答；
										            // 3：rarp请求；4：rarp应答
	TMacAddress	        source_mac_addr;
	unsigned long    	source_ip_addr;
	TMacAddress	        end_mac_addr;
	unsigned long   	end_ip_addr;
}TArpRarpPacket;	                                // ARP报文




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
