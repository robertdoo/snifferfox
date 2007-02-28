//---------------------------------------------------------------------------


#pragma hdrstop

#include "MsgDialog.h"
#include "SUIMainMenu.hpp"
#include <Menus.hpp>
#include "SUIGrid.hpp"
#include <Grids.hpp>
#include "SUIButton.hpp"
#include "SUIPageControl.hpp"
#include "SUITabControl.hpp"
#include "SUIMgr.hpp"
#include "SUIPopupMenu.hpp"
#include "SUIToolBar.hpp"
#include <ComCtrls.hpp>
#include <ToolWin.hpp>
#include "SUIGroupBox.hpp"
#include "SUIImagePanel.hpp"
#include "SUIComboBox.hpp"
#include "SUIListBox.hpp"
#include "RecvThread.h"
#include "SUIDlg.hpp"
#include "SUIEdit.hpp"
#include "SUIScrollBar.hpp"
#include "SUIMemo.hpp"
#include "Functions.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)

void ShowMsg(AnsiString msg,AnsiString title,int msgtype)
{
    MsgBox(msg,title,1,msgtype);
}
int MsgBox(AnsiString msg,AnsiString title,int nBtnCnt,int msgtype)
//msg:message
//nBtncnt:Button Count
{
    TsuiFileTheme *pThemeFile = new TsuiFileTheme(Application);
    TsuiMessageDialog *MsgDlg;
    MsgDlg = new TsuiMessageDialog(0);

    if (g_SkinFile == "")
        MsgDlg->UIStyle = (TsuiUIStyle)g_nUiStyle;
    else
    {
        MsgDlg->UIStyle = FromThemeFile;
        MsgDlg->FileTheme = new TsuiFileTheme(Application);
        MsgDlg->FileTheme->ThemeFile = DIR_ROOT + DIR_SKINS + g_SkinFile + EXT_SKIN;
        //pThemeFile->ThemeFile = DIR_ROOT + DIR_SKINS + g_SkinFile + EXT_SKIN;
    }

    if (title == "")
       title = g_pLanguage->GetValue("TEXT_DIALOG_DEFAULT_TITLE");
    MsgDlg->Caption = title;
    MsgDlg->ButtonCount = nBtnCnt;
    MsgDlg->Text = msg;
    switch (msgtype)
    {
		case MSG_HELP:
            MsgDlg->IconType = Suidlg::suiHelp;
            break;
		case MSG_INFO:
            MsgDlg->IconType = suiInformation;
            break;
		case MSG_STOP:
            MsgDlg->IconType = suiStop;
            break;
		case MSG_WARNING:
            MsgDlg->IconType = suiWarning;
            break;
		case MSG_NONE:
            MsgDlg->IconType = suiNone;
            break;
    }

    if (nBtnCnt > 3)
       nBtnCnt = 1;
    if (nBtnCnt == 1)
    {
       MsgDlg->Button1Caption = g_pLanguage->GetValue("TEXT_DIALOG_BUTTON_OK");
       MsgDlg->Button1ModalResult = mrOk;
    }
    if (nBtnCnt == 2)
    {
        MsgDlg->Button1ModalResult = mrYes;
        MsgDlg->Button2ModalResult = mrNo;
        MsgDlg->Button1Caption = g_pLanguage->GetValue("TEXT_DIALOG_BUTTON_YES");
        MsgDlg->Button2Caption = g_pLanguage->GetValue("TEXT_DIALOG_BUTTON_NO");
     }
     if (nBtnCnt == 3)
     {
        MsgDlg->Button1Caption = g_pLanguage->GetValue("TEXT_DIALOG_BUTTON_YES");
        MsgDlg->Button2Caption = g_pLanguage->GetValue("TEXT_DIALOG_BUTTON_NO");
        MsgDlg->Button3Caption = g_pLanguage->GetValue("TEXT_DIALOG_BUTTON_CANCEL");
        MsgDlg->Button1ModalResult = mrYes;
        MsgDlg->Button2ModalResult = mrNo;
        MsgDlg->Button3ModalResult = mrCancel;
     }
     delete pThemeFile;
     return MsgDlg->ShowModal();
}