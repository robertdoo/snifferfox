// $Author: zhengsh $
// $Date: 2006/09/29 15:31:33 $
// $Id: Functions.h,v 1.15 2006/09/29 15:31:33 zhengsh Exp $

//---------------------------------------------------------------------------

#ifndef FunctionsH
#define FunctionsH
//---------------------------------------------------------------------------
#include <vcl.h>
#include <pcap.h>
#include <Global.h>

AnsiString GetDir(AnsiString Path);
//从路径中获得目录

AnsiString GetFileName(AnsiString Path);
//从路径中获得文件名称

AnsiString GetCurDir();
//获得当前目录

void SystemInitialize();
//系统初始化
void SystemDestory();

pcap_if_t *GetNicList(AnsiString &szErrMsg,int &nicount);
//获得系统的网卡列表

AnsiString iptos(u_long in);
/* 将一个unsigned long 型的IP转换为字符串类型的IP */

char *GetProtocolName(int protocol);
//获得协议的名称

AnsiString To16(u_char ch);
//转换成16进位

AnsiString To16(short src);
//转换成16进位

AnsiString To16(int src);
//转换成16进位

bool FileCopy(AnsiString szDest,AnsiString szSrc);
//file copy

AnsiString SpaceFilter(AnsiString szSrc);
//Space Filter
AnsiString CharFilter(AnsiString szSrc,char ch);
//delete specified char from szSrc
bool PortParser(AnsiString szPorts,AnsiString &invalid);
AnsiString FillSpace(AnsiString Src,int Count = 20,bool rightfill=true);
//fill in space to Src string until the length is count

void WaitForExec(AnsiString szCmd);

AnsiString StringFormat(AnsiString Str, int nLineLength=-1);
//delete contninus space, add '\n' if length if more than nLineLength

#endif
