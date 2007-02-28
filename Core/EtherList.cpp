// Author: zhengsh
// Date: 2005/10/09 01:46:28
// $Id: EtherList.cpp,v 1.8 2006/09/16 12:50:01 zhengsh Exp $
//---------------------------------------------------------------------------


#pragma hdrstop                                                      

#include "EtherList.h"
#include "Global.h"
#include "Constant.h"
#include "MsgDialog.h"
#include "stdio.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)

TEtherList::TEtherList()
{
    pHead = 0;
    nRecordCount = 0;
    pCur = 0;
}

TEtherList::~TEtherList()
{
    Clear();
}

int TEtherList::GetCount()
{
    TEtherDataGram * tmp = pHead;
    int cnt = 0;
    while (tmp != 0)
    {
		cnt++;
        tmp = tmp->pNext;
    }
	return cnt;
}


bool TEtherList::GetElem(int id,TEtherDataGram &e)
{
    TEtherDataGram * tmp = pHead;
	while (tmp != 0)
    {
        if (tmp->GetId() == id)
            break;
        tmp = tmp->pNext;
    }
	if (tmp == 0)
        return false;
    e = *tmp;
    return true;
}

void TEtherList::AddNode(const TEtherDataGram &e)
{
     TEtherDataGram * tmp = new TEtherDataGram,*tail = 0 ;
     *tmp = e;
     tail = getTail();
     tmp->pNext = 0;
     if (tail == 0)
        pHead = tmp;
     else
        tail->pNext = tmp;
}


TEtherDataGram *TEtherList::getTail()
//get tail node
{
    TEtherDataGram * tmp = pHead,*pre = pHead;
    while (tmp != 0)
    {
        pre = tmp;
        tmp = tmp->pNext;
	}
	return pre;
}

void TEtherList::Clear()
{
    TEtherDataGram * tmp = pHead,*pre;
    pHead = 0;
    nRecordCount = 0;
    pCur = 0;
	while (tmp != 0)
    {
        pre = tmp;
        tmp = tmp->pNext;
        delete pre;
    }
}

bool TEtherList::SaveToCache()
{
    FILE *fp;
    AnsiString szFile = DIR_ROOT+DIR_CACHE+FILE_CACHE;
	//int nCurCount =  GetCount();
	fp = fopen(szFile.c_str(),"a+b");
	//int nTotalCount = 0;
	if (!fp)
	{
    	//ShowMsg("open file error");
    	return false;
    }
	TEtherDataGram * tmp = pHead,*pre;
	pHead = 0;
	fseek(fp,0,SEEK_END);
	while (tmp)
	{
		tmp->SaveToCache(fp);
		pre = tmp;
		tmp = tmp->pNext;
		delete pre;
	}
	fclose(fp);
	return true;
}

int TEtherList::GetRecordCount()
//get cache record count
{
	if (nRecordCount != 0)
    	return nRecordCount;
    FILE *fp;
    long pos = 0;
    fp = fopen(szCacheFile.c_str(),"r");
    if (fp == 0)
    	return -1;
    //TEtherDataGram *tmp = new  TEtherDataGram,*pre;
    //struct pcap_pkthdr
    int intsize = sizeof(int);
    fseek(fp,0,SEEK_END);
    int filesize = ftell(fp);
    int cnt = 0;
    int length = 0;
    int offset = 0;
    rewind(fp);
    //ShowMsg(intsize);
    while (!feof(fp))
    {
    	if (pos >= filesize)
        	break;
    	fseek(fp,intsize,SEEK_CUR);
        //ShowMsg(AnsiString("ftell(before read):")+ftell(fp));
        fread(&length,intsize,1,fp);
        //offset = length-2*intsize;
        //ShowMsg(AnsiString("length:")+length);
        //ShowMsg(AnsiString("ftell(after read):")+ftell(fp));
        pos += length;
        fseek(fp,pos,SEEK_SET);
        //ShowMsg(AnsiString("ftell(after fseek):")+AnsiString(ftell(fp))+AnsiString("\npos:")+AnsiString(pos)+AnsiString("\nlength")+AnsiString(length)+AnsiString("\nfilesize:")+filesize);
        cnt++;
        //ShowMsg( cnt);
    }
    nRecordCount = cnt;
    fclose(fp);
    return cnt;
}
int TEtherList::GetPageCount()
//get cache record page count
{
    int total = GetRecordCount();
    if (total % gOption_Record_PerPage == 0)
    	return total / gOption_Record_PerPage;
    return total / gOption_Record_PerPage + 1;
}

