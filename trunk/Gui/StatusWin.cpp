//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "StatusWin.h"
//#include "MainWin.h"
#include "Constant.h"
#include "Global.h"


//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "SUIForm"
#pragma link "SUIMgr"
#pragma link "SUIPopupMenu"
#pragma resource "*.dfm"
TfrmStatus *frmStatus;
//---------------------------------------------------------------------------
__fastcall TfrmStatus::TfrmStatus(TComponent* Owner)
	: TForm(Owner)
{
    Width = 224;
    frmStatus->Width = Width;
    frmStatus->Height = Height;
    //Height = 62;

 	Top = 1;
	Left = Screen->Width - Width - 70;
	Refresh();  
}
//---------------------------------------------------------------------------

void TfrmStatus::Refresh()
{
    lblStatus->Caption = g_pLanguage->GetValue("FRMSTATUS_LBLSTATUS");
    lblTotal->Caption = g_pLanguage->GetValue("FRMSTATUS_LBLSAVE");
    lblDrop->Caption = g_pLanguage->GetValue("FRMSTATUS_LBLDROP");

	if (Visible == false)
		return;
    if (g_SkinFile == "")
    {
        if ((TsuiUIStyle)g_nUiStyle == BlueGlass)
            ThemeManager->UIStyle = Protein;
        else
            ThemeManager->UIStyle = (TsuiUIStyle)g_nUiStyle;
    }//  ThemeManager->UIStyle = (TsuiUIStyle)g_nUiStyle;
    else
    {
        ThemeManager->UIStyle = Protein;
    }

/*
    else
    {
        AnsiString szSkinFile = DIR_ROOT + DIR_SKINS + g_SkinFile + EXT_SKIN;
        ThemeManager->UIStyle = FromThemeFile;
        ThemeManager->FileTheme->ThemeFile = szSkinFile;
    }
*/

	static bool running = true;
	lblTotalCount->Caption = g_nSaveCount;
	lblDropCount->Caption = g_nTotalCount - g_nSaveCount;
	if (g_bThreadIsRun == running)
	{
		running = g_bThreadIsRun;
		return;
	}
	if (g_bThreadIsRun == true)
		imgStatus->Picture->LoadFromFile(DIR_ROOT+DIR_IMAGES+FILE_ACTIVE);
	else
		imgStatus->Picture->LoadFromFile(DIR_ROOT+DIR_IMAGES+FILE_INACTIVE);
    running = g_bThreadIsRun;
}




void __fastcall TfrmStatus::TimerTimer(TObject *Sender)
{
	Refresh();
}
//---------------------------------------------------------------------------




void __fastcall TfrmStatus::frmStatusMouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
	if(Button == mbLeft)
	{
		ReleaseCapture();
		SendMessage( Handle, WM_NCLBUTTONDOWN, HTCAPTION, 0);
	} 
}
//---------------------------------------------------------------------------




void __fastcall TfrmStatus::miHideClick(TObject *Sender)
{
	Hide();	
}
//---------------------------------------------------------------------------









