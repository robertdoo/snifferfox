// $Author: zhengsh $
// $Date: 2006/09/29 15:31:33 $
// $Id: Functions.cpp,v 1.25 2006/09/29 15:31:33 zhengsh Exp $

//---------------------------------------------------------------------------


#pragma hdrstop

#include "Functions.h"
#include "Global.h"
#include "winsock2.h"
#include "windows.h"
#include "Config.h"
#include "Constant.h"
#include "MsgDialog.h"
#include "EtherDataGram.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)

AnsiString GetDir(AnsiString Path)
//从路径中获得目录
{
	int cnt,pos;
    AnsiString Dir;
    for(cnt=Path.Length();cnt>0;cnt--)
    {
       	if(Path[cnt]=='\\')
           	break;
    }

    pos = cnt;

    for(cnt=1;cnt<pos;cnt++)
      	Dir +=Path[cnt];

    return Dir;
}

AnsiString GetFileName(AnsiString Path)
//从路径中获得文件名称
{
	int cnt=0,pos;
    AnsiString FileName;
    for(cnt=Path.Length();cnt>0;cnt--)
       	if(Path[cnt]=='\\')
           	break;
    pos = cnt;
    for(cnt=pos+1;cnt<=Path.Length();cnt++)
       	FileName += Path[cnt];
    FileName+='\0';

    return AnsiString(FileName);
}

AnsiString GetCurDir()
//获得当前目录
{
    char buf[100];
    GetCurrentDirectory(MAX_PATH,buf);
    return AnsiString(buf);
}


