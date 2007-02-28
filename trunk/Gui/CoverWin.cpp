//---------------------------------------------------------------------------

#pragma hdrstop
#include <vcl.h>

#include "CoverWin.h"
#include "Constant.h"
#include "Global.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfrmCover *frmCover;
//---------------------------------------------------------------------------
__fastcall TfrmCover::TfrmCover(TComponent* Owner)
	: TForm(Owner)
{
	Left = (Screen->Width-Width)/2;
    Top = (Screen->Height - Height)/2;
    lblSoftName->Caption = g_pLanguage->GetValue("TEXT_SOFTWARE_NAME");
}
//---------------------------------------------------------------------------
void __fastcall TfrmCover::FormCreate(TObject *Sender)
{


    //Sleep(500);
    //SetWindowLong(Handle, GWL_EXSTYLE, lRt);
    //SetLayeredWindowAttributes(Handle,clBlue,255,LWA_ALPHA);
	//Image1->LoadFromFile(g_SysPath+IMAGE_DIR+"cover.jpg");
}
//---------------------------------------------------------------------------
void __fastcall TfrmCover::Image1Click(TObject *Sender)
{
    long lRt = GetWindowLong(Handle,GWL_EXSTYLE);
    lRt = lRt | WS_EX_LAYERED;
    for (int cnt=255;cnt > 100;cnt-=20)
    {
        SetWindowLong(Handle, GWL_EXSTYLE, lRt);
        SetLayeredWindowAttributes(Handle,clBlue,cnt,LWA_ALPHA);
        Visible = true;
        this->Repaint();
        Sleep(100);
    }
    Visible = false;
	ModalResult=IDOK;
}
//---------------------------------------------------------------------------

void TfrmCover::CloseWindow()
{
	ModalResult=IDOK;
}

void TfrmCover::ShowSplash(int para)
{
    Visible = true;
    long lRt = GetWindowLong(Handle,GWL_EXSTYLE);
    lRt = lRt | WS_EX_LAYERED;
    for (int cnt=100;cnt <= 255;cnt+=20)
    {
        int tmp = cnt;
        if (cnt > 255)
            tmp = 255 - (cnt - 255);
        SetWindowLong(Handle, GWL_EXSTYLE, lRt);
        SetLayeredWindowAttributes(Handle,clBlue,tmp,LWA_ALPHA);
        this->Repaint();
        Sleep(100);
    }
    SetWindowLong(Handle, GWL_EXSTYLE, lRt);
    SetLayeredWindowAttributes(Handle,clBlue,255,LWA_ALPHA);
    Sleep(SPLASH_TIME);
    //Visible = false;
        //Image1Click(0);
}
