//$Author: zhengsh $
//$Date: 2006/09/13 13:47:37 $
//$Id: Language.cpp,v 1.7 2006/09/13 13:47:37 zhengsh Exp $



//---------------------------------------------------------------------------


#pragma hdrstop

#include "Language.h"
#include "Constant.h"
#include "Global.h"
#include "stdio.h"
#include "Config.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)


TLangElem::TLangElem()
{
    pNext = 0;
}

TLanguage::TLanguage()
{
    pHead = 0;
    nTop = 0;
    LoadLanguage(DEFUALT_LANGUAGE);
    szLanguage = DEFUALT_LANGUAGE;
}


TLanguage::TLanguage(AnsiString szLang)
{
    pHead = 0;
    nTop = 0;
    LoadLanguage(szLang);
    szLanguage = szLang;
}

bool TLanguage::LoadLanguage(AnsiString szLang)
{
    char buf[1024];
    AnsiString szFileName = DIR_ROOT + DIR_LANG + szLang + EXT_LANG;
    
    if (!FileExists(szFileName))//文件不存在
        return false;

    FILE *fp = fopen(szFileName.c_str(),"rb");
    if (fp == NULL)//打开文件失败
        return false;

    if (pHead != NULL)
        clear();

    int nLine = countLine(szLang);
    //ShowMessage(nLine);
    pHead = new TLangElem[nLine+1];
    AnsiString szTemp,szKey,szValue;

    while (!feof(fp))
    {
        fgets(buf,1024,fp);
        szTemp = buf;
        int nPos = szTemp.AnsiPos("=");
        if (nPos == 0)
            continue;
        szKey = szTemp.SubString(1,nPos-1);
        szKey = szKey.TrimLeft();
        szKey = szKey.TrimRight();
        szKey = spaceFilter(szKey);
        nPos = szTemp.AnsiPos("[");

        szValue = szTemp.SubString(nPos+1,szTemp.Length()-nPos);
        szValue = szValue.TrimRight();
        if (szValue[szValue.Length()] == ']')
            szValue = szValue.SubString(1,szValue.Length()-1);
        pHead[nTop].szKey = szKey.UpperCase();
        pHead[nTop++].szValue = szValue;
        //ShowMessage(szKey+":"+szValue);
    }
    fclose(fp);
    szLanguage = szLang;
    SetSystemVariable(SECTION_OPTOINS,"Language",szLanguage);
    return true;
}

int TLanguage::countLine(AnsiString szLang)
{//统计文件的行数
    AnsiString szFileName = DIR_ROOT + DIR_LANG + szLang + EXT_LANG;
    if (!FileExists(szFileName))//文件不存在
        return 0;
    FILE *fp = fopen(szFileName.c_str(),"rb");
    if (fp == NULL)//打开文件失败
        return 0;
    int cnt = 0;
    char ch = fgetc(fp);
    while (!feof(fp))
    {
        if (ch == '\n')
            cnt++;
        ch = fgetc(fp);
    }
    fclose(fp);
    return cnt;
}//countLine

AnsiString TLanguage::spaceFilter(AnsiString szSrc)
{
    AnsiString szDest;
    for (int cnt=1; cnt<=szSrc.Length(); cnt++)
        if (szSrc[cnt] != ' ')
            szDest += szSrc[cnt];

    return szDest;
}//spaceFilter

AnsiString TLanguage::GetValue(AnsiString szKey)
{
    int cnt = 0;
    szKey = spaceFilter(szKey);
    szKey = szKey.UpperCase();
    while(cnt < nTop)
    {
        if (szKey == pHead[cnt].szKey)
            return  pHead[cnt].szValue;
        cnt++;
    }
    return "";
}

void TLanguage::clear()
{
    nTop = 0;
    if (pHead != NULL)
        delete [] pHead;
    pHead = 0;
}

TLanguage::~TLanguage()
{
    clear();
}

AnsiString TLanguage::GetCurLang()
//获得当前的语言
{
    return szLanguage;
}

