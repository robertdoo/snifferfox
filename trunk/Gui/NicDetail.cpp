// Author: zhengsh
// Date: 2005/10/03 01:30:35
// $Id: NicDetail.cpp,v 1.7 2006/09/29 15:31:35 zhengsh Exp $

//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "NicDetail.h"
#include "Functions.h"
#include "Global.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "SUIEdit"
#pragma link "SUIForm"
#pragma link "SUIButton"
#pragma link "SUIMgr"
#pragma link "SUIButton"
#pragma resource "*.dfm"
TfrmNicDetail *frmNicDetail;
//---------------------------------------------------------------------------
__fastcall TfrmNicDetail::TfrmNicDetail(TComponent* Owner)
    : TForm(Owner)
{
    //ThemeManager->UIStyle = g_nUiStyle;
	Left = (Screen->Width-Width)/2;
    Top = (Screen->Height - Height)/2;
    nHeight = Height;
    nWidth = Width;
    Refresh();
}
//---------------------------------------------------------------------------

void TfrmNicDetail::SetNic(pcap_if_t *d)
{
    stNicName->Caption = d->name;
    stDesc->Caption = StringFormat(d->description,55);
    pcap_addr_t *a;
    a = d->addresses;

    stAddrFamily->Caption = "AF_INET";
    stAddr->Caption = iptos(((struct sockaddr_in *)a->addr)->sin_addr.s_addr);
    stNetmask->Caption = iptos(((struct sockaddr_in *)a->netmask)->sin_addr.s_addr);
    stBroadcast->Caption = iptos(((struct sockaddr_in *)a->broadaddr)->sin_addr.s_addr);
    stLoopback->Caption = (d->flags & PCAP_IF_LOOPBACK)?"yes":"no";
}
void __fastcall TfrmNicDetail::btnOkClick(TObject *Sender)
{
    Close();
}
//---------------------------------------------------------------------------

void TfrmNicDetail::Refresh()
{
    if (g_SkinFile == "")
        ThemeManager->UIStyle = (TsuiUIStyle)g_nUiStyle;
    else
    {
        AnsiString szSkinFile = DIR_ROOT + DIR_SKINS + g_SkinFile + EXT_SKIN;
        ThemeManager->UIStyle = FromThemeFile;
        ThemeManager->FileTheme->ThemeFile = szSkinFile;
    }

    Height = nHeight;
    Width = nWidth;
	Left = (Screen->Width-Width)/2;
    Top = (Screen->Height - Height)/2;

    frmNicDetail->Caption = g_pLanguage->GetValue("FRMNICDETAIL_TITLE");
    lblNicName->Caption = g_pLanguage->GetValue("FRMNICDETAIL_NEWCARD_NAME");
    lblDesc->Caption = g_pLanguage->GetValue("FRMNICDETAIL_DESC");
    lblLoopback->Caption = g_pLanguage->GetValue("FRMNICDETAIL_LOOPBACK");
    lblAddrFamily->Caption = g_pLanguage->GetValue("FRMNICDETAIL_ADDR_FAMILY");
    lblAddr->Caption = g_pLanguage->GetValue("FRMNICDETAIL_ADDR");
    lblNetmask->Caption = g_pLanguage->GetValue("FRMNICDETAIL_NETMASK");
    lblBroadcast->Caption = g_pLanguage->GetValue("FRMNICDETAIL_BROADCAST");
    btnOk->Caption = g_pLanguage->GetValue("FRMNICDETAIL_BUTTEN_SAVA");
}

void __fastcall TfrmNicDetail::FormResize(TObject *Sender)
{
    Height = nHeight;
    Width = nWidth;
	Left = (Screen->Width-Width)/2;
    Top = (Screen->Height - Height)/2;
}
//---------------------------------------------------------------------------


void __fastcall TfrmNicDetail::FormCreate(TObject *Sender)
{
    Refresh();    
}
//---------------------------------------------------------------------------






