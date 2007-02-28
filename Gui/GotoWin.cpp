//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "GotoWin.h"
#include "Global.h"
#include "Constant.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "SUIButton"
#pragma link "SUIForm"
#pragma link "SUITrackBar"
#pragma link "SUIMgr"
#pragma resource "*.dfm"
TfrmGoto *frmGoto;
//---------------------------------------------------------------------------
__fastcall TfrmGoto::TfrmGoto(TComponent* Owner)
    : TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TfrmGoto::FormCreate(TObject *Sender)
{
	Left = (Screen->Width-Width)/2;
    Top = (Screen->Height - Height)/2;
	//ThemeManager->UIStyle = (TsuiUIStyle)g_nUiStyle;
    frmGoto->Caption = g_pLanguage->GetValue("FRMGOTO_CAPTION");
    btnOk->Caption = g_pLanguage->GetValue("FRMGOTO_BUTTON_OK");
    lblPos->Caption = g_pLanguage->GetValue("FRMGOTO_POSITION");

    if (g_SkinFile == "")
        ThemeManager->UIStyle = (TsuiUIStyle)g_nUiStyle;
    else
    {
        AnsiString szSkinFile = DIR_ROOT + DIR_SKINS + g_SkinFile + EXT_SKIN;
        ThemeManager->UIStyle = FromThemeFile;
        ThemeManager->FileTheme->ThemeFile = szSkinFile;
    }

}
//---------------------------------------------------------------------------

void __fastcall TfrmGoto::btnOkClick(TObject *Sender)
{
    ModalResult = trPos->Position + 100;
}
//---------------------------------------------------------------------------
void __fastcall TfrmGoto::trPosChange(TObject *Sender)
{
    lblPosPer->Caption = AnsiString(trPos->Position) + "%";
    //lblPosPer->Caption += "%";
}
//---------------------------------------------------------------------------
