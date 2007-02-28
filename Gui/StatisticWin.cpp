// $Author: zhengsh $
// $Date: 2006/09/09 16:13:06 $
// $Id: StatisticWin.cpp,v 1.9 2006/09/09 16:13:06 zhengsh Exp $
//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "StatisticWin.h"
#include "Global.h"
#include "Constant.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "SUIButton"
#pragma link "SUIForm"
#pragma link "SUIGroupBox"
#pragma link "SUIImagePanel"
#pragma link "SUIPageControl"
#pragma link "SUITabControl"
#pragma link "SUIMgr"
#pragma link "SUIProgressBar"
#pragma resource "*.dfm"
TfrmStatistic *frmStatistic;
//---------------------------------------------------------------------------
__fastcall TfrmStatistic::TfrmStatistic(TComponent* Owner)
	: TForm(Owner)
{
    frmStatistic->Caption = g_pLanguage->GetValue("FRMSTATISTIC_TITLE");
    tsSummary->Caption = g_pLanguage->GetValue("FRMSTATISTIC_SUMMARY_TITLE");
    Label1->Caption = g_pLanguage->GetValue("FRMSTATISTIC_SUMMARY_TOTLE");
    //stTotal->Caption = g_pLanguage->GetValue("FRMSTATISTIC_SUMMARY_STTOTLE");
    Label2->Caption = g_pLanguage->GetValue("FRMSTATISTIC_SUMMARY_SAVAD");
    //stSaved->Caption = g_pLanguage->GetValue("FRMSTATISTIC_SUMMARY_STSAVED");
    Label3->Caption = g_pLanguage->GetValue("FRMSTATISTIC_SUMMARY_DROPED1");
    //stDropped->Caption = g_pLanguage->GetValue("FRMSTATISTIC_SUMMARY_DROPED2");
    tsDataLink->Caption = g_pLanguage->GetValue("FRMSTATISTIC_DL_TITLE");
    Label4->Caption = g_pLanguage->GetValue("FRMSTATISTIC_DL_TOTLE");
    //stFrameTotal->Caption = g_pLanguage->GetValue("FRMSTATISTIC_DL_STTOTLE");
    Label8->Caption = g_pLanguage->GetValue("FRMSTATISTIC_DL_IP");
    //stIp->Caption = g_pLanguage->GetValue("FRMSTATISTIC_DL_STIP");
    Label9->Caption = g_pLanguage->GetValue("FRMSTATISTIC_DL_ARP");
    stArp->Caption = g_pLanguage->GetValue("FRMSTATISTIC_DL_STARP");
    Label6->Caption = g_pLanguage->GetValue("FRMSTATISTIC_DL_RARP");
    //stRarp->Caption = g_pLanguage->GetValue("FRMSTATISTIC_DL_STRARP");
    Label5->Caption = g_pLanguage->GetValue("FRMSTATISTIC_DL_OTHERS");
    //stOthers->Caption = g_pLanguage->GetValue("FRMSTATISTIC_DL_STOTHERS");
    tsNetTran->Caption = g_pLanguage->GetValue("FRMSTATISTIC_NTL_TITLE");
    Label10->Caption = g_pLanguage->GetValue("FRMSTATISTIC_NTL_TOTLE");
    //stTotalNetTran->Caption = g_pLanguage->GetValue("FRMSTATISTIC_NTL_STTOTLE");
    Label13->Caption = g_pLanguage->GetValue("FRMSTATISTIC_NTL_TCP");
    //stTcp->Caption = g_pLanguage->GetValue("FRMSTATISTIC_NTL_STTCP");
    Label14->Caption = g_pLanguage->GetValue("FRMSTATISTIC_NTL_UDP");
    //stUdp->Caption = g_pLanguage->GetValue("FRMSTATISTIC_NTL_STUDP");
    Label11->Caption = g_pLanguage->GetValue("FRMSTATISTIC_NTL_ICMP");
    //stIcmp->Caption = g_pLanguage->GetValue("FRMSTATISTIC_NTL_STICMP");
    LabelIgmp->Caption = g_pLanguage->GetValue("FRMSTATISTIC_NTL_IGMP");
    //stIgmp->Caption = g_pLanguage->GetValue("FRMSTATISTIC_NTL_STIGMP");
    btnOk->Caption = g_pLanguage->GetValue("FRMSTATISTIC_BUTTEN_OK");
    btnRefresh->Caption = g_pLanguage->GetValue("FRMSTATISTIC_BUTTEN_REFRESH");

    if (g_SkinFile == "")
        ThemeManager->UIStyle = (TsuiUIStyle)g_nUiStyle;
    else
    {
        AnsiString szSkinFile = DIR_ROOT + DIR_SKINS + g_SkinFile + EXT_SKIN;
        ThemeManager->UIStyle = FromThemeFile;
        ThemeManager->FileTheme->ThemeFile = szSkinFile;
    } 

	Refresh();

}
//---------------------------------------------------------------------------
void __fastcall TfrmStatistic::btnOkClick(TObject *Sender)
{
	Close();
}
//---------------------------------------------------------------------------
void __fastcall TfrmStatistic::btnRefreshClick(TObject *Sender)
{
	Refresh();
}
//---------------------------------------------------------------------------

