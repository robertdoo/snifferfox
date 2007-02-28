// $Author: zhengsh $
// $Date: 2006/09/19 15:30:59 $
// $Id: Global.h,v 1.17 2006/09/19 15:30:59 zhengsh Exp $
//---------------------------------------------------------------------------

#ifndef GlobalH
#define GlobalH
#include "vcl.h"
#include "Language.h"
#include "windows.h"
#include "winsock2.h"

extern AnsiString DIR_ROOT;
//软件所在目录的路径
extern TLanguage *g_pLanguage;
extern SOCKET g_Socket;
extern int g_Port;
//端口

extern HANDLE ghCacheFileMutex;
//读cache文件的互斥信号量
extern int g_nUiStyle;
//UI Style

//stat info
extern int g_nTotalCount;
//所以的包的总数
extern int g_nSnapCount;
//抓到的包

//Filter in datalink layer
extern int gOption_Filter_Arp;
extern int gOption_Filter_Rarp;
extern int gOption_Filter_Ip;
extern int gOption_Filter_Others;

//Filter in network layer and transport layer
extern int gOption_Filter_Tcp;
extern int gOption_Filter_Udp;
extern int gOption_Filter_Icmp;
extern int gOption_Filter_Igmp;

//Filter in application layer
//

extern int gOption_Filter_Ftp;
extern int gOption_Filter_Ssh;
extern int gOption_Filter_Telnet;
extern int gOption_Filter_Smtp;
extern int gOption_Filter_Dns;
extern int gOption_Filter_Gopher;
extern int gOption_Filter_Http;
extern int gOption_Filter_Pop3;
extern int gOption_Filter_Finger;
extern int gOption_Filter_Ldap;
extern int gOption_Filter_Tftp;
extern int gOption_Filter_AppOthers;

//Filter in source address
extern int gOption_Filter_Source_Type;
extern AnsiString gOption_Filter_Source_Only_Ip;
extern AnsiString gOption_Filter_Source_From_Ip;
extern AnsiString gOption_Filter_Source_To_Ip;

//Filter in Destine address
extern int gOption_Filter_Destine_Type;
extern AnsiString gOption_Filter_Destine_Only_Ip;
extern AnsiString gOption_Filter_Destine_From_Ip;
extern AnsiString gOption_Filter_Destine_To_Ip;

extern int g_nNextId;
// next record id

//-------stat info
extern int  g_nTotalCount;
//total frame count
extern int  g_nSaveCount;
//Saved frame

//----data link layer
extern int  g_nIpCount;
extern int  g_nArpCount;
extern int  g_nRarpCount;
extern int  g_nOthersCount;
//network layer and transport layer
extern int  g_nUdpCount;
extern int  g_nTcpCount;
extern int  g_nIcmpCount;
extern int  g_nIgmpCount;
extern bool g_bThreadIsRun;

extern int gOption_Record_PerPage;
//record per page
extern int gOption_ClearCache;
extern int gOption_UniqueId;
extern int gOption_SaveBuffer;
extern AnsiString g_szFile_Open;
extern AnsiString g_szFile_Save;
//MISC
extern int gOption_Show_Splash;
extern int gOption_Display_Icon;
extern int gOption_Display_Status;
extern int gOption_Min_Start ;
extern int gOption_Exit_Confirm;
extern int gOption_Auto_Run ;
extern int gOption_Auto_Sniffer;
extern AnsiString gOption_File_Auto_Save;
extern int gOption_Auto_NIC_Index;
extern int gOption_Run_First_Time;

extern int g_pSpecify_Ports[];
//the first element stand for the total number of the ports

extern TStringList *g_SkinList;
extern TStringList *g_LangList;
extern AnsiString g_SkinFile;

//---------------------------------------------------------------------------
#endif