void TEtherList::SetCacheFile(AnsiString szFile)
{
	szCacheFile = szFile;
}

bool TEtherList::LoadFromCahce(int page)
//load packets from cache file
{
	if (page <=0 || page > GetPageCount())
    	return false;
	FILE *fp;
    int pos = 0,id = 0;
    fp = fopen(szCacheFile.c_str(),"r");
    if (fp == 0)
    	return false;

    int intsize = sizeof(int);
    fseek(fp,0,SEEK_END);
    int filesize = ftell(fp);
    int cnt = 0;
    int length = 0;
    int offset = 0;
    rewind(fp);
	//search for current page
    while (!feof(fp))
    {
        //ShowMessage(cnt);
    	if (cnt / gOption_Record_PerPage == page - 1 )//it is current page now
        	break;
    	if (pos >= filesize)//end of file
        	break;
    	fseek(fp,intsize,SEEK_CUR);
        fread(&length,intsize,1,fp);
        pos += length;
        fseek(fp,pos,SEEK_SET);
        //ShowMsg(AnsiString("ftell(after fseek):")+AnsiString(ftell(fp))+AnsiString("\npos:")+AnsiString(pos)+AnsiString("\nlength")+AnsiString(length)+AnsiString("\nfilesize:")+filesize);
        cnt++;
    }

   	if (pos >= filesize)
	{
    	fclose(fp);
    	return false;
    }
    TEtherDataGram tmp;

    struct pcap_pkthdr pkthdr;
    u_char pBuf[BUFFER_SIZE];
    cnt = 0;
    Clear();
    while (!feof(fp))
    {
    	if (pos >= filesize)//end of file
        	break;
        if (cnt >= gOption_Record_PerPage)
        	break;//end of this page
    	fread(&id,sizeof(int),1,fp);
    	tmp.SetId(id);
        //ShowMsg(id);
        fseek(fp,pos+sizeof(int),SEEK_SET);
    	fread(&offset,sizeof(int),1,fp);
       // AnsiString msg;
    	//msg = AnsiString("id:")+AnsiString(id)+AnsiString("\nOffst")+AnsiString(offset)+AnsiString("\npos:")+pos;
    	//ShowMsg(msg);
    	int nDataLength = offset-2*sizeof(int)-sizeof(struct pcap_pkthdr);
    	//pHead = new (struct pcap_pkthdr);
    	//pData = new u_char[nDataLength];
        fseek(fp,pos+2*sizeof(int),SEEK_SET);
    	fread(&pkthdr,sizeof(struct pcap_pkthdr),1,fp);
        fseek(fp,pos+2*sizeof(int)+sizeof(struct pcap_pkthdr),SEEK_SET);
    	fread(pBuf,nDataLength,1,fp);
        //ShowMsg(AnsiString("before")+cnt);
        tmp.SetBuffer(&pkthdr,pBuf,nDataLength);
        //ShowMsg(AnsiString("after")+cnt);
        //ShowMsg(AnsiString("offset:")+offset);
        AddNode(tmp);
        pos += offset;
        fseek(fp,pos,SEEK_SET);
        cnt++;

        //fseek(fp,offset,SEEK_CUR);
	}
    fclose(fp);
    //ShowMessage(cnt);
    return true;
}

void TEtherList::Rewind()
{
	pCur = pHead;
}

bool TEtherList::GetNext(TEtherDataGram &e)
{
	if (pCur == 0)
    	return false;
	e = * pCur;
    pCur = pCur->pNext;
    return true;
}

AnsiString TEtherList::GetHint(int id)
//get description of a packet
{
    AnsiString szHint = "";
    TEtherDataGram e;
    if (GetElem(id,e))
    {
         szHint = e.GetHint();
    }
    return szHint;
}