void SystemInitialize()
//系统初始化
{
    //获得系统根目录
    DIR_ROOT = GetDir(GetDir(ParamStr(0)).c_str());
    
    AnsiString szLang;
    if (GetSystemVariable(SECTION_OPTOINS,"Language",szLang))
        g_pLanguage = new TLanguage(szLang);
    else
        g_pLanguage = new TLanguage();
    DeleteFile(DIR_ROOT + DIR_CACHE + FILE_CACHE);
	ghCacheFileMutex = CreateMutex(NULL,false,"CacheFileMutex");
	AnsiString szUiStyle;
	if (GetSystemVariable(SECTION_OPTOINS,"UIStyle",szUiStyle))
		g_nUiStyle = szUiStyle.ToInt();

	AnsiString szNextId;
	if (GetSystemVariable(SECTION_OPTOINS,"NextId",szNextId))
		g_nNextId = szNextId.ToInt();
	else
		g_nNextId = 0;

	AnsiString Value;
	if (GetSystemVariable(SECTION_OPTOINS,"Arp",Value))
		gOption_Filter_Arp = Value.ToInt();
	else
		gOption_Filter_Arp = 1;
	if (GetSystemVariable(SECTION_OPTOINS,"Rarp",Value))
		gOption_Filter_Rarp = Value.ToInt();
	else
		gOption_Filter_Rarp = 1;
	if (GetSystemVariable(SECTION_OPTOINS,"Ip",Value))
		gOption_Filter_Ip = Value.ToInt();
	else
		gOption_Filter_Ip = 1;
	if (GetSystemVariable(SECTION_OPTOINS,"Others",Value))
		gOption_Filter_Others = Value.ToInt();
	else
		gOption_Filter_Others = 1;

	if (GetSystemVariable(SECTION_OPTOINS,"Tcp",Value))
		gOption_Filter_Tcp = Value.ToInt();
	else
		gOption_Filter_Tcp = 1;
	if (GetSystemVariable(SECTION_OPTOINS,"Udp",Value))
		gOption_Filter_Udp = Value.ToInt();
	else
		gOption_Filter_Udp = 1;
	if (GetSystemVariable(SECTION_OPTOINS,"Icmp",Value))
		gOption_Filter_Icmp = Value.ToInt();
	else
		gOption_Filter_Icmp = 1;
	if (GetSystemVariable(SECTION_OPTOINS,"Igmp",Value))
		gOption_Filter_Igmp = Value.ToInt();
	else
		gOption_Filter_Igmp = 1;

	if (GetSystemVariable(SECTION_OPTOINS,"Source_Type",Value))
		gOption_Filter_Source_Type = Value.ToInt();
	else
	   gOption_Filter_Source_Type = OPTION_SOURCE_ALL;
	if (GetSystemVariable(SECTION_OPTOINS,"Source_Only",Value))
		gOption_Filter_Source_Only_Ip = Value;
	else
	   gOption_Filter_Source_Only_Ip = "";
	if (GetSystemVariable(SECTION_OPTOINS,"Source_From",Value))
		gOption_Filter_Source_From_Ip = Value;
	else
	   gOption_Filter_Source_From_Ip = "";
	if (GetSystemVariable(SECTION_OPTOINS,"Source_To",Value))
		gOption_Filter_Source_To_Ip = Value;
	else
	   gOption_Filter_Source_To_Ip = "";

	if (GetSystemVariable(SECTION_OPTOINS,"Destine_Type",Value))
		gOption_Filter_Destine_Type = Value.ToInt();
	else
	   gOption_Filter_Destine_Type = OPTION_DESTINE_ALL;
	if (GetSystemVariable(SECTION_OPTOINS,"Destine_Only",Value))
		gOption_Filter_Destine_Only_Ip = Value;
	else
	   gOption_Filter_Destine_Only_Ip = "";
	if (GetSystemVariable(SECTION_OPTOINS,"Destine_From",Value))
		gOption_Filter_Destine_From_Ip = Value;
	else
	   gOption_Filter_Destine_From_Ip = "";
	if (GetSystemVariable(SECTION_OPTOINS,"Destine_To",Value))
		gOption_Filter_Destine_To_Ip = Value;
	else
	   gOption_Filter_Destine_To_Ip = "";
	//save option
	if (GetSystemVariable(SECTION_OPTOINS,"Record_PerPage",Value))
		gOption_Record_PerPage = Value.ToInt();
	if (GetSystemVariable(SECTION_OPTOINS,"Clear_Cache",Value))
		gOption_ClearCache = Value.ToInt();
	if (GetSystemVariable(SECTION_OPTOINS,"Unique_Id",Value))
		gOption_UniqueId = Value.ToInt();
	if (GetSystemVariable(SECTION_OPTOINS,"Save_Buffer",Value))
		gOption_SaveBuffer = Value.ToInt();


	if (GetSystemVariable(SECTION_OPTOINS,"Ftp",Value))
		gOption_Filter_Ftp = Value.ToInt();
	if (GetSystemVariable(SECTION_OPTOINS,"Ssh",Value))
		gOption_Filter_Ssh = Value.ToInt();
	if (GetSystemVariable(SECTION_OPTOINS,"Dns",Value))
		gOption_Filter_Dns = Value.ToInt();
	if (GetSystemVariable(SECTION_OPTOINS,"Telnet",Value))
		gOption_Filter_Telnet = Value.ToInt();
	if (GetSystemVariable(SECTION_OPTOINS,"Smtp",Value))
		gOption_Filter_Smtp = Value.ToInt();
	if (GetSystemVariable(SECTION_OPTOINS,"Gopher",Value))
		gOption_Filter_Gopher = Value.ToInt();
	if (GetSystemVariable(SECTION_OPTOINS,"Http",Value))
		gOption_Filter_Http = Value.ToInt();
	if (GetSystemVariable(SECTION_OPTOINS,"Pop3",Value))
		gOption_Filter_Pop3 = Value.ToInt();
	if (GetSystemVariable(SECTION_OPTOINS,"Finger",Value))
		gOption_Filter_Finger = Value.ToInt();
	if (GetSystemVariable(SECTION_OPTOINS,"Ldap",Value))
		gOption_Filter_Ldap = Value.ToInt();
	if (GetSystemVariable(SECTION_OPTOINS,"Tftp",Value))
		gOption_Filter_Tftp = Value.ToInt();
	if (GetSystemVariable(SECTION_OPTOINS,"AppOthers",Value))
		gOption_Filter_AppOthers = Value.ToInt();
    //MISC
	if (GetSystemVariable(SECTION_OPTOINS,"Display_Splash",Value))
		gOption_Show_Splash = Value.ToInt();
	if (GetSystemVariable(SECTION_OPTOINS,"Display_Icon",Value))
		gOption_Display_Icon = Value.ToInt();
	if (GetSystemVariable(SECTION_OPTOINS,"Display_Status",Value))
		gOption_Display_Status = Value.ToInt();
	if (GetSystemVariable(SECTION_OPTOINS,"Min_Start",Value))
		gOption_Min_Start = Value.ToInt();
	if (GetSystemVariable(SECTION_OPTOINS,"Exit_Confirm",Value))
		gOption_Exit_Confirm = Value.ToInt();
	if (GetSystemVariable(SECTION_OPTOINS,"Auto_Run",Value))
		gOption_Auto_Run = Value.ToInt();
	if (GetSystemVariable(SECTION_OPTOINS,"Auto_Sniffer",Value))
		gOption_Auto_Sniffer = Value.ToInt();
	if (GetSystemVariable(SECTION_OPTOINS,"File_Auto_Save",Value))
		gOption_File_Auto_Save = Value;
    else
         gOption_File_Auto_Save = DIR_ROOT + DIR_SAVE + FILE_AUTOSAVE;
	if (GetSystemVariable(SECTION_OPTOINS,"Auto_NIC_Index",Value))
		gOption_Auto_NIC_Index = Value.ToInt();

	if (GetSystemVariable(SECTION_OPTOINS,"Run_First_Time",Value))
	{
    	gOption_Run_First_Time = Value.ToInt();
        SetSystemVariable(SECTION_OPTOINS,"Run_First_Time",0);
    }  

	if (GetSystemVariable(SECTION_OPTOINS,"Skin_File",Value))
		g_SkinFile = Value;
    else
        g_SkinFile = "";
      

    if (gOption_UniqueId == 0)
    {
    	g_nNextId = 0;
    }
    int errport;
	if (GetSystemVariable(SECTION_OPTOINS,"Specify_Port",Value))
		PortParser(Value,errport);

    //get skin file list
    g_SkinList = new TStringList;
    TSearchRec sr;
	if(FindFirst(DIR_ROOT + DIR_SKINS + "*"+ EXT_SKIN,faAnyFile,sr)==0)
	{
		do
		{
            if((sr.Attr) && sr.Name!="." && sr.Name!="..")
			{
                AnsiString szSkinFile = sr.Name;
                szSkinFile = szSkinFile.SubString(0,szSkinFile.Length()-EXT_SKIN.Length());
                g_SkinList->Add(szSkinFile);
            }
		}while(FindNext(sr)==0);
	}
	FindClose(sr);

    //get language file list
    g_LangList = new TStringList;
	if(FindFirst(DIR_ROOT + DIR_LANG + "*" + EXT_LANG,faAnyFile,sr)==0)
	{
		do
		{
            if((sr.Attr) && sr.Name!="." && sr.Name!="..")
			{
                AnsiString szLangFile = sr.Name;
                szLangFile = szLangFile.SubString(0,szLangFile.Length()-EXT_LANG.Length());
                g_LangList->Add(szLangFile);
                //ShowMsg(szLangFile);
            }
		}while(FindNext(sr)==0);
	}
	FindClose(sr);

}


