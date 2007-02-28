//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "OptionsWin.h"
#include "Global.h"
#include "Constant.h"
#include "IpAddr.h"
#include "Config.h"
#include "MsgDialog.h"
 
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "SUIButton"
#pragma link "SUIForm"
#pragma link "SUIGroupBox"
#pragma link "SUIImagePanel"
#pragma link "SUIPageControl"
#pragma link "SUITabControl"
#pragma link "SUIMgr"
#pragma link "SUIEdit"
#pragma link "SUITrackBar"
#pragma link "SUIComboBox"
#pragma resource "*.dfm"
TfrmOptions *frmOptions;
//---------------------------------------------------------------------------
__fastcall TfrmOptions::TfrmOptions(TComponent* Owner)
    : TForm(Owner)
{
    
    nHeight = Height;
	nWidth = Width;

	if (gOption_Filter_Arp)
		cbArp->Checked = true;
	if (gOption_Filter_Rarp)
		cbRarp->Checked = true;
	if (gOption_Filter_Ip)
		cbIp->Checked = true;
	if (gOption_Filter_Others)
		cbOthers->Checked = true;

	if (gOption_Filter_Tcp)
		cbTcp->Checked = true;
	if (gOption_Filter_Udp)
		cbUdp->Checked = true;
	if (gOption_Filter_Icmp)
		cbIcmp->Checked = true;
	if (gOption_Filter_Igmp)
		cbIgmp->Checked = true;

	if (gOption_ClearCache)
		cbClearCache->Checked = true;
	else
		cbClearCache->Checked = false;
	if (gOption_UniqueId)
		rbUniqueId->Checked = true;
	else
		rbForceId->Checked = true;
	if (gOption_SaveBuffer)
		rbSaveBuffer->Checked = true;
	else
		rbDropBuffer->Checked = true;

	tbRecordPerPage->Position = gOption_Record_PerPage;
	stRercorPerPage->Caption = tbRecordPerPage->Position;

	if (gOption_Filter_Source_Type == OPTION_SOURCE_ALL)
	{
		rbSrcAll->Checked = true;
		edtSrcOnly->Enabled = false;
		edtSrcFrom->Enabled = false;
		edtSrcTo->Enabled = false;
	}
	else if(gOption_Filter_Source_Type == OPTION_SOURCE_ONLY)
	{
		rbSrcOnly->Checked = true;
		edtSrcFrom->Enabled = false;
		edtSrcTo->Enabled = false;
		edtSrcOnly->Enabled = true;
	}
	else
	{
		rbSrcSeg->Checked = true;
		edtSrcOnly->Enabled = false;
		edtSrcFrom->Enabled = true;
		edtSrcTo->Enabled = true;
	}

	if (gOption_Filter_Destine_Type == OPTION_DESTINE_ALL)
	{
		rbDestAll->Checked = true;
		edtDestOnly->Enabled = false;
		edtDestFrom->Enabled = false;
		edtDestTo->Enabled = false;
	}
	else if(gOption_Filter_Destine_Type == OPTION_DESTINE_ONLY)
	{
		rbDestOnly->Checked = true;
		edtDestFrom->Enabled = false;
		edtDestTo->Enabled = false;
		edtDestOnly->Enabled = true;
	}
	else
	{
		rbDestSeg->Checked = true;
		edtDestOnly->Enabled = false;
		edtDestFrom->Enabled = true;
		edtDestTo->Enabled = true;
	}
	edtSrcOnly->Text = gOption_Filter_Source_Only_Ip;
	edtSrcFrom->Text = gOption_Filter_Source_From_Ip;
	edtSrcTo->Text = gOption_Filter_Source_To_Ip;
	edtDestOnly->Text = gOption_Filter_Destine_Only_Ip;
	edtDestFrom->Text = gOption_Filter_Destine_From_Ip;
	edtDestTo->Text = gOption_Filter_Destine_To_Ip;

	cbFtp->Checked = gOption_Filter_Ftp ? true : false;
	cbSsh->Checked = gOption_Filter_Ssh ? true : false;
	cbTelnet->Checked = gOption_Filter_Telnet ? true : false;
	cbSmtp->Checked = gOption_Filter_Smtp ? true : false;
	cbDns->Checked = gOption_Filter_Dns ? true : false;
	cbGopher->Checked = gOption_Filter_Gopher ? true : false;
	cbHttp->Checked = gOption_Filter_Http ? true : false;
	cbPop3->Checked = gOption_Filter_Pop3 ? true : false;
	cbFinger->Checked = gOption_Filter_Finger ? true : false;
	cbLdap->Checked = gOption_Filter_Ldap ? true : false;
	cbTftp->Checked = gOption_Filter_Tftp ? true : false;
	cbAppOthers->Checked = gOption_Filter_AppOthers ? true : false;

    //MISC
    cbShowSplash->Checked = gOption_Show_Splash ? true : false;
    cbDispIcon->Checked = gOption_Display_Icon ? true : false;
    cbDispStatus->Checked = gOption_Display_Status ? true : false;
    cbMinStart->Checked = gOption_Min_Start ? true : false;
    cbExitConfirm->Checked = gOption_Exit_Confirm ? true : false;
    cbAutoRun->Checked = gOption_Auto_Run ? true : false;
    cbAutoSniffer->Checked = gOption_Auto_Sniffer ? true : false;
    if (cbAutoSniffer->Checked == false)
    {
        cbNicList->Enabled = false;
        edtAutoSaveFile->Enabled = false;
        btnAutoSave->Enabled = false;
    }
    edtAutoSaveFile->Text = gOption_File_Auto_Save;

    //NIC LIST
    if (cbNicList->Items->Count != 0)
        return;
    pcap_if_t *m_pNicList;

    formatPortList();
	Refresh();
        
    AnsiString szError;
    int niccount;
    m_pNicList = GetNicList(szError,niccount);
    if (m_pNicList == 0)
    {
        //ShowMsg(szError,"",MSG_ERROR);
        return;
    }
    pcap_if_t *d = m_pNicList;
	for(;d;d=d->next)
	{
        cbNicList->Items->Add(StringFormat(d->description));
	}

    if (gOption_Auto_NIC_Index >= 0 && gOption_Auto_NIC_Index < cbNicList->Items->Count)
    {
        cbNicList->ItemIndex = gOption_Auto_NIC_Index;
        cbNicList->Text = cbNicList->Items->Strings[cbNicList->ItemIndex];
    }


}
//---------------------------------------------------------------------------
void __fastcall TfrmOptions::FormCreate(TObject *Sender)
{
	Left = (Screen->Width-Width)/2;
    Top = (Screen->Height - Height)/2;
}

