//$Author: zhengsh $
//$Date: 2005/10/04 03:00:36 $
//$Id: Language.h,v 1.2 2005/10/04 03:00:36 zhengsh Exp $
//用于支持多语言
//---------------------------------------------------------------------------

#ifndef LanguageH
#define LanguageH
#include <vcl.h>


class TLangElem
{
    public:
        AnsiString szKey;
        AnsiString szValue;
        TLangElem * pNext;
        TLangElem();
};


class TLanguage
{
    public:
        TLanguage();
        TLanguage(AnsiString szLang);
        bool LoadLanguage(AnsiString szLang);
        //载入语言包
        //Strings GetLangaugeList(void);
        //获得语言包的列表
        AnsiString GetValue(AnsiString szKey);
        AnsiString GetCurLang();
        //获得当前的语言
        ~TLanguage();
    private:
        int countLine(AnsiString szLang);
        //统计文件的行数
        AnsiString spaceFilter(AnsiString szSrc);
        void clear();
        TLangElem *pHead;
        int nTop;
        AnsiString szLanguage;
};



//---------------------------------------------------------------------------
#endif
