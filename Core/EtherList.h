// $Author: zhengsh $
// $Date: 2006/09/16 09:44:57 $
// $Id: EtherList.h,v 1.4 2006/09/16 09:44:57 zhengsh Exp $
// Link List to save EtherDataGram List
//---------------------------------------------------------------------------

#ifndef EtherListH
#define EtherListH
#include "EtherDataGram.h"
//---------------------------------------------------------------------------
class TEtherList
{
    public:
        TEtherList();
        ~TEtherList();
        int GetCount();
        bool GetElem(int id,TEtherDataGram &e);

        void AddNode(const TEtherDataGram &e);
        void Clear();
        bool SaveToCache();
        void SetCacheFile(AnsiString szFile =  "");
        int GetRecordCount();
        //get cache record count
        int GetPageCount();
        //cache record page count
        bool LoadFromCahce(int page=1);
        //load packets from cache file
    	void Rewind();
        //reset the header as current position
    	bool GetNext(TEtherDataGram &e);

        AnsiString GetHint(int id);
        //get description of a packet

    private:
        TEtherDataGram *pHead,*pCur;
        TEtherDataGram *getTail();
         //get tail node
        int nRecordCount;
        AnsiString szCacheFile;

};

#endif