void TfrmOptions::Refresh()
{
	//ThemeManager->UIStyle = (TsuiUIStyle)g_nUiStyle;
    if (g_SkinFile == "")
        ThemeManager->UIStyle = (TsuiUIStyle)g_nUiStyle;
    else
    {
        AnsiString szSkinFile = DIR_ROOT + DIR_SKINS + g_SkinFile + EXT_SKIN;
        ThemeManager->UIStyle = FromThemeFile;
        ThemeManager->FileTheme->ThemeFile = szSkinFile;
    }

   	Left = (Screen->Width-Width)/2;
    Top = (Screen->Height - Height)/2;

    frmOptions->Caption = g_pLanguage->GetValue("FRMOPTION_TITLE");
    tsFilter->Caption = g_pLanguage->GetValue("FRMOPTION_PROT_FILTER_TITLE");
    gbDataLink->Caption = g_pLanguage->GetValue("FRMOPTION_PROT_FILTER_DL_TITLE");
    cbIp->Caption = g_pLanguage->GetValue("FRMOPTION_PROT_FILTER_DL_IP");
    cbArp->Caption = g_pLanguage->GetValue("FRMOPTION_PROT_FILTER_DL_ARP");
    cbRarp->Caption = g_pLanguage->GetValue("FRMOPTION_PROT_FILTER_DL_RARP");
    cbOthers->Caption = g_pLanguage->GetValue("FRMOPTION_PROT_FILTER_DL_OTHER");
    gbNetTran->Caption = g_pLanguage->GetValue("FRMOPTION_PROT_FILTER_NL_TITLE");
    cbTcp->Caption = g_pLanguage->GetValue("FRMOPTION_PROT_FILTER_NL_TCP");
    cbUdp->Caption = g_pLanguage->GetValue("FRMOPTION_PROT_FILTER_NL_UDP");
    cbIcmp->Caption = g_pLanguage->GetValue("FRMOPTION_PROT_FILTER_NL_ICMP");
    cbIgmp->Caption = g_pLanguage->GetValue("FRMOPTION_PROT_FILTER_NL_IGMP");
    gbAppLayer->Caption = g_pLanguage->GetValue("FRMOPTION_PROT_FILTER_APP_TITLE");
    cbFtp->Caption = g_pLanguage->GetValue("FRMOPTION_PROT_FILTER_APP_FTP");
    cbSsh->Caption = g_pLanguage->GetValue("FRMOPTION_PROT_FILTER_APP_SSH");
    cbTelnet->Caption = g_pLanguage->GetValue("FRMOPTION_PROT_FILTER_APP_TELNET");
    cbSmtp->Caption = g_pLanguage->GetValue("FRMOPTION_PROT_FILTER_APP_SMTP");
    cbDns->Caption = g_pLanguage->GetValue("FRMOPTION_PROT_FILTER_APP_DOMAIN");
    cbGopher->Caption = g_pLanguage->GetValue("FRMOPTION_PROT_FILTER_APP_GOPHER");
    cbHttp->Caption = g_pLanguage->GetValue("FRMOPTION_PROT_FILTER_APP_HTTP");
    cbPop3->Caption = g_pLanguage->GetValue("FRMOPTION_PROT_FILTER_APP_POP3");
    cbFinger->Caption = g_pLanguage->GetValue("FRMOPTION_PROT_FILTER_APP_FINGER");
    cbLdap->Caption = g_pLanguage->GetValue("FRMOPTION_PROT_FILTER_APP_LDAP");
    cbTftp->Caption = g_pLanguage->GetValue("FRMOPTION_PROT_FILTER_APP_TFTP");
    cbAppOthers->Caption = g_pLanguage->GetValue("FRMOPTION_PROT_FILTER_APP_OTHER");
    lblPort->Caption = g_pLanguage->GetValue("FRMOPTION_PROT_FILTER_SPECIFY_PORT");

    tsAddrFilter->Caption = g_pLanguage->GetValue("FRMOPTION_IPADDR_FILTER_TITLE");
    gbDest->Caption = g_pLanguage->GetValue("FRMOPTION_IPADDR_FILTER_SRC_TITLE");
    rbSrcAll->Caption = g_pLanguage->GetValue("FRMOPTION_IPADDR_FILTER_SRC_ALL");
    rbSrcOnly->Caption = g_pLanguage->GetValue("FRMOPTION_IPADDR_FILTER_SRC_ONLY");
    lblSrcAddr->Caption = g_pLanguage->GetValue("FRMOPTION_IPADDR_FILTER_SRC_ONLY_ADDR");
    rbSrcSeg->Caption = g_pLanguage->GetValue("FRMOPTION_IPADDR_FILTER_SRC_SEG");
    Label1->Caption = g_pLanguage->GetValue("FRMOPTION_IPADDR_FILTER_SRC_SEG_FROM");
    Label2->Caption = g_pLanguage->GetValue("FRMOPTION_IPADDR_FILTER_SRC_SEG_TO");
    gbSrc->Caption = g_pLanguage->GetValue("FRMOPTION_IPADDR_FILTER_DEST_TITLE");
    rbDestAll->Caption = g_pLanguage->GetValue("FRMOPTION_IPADDR_FILTER_DEST_ALL");
    rbDestOnly->Caption = g_pLanguage->GetValue("FRMOPTION_IPADDR_FILTER_DEST_ONLY");
    lblDestAddr->Caption = g_pLanguage->GetValue("FRMOPTION_IPADDR_FILTER_DEST_ONLY_ADDR");
    rbDestSeg->Caption = g_pLanguage->GetValue("FRMOPTION_IPADDR_FILTER_DEST_SEG");
    Label4->Caption = g_pLanguage->GetValue("FRMOPTION_IPADDR_FILTER_DEST_SEG_FROM");
    Label5->Caption = g_pLanguage->GetValue("FRMOPTION_IPADDR_FILTER_DEST_SEG_TO");
    
    tsSave->Caption = g_pLanguage->GetValue("FRMOPTION_SAVE_TITLE");
    Label3->Caption = g_pLanguage->GetValue("FRMOPTION_SAVE_RECORD");
    //stRercorPerPage->Caption = g_pLanguage->GetValue("FRMOPTION_SAVE_RECORD_PER_PAGE");
    suiGroupBox2->Caption = g_pLanguage->GetValue("FRMOPTION_SAVE_BUF");
    rbDropBuffer->Caption = g_pLanguage->GetValue("FRMOPTION_SAVE_BUF_CLEAR");
    rbSaveBuffer->Caption = g_pLanguage->GetValue("FRMOPTION_SAVE_BUF_SAVE");
    cbClearCache->Caption = g_pLanguage->GetValue("FRMOPTION_SAVE_BUF_REMOVE");
    suiGroupBox3->Caption = g_pLanguage->GetValue("FRMOPTION_SAVE_NEXT_ID");
    rbUniqueId->Caption = g_pLanguage->GetValue("FRMOPTION_SAVE_NEXT_ID_GLOBL");
    rbForceId->Caption = g_pLanguage->GetValue("FRMOPTION_SAVE_NEXT_ID_FORCE");
    btnSave->Caption = g_pLanguage->GetValue("FRMOPTION_BUTTEN_SAVE");
    btnRestore->Caption = g_pLanguage->GetValue("FRMOPTION_BUTTEN_RESET");
    btnCancel->Caption = g_pLanguage->GetValue("FRMOPTION_BUTTEN_CANCEL");

    //MISC
	tsMisc->Caption = g_pLanguage->GetValue("FRMOPTION_MISC_TITLE");		
    gbUIRules->Caption = g_pLanguage->GetValue("FRMOPTION_MISC_TITLE_INTERFACE_RULE");
    cbShowSplash->Caption = g_pLanguage->GetValue("FRMOPTION_MISC_SHOW_SPLASH");
    cbDispIcon->Caption = g_pLanguage->GetValue("FRMOPTION_MISC_DISPLAY_ICON");
    cbDispStatus->Caption = g_pLanguage->GetValue("FRMOPTION_MISC_DISPLAY_STATUS");
    cbMinStart->Caption = g_pLanguage->GetValue("FRMOPTION_MISC_MIN_START");
    cbExitConfirm->Caption = g_pLanguage->GetValue("FRMOPTION_MISC_EXIT_CONFIRM");
    gbAutoSave->Caption = g_pLanguage->GetValue("FRMOPTION_MISC_TITLE_AUTO_SAVE");
    cbAutoRun->Caption = g_pLanguage->GetValue("FRMOPTION_MISC_AUTO_RUN");
    cbAutoSniffer->Caption = g_pLanguage->GetValue("FRMOPTION_MISC_AUTO_SNIFFER");
    lblAutoSaveFile->Caption = g_pLanguage->GetValue("FRMOPTION_MISC_AUTO_SAVE_FILE");
    gbHotKey->Caption = g_pLanguage->GetValue("FRMOPTION_MISC_TITLE_HOT_KEY");
    lblKeyDispMain->Caption = g_pLanguage->GetValue("FRMOPTION_MISC_HOT_KEY_MAIN");
    lblKeyDispStatus->Caption = g_pLanguage->GetValue("FRMOPTION_MISC_HOT_KEY_STATUS");
    lblNicList->Caption = g_pLanguage->GetValue("FRMOPTION_MISC_AUTO_NIC");
    if (cbNicList->Text == "")
        cbNicList->Text = g_pLanguage->GetValue("FRMOPTION_MISC_AUTO_SELECT_ONE");
}
//---------------------------------------------------------------------------
void __fastcall TfrmOptions::FormResize(TObject *Sender)
{
    Width = nWidth;
    Height = nHeight;
    
	Left = (Screen->Width-Width)/2;
    Top = (Screen->Height - Height)/2;

    //Width = 682;
    //Height = 444;
}
//---------------------------------------------------------------------------

