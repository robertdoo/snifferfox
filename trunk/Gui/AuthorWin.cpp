//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "AuthorWin.h"
#include "Language.h"
#include "Global.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "SUIButton"
#pragma link "SUIForm"
#pragma link "SUIURLLabel"
#pragma link "SUIMgr"
#pragma resource "*.dfm"
TfrmAuthor *frmAuthor;
//---------------------------------------------------------------------------
__fastcall TfrmAuthor::TfrmAuthor(TComponent* Owner)
	: TForm(Owner)
{
	Left = (Screen->Width-Width)/2;
    Top = (Screen->Height - Height)/2;
	Refresh();
}
//---------------------------------------------------------------------------

void __fastcall TfrmAuthor::suiButton1Click(TObject *Sender)
{
	Close();	
}
//---------------------------------------------------------------------------


void TfrmAuthor::Refresh()
{
	lblVersion->Caption = g_pLanguage->GetValue("TEXT_SOFTWARE_VERSION");

    if (g_SkinFile == "")
        ThemeManager->UIStyle = (TsuiUIStyle)g_nUiStyle;
    else
    {
        AnsiString szSkinFile = DIR_ROOT + DIR_SKINS + g_SkinFile + EXT_SKIN;
        ThemeManager->UIStyle = FromThemeFile;
        ThemeManager->FileTheme->ThemeFile = szSkinFile;
    }
}