pcap_if_t *GetNicList(AnsiString &szErrMsg, int &nicount)
//获得系统的网卡列表
{
	pcap_if_t *alldevs;
	pcap_if_t *d;
	int i=0;
	char errbuf[PCAP_ERRBUF_SIZE];

	/* 这个API用来获得网卡的列表 */
	if (pcap_findalldevs(&alldevs, errbuf) == -1)
	{
	    szErrMsg = g_pLanguage->GetValue("ERROR_FIND_NETWORK_LIST_FAILURE") + errbuf;
	    return NULL;
	}

	/* 计算网卡数量 */
	for(d=alldevs;d;d=d->next)
        i++;
    nicount = i;

    return alldevs;

	/* We don't need any more the device list. Free it */
	//pcap_freealldevs(alldevs);
}

#define IPTOSBUFFERS   12
AnsiString iptos(ULONG in)
/* 将一个unsigned long 型的IP转换为字符串类型的IP */
{ //TIpAddress
	TIpAddress *IpAddr = (TIpAddress*)(&in);
    return AnsiString(IpAddr->byte1)+AnsiString(".")+AnsiString(IpAddr->byte2)+AnsiString(".")
    	+AnsiString(IpAddr->byte3)+AnsiString(".")+AnsiString(IpAddr->byte4);
}

