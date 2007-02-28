//$Author: zhengsh $
//$Date: 2006/09/16 12:50:01 $
//$Id: IpAddr.cpp,v 1.11 2006/09/16 12:50:01 zhengsh Exp $
//---------------------------------------------------------------------------


#pragma hdrstop

#include "IpAddr.h"

TIpAddr::TIpAddr()
{
	ipBuf = "";
}

TIpAddr::TIpAddr(AnsiString ip)
{
	ipBuf = ip;
    //ipTemp = NULL;
}

AnsiString TIpAddr::FillStr(AnsiString sIp)
{
	AnsiString ipBuf;
	char *ch[5];
	ch[0]=sIp.c_str();
	char data[4][20]={"0","0","0","0"};
	for(int ret=1;ret<=4;ret++)
	{
		ch[ret]=strchr(ch[ret-1],'.')+1;

	}

	strncpy(data[0],ch[0],(int)(ch[1]-ch[0])-1);
	strncpy(data[1],ch[1],(int)(ch[2]-ch[1])-1);
	strncpy(data[2],ch[2],(int)(ch[3]-ch[2])-1);
	strcpy(data[3],ch[3]);
    
	//int count=0;
	for(int i=0;i<=3;i++)
	{
		int iLen;
		if( (iLen = strlen(data[i])) < 3 )
		{
			for(int j=3-iLen;j>0;j--)
			{
				ipBuf+=(AnsiString)"0";
			}
		}
		ipBuf+=(AnsiString)data[i];
		if(i==3)
			break;
		ipBuf+=(AnsiString)".";
	}
    return ipBuf;
}


bool TIpAddr::IsValid()
{
	char *ch[5];
	ch[0]=ipBuf.c_str();
	char data[4][20]={"","","",""};
	for(int ret=1;ret<=4;ret++)
	{
		ch[ret]=strchr(ch[ret-1],'.');
		if((ch[ret]==NULL)&&(ret!=4))
        {
            return 0;
        }else if((ch[ret]==NULL)&&(ret==4))
        {
            break;
        }else if((ch[ret]!=NULL)&&(ret>=5))
        {
            return 0;
        }
		ch[ret]+=1;
    }

    strncpy(data[0],ch[0],(int)(ch[1]-ch[0])-1);
    strncpy(data[1],ch[1],(int)(ch[2]-ch[1])-1);
    strncpy(data[2],ch[2],(int)(ch[3]-ch[2])-1);
    strcpy(data[3],ch[3]);

    for(int k=0;k<=3;k++)
    {
        int jr;
        jr=JudgeValue(data[k]);
        if( jr == 1 )
		{
            return 0;
		}

    }
    return 1;
}

bool TIpAddr::JudgeValue(char *str)
{
    char buf[4]="";
    int  sLen=strlen(str);
    if((sLen<=0)&&(sLen>3))
	{
        return 1;
	}

    strncpy(buf,str,sLen);
    for(int i=0;i<sLen;i++)
    {
        if((buf[i]<'0')||(buf[i]>'9'))
		{
            return 1;
		}
    }
	
	if(sLen==1||sLen==2)
        return 0;

    if(buf[0]>'2')
    {
        return 1;
    }else if(buf[0]=='2'){
        if(buf[1]>'5')
        {
            return 1;
        }else if(buf[1]=='5')
        {
            if(buf[2]>'5')
                return 1;
        }else
			return 0;
    }
    return 0;
}

bool TIpAddr::operator >(const TIpAddr &Ip)
{
	AnsiString sIp = Ip.ipBuf;
	AnsiString sIpTempDes = new char[16];
    AnsiString sIpTempSrc = new char[16];
    sIpTempDes=sIp;
    sIpTempSrc=ipBuf;
    sIpTempDes = FillStr(sIpTempDes);
    sIpTempSrc = FillStr(sIpTempSrc);

    if(sIpTempDes<=sIpTempSrc)
    {
        delete []sIpTempDes.c_str();
        delete []sIpTempSrc.c_str();
        return 1;
    }
    else
    {
        delete []sIpTempDes.c_str();
        delete []sIpTempSrc.c_str();
        return 0;
    }
}

bool TIpAddr::operator <(const TIpAddr &Ip)
{
	AnsiString sIp = Ip.ipBuf;
	AnsiString sIpTempDes = new char[16];
    AnsiString sIpTempSrc = new char[16];
    sIpTempDes=sIp;
    sIpTempSrc=ipBuf;
    sIpTempDes = FillStr(sIpTempDes);
    sIpTempSrc = FillStr(sIpTempSrc);

    if(sIpTempDes>=sIpTempSrc)
    {
        delete []sIpTempDes.c_str();
        delete []sIpTempSrc.c_str();
        return 1;
    }
    else
    {
        delete []sIpTempDes.c_str();
        delete []sIpTempSrc.c_str();
        return 0;
    }
}

bool TIpAddr::operator == (const TIpAddr &Ip)
{
	AnsiString sIp = Ip.ipBuf;
	AnsiString sIpTempDes = new char[16];
    AnsiString sIpTempSrc = new char[16];
    sIpTempDes=sIp;
    sIpTempSrc=ipBuf;
    sIpTempDes = FillStr(sIpTempDes);
    sIpTempSrc = FillStr(sIpTempSrc);

    if(sIpTempDes==sIpTempSrc)
    {
        delete []sIpTempDes.c_str();
        delete []sIpTempSrc.c_str();
        return 1;
    }
    else
    {
        delete []sIpTempDes.c_str();
        delete []sIpTempSrc.c_str();
        return 0;
    }

}

TIpAddr & TIpAddr::operator=(AnsiString sIp)
{
	this->ipBuf = sIp;
	return *this;
}

//---------------------------------------------------------------------------

#pragma package(smart_init)