void __fastcall TfrmOptions::btnSaveClick(TObject *Sender)
{
	//validation check
    AnsiString errport=0;
    edtPorts->Text = SpaceFilter(edtPorts->Text);
    if (!PortParser(edtPorts->Text,errport))
    {
        if (errport == "")
        {
            ShowMsg(g_pLanguage->GetValue("FRMOPTION_PROT_FILTER_INVALID_PORT_LIST"));
            edtPorts->Focused();
            //edtPorts->SelectAll();
            return;
        }
        else
        {
            ShowMsg(g_pLanguage->GetValue("FRMOPTION_PROT_FILTER_INVALID_PORT_NUMBER") + AnsiString(errport) + g_pLanguage->GetValue("FRMOPTION_PROT_FILTER_PORT_RANGE"));
            //edtPorts->SelStart = 0;
            return;
        }
    }
    formatPortList();  

	TIpAddr IpAddr1,IpAddr2;
	//src
	if (rbSrcOnly->Checked)
	{
		if (edtSrcOnly->Text == "")
		{
			ShowMsg(g_pLanguage->GetValue("ALERT_OPTIONSWIN_ADDRESS_NOT_NULL"));
			return;
		}
		IpAddr1 = edtSrcOnly->Text;

		if ( !IpAddr1.IsValid())
		{
			ShowMsg(edtSrcOnly->Text + g_pLanguage->GetValue("ALERT_OPTIONSWIN_IP_ADDRESS_INVALID"));
			return;
		}
	}
	if (rbSrcSeg->Checked)
	{
		if (edtSrcFrom->Text == "" || edtSrcTo->Text == "")
		{
			ShowMsg(g_pLanguage->GetValue("ALERT_OPTIONSWIN_ADDRESS_NOT_NULL"));
			return;
		}
		IpAddr1 = edtSrcFrom->Text;
		IpAddr2 = edtSrcTo->Text;
		if (!IpAddr1.IsValid())
		{
			ShowMsg(edtSrcFrom->Text + g_pLanguage->GetValue("ALERT_OPTIONSWIN_IP_ADDRESS_INVALID"));
			return;
		}
		if (!IpAddr2.IsValid())
		{
			ShowMsg(edtSrcTo->Text + g_pLanguage->GetValue("ALERT_OPTIONSWIN_IP_ADDRESS_INVALID"));
			return;
		}
		if (IpAddr1 > IpAddr2)
		{   //ALERT_OPTIONSWIN_FROM_SHOULD_LESS_TO
			ShowMsg(edtSrcFrom->Text + g_pLanguage->GetValue("ALERT_OPTIONSWIN_FROM_SHOULD_LESS_TO") + edtSrcTo->Text);
			return;
		}
	}

	//dest
	if (rbDestOnly->Checked)
	{
		if (edtDestOnly->Text == "")
		{
			ShowMsg(g_pLanguage->GetValue("ALERT_OPTIONSWIN_ADDRESS_NOT_NULL"));
			return;
		}
		IpAddr1 = edtDestOnly->Text;

		if ( !IpAddr1.IsValid())
		{
			ShowMsg(edtDestOnly->Text + g_pLanguage->GetValue("ALERT_OPTIONSWIN_IP_ADDRESS_INVALID"));
			return;
		}
	}
	if (rbDestSeg->Checked)
	{
		if (edtDestFrom->Text == "" || edtDestTo->Text == "")
		{
			ShowMsg(g_pLanguage->GetValue("ALERT_OPTIONSWIN_ADDRESS_NOT_NULL"));
			return;
		}
		IpAddr1 = edtDestFrom->Text;
		IpAddr2 = edtDestTo->Text;
		if (!IpAddr1.IsValid())
		{
			ShowMsg(edtDestFrom->Text + g_pLanguage->GetValue("ALERT_OPTIONSWIN_IP_ADDRESS_INVALID"));
			return;
		}
		if (!IpAddr2.IsValid())
		{
			ShowMsg(edtDestTo->Text + g_pLanguage->GetValue("ALERT_OPTIONSWIN_IP_ADDRESS_INVALID"));
			return;
		}
		if (IpAddr1 > IpAddr2)
		{   //ALERT_OPTIONSWIN_FROM_SHOULD_LESS_TO
			ShowMsg(edtDestFrom->Text + g_pLanguage->GetValue("ALERT_OPTIONSWIN_FROM_SHOULD_LESS_TO") + edtDestTo->Text);
			return;
		}
	}

    if (cbAutoSniffer->Checked)
    {
        if (cbNicList->ItemIndex < 0)
        {
            ShowMsg(g_pLanguage->GetValue("ERROR_SELECT_ONE_NIC"));
            pcOptions->ActivePage = tsMisc;
            cbNicList->Focused();
            cbNicList->DroppedDown = true;
            return;
        }
    }

	if (rbSrcAll->Checked)
		gOption_Filter_Source_Type = OPTION_SOURCE_ALL;
	else if (rbSrcOnly->Checked)
	{
		gOption_Filter_Source_Type = OPTION_SOURCE_ONLY;
	}
	else
		gOption_Filter_Source_Type = OPTION_SOURCE_SEGMENT;

	if (rbDestAll->Checked)
		gOption_Filter_Destine_Type = OPTION_DESTINE_ALL;
	else if (rbDestOnly->Checked)
		gOption_Filter_Destine_Type = OPTION_DESTINE_ONLY;
	else
		gOption_Filter_Destine_Type = OPTION_DESTINE_SEGMENT;

	gOption_Filter_Arp = cbArp->Checked;
	gOption_Filter_Rarp = cbRarp->Checked;
	gOption_Filter_Ip = cbIp->Checked;
	gOption_Filter_Others = cbOthers->Checked;

	gOption_Filter_Tcp = cbTcp->Checked;
	gOption_Filter_Udp = cbUdp->Checked;
	gOption_Filter_Icmp = cbIcmp->Checked;
	gOption_Filter_Igmp = cbIgmp->Checked;

	gOption_ClearCache = cbClearCache->Checked;
	gOption_UniqueId = rbUniqueId->Checked;
	gOption_SaveBuffer = rbSaveBuffer->Checked;
	gOption_Record_PerPage = tbRecordPerPage->Position;

	gOption_Filter_Ftp = cbFtp->Checked;
	gOption_Filter_Ssh = cbSsh->Checked;
	gOption_Filter_Telnet = cbTelnet->Checked ;
	gOption_Filter_Smtp = cbSmtp->Checked;
	gOption_Filter_Dns = cbDns->Checked;
	gOption_Filter_Gopher = cbGopher->Checked ;
	gOption_Filter_Http = cbHttp->Checked;
	gOption_Filter_Pop3 = cbPop3->Checked;
	gOption_Filter_Finger = cbFinger->Checked;
	gOption_Filter_Ldap = cbLdap->Checked;
	gOption_Filter_Tftp = cbTftp->Checked;
	gOption_Filter_AppOthers = cbAppOthers->Checked;

	if (gOption_ClearCache)
		cbClearCache->Checked = true;
	else
		cbClearCache->Checked = false;
	if (gOption_UniqueId)
		rbUniqueId->Checked = true;
	else
		rbUniqueId->Checked = false;
	if (gOption_UniqueId)
		rbUniqueId->Checked = true;
	else
		rbUniqueId->Checked = false;
	if (gOption_SaveBuffer)
		rbSaveBuffer->Checked = true;
	else
		rbSaveBuffer->Checked = false;
	tbRecordPerPage->Position = gOption_Record_PerPage;

	gOption_Filter_Source_Only_Ip = edtSrcOnly->Text;
	gOption_Filter_Source_From_Ip = edtSrcFrom->Text;
	gOption_Filter_Source_To_Ip = edtSrcTo->Text;
	gOption_Filter_Destine_Only_Ip = edtDestOnly->Text;
	gOption_Filter_Destine_From_Ip = edtDestFrom->Text;
	gOption_Filter_Destine_To_Ip = edtDestTo->Text;
	//add code to here to save options
	gOption_Show_Splash = (int)cbShowSplash->Checked;
	gOption_Display_Icon = (int)cbDispIcon->Checked;
	gOption_Display_Status = (int)cbDispStatus->Checked;
	gOption_Min_Start = (int)cbMinStart->Checked;
	gOption_Exit_Confirm = (int)cbExitConfirm->Checked;
	gOption_Auto_Run = (int)cbAutoRun->Checked;
	gOption_Auto_Sniffer = (int)cbAutoSniffer->Checked;
	gOption_File_Auto_Save = edtAutoSaveFile->Text;
    gOption_Auto_NIC_Index = cbNicList->ItemIndex;

	SetSystemVariable(SECTION_OPTOINS,"Arp",gOption_Filter_Arp);
	SetSystemVariable(SECTION_OPTOINS,"Rarp",gOption_Filter_Rarp);
	SetSystemVariable(SECTION_OPTOINS,"Ip",gOption_Filter_Ip);
	SetSystemVariable(SECTION_OPTOINS,"Others",gOption_Filter_Others);
	SetSystemVariable(SECTION_OPTOINS,"Tcp",gOption_Filter_Tcp);
	SetSystemVariable(SECTION_OPTOINS,"Udp",gOption_Filter_Udp);
	SetSystemVariable(SECTION_OPTOINS,"Icmp",gOption_Filter_Icmp);
	SetSystemVariable(SECTION_OPTOINS,"Igmp",gOption_Filter_Igmp);

	SetSystemVariable(SECTION_OPTOINS,"Ftp",gOption_Filter_Ftp);
	SetSystemVariable(SECTION_OPTOINS,"Ssh",gOption_Filter_Ssh);
	SetSystemVariable(SECTION_OPTOINS,"Dns",gOption_Filter_Dns);
	SetSystemVariable(SECTION_OPTOINS,"Telnet",gOption_Filter_Telnet);
	SetSystemVariable(SECTION_OPTOINS,"Smtp",gOption_Filter_Smtp);
	SetSystemVariable(SECTION_OPTOINS,"Gopher",gOption_Filter_Gopher);
	SetSystemVariable(SECTION_OPTOINS,"Http",gOption_Filter_Http);
	SetSystemVariable(SECTION_OPTOINS,"Pop3",gOption_Filter_Pop3);
	SetSystemVariable(SECTION_OPTOINS,"Finger",gOption_Filter_Finger);
	SetSystemVariable(SECTION_OPTOINS,"Ldap",gOption_Filter_Ldap);
	SetSystemVariable(SECTION_OPTOINS,"Tftp",gOption_Filter_Tftp);
	SetSystemVariable(SECTION_OPTOINS,"AppOthers",gOption_Filter_AppOthers);

    //gOption_Filter_Dns
	SetSystemVariable(SECTION_OPTOINS,"Source_Type",gOption_Filter_Source_Type);
	SetSystemVariable(SECTION_OPTOINS,"Destine_Type",gOption_Filter_Destine_Type);

	SetSystemVariable(SECTION_OPTOINS,"Source_Only",gOption_Filter_Source_Only_Ip);
	SetSystemVariable(SECTION_OPTOINS,"Source_From",gOption_Filter_Source_From_Ip);
	SetSystemVariable(SECTION_OPTOINS,"Source_To",gOption_Filter_Source_To_Ip);

	SetSystemVariable(SECTION_OPTOINS,"Destine_Only",gOption_Filter_Destine_Only_Ip);
	SetSystemVariable(SECTION_OPTOINS,"Destine_From",gOption_Filter_Destine_From_Ip);
	SetSystemVariable(SECTION_OPTOINS,"Destine_To",gOption_Filter_Destine_To_Ip);

	SetSystemVariable(SECTION_OPTOINS,"Record_PerPage",gOption_Record_PerPage);
	SetSystemVariable(SECTION_OPTOINS,"Clear_Cache",AnsiString(gOption_ClearCache));
	SetSystemVariable(SECTION_OPTOINS,"Unique_Id",gOption_UniqueId);
	SetSystemVariable(SECTION_OPTOINS,"Save_Buffer",gOption_SaveBuffer);
    SetSystemVariable(SECTION_OPTOINS,"Specify_Port",edtPorts->Text);

    //MISC
    SetSystemVariable(SECTION_OPTOINS,"Display_Splash",(int)cbShowSplash->Checked);
    SetSystemVariable(SECTION_OPTOINS,"Display_Icon",(int)cbDispIcon->Checked);
    SetSystemVariable(SECTION_OPTOINS,"Display_Status",(int)cbDispStatus->Checked);
    SetSystemVariable(SECTION_OPTOINS,"Min_Start",(int)cbMinStart->Checked);
    SetSystemVariable(SECTION_OPTOINS,"Exit_Confirm",(int)cbExitConfirm->Checked);
    SetSystemVariable(SECTION_OPTOINS,"Auto_Run",(int)cbAutoRun->Checked);
    SetSystemVariable(SECTION_OPTOINS,"Auto_Sniffer",(int)cbAutoSniffer->Checked);
    SetSystemVariable(SECTION_OPTOINS,"File_Auto_Save",edtAutoSaveFile->Text);
    SetSystemVariable(SECTION_OPTOINS,"Auto_NIC_Index",cbNicList->ItemIndex);

    if (gOption_Auto_Run)
        SetAutoRun();
    else
        UnsetAutoRun();

    ShowMsg(g_pLanguage->GetValue("TEXT_OPTIONSWIN_SAVE_CONFIGURE_OK"));
	Close();
}
//---------------------------------------------------------------------------

