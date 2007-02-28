// Author: zhengsh
// Date: 2005/10/03 01:30:37 
// $Id: SnifferFox.cpp,v 1.22 2006/10/02 16:44:24 zhengsh Exp $

//---------------------------------------------------------------------------

#include <vcl.h>
#include "..\Core\Functions.h"
#include "StatusWin.h"
#include "CoverWin.h"
#include "Constant.h"
#include "MsgDialog.h"

#pragma hdrstop


//---------------------------------------------------------------------------
USEFORM("..\Gui\MainWin.cpp", frmMain);
USEFORM("..\Gui\OptionsWin.cpp", frmOptions);
USEFORM("..\Gui\NicDetail.cpp", frmNicDetail);
USEFORM("..\Gui\StatisticWin.cpp", frmStatistic);
USEFORM("..\Gui\StatusWin.cpp", frmStatus);
USEFORM("..\Gui\CoverWin.cpp", frmCover);
USEFORM("..\Gui\AuthorWin.cpp", frmAuthor);
USEFORM("..\Gui\GotoWin.cpp", frmGoto);
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
      	SystemInitialize();
		//TfrmStatus *frmStatus = new TfrmStatus(0);
		//frmStatus->Show();
        int NicCount;

        HWND hWnd;
        hWnd = FindWindow(NULL,SOFTWARE_TITLE_CAPTION.c_str());
        if (hWnd)
        {
        	ShowMsg(g_pLanguage->GetValue("ERROR_SNIFFERFOX_IS_RUNNING"),"",MSG_ERROR);
        	//BringWindowToTop(hWnd);
            //SetActiveWindow(hWnd);
            return 0;
        }
        AnsiString(szError);
        GetNicList(szError,NicCount);
        if ( NicCount == 0)
        {
            if (gOption_Run_First_Time)
            {
                ShowMsg(g_pLanguage->GetValue("TEXT_RUN_FIRST_TIME"));
                WaitForExec((DIR_ROOT + DIR_BIN + FILE_WINPCAP).c_str());
                ShowMsg(g_pLanguage->GetValue("TEXT_RESTART_PLEASE"));
                return 0;
            }
            else
            {
                if (MsgBox(g_pLanguage->GetValue("ERROR_NO_NETWORK_CARD_FOUND"),"",2,MSG_ERROR) == mrYes)
                {
                    AnsiString FileName = DIR_ROOT + DIR_BIN + FILE_WINPCAP;
                    if (FileExists(FileName))
                    {
                        WaitForExec(FileName.c_str());
                        ShowMsg(g_pLanguage->GetValue("TEXT_RESTART_PLEASE"));
                        return 0;
                    }
                    else
                    {
                        ShowMsg(g_pLanguage->GetValue("ALERT_MAINWIN_FILE_NOT_EXISTS") + FileName + AnsiString("\n") + \
                            g_pLanguage->GetValue("ALERT_MAINWIN_DOWNLOAD_WINPCAP"),g_pLanguage->GetValue("TEXT_MESSAGE_FILE_LOST"),MSG_ERROR);
                    }
                }
            }
        }

        try
        {
            if (gOption_Show_Splash)
            {
		        TfrmCover *frmCover = new TfrmCover(0);
    		    frmCover->ShowSplash();
	        //frmCover->Update();
		//Sleep(SPLASH_TIME);
                delete frmCover;
            }

            Application->Initialize();
		    Application->Title = SOFTWARE_TITLE_CAPTION;
		    Application->CreateForm(__classid(TfrmMain), &frmMain);
            Application->Run();

		}
        catch (Exception &exception)
        {
                 Application->ShowException(&exception);
        }
        catch (...)
        {
                 try
                 {
                         throw Exception("");
                 }
                 catch (Exception &exception)
                 {
                         Application->ShowException(&exception);
                 }
		}
        SystemDestory();
		//delete frmStatus;
		return 0;
}
//---------------------------------------------------------------------------