void TfrmStatistic::Refresh()
{
	//ThemeManager->UIStyle = (TsuiUIStyle)g_nUiStyle;
	stFrameTotal->Caption = g_nSaveCount;
	stTotal->Caption = g_nTotalCount;
	stSaved->Caption = g_nSaveCount;
	stDropped->Caption = g_nTotalCount - g_nSaveCount;
	if (g_nTotalCount != 0)
	{
		pbSave->Position = 100*g_nSaveCount/g_nTotalCount;
		pbDrop->Position = 100 - 100*g_nSaveCount/g_nTotalCount;

		pbArp->Position = g_nSaveCount ? 100 * g_nArpCount/g_nSaveCount : 0;
		pbRarp->Position = g_nSaveCount ? 100 * g_nRarpCount/g_nSaveCount : 0;
		pbIp->Position = g_nSaveCount ? 100 * g_nIpCount/g_nSaveCount : 0;
		pbOthers->Position = g_nSaveCount ? 100 * g_nOthersCount/g_nSaveCount : 0;
		stArp->Caption = g_nArpCount;
		stRarp->Caption = g_nRarpCount;
		stIp->Caption =  g_nIpCount;
		stOthers->Caption = g_nOthersCount;
	}
	else
	{
		pbSave->Position = 0;
		pbDrop->Position = 0;
		pbArp->Position = 0;
		pbRarp->Position = 0;
		pbIp->Position = 0;
		pbOthers->Position = 0;
		stArp->Caption = 0;
		stRarp->Caption = 0;
		stIp->Caption =  0;
		stOthers->Caption = 0;
	}
	if (g_nIpCount != 0)
	{
		stTotalNetTran->Caption = g_nIpCount;
		pbTcp->Position = 100 * g_nTcpCount/g_nIpCount ;
		pbUdp->Position = 100 * g_nUdpCount/g_nIpCount;
		pbIcmp->Position = 100 * g_nIcmpCount/g_nIpCount;
		pbIgmp->Position = 100 * g_nIgmpCount/g_nIpCount;
		stTcp->Caption = g_nTcpCount;
		stUdp->Caption = g_nUdpCount;
		stIcmp->Caption = g_nIcmpCount;
		stIgmp->Caption = g_nIgmpCount;
	}
	else
	{
		pbTcp->Position = 0;
		pbUdp->Position = 0;
		pbIcmp->Position = 0;
		pbIgmp->Position = 0;
		stTcp->Caption = 0;
		stUdp->Caption = 0;
		stIcmp->Caption = 0;
		stIgmp->Caption = 0;
		stTotalNetTran->Caption = 0;
	}
}
void __fastcall TfrmStatistic::TimerTimer(TObject *Sender)
{
	Refresh();	
}
//---------------------------------------------------------------------------