void __fastcall TfrmOptions::btnCancelClick(TObject *Sender)
{
	//ThemeManager->UIStyle = g_nUiStyle;
    Close();
    //Refresh();
}
//---------------------------------------------------------------------------


void __fastcall TfrmOptions::rbSrcOnlyClick(TObject *Sender)
{
	edtSrcFrom->Enabled = false;
	edtSrcTo->Enabled = false;
	edtSrcOnly->Enabled = true;
}
//---------------------------------------------------------------------------

void __fastcall TfrmOptions::rbSrcSegClick(TObject *Sender)
{
	edtSrcOnly->Enabled = false;
	edtSrcFrom->Enabled = true;
	edtSrcTo->Enabled = true;
}
//---------------------------------------------------------------------------

void __fastcall TfrmOptions::rbDestOnlyClick(TObject *Sender)
{
	edtDestOnly->Enabled = true;
	edtDestFrom->Enabled = false;
	edtDestTo->Enabled = false;
}
//---------------------------------------------------------------------------

void __fastcall TfrmOptions::rbDestSegClick(TObject *Sender)
{
	edtDestOnly->Enabled = false;
	edtDestFrom->Enabled = true;
	edtDestTo->Enabled = true;

}
//---------------------------------------------------------------------------

void __fastcall TfrmOptions::btnRestoreClick(TObject *Sender)
{
	if (MsgBox(g_pLanguage->GetValue("ALERT_OPTIONSWIN_RESET_CONFRIM")) == mrNo)
		return;

	rbSrcAll->Checked = true;
	rbDestAll->Checked = true;
	edtDestOnly->Enabled = false;
	edtDestFrom->Enabled = false;
	edtDestTo->Enabled = false;
	edtSrcOnly->Enabled = false;
	edtSrcFrom->Enabled = false;
	edtSrcTo->Enabled = false;

	cbIp->Checked = true;
	cbArp->Checked = true;
	cbRarp->Checked = true;
	cbOthers->Checked = true;
	cbTcp->Checked = true;
	cbUdp->Checked = true;
	cbIcmp->Checked = true;
	cbIgmp->Checked = true;

	cbClearCache->Checked = true;
	rbUniqueId->Checked = true;
	rbSaveBuffer->Checked = true;
	cbFtp->Checked = true;
	cbSsh->Checked = true;
	cbTelnet->Checked = true;
	cbSmtp->Checked = true;
	cbDns->Checked = true;
	cbGopher->Checked = true;
	cbHttp->Checked = true;
	cbPop3->Checked = true;
	cbFinger->Checked = true;
	cbLdap->Checked = true;
	cbTftp->Checked = true;
	cbAppOthers->Checked = true;

	tbRecordPerPage->Position = DEFAULT_RECORD_COUNT_PERPAGE;

    //MISC
    cbShowSplash->Checked = true;
    cbDispIcon->Checked = true;
    cbDispStatus->Checked = true;
    cbMinStart->Checked = false;
    cbExitConfirm->Checked = true;
    cbAutoRun->Checked = false;
    edtAutoSaveFile->Enabled = false;
    cbAutoSniffer->Checked = false;
    cbNicList->Enabled = false;
    edtAutoSaveFile->Text = DIR_ROOT + DIR_SAVE + FILE_AUTOSAVE;
    
}
//---------------------------------------------------------------------------