#define PROTOCOL_NUMBER 11
//ip层以上的协议个数
typedef struct
{
    int protocol;//协议代码
    char name[20];//协议名称
}TProtocol;

static TProtocol Protocol[PROTOCOL_NUMBER + 1] = {
	{ IPPROTO_IP   , "IP" },
	{ IPPROTO_ICMP , "ICMP" },
	{ IPPROTO_IGMP , "IGMP" },
	{ IPPROTO_GGP  , "GGP" },
	{ IPPROTO_TCP  , "TCP" },
	{ IPPROTO_PUP  , "PUP" },
	{ IPPROTO_UDP  , "UDP" },
	{ IPPROTO_IDP  , "IDP" },
	{ IPPROTO_ND   , "NP"  },
	{ IPPROTO_RAW  , "RAW" },
	{ IPPROTO_MAX  , "MAX" },
	{ NULL , "" }
};//Protocol

char *GetProtocolName(int protocol)
//获得协议的名称
{
    for (int cnt=0; cnt < PROTOCOL_NUMBER;cnt++)
        if (protocol == Protocol[cnt].protocol)
            return Protocol[cnt].name;
    return "";
}

AnsiString To16(u_char ch)
//转换成16进位
{
    char buf[10];
    AnsiString Ret;
    sprintf(buf,"%x",ch);
    if (strlen(buf) == 1)
    {
        Ret = "0";
        Ret += buf;
    }
    else
        Ret = buf;
    return Ret.UpperCase();
}

AnsiString To16(int src)
//转换成16进位
{
    u_char ch1,ch2,ch3,ch4,*p=(u_char*)&src;
    memcpy(&ch1,p,1);
    memcpy(&ch2,p+2,1);
    memcpy(&ch3,p+3,1);
    memcpy(&ch4,p+4,1);
    AnsiString tmp;
    tmp = To16(ch1)+To16(ch2)+To16(ch3)+To16(ch4);
    return tmp;
}

AnsiString To16(short src)
//转换成16进位
{
    u_char ch1,ch2,*p=(u_char*)&src;
    memcpy(&ch1,p,1);
    memcpy(&ch2,p+2,1);
    AnsiString tmp;
    tmp = To16(ch1)+To16(ch2);
    return tmp;
}


bool FileCopy(AnsiString szDest,AnsiString szSrc)
//file copy
{
    if (!FileExists(szSrc))
    	return false;
    u_char buf[BUFFER_SIZE+1];
    FILE *fpSrc,*fpDest;
    fpSrc = fopen(szSrc.c_str(),"r");
    fpDest = fopen(szDest.c_str(),"w");
    if (!fpSrc || !fpDest)
    	return false;
    int filesize = 0,length;
    fseek(fpSrc,0,SEEK_END);
    filesize = ftell(fpSrc);
    ShowMsg(filesize);
    rewind(fpSrc);
    int pos = 0;
    while (true)
    {
    	ShowMsg(pos);
    	if (pos >= filesize)
        	break;
    	if (filesize - pos > BUFFER_SIZE)
        	length = BUFFER_SIZE;
        else
        	length = filesize - pos;

    	fread(buf,length,1,fpSrc);
        fwrite(buf,length,1,fpDest);
        pos += length;
    }
    fclose(fpDest);
    fclose(fpSrc);
    return true;
}

