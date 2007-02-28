// Author: zhengsh
// Date: 2005/10/03 01:30:35
// $Id: MainWin.cpp,v 1.54 2006/10/02 16:44:23 zhengsh Exp $

//---------------------------------------------------------------------------

#include <vcl.h>

#pragma hdrstop

#include "MainWin.h"
#include "AuthorWin.h"
//#include "shellapi.h"
#include "ArpPacket.h"
#include "Global.h"
#include "Constant.h"
#include "Language.h"
#include "Functions.h"
#include "CoverWin.h"
#include "Config.h"
#include "OptionsWin.h"
#include "IpDataGram.h"
#include "EtherDataGram.h"
#include "NicDetail.h"
#include "EtherList.h"
#include "IcmpPacket.h"
#include "TcpPacket.h"
#include "StatisticWin.h"
#include "StatusWin.h"
#include "UdpPacket.h"
#include "GotoWin.h"
#include "IpAddr.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "SUIForm"
#pragma link "SUIMainMenu"
#pragma link "SUIGrid"
#pragma link "SUIButton"
#pragma link "SUIPageControl"
#pragma link "SUITabControl"
#pragma link "SUIMgr"
#pragma link "SUIPopupMenu"
#pragma link "SUIToolBar"
#pragma link "SUIGroupBox"
#pragma link "SUIImagePanel"
#pragma link "SUIComboBox"
#pragma link "SUIListBox"
#pragma link "SUIDlg"
#pragma link "SUIEdit"
#pragma link "SUIScrollBar"
#pragma link "SUIMemo"
#pragma link "trayicon"
#pragma link "SUITrackBar"
#pragma link "SUIURLLabel"
#pragma link "SUITitleBar"
#pragma resource "*.dfm"

