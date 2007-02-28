// Author: zhengsh
// Date: 2005/10/03 01:30:34 
// $Id: Global.cpp,v 1.19 2006/09/29 15:31:33 zhengsh Exp $
//---------------------------------------------------------------------------


#pragma hdrstop

#include "Global.h"
#include "Constant.h"
#include <Menus.hpp>
#include "SUIGrid.hpp"
#include <Grids.hpp>
#include "SUIButton.hpp"
#include "SUIPageControl.hpp"
#include "SUITabControl.hpp"
#include "SUIMgr.hpp"
#include "SUIPopupMenu.hpp"
#include "SUIToolBar.hpp"
#include <ComCtrls.hpp>
#include <ToolWin.hpp>
#include "SUIGroupBox.hpp"
#include "SUIImagePanel.hpp"
#include "SUIComboBox.hpp"
#include "SUIListBox.hpp"
#include "RecvThread.h"
#include "SUIDlg.hpp"
#include <pcap.h>
#include "SUIEdit.hpp"
#include "SUIScrollBar.hpp"
#include "SUIMemo.hpp"
#include "Constant.h"
//---------------------------------------------------------------------------

#pragma package(smart_init)

AnsiString DIR_ROOT;
//软件所在目录的路径

TLanguage *g_pLanguage;
//管理语言包的全局变量
SOCKET g_Socket;
//全局的socket
int g_Port = htons(DEFAULT_PORT);

//Filter in datalink layer
int gOption_Filter_Arp;
int gOption_Filter_Rarp;
int gOption_Filter_Ip;
int gOption_Filter_Others;

//Filter in network layer and transport layer
int gOption_Filter_Tcp;
int gOption_Filter_Udp;
int gOption_Filter_Icmp;
int gOption_Filter_Igmp;

//Filter in application layer
//
int gOption_Filter_Ftp = 1;
int gOption_Filter_Ssh = 1;
int gOption_Filter_Telnet = 1;
int gOption_Filter_Smtp = 1;
int gOption_Filter_Dns = 1;
int gOption_Filter_Gopher = 1;
int gOption_Filter_Http = 1;
int gOption_Filter_Pop3 = 1;
int gOption_Filter_Finger = 1;
int gOption_Filter_Ldap = 1;
int gOption_Filter_Tftp = 1;
int gOption_Filter_AppOthers = 1;

//int gOption_Source = OPTION_SOURCE_ALL;
//int gOption_Destine = OPTION_DESTINE_ALL;
//int Option_SOURCE;
int g_nUiStyle = MacOS;

HANDLE ghCacheFileMutex;
//读cache文件的互斥信号量

//-------stat info
int g_nTotalCount = 0;
//total frame count
int g_nSaveCount = 0;
//Saved frame

//----data link layer
int g_nIpCount = 0;
int g_nArpCount = 0;
int g_nRarpCount = 0;
int g_nOthersCount = 0;
//network layer and transport layer
int g_nUdpCount = 0;
int g_nTcpCount = 0;
int g_nIcmpCount = 0;
int g_nIgmpCount = 0;

//Filter in source address
int gOption_Filter_Source_Type;
AnsiString gOption_Filter_Source_Only_Ip;
AnsiString gOption_Filter_Source_From_Ip;
AnsiString gOption_Filter_Source_To_Ip;

//Filter in Destine address
int gOption_Filter_Destine_Type;
AnsiString gOption_Filter_Destine_Only_Ip;
AnsiString gOption_Filter_Destine_From_Ip;
AnsiString gOption_Filter_Destine_To_Ip;

int g_nNextId;
// next record id

bool g_bThreadIsRun = false;

int gOption_Record_PerPage = DEFAULT_RECORD_COUNT_PERPAGE;//record per page
int gOption_ClearCache = 1;
int gOption_UniqueId = 1;
int gOption_SaveBuffer = 1;

//MISC
int gOption_Show_Splash = 1;
int gOption_Display_Icon = 1;
int gOption_Display_Status = 1;
int gOption_Min_Start = 1;
int gOption_Exit_Confirm = 1;
int gOption_Auto_Run = 0;
int gOption_Auto_Sniffer = 0;
int gOption_Auto_NIC_Index = -1;

int gOption_Run_First_Time = 0;

AnsiString gOption_File_Auto_Save;

AnsiString g_szFile_Open;
AnsiString g_szFile_Save;

int g_pSpecify_Ports[NUMBER_MAX_SPECIFY_PORT]={0};

TStringList *g_SkinList;
TStringList *g_LangList;
AnsiString g_SkinFile;
