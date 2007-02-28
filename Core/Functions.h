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
//��·���л��Ŀ¼

AnsiString GetFileName(AnsiString Path);
//��·���л���ļ�����

AnsiString GetCurDir();
//��õ�ǰĿ¼

void SystemInitialize();
//ϵͳ��ʼ��
void SystemDestory();

pcap_if_t *GetNicList(AnsiString &szErrMsg,int &nicount);
//���ϵͳ�������б�

AnsiString iptos(u_long in);
/* ��һ��unsigned long �͵�IPת��Ϊ�ַ������͵�IP */

char *GetProtocolName(int protocol);
//���Э�������

AnsiString To16(u_char ch);
//ת����16��λ

AnsiString To16(short src);
//ת����16��λ

AnsiString To16(int src);
//ת����16��λ

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