AnsiString CharFilter(AnsiString szSrc,char ch)
//delete specified char from szSrc
{
    AnsiString szDest;
    for (int cnt=1; cnt<=szSrc.Length(); cnt++)
        if (szSrc[cnt] != ch)
            szDest += szSrc[cnt];

    return szDest;
}

AnsiString SpaceFilter(AnsiString szSrc)
{
    return CharFilter(szSrc, ' ');
}//spaceFilter

bool PortParser(AnsiString szPorts,AnsiString &invalid)
{
    szPorts = SpaceFilter(szPorts);
    invalid = "" ;
    int cnt,portcnt=0;
    for (cnt=1; cnt<=szPorts.Length(); cnt++)
    {
        if (szPorts[cnt] != ',' && !(szPorts[cnt] >= '0' && szPorts[cnt] <= '9'))
            break;
    }
    if (cnt <= szPorts.Length())
        return false;
    AnsiString szNum = "";
  
    for (cnt=1;cnt<=szPorts.Length(); cnt++)
    {
        if (szPorts[cnt] == ',' || cnt == szPorts.Length())
        {
            if (cnt == szPorts.Length() && (szPorts[cnt] >= '0' && szPorts[cnt] <= '9'))
                szNum += szPorts[cnt];
            if (szNum.Length() != 0)
            {
                int port;
                try{
                    port = szNum.ToInt();
                }
                catch(...)
                {
                    invalid = szNum;
                    return false;
                }
                if (port <=0 || port >= 65536)
                {
                    invalid = szNum;
                    return false;
                }
                portcnt++;
                g_pSpecify_Ports[portcnt] = port;
                szNum = "";
            }
        }
        else
            szNum += szPorts[cnt];
    }
    g_pSpecify_Ports[0] = portcnt;
    return  true;
}

void SystemDestory()
{
    //ShowMessage("SystemDestory");
}

AnsiString FillSpace(AnsiString Src,int Count,bool rightfill)
//fill in space to Src string until the length is count
{
    if (rightfill == true)
    {
        while (Src.Length() < Count)
            Src += " ";
    }
    else
    {
        while (Src.Length() < Count)
            Src = " " + Src;
    }

    return Src;
}

void WaitForExec(AnsiString szCmd)
{
    SHELLEXECUTEINFO ShExecInfo = {0};
    ShExecInfo.cbSize = sizeof(SHELLEXECUTEINFO);
    ShExecInfo.fMask = SEE_MASK_NOCLOSEPROCESS;
    ShExecInfo.hwnd = NULL;
    ShExecInfo.lpVerb = NULL;
    ShExecInfo.lpFile = szCmd.c_str();
    ShExecInfo.lpParameters = "";
    ShExecInfo.lpDirectory = NULL;
    ShExecInfo.nShow = SW_SHOW;
    ShExecInfo.hInstApp = NULL;
    ShellExecuteEx(&ShExecInfo);
    WaitForSingleObject(ShExecInfo.hProcess,INFINITE);
}

AnsiString StringFormat(AnsiString Src, int nLineLength)
//delete contninus space, add '\n' if length if more than nLineLength
{
    int cnt;
    AnsiString Dst;
    bool LastIsSpace = false;
    for (cnt=1; cnt<=Src.Length(); cnt++)
    {
        if (Src[cnt] == ' ' && LastIsSpace)
            continue;
        LastIsSpace = (Src[cnt] == ' ');
        if (nLineLength > 0 && Dst.Length() != 0)
            if ((Dst.Length()%nLineLength) == 0)
                Dst += "\n";
        Dst += Src[cnt];
    }
    return Dst;
}