void __fastcall TfrmOptions::rbSrcAllClick(TObject *Sender)
{
	edtSrcOnly->Enabled = false;
	edtSrcFrom->Enabled = false;
	edtSrcTo->Enabled = false;
}
//---------------------------------------------------------------------------


void __fastcall TfrmOptions::rbDestAllClick(TObject *Sender)
{
	edtDestOnly->Enabled = false;
	edtDestFrom->Enabled = false;
	edtDestTo->Enabled = false;

}
//---------------------------------------------------------------------------




void __fastcall TfrmOptions::tbRecordPerPageChange(TObject *Sender)
{
	stRercorPerPage->Caption = tbRecordPerPage->Position;	
}
//---------------------------------------------------------------------------



void __fastcall TfrmOptions::cbIpClick(TObject *Sender)
{
	if (!cbIp->Checked)
	{
		cbTcp->Checked = false;
		cbUdp->Checked = false;
		cbIcmp->Checked = false;
		cbIgmp->Checked = false;
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmOptions::cbTcpUdpClick(TObject *Sender)
{
	if (cbTcp->Checked == false && cbUdp->Checked == false)
	{
		cbFtp->Checked = false;
		cbSsh->Checked = false;
		cbTelnet->Checked = false;
		cbSmtp->Checked = false;
		cbDns->Checked = false;
		cbGopher->Checked = false;
		cbHttp->Checked = false;
		cbPop3->Checked = false;
		cbFinger->Checked = false;
		cbLdap->Checked = false;
		cbTftp->Checked = false;
		cbAppOthers->Checked = false;
	}
}
//---------------------------------------------------------------------------

void TfrmOptions::formatPortList()
{
    int cnt;
    AnsiString szPorts = "";
    edtPorts->Text = "";
    for (cnt=0; cnt<g_pSpecify_Ports[0]; cnt++)
    {
        if (szPorts != "")
            szPorts += ",";
        szPorts +=  IntToStr(g_pSpecify_Ports[cnt+1]);
    }
    edtPorts->Text = szPorts;
}
void __fastcall TfrmOptions::btnAutoSaveClick(TObject *Sender)
{
    dlgSaveAutoSave->InitialDir = DIR_ROOT + DIR_SAVE;
    if (dlgSaveAutoSave->Execute())
    {
        if (FileExists(dlgSaveAutoSave->FileName))
        {
            TModalResult mrRet;
            mrRet = MsgBox(g_pLanguage->GetValue("TEXT_MESSAGE_AUTO_SAVE_FILE_EXITST"),"",2,MSG_HELP);
            if (mrRet == mrYes)
            {
                edtAutoSaveFile->Text = dlgSaveAutoSave->FileName;
            }
        }
        else
            edtAutoSaveFile->Text = dlgSaveAutoSave->FileName;

    }
}
//---------------------------------------------------------------------------






void __fastcall TfrmOptions::cbAutoSnifferClick(TObject *Sender)
{
    if (cbAutoSniffer->Checked == false)
    {
        edtAutoSaveFile->Enabled = false;
        cbNicList->Enabled = false;
        btnAutoSave->Enabled = false;
    }
    else
    {
        edtAutoSaveFile->Enabled = true;
        cbNicList->Enabled = true;
        btnAutoSave->Enabled = true;
    }
}
//---------------------------------------------------------------------------





void __fastcall TfrmOptions::edtMainHotKeyKeyPress(TObject *Sender,
      char &Key)
{
/*    AnsiString szKey;
    if (Key & VK_SHIFT )
    {
        szKey ="<Shift>+";
        Key = Key & (~VK_SHIFT);
    }

    szKey += Key;
    edtMainHotKey->Text = szKey;
*/
}
//---------------------------------------------------------------------------