bool TfrmMain::ascOrDesc[10]={true,true,true,true,true,true,true,true,true};
TfrmMain *frmMain;
//---------------------------------------------------------------------------
__fastcall TfrmMain::TfrmMain(TComponent* Owner)
        : TForm(Owner)
{
    TMenuItem *NewItem;
    int cnt;
	bThreadIsRun = false;
	AnsiString szError;
    int niccount;
    m_pNicList = GetNicList(szError,niccount);
    if (m_pNicList != 0 )
    {
        cnt = 0;
        pcap_if_t * d = m_pNicList;
        //m_pNicList
        while ( d!=0 )
        {
            NewItem = new TMenuItem(MainMenu);
            NewItem->Tag = ++cnt;
            NewItem->Caption = StringFormat(d->description);
            NewItem->OnClick = miNicListClick;
			miNicList->Add(NewItem);
            //Items[0]->Add(NewItem);
            cbNicList->Items->Add(StringFormat(d->description));
            d = d->next;
        }                //miNicList->Items[
        if ( cnt == 1 )
        {//have one nic only, select it automaticly
            cbNicList->ItemIndex = 0;
            cbNicList->Text = cbNicList->Items->Strings[0];
            btnNicDetail->Enabled = true;
            btnStartPause->Enabled = true;
        }
   }
    else if ( niccount == 0)
    {
    }
    else
		ShowMsg(szError,"",MSG_ERROR);

    //Skin List
    for (cnt=0; cnt<g_SkinList->Count; cnt++)
    {
        TMenuItem *tmp = new TMenuItem(MainMenu);
        NewItem = new TMenuItem(MainMenu);
        NewItem->Tag = cnt;
        tmp->Caption = g_SkinList->Strings[cnt];
        NewItem->Caption = g_SkinList->Strings[cnt];
        tmp->OnClick = ChangeUIStyle;
        NewItem->OnClick = ChangeUIStyle;
        //ShowMsg(cnt);
		miStyle->Add(NewItem);
        miMainStyle->Add(tmp);
    }
    //Language list
    for (cnt=0; cnt<g_LangList->Count; cnt++)
    {
        TMenuItem *tmp = new TMenuItem(MainMenu);
        NewItem = new TMenuItem(MainMenu);
        NewItem->Tag = cnt;
        tmp->Caption = g_LangList->Strings[cnt];
        NewItem->Caption = g_LangList->Strings[cnt];
        tmp->OnClick = ChangeLanguage;
        NewItem->OnClick = ChangeLanguage;
        //ShowMsg(cnt);
		miLanguage->Add(NewItem);
        miLang->Add(tmp);
    }

    //->Add(sr.Name);
	//miLanguage = miLang;

    nRecordCount = 0;
    RecvThread = new TRecvThread;
    HidePanel();
    frmStatus = new TfrmStatus(Application);
    if (gOption_Display_Status)
        frmStatus->Show();
    TrayIcon->IconIndex =0;
    bCancelSave = false;
   // havestarted = false;
   //miMainWin->ShowHint = true;

    if (gOption_Auto_Sniffer)
    {
        if (gOption_Auto_NIC_Index >= 0 && gOption_Auto_NIC_Index < cbNicList->Items->Count)
        {
            cbNicList->ItemIndex = gOption_Auto_NIC_Index;
            cbNicList->Text = cbNicList->Items->Strings[cbNicList->ItemIndex];
            bThreadIsRun = true;
            btnStartPauseClick(Application);
            g_szFile_Save = gOption_File_Auto_Save;
        }
    }

    Refresh();
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::ShowNicDetail(TObject *Sender)
{
    static int i = 0;
    i++;

    pcap_if_t * d =  m_pNicList;
    int cnt = 1;
    TMenuItem *pMenu = (TMenuItem*)Sender;

    if (pMenu->Tag == 0)
        return;
    while ( d!=0 )
    {
        if (cnt == pMenu->Tag)
            break;
        d = d->next;
        cnt++;
    }
    if (d == 0)
        return;

    TfrmNicDetail *frm = new TfrmNicDetail(Application);
    frm->SetNic(d);
    frm->ShowModal();
    delete frm;
    //ShowMsg(pMenu->Tag);

}

void __fastcall TfrmMain::WinXp1Click(TObject *Sender)
{
    SetUiStyle(WinXP);
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::Protein1Click(TObject *Sender)
{
    SetUiStyle(Protein);
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::BlueGlass1Click(TObject *Sender)
{
    SetUiStyle(BlueGlass);
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::DeepBlue1Click(TObject *Sender)
{
     SetUiStyle(DeepBlue);
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::MacOS1Click(TObject *Sender)
{
	SetUiStyle((int)MacOS);
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::cbNicListDropDown(TObject *Sender)
{
    btnNicDetail->Enabled = true;
    btnStartPause->Enabled = true;
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::btnNicDetailClick(TObject *Sender)
{
    //ShowMsg(cbNicList->SelText);
    AnsiString szNicInfo;
    pcap_if_t *d = GetSelectedNic();

    //pcap_addr * addr = d->addresses;


    if (d == 0)
    {
        ShowMsg(g_pLanguage->GetValue("ERROR_SELECT_ONE_NIC"),"",MSG_WARNING);
        return;
    }
    TfrmNicDetail *frm = new TfrmNicDetail(Application);
    frm->SetNic(d);
    frm->ShowModal();
    delete frm;
}
//---------------------------------------------------------------------------



pcap_if_t* TfrmMain::GetSelectedNic()
{
    if (cbNicList->ItemIndex == -1)
        return 0;
    pcap_if_t *d = m_pNicList;
	for(int i=0;d;d=d->next,i++)
	{
        //if (cbNicList->Text == d->description)
        if (cbNicList->ItemIndex == i)
            break;
	}
    return d;
}


void TfrmMain::Refresh()
{
    if (cbNicList->ItemIndex < 0)
        cbNicList->Text = g_pLanguage->GetValue("TEXT_NIC_SELECT_ONE");
    sgDataList->Cells[0][0] =  g_pLanguage->GetValue("TEXT_MAINWIN_DATALIST_NUMBER");
    sgDataList->Cells[1][0] =  g_pLanguage->GetValue("TEXT_MAINWIN_DATALIST_SOURCE_HOST");
    sgDataList->Cells[2][0] =  g_pLanguage->GetValue("TEXT_MAINWIN_DATALIST_DESTINE_HOST");
    sgDataList->Cells[3][0] =  g_pLanguage->GetValue("TEXT_MAINWIN_DATALIST_SOURCE_MAC");
    sgDataList->Cells[4][0] =  g_pLanguage->GetValue("TEXT_MAINWIN_DATALIST_DESTINE_MAC");
    sgDataList->Cells[5][0] =  g_pLanguage->GetValue("TEXT_MAINWIN_DATALIST_SIZE");
    sgDataList->Cells[6][0] =  g_pLanguage->GetValue("TEXT_MAINWIN_DATALIST_TTL");
    sgDataList->Cells[7][0] =  g_pLanguage->GetValue("TEXT_MAINWIN_DATALIST_IP_PROTOCOL");
    sgDataList->Cells[8][0] =  g_pLanguage->GetValue("TEXT_MAINWIN_DATALIST_TIMESTAMP");
    sgDataList->ColWidths[0] = 40;
    sgDataList->ColWidths[1] = 150;
    sgDataList->ColWidths[2] = 150;
    sgDataList->ColWidths[5] = 80;
    sgDataList->ColWidths[6] = 80;
    sgDataList->ColWidths[7] = 100;
    sgDataList->ColWidths[8] = 120;
    frmMain->Caption =  g_pLanguage->GetValue("FRMMAIN_MAINBOARD_NAME");
    Label1->Caption =   g_pLanguage->GetValue("FRMMAIN_NET_WORKCARD");
    //btnStartPause->Caption = g_pLanguage->GetValue("FRMMAIN_BUTTEN_START");
    tsEtherHeader->Caption = g_pLanguage->GetValue("FRMMAIN_ETHERNET_HEADER_TITLE");
    lblSrcMac->Caption = g_pLanguage->GetValue("FRMMAIN_ETHERNET_HEADER_SRCMAC");
    lblType->Caption = g_pLanguage->GetValue("FRMMAIN_ETHERNET_HEADER_TYPE");
    lblActLen->Caption = g_pLanguage->GetValue("FRMMAIN_ETHERNET_HEADER_ACT_LEN");
    lblDestMac->Caption = g_pLanguage->GetValue("FRMMAIN_ETHERNET_HEADER_DESTMAC");
    lblTimeStamp->Caption = g_pLanguage->GetValue("FRMMAIN_ETHERNET_HEADER_TIMESTAMP");
    lblCapLen->Caption = g_pLanguage->GetValue("FRMMAIN_ETHERNET_HEADER_CAP_LEN");
    tsIpHeader->Caption = g_pLanguage->GetValue("FRMMAIN_IP_HEADER_TITLE");
    lblVersion->Caption = g_pLanguage->GetValue("FRMMAIN_IP_HEADER_VERSION");
    lblTotalLength->Caption = g_pLanguage->GetValue("FRMMAIN_IP_HEADER_TOTAL_LEN");
    lblFragOffset->Caption = g_pLanguage->GetValue("FRMMAIN_IP_HEADER_FRAG_OFFSET");
    lblIhl->Caption = g_pLanguage->GetValue("FRMMAIN_IP_HEADER_IHL");
    lblId->Caption = g_pLanguage->GetValue("FRMMAIN_IP_HEADER_ID");
    lblTimeToLive->Caption = g_pLanguage->GetValue("FRMMAIN_IP_HEADER_TIME_TO_LIVE");
    lblTos->Caption = g_pLanguage->GetValue("FRMMAIN_IP_HEADER_TOS");
    lblFlags->Caption = g_pLanguage->GetValue("FRMMAIN_IP_HEADER_FLAGS");
    lblProtocol->Caption = g_pLanguage->GetValue("FRMMAIN_IP_HEADER_PROTOCOL");
    lblHeaderCrc->Caption = g_pLanguage->GetValue("FRMMAIN_IP_HEADER_CRC");
    lblSrcAddr->Caption = g_pLanguage->GetValue("FRMMAIN_IP_HEADER_SRCADDR");
    lblDestAddr->Caption = g_pLanguage->GetValue("FRMMAIN_IP_HEADER_DESTADDR");
    tsTcp->Caption = g_pLanguage->GetValue("FRMMAIN_TCP_HEADER_TITLE");
    lblTcpSrcPort->Caption = g_pLanguage->GetValue("FRMMAIN_TCP_HEADER_SRCPORT");
    lblTcpWinSize->Caption = g_pLanguage->GetValue("FRMMAIN_TCP_HEADER_WINSIZE");
    lblAckSeq->Caption = g_pLanguage->GetValue("FRMMAIN_TCP_HEADER_ACKSEQ");
    lblTcpDestPort->Caption = g_pLanguage->GetValue("FRMMAIN_TCP_HEADER_DESTPORT");
    lblTcpSeqNum->Caption = g_pLanguage->GetValue("FRMMAIN_TCP_HEADER_SEQNUM");
    lblTcpProtoName->Caption = g_pLanguage->GetValue("FRMMAIN_TCP_HEADER_PROL_NAME");
    tsUdp->Caption = g_pLanguage->GetValue("FRMMAIN_UDP_HEADER_TITLE");
    lblUdpSrcPort->Caption = g_pLanguage->GetValue("FRMMAIN_UDP_HEADER_SRCPORT");
    lblUdpLength->Caption = g_pLanguage->GetValue("FRMMAIN_UDP_HEADER_LEN");
    lblUdpProtoName->Caption = g_pLanguage->GetValue("FRMMAIN_UDP_HEADER_PROL_NAME");
    lblUdpDestPort->Caption = g_pLanguage->GetValue("FRMMAIN_UDP_HEADER_DESTPORT");
    lblUdpCrc->Caption = g_pLanguage->GetValue("FRMMAIN_UDP_HEADER_CRC");
    tsData->Caption = g_pLanguage->GetValue("FRMMAIN_DATA_TITLE");
    lblBinary->Caption = g_pLanguage->GetValue("FRMMAIN_DATA_BINARY");
    Label2->Caption = g_pLanguage->GetValue("FRMMAIN_DATA_TEXT");
    tsArpHeader->Caption = g_pLanguage->GetValue("FRMMAIN_ARP_RARP_TITLE");
    lblProtocolType->Caption = g_pLanguage->GetValue("FRMMAIN_ARP_RARP_PROL_TYPE");
    lblArpSrcAddr->Caption = g_pLanguage->GetValue("FRMMAIN_ARP_RARP_SRCADDR");
    Label7->Caption = g_pLanguage->GetValue("FRMMAIN_ARP_RARP_DESTADDR");
    lblArpSrcMac->Caption = g_pLanguage->GetValue("FRMMAIN_ARP_RARP_SRCMAC");
    lblArpDestMac->Caption = g_pLanguage->GetValue("FRMMAIN_ARP_RARP_DESTMAC");
    tsIcmp->Caption = g_pLanguage->GetValue("FRMMAIN_ICMP_TITLE");
    lblIcmpType->Caption = g_pLanguage->GetValue("FRMMAIN_ICMP_TYPE");
    lblIcmpCode->Caption = g_pLanguage->GetValue("FRMMAIN_ICMP_CODE");
    lblIcmpCrc->Caption = g_pLanguage->GetValue("FRMMAIN_ICMP_CRC");
    lblIcmpDesc->Caption = g_pLanguage->GetValue("FRMMAIN_ICMP_DESC");
    miClose->Caption = g_pLanguage->GetValue("FRMMAIN_MAINMENU_FILE_CLOSE");
    miAuthor->Caption = g_pLanguage->GetValue("FRMMAIN_MAINMENU_HELP_DEVELOPER");

    miMainWin->Caption = g_pLanguage->GetValue("FRMMAIN_POPUPMENU_MAINWIN");
    miStatusWindow1->Caption = g_pLanguage->GetValue("FRMMAIN_POPUPMENU_STATUS_WIN");
    miDetailPanel1->Caption = g_pLanguage->GetValue("FRMMAIN_POPUPMENU_DETAIL_PANEL");
    miStyle->Caption = g_pLanguage->GetValue("FRMMAIN_POPUPMENU_STYLE");
    WinXp1->Caption = g_pLanguage->GetValue("FRMMAIN_POPUPMENU_STYLE_WINXP1");
    MacOS1->Caption = g_pLanguage->GetValue("FRMMAIN_POPUPMENU_STYLE_MACOS1");
    Protein1->Caption = g_pLanguage->GetValue("FRMMAIN_POPUPMENU_STYLE_PROTEIN1");
    DeepBlue1->Caption = g_pLanguage->GetValue("FRMMAIN_POPUPMENU_STYLE_DEEPBLUE1");
    BlueGlass1->Caption = g_pLanguage->GetValue("FRMMAIN_POPUPMENU_STYLE_BLUEGLASS1");
    miLang->Caption = g_pLanguage->GetValue("FRMMAIN_POPUPMENU_LANGUAGE");
    miChinese->Caption = g_pLanguage->GetValue("FRMMAIN_POPUPMENU_LANGUAGE_CH");
    miEnglish->Caption = g_pLanguage->GetValue("FRMMAIN_POPUPMENU_LANGUAGE_EN");
    miStart->Caption = g_pLanguage->GetValue("FRMMAIN_POPUPMENU_START");
    miExit1->Caption = g_pLanguage->GetValue("FRMMAIN_POPUPMENU_EXIT");
    
    miFile->Caption = g_pLanguage->GetValue("FRMMAIN_MAINMENU_FILE");
    miOpen->Caption = g_pLanguage->GetValue("FRMMAIN_MAINMENU_FILE_OPEN_FILE");
    OpenText1->Caption = g_pLanguage->GetValue("FRMMAIN_MAINMENU_FILE_OPEN_TEXT");
    Reopen1->Caption = g_pLanguage->GetValue("FRMMAIN_MAINMENU_FILE_REOPEN");
    Save1->Caption = g_pLanguage->GetValue("FRMMAIN_MAINMENU_FILE_SAVE");
    SaveAs1->Caption = g_pLanguage->GetValue("FRMMAIN_MAINMENU_FILE_SAVEAS1");
    SaveAsText1->Caption = g_pLanguage->GetValue("FRMMAIN_MAINMENU_FILE_SAVEASTEXT");
    miExit->Caption = g_pLanguage->GetValue("FRMMAIN_MAINMENU_FILE_EXIT");
    miEdit->Caption = g_pLanguage->GetValue("FRMMAIN_MAINMENU_EDIT");
    Find1->Caption = g_pLanguage->GetValue("FRMMAIN_MAINMENU_EDIT_FIND");
    miClearAll->Caption = g_pLanguage->GetValue("FRMMAIN_MAINMENU_EDIT_CLEARALL");
    //miSavetoCache->Caption = g_pLanguage->GetValue("FRMMAIN_MAINMENU_EDIT_SAVETOCACHE");
    miGoTo->Caption = g_pLanguage->GetValue("FRMMAIN_MAINMENU_EDIT_GOTO");
    miGoToTop->Caption = g_pLanguage->GetValue("FRMMAIN_MAINMENU_EDIT_GOTOTOP");
    miGoToBottom->Caption = g_pLanguage->GetValue("FRMMAIN_MAINMENU_EDIT_GOTOBOTTOM");
    FirstPage1->Caption = g_pLanguage->GetValue("FRMMAIN_MAINMENU_EDIT_FIRSTPAGE");
    Prevous1->Caption = g_pLanguage->GetValue("FRMMAIN_MAINMENU_EDIT_PREVIOUSPAGE");
    NextPage1->Caption = g_pLanguage->GetValue("FRMMAIN_MAINMENU_EDIT_NEXTPAGE");
    LastPage1->Caption = g_pLanguage->GetValue("FRMMAIN_MAINMENU_EDIT_LASTPAGE");
    btnFirst->Caption = g_pLanguage->GetValue("FRMMAIN_MAINMENU_EDIT_FIRSTPAGE");
    btnPrevious->Caption = g_pLanguage->GetValue("FRMMAIN_MAINMENU_EDIT_PREVIOUSPAGE");
    btnNext->Caption = g_pLanguage->GetValue("FRMMAIN_MAINMENU_EDIT_NEXTPAGE");
    btnLast->Caption = g_pLanguage->GetValue("FRMMAIN_MAINMENU_EDIT_LASTPAGE");

    miClearAllPacket->Caption =  g_pLanguage->GetValue("FRMMAIN_MAINMENU_EDIT_CLEARALL");
    miView->Caption = g_pLanguage->GetValue("FRMMAIN_MAINMENU_VIEW");
    miStat->Caption = g_pLanguage->GetValue("FRMMAIN_MAINMENU_VIEW_SATATISTIC");
    miNicList->Caption = g_pLanguage->GetValue("FRMMAIN_MAINMENU_VIEW_NEWWORKCARDS");
    miOptions->Caption = g_pLanguage->GetValue("FRMMAIN_MAINMENU_VIEW_OPTIONS");
    miInterface->Caption = g_pLanguage->GetValue("FRMMAIN_MAINMENU_INTERFACE");
    miMainStyle->Caption = g_pLanguage->GetValue("FRMMAIN_MAINMENU_INTERFACE_STYLE");
    miWinXp->Caption = g_pLanguage->GetValue("FRMMAIN_MAINMENU_INTERFACE_STYLE_WINXP1");
    miMacOS->Caption = g_pLanguage->GetValue("FRMMAIN_MAINMENU_INTERFACE_STYLE_MACOS1");
    miProtein->Caption = g_pLanguage->GetValue("FRMMAIN_MAINMENU_INTERFACE_STYLE_PROTEIN1");
    miDeepBlue->Caption = g_pLanguage->GetValue("FRMMAIN_MAINMENU_INTERFACE_STYLE_DEEPBLUE1");
    miBlueGlass->Caption = g_pLanguage->GetValue("FRMMAIN_MAINMENU_INTERFACE_STYLE_BLUEGLASS1");
    miLanguage->Caption = g_pLanguage->GetValue("FRMMAIN_MAINMENU_INTERFACE_LANGUAGE");
    Chinese1->Caption = g_pLanguage->GetValue("FRMMAIN_MAINMENU_INTERFACE_LANGUAGE_CH");
    English1->Caption = g_pLanguage->GetValue("FRMMAIN_MAINMENU_INTERFACE_LANGUAGE_EN");
    miMainWindow->Caption = g_pLanguage->GetValue("FRMMAIN_MAINMENU_INTERFACE_MAINWIN");
    miDetailPanel->Caption = g_pLanguage->GetValue("FRMMAIN_MAINMENU_INTERFACE_DETAILPANEL");
    miStatusWindow->Caption = g_pLanguage->GetValue("FRMMAIN_MAINMENU_INTERFACE_STATUSWIN");
    miHelp->Caption = g_pLanguage->GetValue("FRMMAIN_MAINMENU_HELP");
    miAbout->Caption = g_pLanguage->GetValue("FRMMAIN_MAINMENU_HELP_ABOUT");
    frmMain->Caption = g_pLanguage->GetValue("TEXT_SOFTWARE_NAME");
    miSniHelp->Caption = g_pLanguage->GetValue("FRMMAIN_MAINMENU_HELP_SNIFFERFOX");
    miFeedBack->Caption = g_pLanguage->GetValue("FRMMAIN_MAINMENU_HELP_FEEDBACK");
    miTurtorial->Caption = g_pLanguage->GetValue("FRMMAIN_MAINMENU_HELP_TURTORIAL");
    miGetSource->Caption = g_pLanguage->GetValue("FRMMAIN_MAINMENU_HELP_GET_SOURCE");
    btnNicDetail->Hint = g_pLanguage->GetValue("FRMMAIN_HINT_NIC_LIST");
    btnStartPause->Hint = g_pLanguage->GetValue("FRMMAIN_HINT_START_PAUSE");

    miSortBy->Caption = g_pLanguage->GetValue("FRMMAIN_MAINMENU_EDIT_SORT_BY");
    miSortById->Caption = g_pLanguage->GetValue("FRMMAIN_MAINMENU_EDIT_SORT_BY_ID");
    miSrcHost->Caption = g_pLanguage->GetValue("FRMMAIN_MAINMENU_EDIT_SORT_BY_SRC_HOST");
    miDestHost->Caption = g_pLanguage->GetValue("FRMMAIN_MAINMENU_EDIT_SORT_BY_DST_HOST");
    miSrcMac->Caption = g_pLanguage->GetValue("FRMMAIN_MAINMENU_EDIT_SORT_BY_Src_MAC");
    miDestMac->Caption = g_pLanguage->GetValue("FRMMAIN_MAINMENU_EDIT_SORT_BY_DST_MAC");
    miSortBySize->Caption = g_pLanguage->GetValue("FRMMAIN_MAINMENU_EDIT_SORT_BY_SIZE");
    miSortByTTL->Caption = g_pLanguage->GetValue("FRMMAIN_MAINMENU_EDIT_SORT_BY_TTL");
    miProtocol->Caption = g_pLanguage->GetValue("FRMMAIN_MAINMENU_EDIT_SORT_BY_PROTOCOL");
    miTimestamp->Caption = g_pLanguage->GetValue("FRMMAIN_MAINMENU_EDIT_SORT_BY_TIMESTAMP");

    if (g_bThreadIsRun)
        btnStartPause->Caption = g_pLanguage->GetValue("LEBAL_MAINWIN_PAUSE");
    else
        btnStartPause->Caption = g_pLanguage->GetValue("LEBAL_MAINWIN_START");
    if (g_SkinFile == "")
        ThemeManager->UIStyle = (TsuiUIStyle)g_nUiStyle;
    else
    {
        AnsiString szSkinFile = DIR_ROOT + DIR_SKINS + g_SkinFile + EXT_SKIN;
        ThemeManager->UIStyle = FromThemeFile;
        ThemeManager->FileTheme->ThemeFile = szSkinFile;
    }
    int cnt;
    AnsiString szLangFile = g_pLanguage->GetCurLang();

    //update language menu
    for (cnt=0; cnt<miLang->Count; cnt++)
    {
        if ( CharFilter(miLang->Items[cnt]->Caption,'&') == szLangFile)
        {
            miLang->Items[cnt]->Checked = true;
            //ShowMsg(szLangFile);
        }
        else
            miLang->Items[cnt]->Checked = false;
        if (CharFilter(miLanguage->Items[cnt]->Caption,'&') == szLangFile)
            miLanguage->Items[cnt]->Checked = true;
        else
            miLanguage->Items[cnt]->Checked = false;
    }
}

void __fastcall TfrmMain::miChineseClick(TObject *Sender)
{
    if (g_pLanguage->GetCurLang() != "Chinese")
    {
        g_pLanguage->LoadLanguage("Chinese");
        //Visible = false;
	    Refresh();
        //Visible = true;
    }
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::miEnglishClick(TObject *Sender)
{

    if (g_pLanguage->GetCurLang() != "English")
    {
        g_pLanguage->LoadLanguage("English");
        //Visible = false;
        Refresh();
        //Visible = true;
    }
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::suiButton1Click(TObject *Sender)
{
    Refresh();
}
//---------------------------------------------------------------------------
  //

void __fastcall TfrmMain::btnStartPauseClick(TObject *Sender)
{
	//static is_running = false;
	if (g_bThreadIsRun)
	{
        RecvThread->Suspend();
		g_bThreadIsRun = false;
        btnStartPause->Caption = g_pLanguage->GetValue("LEBAL_MAINWIN_START");
        //cbNicList->Enabled = true;
		//bThreadIsRun = false;
        TrayIcon->Animate = false;
        TrayIcon->IconIndex =0;
		return;
    }
    if (g_szFile_Open != "")
        CloseFile(0);

    AnsiString szError;
    pcap_if_t * temp = GetSelectedNic();
    if (temp == 0)
    {
        ShowMsg(g_pLanguage->GetValue("ERROR_SELECT_ONE_NIC"),"",MSG_WARNING);
        return;
    }
    else
    {
        btnStartPause->Enabled = true;
        btnNicDetail->Enabled = true;
    }
	//ShowMsg(cbNicList->Text);
	if (RecvThread->IsInitialized() == false)
		if (!RecvThread->Initialize(temp,szError))
		{
			ShowMsg(szError,"",MSG_ERROR);
			return;
		}
	RecvThread->Resume();
	g_bThreadIsRun = true;
	btnStartPause->Caption = g_pLanguage->GetValue("LEBAL_MAINWIN_PAUSE");
    cbNicList->Enabled = false;
    TrayIcon->Animate = true;

	//bThreadIsRun = true;
}
//---------------------------------------------------------------------------


void __fastcall TfrmMain::miOptionsClick(TObject *Sender)
{
    TfrmOptions *frmOptions = new TfrmOptions(Application);
    frmOptions->ShowModal();
    delete  frmOptions;
}
//---------------------------------------------------------------------------


bool TfrmMain::protocolAllow(const struct pcap_pkthdr *header, const u_char *pkt_data)
{
	bool flag = true;
	TEtherDataGram Ether;
	Ether.SetBuffer(header,pkt_data);
    int SrcPort,DstPort,cnt;

	AnsiString szType;
	try{
		szType = Ether.GetTypeName();
	}
	catch(...)
	{
		ShowMsg("getTypeName()");
	}
	if (szType == "IP")
	{
		if (!gOption_Filter_Ip)
			flag = false;
		TIpDataGram Ip = Ether;
		TTcpPacket TcpPacket;
		TUdpPacket UdpPacket;
		AnsiString szProto;
		switch (Ip.GetProtocolValue())
		{
			case IPPROTO_ICMP:
				if (!gOption_Filter_Icmp)
					flag = false;
				break;
			case IPPROTO_IGMP:
				if (!gOption_Filter_Igmp)
					flag = false;
				break;
			case IPPROTO_TCP:
				if (!gOption_Filter_Tcp)
				{
                	flag = false;
                    break;
                }
				TcpPacket.SetBuffer(Ip.GetDataHeader(),Ip.GetDataSize());
				szProto = TcpPacket.GetAppProtocolName();

                SrcPort = TcpPacket.GetSrcPort().ToInt();
                DstPort = TcpPacket.GetDesPort().ToInt();

                for (cnt=1; cnt<=g_pSpecify_Ports[0]; cnt++)
                {
                    if (DstPort == g_pSpecify_Ports[cnt] || SrcPort == g_pSpecify_Ports[cnt])
                    {
                        return true;
                    }
                }

				if (szProto == "FTP")
					flag = gOption_Filter_Ftp;
				else if (szProto == "SSH")
					flag = gOption_Filter_Ssh;
				else if (szProto == "TELNET")
					flag = gOption_Filter_Telnet;
				else if (szProto == "SMTP")
					flag = gOption_Filter_Smtp;
				else if (szProto == "DOMAIN")
					flag = gOption_Filter_Dns;
				else if (szProto == "GOPHER")
					flag = gOption_Filter_Gopher;
				else if (szProto == "HTTP")
					flag = gOption_Filter_Http;
				else if (szProto == "POP#")
					flag = gOption_Filter_Pop3;
				else if (szProto == "FINGER")
					flag = gOption_Filter_Finger;
				else if (szProto == "LDAP")
					flag = gOption_Filter_Ldap;
				else if (szProto == "TFTP")
					flag = gOption_Filter_Tftp;
				else
					flag = gOption_Filter_AppOthers;
				break;
			case IPPROTO_UDP:
				if (!gOption_Filter_Udp)
				{
                	flag = false;
                    break;
                }
				UdpPacket.SetBuffer(Ip.GetDataHeader(),Ip.GetDataSize());
				szProto = UdpPacket.GetAppProtocolName();

                SrcPort = UdpPacket.GetSrcPort().ToInt();
                DstPort = UdpPacket.GetDesPort().ToInt();

                for (cnt=1; cnt<=g_pSpecify_Ports[0]; cnt++)
                {
                    if (DstPort == g_pSpecify_Ports[cnt] || SrcPort == g_pSpecify_Ports[cnt])
                    {
                        return true;
                    }
                }

				if (szProto == "FTP")
					flag = gOption_Filter_Ftp;
				else if (szProto == "SSH")
					flag = gOption_Filter_Ssh;
				else if (szProto == "TELNET")
					flag = gOption_Filter_Telnet;
				else if (szProto == "SMTP")
					flag = gOption_Filter_Smtp;
				else if (szProto == "DOMAIN")
					flag = gOption_Filter_Dns;
				else if (szProto == "GOPHER")
					flag = gOption_Filter_Gopher;
				else if (szProto == "HTTP")
					flag = gOption_Filter_Http;
				else if (szProto == "POP#")
					flag = gOption_Filter_Pop3;
				else if (szProto == "FINGER")
					flag = gOption_Filter_Finger;
				else if (szProto == "LDAP")
					flag = gOption_Filter_Ldap;
				else if (szProto == "TFTP")
					flag = gOption_Filter_Tftp;
				else
					flag = gOption_Filter_AppOthers;
	            //if (szProto == "OICQ")
                    //flag = true;
				break;
		}
	}
	else if (szType == "ARP")
	{
		if (!gOption_Filter_Arp)
			 flag = false;
	}
	else if (szType == "RARP")
	{
		if (!gOption_Filter_Rarp)
			flag = false;
	}
	else //other such as ieee802.3
	{
		if (!gOption_Filter_Others)
			flag = false;
	}
	return flag;
}

bool TfrmMain::sourceAllow(const struct pcap_pkthdr *header, const u_char *pkt_data)
{
	bool flag = true;
	TIpDataGram IpHeader;
    TEtherDataGram Ether;
	Ether.SetBuffer(header,pkt_data);
	IpHeader.SetBuffer(Ether.GetDataHeader(),Ether.GetDataSize());
    AnsiString szSrcIp;

  try{
		szSrcIp = IpHeader.GetSrcAddr();
	}
	catch(...)
	{
		ShowMsg("GetSrcAddr()");
	}

    if(gOption_Filter_Source_Type == OPTION_SOURCE_ALL)
    {
       flag = true;
    }else if(gOption_Filter_Source_Type == OPTION_SOURCE_ONLY)
    {
        if(szSrcIp == gOption_Filter_Source_Only_Ip)
            flag = true;
        else
            flag = false;
    }else if(gOption_Filter_Source_Type == OPTION_SOURCE_SEGMENT)
    {
        if((szSrcIp<gOption_Filter_Source_From_Ip) || (szSrcIp>gOption_Filter_Source_To_Ip))
            flag = false;
        else
            flag = true;
    }else
        flag = false;

	return flag;

}

bool TfrmMain::destineAllow(const struct pcap_pkthdr *header, const u_char *pkt_data)
{
	bool flag = true;
    TIpDataGram IpHeader;
    TEtherDataGram Ether;
	Ether.SetBuffer(header,pkt_data);
	IpHeader.SetBuffer(Ether.GetDataHeader(),Ether.GetDataSize());
    AnsiString szDestIp;
    
    try{
        szDestIp = IpHeader.GetDestAddr();
	}
	catch(...)
	{
		ShowMsg("GetSrcAddr()");
	}

    if(gOption_Filter_Destine_Type == OPTION_DESTINE_ALL)
    {
       flag = true;
    }else if(gOption_Filter_Destine_Type == OPTION_DESTINE_ONLY)
    {
        if(szDestIp == gOption_Filter_Destine_Only_Ip)
            flag = true;
        else
            flag = false;
    }else if(gOption_Filter_Destine_Type == OPTION_DESTINE_SEGMENT)
    {
        if((szDestIp<gOption_Filter_Destine_From_Ip) || (szDestIp>gOption_Filter_Destine_To_Ip))
            flag = false;
        else
            flag = true;
    }else
        flag = false;

	return flag;
}



bool TfrmMain::DataProcess(const struct pcap_pkthdr *header, const u_char *pkt_data,int id)
//
{   //drop it, if we don't need it
    if (sgDataList->FixedRows == 0 && sgDataList->RowCount > 1)
        sgDataList->FixedRows = 1;

	if (header == NULL || pkt_data == 0)
		return false;
	//g_nTotalCount++;
	TEtherDataGram EtherDataGram;
	if (!protocolAllow(header,pkt_data))
		return false;
	if (!destineAllow(header,pkt_data))
		return false;
	if (!sourceAllow(header,pkt_data))
		return false;

	g_nNextId++;
	EtherDataGram.SetId(g_nNextId);
	AnsiString SrcMac,DestMac,TimeStamp,SrcAddr,DestAddr,Protocol;
	int  nActLen, nTtl = 0;
	EtherDataGram.SetBuffer(header,pkt_data);
	SrcMac = EtherDataGram.GetSrcMac();
	DestMac = EtherDataGram.GetDestMac();
	nActLen = EtherDataGram.GetActLen();
	//nCapLen = EtherDataGram.GetCapLen();
	Protocol = EtherDataGram.GetTypeName();
	TimeStamp = EtherDataGram.GetTimeStamp();
	//ip packet
	if (EtherDataGram.GetTypeName() == "IP")
	{
		g_nIpCount++;
		TIpDataGram IpDataGram;
		IpDataGram.SetBuffer(EtherDataGram.GetDataHeader(),EtherDataGram.GetDataSize());
		//if (!protocolAllow(IpDataGram.GetProtocolValue()))
			//return;
		//if (IpDataGram.GetProtocolValue() != IPPROTO_ICMP)
		//    return;
		int protocol = IpDataGram.GetProtocolValue();

		nTtl = IpDataGram.GetTimeToLive();
		SrcAddr = IpDataGram.GetSrcAddr();
		DestAddr = IpDataGram.GetDestAddr();
		Protocol = IpDataGram.GetProtocol();

		TUdpPacket UdpPacket;
		TTcpPacket TcpPacket;
        AnsiString szTmp;
		switch(protocol)
		{
			case IPPROTO_ICMP:
				g_nIcmpCount ++;
				break;
			case IPPROTO_UDP:
			    UdpPacket.SetBuffer(IpDataGram.GetDataHeader(),IpDataGram.GetDataSize());
                //g_pLanguage->GetValue("PROTOCOL_APPLICATION_UNKNOWN")
                szTmp = UdpPacket.GetAppProtocolName();
                if (szTmp != g_pLanguage->GetValue("PROTOCOL_APPLICATION_UNKNOWN"))
			        Protocol += AnsiString("/") + szTmp;
				g_nUdpCount++;
				break;
			case IPPROTO_TCP:
	    		TcpPacket.SetBuffer(IpDataGram.GetDataHeader(),IpDataGram.GetDataSize());
                szTmp = TcpPacket.GetAppProtocolName();
                if (szTmp != g_pLanguage->GetValue("PROTOCOL_APPLICATION_UNKNOWN"))
                    Protocol += AnsiString("/")+szTmp;
				g_nTcpCount++;
				break;
			case IPPROTO_IGMP:
				g_nIgmpCount++;
				break;
		}
	}
	else if (EtherDataGram.GetTypeName() == "ARP")
	{
		g_nArpCount++;
		TArpPacket ArpPacket;
		ArpPacket.SetBuffer(EtherDataGram.GetDataHeader(),EtherDataGram.GetDataSize());
		SrcAddr = ArpPacket.GetSrcAddr();
		DestAddr = ArpPacket.GetDestAddr();
	}
	else if (EtherDataGram.GetTypeName() == "RARP")
	{
		g_nRarpCount++;
		TArpPacket ArpPacket;
		ArpPacket.SetBuffer(EtherDataGram.GetDataHeader(),EtherDataGram.GetDataSize());
		SrcAddr = ArpPacket.GetSrcAddr();
		DestAddr = ArpPacket.GetDestAddr();
	}
	else
	{
		g_nOthersCount++;
	}

	if (sgDataList->RowCount <= nRecordCount + 1)
		 sgDataList->RowCount++;
	nRecordCount++;

	sgDataList->Cells[0][nRecordCount] = g_nNextId;
	sgDataList->Cells[1][nRecordCount] = SrcAddr;
	sgDataList->Cells[2][nRecordCount] = DestAddr;
	sgDataList->Cells[3][nRecordCount] = SrcMac;
	sgDataList->Cells[4][nRecordCount] = DestMac;
	sgDataList->Cells[5][nRecordCount] = nActLen;
	sgDataList->Cells[6][nRecordCount] = nTtl;
	sgDataList->Cells[7][nRecordCount] = Protocol;
	sgDataList->Cells[8][nRecordCount] = TimeStamp;

	EtherList.AddNode(EtherDataGram);
	//EtherDataGram.SaveToCache(nRecordCount);
    //lblCurPos->Caption = AnsiString(sgDataList->Row) + AnsiString(" / ") + AnsiString(sgDataList->RowCount-1)+ AnsiString(" / ") + AnsiString(AnsiString(gOption_Record_PerPage));

	if (nRecordCount < gOption_Record_PerPage)
		return true;
	//if this page is full, save the buffer to caceh or drop all
	nRecordCount = 0;
    if (gOption_SaveBuffer)
		EtherList.SaveToCache();
    else
        EtherList.Clear();
	sgDataList->CleanupInstance();
	sgDataList->RowCount = 1;
	sgDataList->RowCount = 2;


	try
	{
		//sgDataList->Rows->Clear();
		//sgDataList->Row = 2;

	}
	catch(...)
	{
		ShowMsg(nRecordCount);
	}
	return true;
}
void __fastcall TfrmMain::miExitClick(TObject *Sender)
{
	Close();
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::suiButton2Click(TObject *Sender)
{
	ShowMsg(sizeof(u_short));
}
//---------------------------------------------------------------------------


void __fastcall TfrmMain::miGoToTopClick(TObject *Sender)
{
    sgDataList->Row = 1;
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::miGoToBottomClick(TObject *Sender)
{
        sgDataList->Row = nRecordCount;
        sgDataListDblClick(0); 
}
//---------------------------------------------------------------------------


void TfrmMain::SetUiStyle(int ui)
{
	//Hide();
    SetSystemVariable("Options","UIStyle",ui);
	g_nUiStyle = ui;
    g_SkinFile = "";
SetSystemVariable("Options","Skin_File","");
	Refresh();
    //Show();
}


void __fastcall TfrmMain::imgUpDownClick(TObject *Sender)
{
	if (nRecordCount == 0)
		return;
	if (pcDataInfo->Visible)
        HidePanel();
    else
    {
        ShowDetail();
        ShowPanel();
    }
}
//---------------------------------------------------------------------------

void TfrmMain::HidePanel()
{
    pcDataInfo->Visible = false;
    imgUpDown->Picture->LoadFromFile(DIR_ROOT+DIR_IMAGES+FILE_ICON_UP);
}

void TfrmMain::ShowPanel()
{
    pcDataInfo->Visible = true;
    imgUpDown->Picture->LoadFromFile(DIR_ROOT+DIR_IMAGES+FILE_ICON_DOWN);
}

void __fastcall TfrmMain::FormCloseQuery(TObject *Sender, bool &CanClose)
{
    AnsiString szSrc = DIR_ROOT+DIR_CACHE+FILE_CACHE;
    //file not save
    if (g_szFile_Save == "" && g_nSaveCount != 0)
    {
        int retval = MsgBox(g_pLanguage->GetValue("ALERT_MAINWIN_FILE_SAVE_QUESTION"),"",3);

    	if ( retval== mrYes)
        {
        	SaveFile(0);
        }
        else if ( retval == mrCancel)
        {
            CanClose = false;
            return;
        }
        if (bCancelSave == true)
        {
            bCancelSave = false;
            CanClose = false;
            return;
        }
    }
    else
    {
        if (gOption_Exit_Confirm)
        {
           if (MsgBox(g_pLanguage->GetValue("TEXT_MESSAGE_EXIT_CONFIRM")) == mrYes)
                CanClose = true;
            else
                CanClose = false;
        }
        
        if (g_nSaveCount == 0 )
            return;

        EtherList.SaveToCache();
        //ShowMsg(szSrc);
        //ShowMsg(g_szFile_Save);
    	if (FileExists(g_szFile_Save))
    		DeleteFile(g_szFile_Save);
		if (!CopyFileTo(szSrc,g_szFile_Save))
    		ShowMsg(g_pLanguage->GetValue("ALERT_MAMINWIN_FILE_SAVE_ERROR"),"",MSG_ERROR);
        //CanClose = false;
    }
}
//---------------------------------------------------------------------------


void __fastcall TfrmMain::miNicListClick(TObject *Sender)
{
    //
    ShowNicDetail(Sender);
}
//---------------------------------------------------------------------------


void __fastcall TfrmMain::sgDataListDblClick(TObject *Sender)
{
	if (nRecordCount == 0 || sgDataList->Row == 0)
		return;
    if (pcDataInfo->Visible)
        HidePanel();
    else
    {
        ShowDetail();
        ShowPanel();
    }
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::FormClose(TObject *Sender, TCloseAction &Action)
{
	if (gOption_SaveBuffer == 0)
    	return;
    EtherList.SaveToCache();
	SetSystemVariable("Options","NextId",g_nNextId);
	delete frmStatus;
    if (g_szFile_Open != "")
    	return;
    AnsiString szSrc;
    szSrc = DIR_ROOT+DIR_CACHE+FILE_CACHE;

    UnregisterHotKey(Handle, 2000);
    UnregisterHotKey(Handle, 2001);
    //退出程序时注销热键  
}
//---------------------------------------------------------------------------

void TfrmMain::Sort(int field, bool asc, bool asint)
{
    //begin sort
    sgDataList->Cursor = crHourGlass;
    Cursor = crHourGlass;

    if (nRecordCount <= 1)
        return;

    TStringList *pStrList = new TStringList;
    int cnt,col;
    for (cnt=0; cnt<miSortBy->Count; cnt++)
    {
        if (miSortBy->Items[cnt]->Tag ==  field)
            miSortBy->Items[cnt]->Checked = true;
        else
            miSortBy->Items[cnt]->Checked = false;
    }


    AnsiString Str;
    pStrList->Sorted = true;
    //get element from string grid and sort
    for (cnt=1; cnt<sgDataList->RowCount; cnt++)
    {
        if (sgDataList->Cells[0][cnt] != "")
        {
            //first string is the key word
            Str = FillSpace(sgDataList->Cells[field][cnt],20,!asint);
            for (col=0; col<sgDataList->ColCount; col++)
            {
                Str += ";";
                Str += sgDataList->Cells[col][cnt];
                //ShowMsg(sgDataList->Cells[col][cnt]);
            }
            pStrList->Add(Str);
            //ShowMsg(Str);
        }
    }
    pStrList->Sorted = false;
    //reverse list
    if (asc == false)
    {
        for (cnt=0; cnt<=pStrList->Count/2; cnt++)
        {
            int wife = pStrList->Count-1-cnt;
            Str = pStrList->Strings[cnt];
            pStrList->Strings[cnt] = pStrList->Strings[wife];
            pStrList->Strings[wife] = Str;
        }
    }

    //copy string to grid
    for (cnt=1; cnt<sgDataList->RowCount; cnt++)
    {
        int start;
        Str = pStrList->Strings[cnt-1];
        start = Str.Pos(";") + 1;
        Str = Str.SubString(start,Str.Length());

        for (col=0; col<sgDataList->ColCount; col++)
        {
            start = Str.Pos(";");
            if (start == 0)
                break;
            else
                start++;
            //ShowMessage(Str);
            sgDataList->Cells[col][cnt] = Str.SubString(1,start-2);
            Str = Str.SubString(start,Str.Length());
        }
        sgDataList->Cells[sgDataList->ColCount-1][cnt] = Str;
    }

    sgDataList->Cursor = crDefault;
    Cursor = crDefault;
}

void TfrmMain::Exchange(int Index1, int Index2)
{
    int col1,col2;
    bool vType;
    AnsiString  sTemp[9];
    col1 = Index1;
    col2 = Index2;


    for(int i=0;i<=8;i++)
    {
        if((i==5)||(i==6)||(i==0))
        {
           sTemp[i] =  sgDataList->Cells[i][Index1].ToInt();
           continue;
        }
        sTemp[i] =  sgDataList->Cells[i][Index1];
    }

    for(int i=0;i<=8;i++)
    {
        sgDataList->Cells[i][Index1]=sgDataList->Cells[i][Index2];
    }

    for(int i=0;i<=8;i++)
    {
        if((i==5)||(i==6)||(i==0))
        {
           sgDataList->Cells[i][Index2] = (AnsiString)sTemp[i];
           continue;
        }
        sgDataList->Cells[i][Index2]=sTemp[i];
    }

}
void __fastcall TfrmMain::miStatClick(TObject *Sender)
{
		TfrmStatistic *frm = new TfrmStatistic(Application);
		frm->ShowModal();
		delete frm;
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::PopupMenuPopup(TObject *Sender)
{
	AnsiString szLang = g_pLanguage->GetCurLang();
    if (nRecordCount == 0)
    	miClearAllPacket->Enabled = false;
    else
    	miClearAllPacket->Enabled = true;
	miChinese->Checked = false;
	miEnglish->Checked  = false;

    //Skin list
    int cnt;
    for (cnt=0; cnt<miStyle->Count;cnt++)
        miStyle->Items[cnt]->Checked = false;

	if (g_SkinFile == "")
	{
		TsuiUIStyle uis = (TsuiUIStyle)g_nUiStyle;
		if (uis == WinXP)
			WinXp1->Checked = true;
		else if (uis == MacOS)
			MacOS1->Checked = true;
		else if (uis == BlueGlass)
			BlueGlass1->Checked = true;
		else if (uis == Protein)
			Protein1->Checked = true;
		else
			DeepBlue1->Checked = true;
	}
	else
	{
        for (cnt=0; cnt<miStyle->Count;cnt++)
        {
            if (g_SkinFile ==  CharFilter(miStyle->Items[cnt]->Caption,'&'))
            {
                miStyle->Items[cnt]->Checked = true;
                break;
            }
        } //for
	}//else

	miStatusWindow1->Checked = frmStatus->Visible;
	miDetailPanel1->Checked = pcDataInfo->Visible;
	miMainWin->Checked = Visible;
	if (g_bThreadIsRun)
		miStart->Checked = true;
	else
		miStart->Checked = false;
	//switch(g_
		
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::miMainStyleClick(TObject *Sender)
{
    int cnt;
    for (cnt=0; cnt<miMainStyle->Count;cnt++)
        miMainStyle->Items[cnt]->Checked = false;

	if (g_SkinFile == "")
	{
		TsuiUIStyle uis = (TsuiUIStyle)g_nUiStyle;
		if (uis == WinXP)
			miWinXp->Checked = true;
		else if (uis == MacOS)
			miMacOS->Checked = true;
		else if (uis == BlueGlass)
			miBlueGlass->Checked = true;
		else if (uis == Protein)
			miProtein->Checked = true;
		else
			miDeepBlue->Checked = true;
	}
	else
	{
        for (cnt=0; cnt<miMainStyle->Count;cnt++)
        {
            if (g_SkinFile ==  CharFilter(miMainStyle->Items[cnt]->Caption,'&'))
            {
                miMainStyle->Items[cnt]->Checked = true;
                break;
            }
        } //for
	}//else
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::miLanguageClick(TObject *Sender)
{
	AnsiString szLang = g_pLanguage->GetCurLang();
	miChinese->Checked = false;
	miEnglish->Checked  = false;
	if (szLang == "Chinese")
		Chinese1->Checked = true;
	else
		English1->Checked = true;
	
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::miInterfaceClick(TObject *Sender)
{
	miDetailPanel->Checked = pcDataInfo->Visible;
	miStatusWindow->Checked = frmStatus->Visible;
	miMainWindow->Checked = Visible;

	Chinese1->Checked = false;
	English1->Checked = false;
	AnsiString szLang = g_pLanguage->GetCurLang();
	if (szLang == "Chinese")
		Chinese1->Checked = true;
	else
		English1->Checked = true;
    if (nRecordCount)
        miDetailPanel->Enabled = true;
    else
        miDetailPanel->Enabled = false;
    //miInterface->
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::miDetailPanelClick(TObject *Sender)
{
	if (nRecordCount == 0)
		return;
	if (pcDataInfo->Visible)
        HidePanel();
    else
        ShowPanel();
	
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::miEditClick(TObject *Sender)
{
	if (nRecordCount == 0)
	{
		miClearAll->Enabled = false;
		//miSavetoCache->Enabled = false;
		miGoTo->Enabled = false;
		miGoToTop->Enabled = false;
        miSortBy->Enabled = false;
		miGoToBottom->Enabled = false;
	}
	else
	{
		miClearAll->Enabled = true;
		//miSavetoCache->Enabled = true;
		miGoTo->Enabled = true;
		miGoToTop->Enabled = true;
		miGoToBottom->Enabled = true;
        miSortBy->Enabled = !g_bThreadIsRun;
	}
    if (g_szFile_Open == "")
    {
		FirstPage1->Enabled = false;
    	Prevous1->Enabled = false;
    	NextPage1->Enabled = false;
    	LastPage1->Enabled = false;
        return;
    }
	FirstPage1->Enabled = true;
    Prevous1->Enabled = true;
    NextPage1->Enabled = true;
    LastPage1->Enabled = true;
    if (nCurPage == 1)
    {
		FirstPage1->Enabled = false;
    	Prevous1->Enabled = false;
    }
    if (nCurPage == EtherList.GetPageCount())
    {
        NextPage1->Enabled = false;
	    LastPage1->Enabled = false;
	}    
}
//---------------------------------------------------------------------------

bool TfrmMain::ThreadIsRun()
{
	return bThreadIsRun;
}




void __fastcall TfrmMain::TrayIconMinimize(TObject *Sender)
{
	//ShowMsg("mim");	
}
//---------------------------------------------------------------------------



void __fastcall TfrmMain::TrayIconDeactivate(TObject *Sender)
{
	//ShowMsg("mim");	
}
//---------------------------------------------------------------------------


void __fastcall TfrmMain::miStatusWindowClick(TObject *Sender)
{
	frmStatus->Visible = !frmStatus->Visible; 	
}
//---------------------------------------------------------------------------



void __fastcall TfrmMain::sgDataListMouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
    if (pcDataInfo->Visible == true)
        ShowDetail();
        
    len[0]=sgDataList->ColWidths[0];
    len[1]=len[0]+sgDataList->ColWidths[1];
    len[2]=len[1]+sgDataList->ColWidths[2];
    len[3]=len[2]+sgDataList->ColWidths[3];
    len[4]=len[3]+sgDataList->ColWidths[4];
    len[5]=len[4]+sgDataList->ColWidths[5];
    len[6]=len[5]+sgDataList->ColWidths[6];
    len[7]=len[6]+sgDataList->ColWidths[7];
    len[8]=len[7]+sgDataList->ColWidths[8];

    //sgDataList->DefaultRowHeight * sgDataList->FixedRows
    if (g_bThreadIsRun)
    	return;
	if ((Y > 0 ) && (Y < sgDataList->DefaultRowHeight)&&(Button == mbLeft))
	{

        if((X>0)&&(X<len[0]))
        {
            if(ascOrDesc[0] ==  true)
            {
                Sort(0,0,1);
                ascOrDesc[0]=false;
            }else{
                Sort(0,1,1);
                ascOrDesc[0]=true;
            }

        }else if((X>len[0])&&(X<len[1]))
        {
            if(ascOrDesc[1] ==  true)
            {
                Sort(1,0,0);
                ascOrDesc[1]=false;
            }else{
                Sort(1,1,0);
                ascOrDesc[1]=true;
            }
        }else if((X>len[1])&&(X<len[2]))
        {
            if(ascOrDesc[2] ==  true)
            {
                Sort(2,0,0);
                ascOrDesc[2]=false;
            }else{
                Sort(2,1,0);
                ascOrDesc[2]=true;
            }
        }else if((X>len[2])&&(X<len[3]))
        {
           if(ascOrDesc[3] ==  true)
            {
                Sort(3,0,0);
                ascOrDesc[3]=false;
            }else{
                Sort(3,1,0);
                ascOrDesc[3]=true;
            }
        }else if((X>len[3])&&(X<len[4]))
        {
            if(ascOrDesc[4] ==  true)
            {
                Sort(4,0,0);
                ascOrDesc[4]=false;
            }else{
                Sort(4,1,0);
                ascOrDesc[4]=true;
            }
        }else if((X>len[4])&&(X<len[5]))
        {
            if(ascOrDesc[5] ==  true)
            {
                Sort(5,0,1);
                ascOrDesc[5]=false;
            }else{
                Sort(5,1,1);
                ascOrDesc[5]=true;
            }
        }else if((X>len[5])&&(X<len[6]))
        {
            if(ascOrDesc[6] ==  true)
            {
                Sort(6,0,1);
                ascOrDesc[6]=false;
            }else{
                Sort(6,1,1);
                ascOrDesc[6]=true;
            }
        }else if((X>len[6])&&(X<len[7]))
        {
            if(ascOrDesc[7] ==  true)
            {
                Sort(7,0,0);
                ascOrDesc[7]=false;
            }else{
                Sort(7,1,0);
                ascOrDesc[7]=true;
            }
        }else if((X>len[7])&&(X<len[8]))
        {
            if(ascOrDesc[8] ==  true)
            {
                Sort(8,0,0);
                ascOrDesc[8]=false;
            }else{
                Sort(8,1,0);
                ascOrDesc[8]=true;
            }
        }
        else if((X>len[8]))
        {
            if(ascOrDesc[9] ==  true)
            {
                Sort(9,0,0);
                ascOrDesc[9]=false;
            }else{
                Sort(9,1,0);
                ascOrDesc[9]=true;
            }
        }
	}
}
//---------------------------------------------------------------------------



void __fastcall TfrmMain::miMainWindowClick(TObject *Sender)
{
	if (Visible)
		Hide();
	else
		Show();
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::miExit1Click(TObject *Sender)
{
	Close();
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::miSniHelpClick(TObject *Sender)
{
	AnsiString Path = DIR_ROOT+DIR_DOCS+FILE_HELP;
	ShellExecute(NULL,NULL,(Path.c_str()),NULL,"",SW_SHOW);
}
//---------------------------------------------------------------------------



void TfrmMain::LoadFromList()
{
	sgDataList->CleanupInstance();
	sgDataList->RowCount = 1;
    TEtherDataGram EtherDataGram;
    nRecordCount = 0;
    //ShowMsg(EtherList.GetCount());
    EtherList.Rewind();
    while (EtherList.GetNext(EtherDataGram))
    {
    	//ShowMsg(nRecordCount);
		AnsiString SrcMac,DestMac,TimeStamp,SrcAddr,DestAddr,Protocol;
		int  nActLen, nTtl;
		//EtherDataGram.SetBuffer(header,pkt_data);
		SrcMac = EtherDataGram.GetSrcMac();
		DestMac = EtherDataGram.GetDestMac();
		nActLen = EtherDataGram.GetActLen();
		//nCapLen = EtherDataGram.GetCapLen();
		Protocol = EtherDataGram.GetTypeName();
		TimeStamp = EtherDataGram.GetTimeStamp();
		//ip packet
		if (EtherDataGram.GetTypeName() == "IP")
		{
			TIpDataGram IpDataGram;
			IpDataGram.SetBuffer(EtherDataGram.GetDataHeader(),EtherDataGram.GetDataSize());
			//if (!protocolAllow(IpDataGram.GetProtocolValue()))
				//return;
			//if (IpDataGram.GetProtocolValue() != IPPROTO_ICMP)
			//    return;
			int protocol = IpDataGram.GetProtocolValue();
	
			nTtl = IpDataGram.GetTimeToLive();
			SrcAddr = IpDataGram.GetSrcAddr();
			DestAddr = IpDataGram.GetDestAddr();
			Protocol = IpDataGram.GetProtocol();

		}
		else if (EtherDataGram.GetTypeName() == "ARP")
		{
			TArpPacket ArpPacket;
			ArpPacket.SetBuffer(EtherDataGram.GetDataHeader(),EtherDataGram.GetDataSize());
			SrcAddr = ArpPacket.GetSrcAddr();
			DestAddr = ArpPacket.GetDestAddr();
		}
		else if (EtherDataGram.GetTypeName() == "RARP")
		{			
			TArpPacket ArpPacket;
			ArpPacket.SetBuffer(EtherDataGram.GetDataHeader(),EtherDataGram.GetDataSize());
			SrcAddr = ArpPacket.GetSrcAddr();
			DestAddr = ArpPacket.GetDestAddr();
		}
		else
		{			
		}
	
		if (sgDataList->RowCount <= nRecordCount + 1)
			 sgDataList->RowCount++;
		nRecordCount++;
	
		sgDataList->Cells[0][nRecordCount] = EtherDataGram.GetId();
		sgDataList->Cells[1][nRecordCount] = SrcAddr;
		sgDataList->Cells[2][nRecordCount] = DestAddr;
		sgDataList->Cells[3][nRecordCount] = SrcMac;
		sgDataList->Cells[4][nRecordCount] = DestMac;
		sgDataList->Cells[5][nRecordCount] = nActLen;
		sgDataList->Cells[6][nRecordCount] = nTtl;
		sgDataList->Cells[7][nRecordCount] = Protocol;
		sgDataList->Cells[8][nRecordCount] = TimeStamp;    
    }
}
void __fastcall TfrmMain::ClearAll(TObject *Sender)
{
    if (!(MsgBox(g_pLanguage->GetValue("ALERT_MAINWIN_CLEAR_ALL_CONFIRM"))== mrYes))
    	return;
	EtherList.Clear();
    sgDataList->CleanupInstance();
    sgDataList->RowCount = 1;
    nRecordCount = 0;
    HidePanel();
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::sgDataListMouseMove(TObject *Sender,
      TShiftState Shift, int X, int Y)
{
    if ((Y > 0 ) && (Y < sgDataList->DefaultRowHeight))
    	sgDataList->Cursor = crHandPoint;
    else
    	sgDataList->Cursor = crDefault;
	if (g_bThreadIsRun)
        sgDataList->Cursor = crDefault;
}
//---------------------------------------------------------------------------


void __fastcall TfrmMain::miOpenClick(TObject *Sender)
{
	OpenDialog->InitialDir = DIR_ROOT + DIR_SAVE;

	if (OpenDialog->Execute())
    {
    	if (!FileExists(OpenDialog->FileName))
        {
        	ShowMsg(g_pLanguage->GetValue("ALERT_MAINWIN_FILE_NOT_EXISTS"),"",MSG_WARNING);
    		return;
        }
        EtherList.Clear();
        EtherList.SetCacheFile(OpenDialog->FileName);
       	nCurPage = 1;
        EtherList.LoadFromCahce(nCurPage);
        LoadFromList();
    	lblStatus->Caption = AnsiString(nCurPage)+AnsiString("/")+AnsiString(EtherList.GetPageCount())+AnsiString("   ")+AnsiString((nCurPage-1)*gOption_Record_PerPage+1)+ AnsiString(" - ")+ AnsiString(gOption_Record_PerPage*nCurPage<EtherList.GetRecordCount()?gOption_Record_PerPage*nCurPage:EtherList.GetRecordCount())+AnsiString(" / ") + AnsiString(EtherList.GetRecordCount());
        lblStatus->Enabled = true;
        btnFirst->Enabled = true;
        btnPrevious->Enabled = true;
        btnNext->Enabled = true;
        btnLast->Enabled = true;
        PageCtrl();
        g_szFile_Open = OpenDialog->FileName;
    }
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::btnFirstClick(TObject *Sender)
{
	if (nCurPage == 1)
    	return;
   	nCurPage = 1;
    EtherList.LoadFromCahce(nCurPage);
    LoadFromList();
	lblStatus->Caption = AnsiString(nCurPage)+AnsiString("/")+AnsiString(EtherList.GetPageCount())+AnsiString("   ")+AnsiString((nCurPage-1)*gOption_Record_PerPage+1)+ AnsiString(" - ")+ AnsiString(gOption_Record_PerPage*nCurPage<EtherList.GetRecordCount()?gOption_Record_PerPage*nCurPage:EtherList.GetRecordCount())+AnsiString(" / ") + AnsiString(EtherList.GetRecordCount());
	PageCtrl();
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::btnPreviousClick(TObject *Sender)
{
	if (nCurPage == 1)
    	return;
   	nCurPage -= 1;
    EtherList.LoadFromCahce(nCurPage);
    LoadFromList();
	lblStatus->Caption = AnsiString(nCurPage)+AnsiString("/")+AnsiString(EtherList.GetPageCount())+AnsiString("   ")+AnsiString((nCurPage-1)*gOption_Record_PerPage+1)+ AnsiString(" - ")+ AnsiString(gOption_Record_PerPage*nCurPage<EtherList.GetRecordCount()?gOption_Record_PerPage*nCurPage:EtherList.GetRecordCount())+AnsiString(" / ") + AnsiString(EtherList.GetRecordCount());
	PageCtrl();
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::btnNextClick(TObject *Sender)
{
	if (nCurPage == EtherList.GetPageCount())
    	return;
   	nCurPage += 1;
    EtherList.LoadFromCahce(nCurPage);
    LoadFromList();
	lblStatus->Caption = AnsiString(nCurPage)+AnsiString("/")+AnsiString(EtherList.GetPageCount())+AnsiString("   ")+AnsiString((nCurPage-1)*gOption_Record_PerPage+1)+ AnsiString(" - ")+ AnsiString(gOption_Record_PerPage*nCurPage<EtherList.GetRecordCount()?gOption_Record_PerPage*nCurPage:EtherList.GetRecordCount())+AnsiString(" / ") + AnsiString(EtherList.GetRecordCount());
	PageCtrl();
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::btnLastClick(TObject *Sender)
{
	if (nCurPage == EtherList.GetPageCount())
    	return;
   	nCurPage = EtherList.GetPageCount();
    EtherList.LoadFromCahce(nCurPage);
    LoadFromList();
	lblStatus->Caption = AnsiString(nCurPage)+AnsiString("/")+AnsiString(EtherList.GetPageCount())+AnsiString("   ")+AnsiString((nCurPage-1)*gOption_Record_PerPage+1)+ AnsiString(" - ")+ AnsiString(gOption_Record_PerPage*nCurPage<EtherList.GetRecordCount()?gOption_Record_PerPage*nCurPage:EtherList.GetRecordCount())+AnsiString(" / ") + AnsiString(EtherList.GetRecordCount());
	PageCtrl();
}
//---------------------------------------------------------------------------

void TfrmMain::PageCtrl()
{
	btnFirst->Enabled = true;
    btnPrevious->Enabled = true;
    btnNext->Enabled = true;
    btnLast->Enabled = true;
    if (nCurPage == 1)
    {
		btnFirst->Enabled = false;
    	btnPrevious->Enabled = false;
    }
    if (nCurPage == EtherList.GetPageCount())
    {
        btnNext->Enabled = false;
	    btnLast->Enabled = false;
	} 
    lblCurPos->Caption = AnsiString(sgDataList->Row) + AnsiString(" / ") + AnsiString(sgDataList->RowCount-1)+ AnsiString(" / ") + AnsiString(AnsiString(gOption_Record_PerPage));
}
void __fastcall TfrmMain::CloseFile(TObject *Sender)
{
	g_szFile_Open = "";
	FirstPage1->Enabled = false;
    Prevous1->Enabled = false;
    NextPage1->Enabled = false;
    LastPage1->Enabled = false;
	btnFirst->Enabled = false;
    btnPrevious->Enabled = false;
    btnNext->Enabled = false;
    btnLast->Enabled = false;

	EtherList.Clear();
    nRecordCount = 0;
    sgDataList->RowCount = 1;
    lblStatus->Caption = "";
    lblStatus->Enabled = false;
    lblCurPos->Caption = "";
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::miFileClick(TObject *Sender)
{
    if (g_szFile_Open != "")
	{
		miOpen->Enabled = false;
    	Save1->Enabled = false;
        SaveAs1->Enabled = true;
        miClose->Enabled = true;		
	}
	else
	{
		if (g_bThreadIsRun)
		{
			miOpen->Enabled = false;
	    	Save1->Enabled = true;
	        SaveAs1->Enabled = true;
	        miClose->Enabled = false;				
		}
		else
		{
			miOpen->Enabled = true;
	    	Save1->Enabled = true;
	        SaveAs1->Enabled = true;
	        miClose->Enabled = false;
		}
        if (nRecordCount == 0)
        {
            Save1->Enabled = false;
            SaveAs1->Enabled = false;
        }
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::SaveAsFile(TObject *Sender)
{
 
	AnsiString szDest,szSrc;
	SaveDialog->InitialDir = DIR_ROOT + DIR_SAVE;
    if (g_szFile_Open != "")
		szSrc = DIR_ROOT+DIR_CACHE+FILE_CACHE;
	else
		szSrc = g_szFile_Open;

	if (SaveDialog->Execute())
    {
    	if (FileExists(SaveDialog->FileName))
        {
        	if (!MsgBox(SaveDialog->FileName+g_pLanguage->GetValue("ALERT_MAINWIN_FILE_REPLACE_CONRIM")))
            	return;
            DeleteFile(SaveDialog->FileName);
        }
        szDest = SaveDialog->FileName;
        g_szFile_Save = szDest;
    }
   	else
    {
   		return;
    }
    
    if (!FileExists(szSrc))
    {
    	return ;
    }
    if (FileExists(szDest))
    	DeleteFile(szDest);
	if (CopyFileTo(szSrc,szDest))
       	ShowMsg(g_pLanguage->GetValue("TEXT_MAINWIN_FILE_SAVE_OK"));
    else
	   	ShowMsg(g_pLanguage->GetValue("ALERT_MAMINWIN_FILE_SAVE_ERROR"),"",MSG_ERROR);

}
//---------------------------------------------------------------------------



void __fastcall TfrmMain::miAuthorClick(TObject *Sender)
{
	TfrmAuthor * frm = new TfrmAuthor(0);
    frm->ShowModal();
    delete frm;
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::SaveFile(TObject *Sender)
{
	AnsiString szDest,szSrc;
   	szSrc = DIR_ROOT+DIR_CACHE+FILE_CACHE;
	SaveDialog->InitialDir = DIR_ROOT + DIR_SAVE;

    if (g_szFile_Open != "")
    	return;
    if (g_szFile_Save != "")
    {
    	szDest = g_szFile_Save;
    }

	else if (SaveDialog->Execute())
    {
    	if (FileExists(SaveDialog->FileName))
        {
        	if (!MsgBox(SaveDialog->FileName+g_pLanguage->GetValue("ALERT_MAINWIN_FILE_REPLACE_CONRIM")))
            	return;
            DeleteFile(SaveDialog->FileName);
        }
        szDest = SaveDialog->FileName;
        g_szFile_Save = szDest;
    }
    else
    {
        bCancelSave = true;
        return;
    }

    EtherList.SaveToCache();

    if (!FileExists(szSrc))
    {
    	return;
    }
    if (FileExists(szDest))
    	DeleteFile(szDest);
    //ShowMsg(szSrc + "\n" + szDest);
    //copy file from cache to destination file

	if (CopyFileTo(szSrc,szDest))
       	ShowMsg(g_pLanguage->GetValue("TEXT_MAINWIN_FILE_SAVE_OK"));
    else
	   	ShowMsg(g_pLanguage->GetValue("ALERT_MAMINWIN_FILE_SAVE_ERROR"));

}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::miViewClick(TObject *Sender)
{
	if (g_nTotalCount == 0)
    	miStat->Enabled = false;
    else
    	miStat->Enabled = true;
}
//---------------------------------------------------------------------------

 
void __fastcall TfrmMain::miAboutClick(TObject *Sender)
{
	TfrmCover *frmCover = new TfrmCover(0);
    //frmCover->  
    //frmCover->ShowSplash();
    //frmCover->Visible = false;
    frmCover->ShowModal();
    delete frmCover;
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::miFeedBackClick(TObject *Sender)
{
	AnsiString Path = AnsiString("mailto:") + MAIL_FEEDBACK;
	ShellExecute(NULL,NULL,(Path.c_str()),NULL,"",SW_SHOW); 
}
//---------------------------------------------------------------------------



void __fastcall TfrmMain::sgDataListMouseWheelUp(TObject *Sender,
      TShiftState Shift, TPoint &MousePos, bool &Handled)
{
    //HidePanel();
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::sgDataListClick(TObject *Sender)
{

    if (sgDataList->Row == 0)
        return;

    if (sgDataList->Cells[0][sgDataList->Row] != "")
    {
        sgDataList->Hint = EtherList.GetHint(sgDataList->Cells[0][sgDataList->Row].ToInt());
        sgDataList->ShowHint = true;
        //ShowMsg(sgDataList->Hint + sgDataList->Row);
    }
    ShowDetail();  
}
//---------------------------------------------------------------------------

void TfrmMain::ShowDetail()
{
    lblCurPos->Caption = "";
	if (sgDataList->Row > nRecordCount)
	{
		//ShowMsg("not find");
		return;
	}
    //ShowMsg(sgDataList->Row);
	if (sgDataList->Row == 0)
		return;

	//HidePanel();
    lblCurPos->Caption = AnsiString(sgDataList->Row) + AnsiString(" / ") + AnsiString(sgDataList->RowCount-1)+ AnsiString(" / ") + AnsiString(AnsiString(gOption_Record_PerPage));
    //TsuiTabSheet *pActive = pcDataInfo->ActivePage;
	TEtherDataGram Ether;
	if (!EtherList.GetElem(sgDataList->Cells[0][sgDataList->Row].ToInt(),Ether))
	{
		ShowMsg(AnsiString("cant get elem ")+sgDataList->Cells[0][sgDataList->Row]);
		return;
	}
    //Ether.LoadFromCache(sgDataList->Row);
    //if (!Ether.LoadFromCache(sgDataList->Row))
        //ShowMsg("error");

	edtSrcMac->Text = Ether.GetSrcMac();
    edtDestMac->Text = Ether.GetDestMac();
    edtType->Text = Ether.GetTypeName() + "(" + Ether.GetTypeValue() + ")";
    edtTimeStamp->Text = Ether.GetTimeStamp();
    edtActLen->Text = Ether.GetActLen();
    edtCapLen->Text = Ether.GetCapLen();


	if (Ether.GetTypeName() == "IP")
    {
        //IP header
        TIpDataGram IpDataGram;
        IpDataGram = Ether;

        tsArpHeader->TabVisible = false;

        edtVersion->Text = IpDataGram.GetVersion();
        edtIhl->Text = IpDataGram.GetHeaderLength();
        edtTos->Text = IpDataGram.GetTos();
        edtSrcAddr->Text = IpDataGram.GetSrcAddr();
        edtDestAddr->Text = IpDataGram.GetDestAddr();
        edtId->Text = IpDataGram.GetIdentification();
        edtTotalLength->Text = IpDataGram.GetTotalLength();
        edtFlags->Text = IpDataGram.GetFlags();
        edtOffset->Text = IpDataGram.GetOffset();
        edtTtl->Text = IpDataGram.GetTimeToLive();
        edtProtocol->Text = IpDataGram.GetProtocol();
        edtHeaderCrc->Text = IpDataGram.GetChecksum();
		//ICMP
		if (IpDataGram.GetProtocolValue() == IPPROTO_ICMP)
		{
			TIcmpPacket Icmp;
			Icmp.SetBuffer(IpDataGram.GetDataHeader());
			edtIcmpType->Text = Icmp.GetType();
			edtIcmpCode->Text = Icmp.GetCode();
			edtIcmpCrc->Text = Icmp.GetCheckSum();
			edtIcmpDesc->Text = Icmp.GetDescri();
			if (!tsIpHeader->TabVisible)
				tsIpHeader->TabVisible = true;
			if (tsTcp->TabVisible)
				tsTcp->TabVisible = false;
			if (tsUdp->TabVisible)
				tsUdp->TabVisible = false;
			if (!tsIcmp->TabVisible)
				tsIcmp->TabVisible = true;
			if (tsArpHeader->TabVisible)
				tsArpHeader->TabVisible = false;
			if (tsData->TabVisible)
				tsData->TabVisible = false;
		}
		else if (IpDataGram.GetProtocolValue() == IPPROTO_TCP)
		{
			TTcpPacket TcpPacket;
			TcpPacket.SetBuffer(IpDataGram.GetDataHeader(),IpDataGram.GetDataSize());

			if (tsIcmp->TabVisible)
				tsIcmp->TabVisible = false;
			if (tsUdp->TabVisible)
				tsUdp->TabVisible = false;
			if (tsArpHeader->TabVisible)
				tsArpHeader->TabVisible = false;
			if (!tsTcp->TabVisible)
				tsTcp->TabVisible = true;
            if (!tsData->TabVisible)
            	tsData->TabVisible = true;
            if (!tsIpHeader->TabVisible)
            	tsIpHeader->TabVisible = true;

			edtTcpSrcPort->Text = TcpPacket.GetSrcPort();
			edtTcpDestPort->Text = TcpPacket.GetDesPort();
			edtTcpWinSize->Text = TcpPacket.GetWindowSize();
			edtTcpSeqNum->Text = TcpPacket.GetSeqNum();
			edtAckSeq->Text = TcpPacket.GetAckNum();
			edtTcpProtoName->Text = TcpPacket.GetAppProtocolName();
            tsData->Visible = false;
			mmoBin->Lines->Clear();
			TcpPacket.GetAppData16(mmoBin->Lines);

			mmoText->Lines->Clear();
			TcpPacket.GetAppDataAsc(mmoText->Lines);
            tsData->Visible = true;
			//mmoText->Lines = StrList;
		}
		else if (IpDataGram.GetProtocolValue() == IPPROTO_UDP)
		{
			TUdpPacket UdpPacket;
			UdpPacket.SetBuffer(IpDataGram.GetDataHeader(),IpDataGram.GetDataSize());

			if (tsIcmp->TabVisible)
				tsIcmp->TabVisible = false;
			if (!tsUdp->TabVisible)
				tsUdp->TabVisible = true;
			if (tsTcp->TabVisible)
				tsTcp->TabVisible = false;
			if (!tsIpHeader->TabVisible)
				tsIpHeader->TabVisible = true;
            if (!tsIpHeader->TabVisible)
            	tsIpHeader->TabVisible = true;

			edtUdpSrcPort->Text = UdpPacket.GetSrcPort();
			edtUdpDestPort->Text = UdpPacket.GetDesPort();
			edtUdpLength->Text = UdpPacket.GetDataLen();
			edtUdpCrc->Text = UdpPacket.GetCheckSum();
			edtUdpProtoName->Text = UdpPacket.GetAppProtocolName();

            tsData->Visible = false;
			mmoBin->Lines->Clear();
			UdpPacket.GetAppData16(mmoBin->Lines);

			mmoText->Lines->Clear();
			UdpPacket.GetAppDataAsc(mmoText->Lines);
            tsData->Visible = true;
			//mmoText->l

		}
		else
		{//igmp, wait for extend
		}
	}
	else if (Ether.GetTypeName() == "ARP" || Ether.GetTypeName() == "RARP")
	{//ARP or RARP
		TArpPacket Arp;
		Arp.SetBuffer(Ether.GetDataHeader(),Ether.GetDataSize());
		edtArpDestAddr->Text = Arp.GetDestAddr();
		edtArpSrcAddr->Text = Arp.GetSrcAddr();
		edtArpDestMac->Text = Arp.GetDestMac();
		edtArpSrcMac->Text =  Arp.GetSrcMac();
		//if ( Arp.GetOpType() == 1 || Arp.GetOpType() == 2)
		edtProtocolType->Text = Ether.GetTypeName();
		if (tsIpHeader->TabVisible)
			tsIpHeader->TabVisible = false;
		if (tsTcp->TabVisible)
			tsTcp->TabVisible = false;
		if (tsUdp->TabVisible)
			tsUdp->TabVisible = false;
		if (!tsArpHeader->TabVisible)
			tsArpHeader->TabVisible = true;
		if (tsIcmp->TabVisible)
			tsArpHeader->TabVisible = false;
        if (tsData->TabVisible)
            tsData->TabVisible = false;

	}
	else
	{//unkown protocol
        //ShowMsg("unkown protocol");
		if (tsIpHeader->TabVisible)
			tsIpHeader->TabVisible = false;
		if (tsTcp->TabVisible)
			tsTcp->TabVisible = false;
		if (tsUdp->TabVisible)
			tsUdp->TabVisible = false;
		if (tsArpHeader->TabVisible)
			tsArpHeader->TabVisible = false;
		if (tsIcmp->TabVisible)
			tsIcmp->TabVisible = false;
	}
	//pcDataInfo->ActivePage = tsEtherHeader;
	//ShowPanel();
}
void __fastcall TfrmMain::sgDataListMouseWheelDown(TObject *Sender,
      TShiftState Shift, TPoint &MousePos, bool &Handled)
{
    //HidePanel();    
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::miTurtorialClick(TObject *Sender)
{
	AnsiString Path = DIR_ROOT+DIR_DOCS+FILE_TUTORIAL;
	ShellExecute(NULL,NULL,(Path.c_str()),NULL,"",SW_SHOW);   
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::miGoToClick(TObject *Sender)
{
    int percent;
    TfrmGoto * frm = new TfrmGoto(Application);
    percent = frm->ShowModal();
    if (percent < 100)
        return;
    percent -= 100;
    int pos;
    pos = percent * sgDataList->RowCount / 100;
    if (percent == 100)
        pos -= 1;
    if (pos < 2)
        pos = 2;
    sgDataList->Row = pos;
}
//---------------------------------------------------------------------------


void __fastcall TfrmMain::Timer1Timer(TObject *Sender)
{
    if (nRecordCount == 0)
        return;
    lblCurPos->Caption = AnsiString(sgDataList->Row) + AnsiString(" / ") + AnsiString(sgDataList->RowCount-1)+ AnsiString(" / ") + AnsiString(AnsiString(gOption_Record_PerPage));
}
//---------------------------------------------------------------------------



void __fastcall TfrmMain::ChangeUIStyle(TObject *Sender)
{
    TMenuItem *pMenu = (TMenuItem*)Sender;
    AnsiString szOldSkin = g_SkinFile;
    this->Hide();
    AnsiString szSkinFile = DIR_ROOT + DIR_SKINS + CharFilter(pMenu->Caption,'&') + EXT_SKIN;
    if (!FileExists(szSkinFile))
    {
        ShowMsg(g_pLanguage->GetValue("TEXT_MESSAGE_CAN_NOT_FIND_SKIN_FILE") + "\n"+ szSkinFile,g_pLanguage->GetValue("TEXT_MESSAGE_FILE_LOST"),MSG_ERROR);
    }
    else
    {
        ThemeManager->UIStyle = FromThemeFile;
        try
        {
            ThemeManager->FileTheme->ThemeFile = szSkinFile;
            SetSystemVariable("Options","Skin_File",CharFilter(pMenu->Caption,'&'));

            g_SkinFile = CharFilter(pMenu->Caption,'&');
        }catch(...)
        {
            g_SkinFile = szOldSkin;
            ShowMsg(g_pLanguage->GetValue("TEXT_MESSAGE_INVALID_SKIN_FILE") + "\n"+ szSkinFile,"",MSG_ERROR);
        }
   }
   this->Show();
}

void __fastcall TfrmMain::ChangeLanguage(TObject *Sender)
{
    TMenuItem *pMenu = (TMenuItem*)Sender;
    AnsiString szLangFile = CharFilter(pMenu->Caption,'&');

    if (!g_pLanguage->LoadLanguage(szLangFile))
    {
        ShowMsg(g_pLanguage->GetValue("TEXT_MESSAGE_CAN_NOT_LOAD_FILE")+DIR_ROOT+DIR_LANG+szLangFile,"",MSG_ERROR);
        return;
   }
    else
        Refresh();
}
//---------------------------------------------------------------------------



void __fastcall TfrmMain::miGetSourceClick(TObject *Sender)
{
    if (MsgBox(g_pLanguage->GetValue("TEXT_MESSAGE_GET_SOURCE_CODE")) == mrYes)
        ShellExecute(NULL,NULL,(URL_SOURCE_CODE.c_str()),NULL,"",SW_SHOW);
}
//---------------------------------------------------------------------------



void __fastcall TfrmMain::FormCreate(TObject *Sender)
{
    if (gOption_Min_Start)
    {
        //ShowMsg("m");
        WindowState = wsMinimized;
        //Hide();
        //ShowWindow(Application->Handle, SW_HIDE);
    }
    else
        WindowState = wsMaximized;

    if(!RegisterHotKey(Handle,2000,MOD_CONTROL,VK_F8))
        ShowMsg(g_pLanguage->GetValue("ERROR_CAN_NOT_REGISTER_HOT_KEY") + "<CTRL>+F8");
    if(!RegisterHotKey(Handle,2001,MOD_CONTROL,VK_RETURN))
        ShowMsg(g_pLanguage->GetValue("ERROR_CAN_NOT_REGISTER_HOT_KEY") + "<CTRL>+<Enter>");

    if (gOption_Display_Icon)
    {
        TrayIcon->Hide = false;
        TrayIcon->Visible = true;
    }
    else
        TrayIcon->Hide = true;
        //TrayIcon->Visible = false;
        
}
//---------------------------------------------------------------------------


void __fastcall TfrmMain::TrayIconClick(TObject *Sender)
{
    AnsiString szHint;
    szHint += FillSpace(g_pLanguage->GetValue("FRMSTATUS_LBLSTATUS"));
    if (g_bThreadIsRun)
        szHint += "Running";
    else
        szHint += "Stop";
    szHint += "\n";
    szHint += FillSpace(g_pLanguage->GetValue("FRMSTATUS_LBLSAVE")) + g_nSaveCount + "\n";
    szHint += FillSpace(g_pLanguage->GetValue("FRMSTATUS_LBLDROP")) + AnsiString(g_nTotalCount - g_nSaveCount);
    TrayIcon->Hint = szHint;
}
//---------------------------------------------------------------------------



void __fastcall TfrmMain::btn1Click(TObject *Sender)
{
    ShowMsg(sgDataList->RowCount);     
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::OnHotKey(TMessage &Message)
{
    if (!this->Visible)
    {
        //ShowMsg("show");
        this->Show();
        this->BringToFront();
    }
    else
    {
        //ShowMsg("hide");
        this->Hide();
    }
}

void __fastcall TfrmMain::miSortByIdClick(TObject *Sender)
{
    if(ascOrDesc[0] ==  true)
    {
        Sort(0,0,1);
        ascOrDesc[0]=false;
    }else{
        Sort(0,1,1);
        ascOrDesc[0]=true;
    }  
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::miSrcHostClick(TObject *Sender)
{
    if(ascOrDesc[1] ==  true)
    {
        Sort(1,0,0);
        ascOrDesc[1]=false;
    }else{
        Sort(1,1,0);
        ascOrDesc[1]=true;
    }     
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::miDestHostClick(TObject *Sender)
{
    if(ascOrDesc[2] ==  true)
    {
        Sort(2,0,0);
        ascOrDesc[2]=false;
    }else{
        Sort(2,1,0);
        ascOrDesc[2]=true;
    }    
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::miSrcMacClick(TObject *Sender)
{
   if(ascOrDesc[3] ==  true)
    {
        Sort(3,0,0);
        ascOrDesc[3]=false;
    }else{
        Sort(3,1,0);
        ascOrDesc[3]=true;
    }
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::miDestMacClick(TObject *Sender)
{
    if(ascOrDesc[4] ==  true)
    {
        Sort(4,0,0);
        ascOrDesc[4]=false;
    }else{
        Sort(4,1,0);
        ascOrDesc[4]=true;
    }  
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::miSortBySizeClick(TObject *Sender)
{
    if(ascOrDesc[5] ==  true)
    {
        Sort(5,0,1);
        ascOrDesc[5]=false;
    }else{
        Sort(5,1,1);
        ascOrDesc[5]=true;
    }   
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::miSortByTTLClick(TObject *Sender)
{
    if(ascOrDesc[6] ==  true)
    {
        Sort(6,0,1);
        ascOrDesc[6]=false;
    }else{
        Sort(6,1,1);
        ascOrDesc[6]=true;
    }    
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::miProtocolClick(TObject *Sender)
{
    if(ascOrDesc[7] ==  true)
    {
        Sort(7,0,0);
        ascOrDesc[7]=false;
    }else{
        Sort(7,1,0);
        ascOrDesc[7]=true;
    } 
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::miTimestampClick(TObject *Sender)
{
    if(ascOrDesc[8] ==  true)
    {
        Sort(8,0,0);
        ascOrDesc[8]=false;
    }else{
        Sort(8,1,0);
        ascOrDesc[8]=true;
    } 
}
//---------------------------------------------------------------------------



void __fastcall TfrmMain::TrayIconMouseMove(TObject *Sender,
      TShiftState Shift, int X, int Y)
{

    //ShowMessage(szHint);
    //TrayIcon->ShowHint = true;
}
//---------------------------------------------------------------------------




