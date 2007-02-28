// Author: zhengsh
// Date: 2005/10/05 15:48:42
// $Id: Config.cpp,v 1.3 2006/09/16 09:44:56 zhengsh Exp $

//---------------------------------------------------------------------------


#pragma hdrstop

#include "Config.h"
#include "Constant.h"
#include <IniFiles.hpp>
#include "Global.h"
#include "registry.hpp"

//---------------------------------------------------------------------------

#pragma package(smart_init)

bool getConfigKey(AnsiString Section,AnsiString Key,AnsiString &Value)
{
    TIniFile *ini;
    ini=new TIniFile(DIR_ROOT+DIR_CONF+SYSTEM_CONFIG_FILE);
   
    Value=ini->ReadString(Section,Key,"failflag");
	delete ini;
	//ShowMessage(Value);
	if(Value=="failflag")
		return false;
	else
		return true;
}

bool setConfigKey(AnsiString Section,AnsiString Key,AnsiString Value)
{
    TIniFile *ini;
    ini=new TIniFile(DIR_ROOT+DIR_CONF+SYSTEM_CONFIG_FILE);
    ini->WriteString(Section,Key,Value);
	delete ini;	    
	return true;	
}

bool GetSystemVariable(AnsiString Section,AnsiString Key,AnsiString &Value)
//获得系统设置
{
	return getConfigKey(Section,Key,Value);	
}

bool SetSystemVariable(AnsiString Section,AnsiString Key,AnsiString Value)
//设置系统设置
{
	return setConfigKey(Section,Key,Value);
}


bool SetAutoRun()
{
    TRegistry *rg;
    rg = new TRegistry();
    rg->RootKey=HKEY_LOCAL_MACHINE;
    AnsiString szKey = "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run\\";
    rg->OpenKey(szKey,false);

    if (!rg->KeyExists("SnifferFox"))
        if (!rg->CreateKey("SnifferFox"))
            return false;
    rg->WriteString("SnifferFox",DIR_ROOT+DIR_BIN+"SnifferFox.exe autorun");
    delete rg;

	return true;
}

bool UnsetAutoRun()
{
    TRegistry *rg;
    rg = new TRegistry();
    rg->RootKey=HKEY_LOCAL_MACHINE;
    AnsiString szKey = "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run\\";
    rg->OpenKey(szKey,false);
   // ShowMessage(rg->CurrentKey);
    //ShowMessage(rg->CurrentPath);

    rg->WriteString("SnifferFox","");

    if (rg->KeyExists("SnifferFox"))
    {  
        rg->DeleteKey("SnifferFox");
    }
    delete rg;

	return true;
}


