//$Author: zhengsh $
//$Date: 2005/10/04 03:00:36 $
//$Id: Language.h,v 1.2 2005/10/04 03:00:36 zhengsh Exp $
//����֧�ֶ�����
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
        //�������԰�
        //Strings GetLangaugeList(void);
        //������԰����б�
        AnsiString GetValue(AnsiString szKey);
        AnsiString GetCurLang();
        //��õ�ǰ������
        ~TLanguage();
    private:
        int countLine(AnsiString szLang);
        //ͳ���ļ�������
        AnsiString spaceFilter(AnsiString szSrc);
        void clear();
        TLangElem *pHead;
        int nTop;
        AnsiString szLanguage;
};



//---------------------------------------------------------------------------
#endif
