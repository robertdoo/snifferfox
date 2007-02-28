// $Author: zhengsh $
// $Date: 2006/09/09 16:13:06 $
// $Id: StatisticWin.h,v 1.6 2006/09/09 16:13:06 zhengsh Exp $
//---------------------------------------------------------------------------

#ifndef StatisticWinH
#define StatisticWinH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "SUIButton.hpp"
#include "SUIForm.hpp"
#include "SUIGroupBox.hpp"
#include "SUIImagePanel.hpp"
#include "SUIPageControl.hpp"
#include "SUITabControl.hpp"
#include <ExtCtrls.hpp>
#include "SUIMgr.hpp"
#include "SUIProgressBar.hpp"
#include <Graphics.hpp>
//---------------------------------------------------------------------------
class TfrmStatistic : public TForm
{
__published:	// IDE-managed Components
	TsuiForm *frmStatistic;
	TsuiGroupBox *suiGroupBox1;
	TsuiButton *btnOk;
	TsuiThemeManager *ThemeManager;
	TLabel *Label7;
	TsuiPageControl *pcStatistic;
	TsuiTabSheet *tsNetTran;
	TsuiTabSheet *tsDataLink;
	TLabel *Label4;
	TLabel *Label6;
	TStaticText *stFrameTotal;
	TsuiProgressBar *pbOthers;
	TsuiTabSheet *tsSummary;
	TLabel *Label1;
	TLabel *Label2;
	TLabel *Label3;
	TStaticText *stTotal;
	TStaticText *stSaved;
	TStaticText *stDropped;
	TsuiProgressBar *pbSave;
	TsuiProgressBar *pbDrop;
	TLabel *Label5;
	TLabel *Label8;
	TsuiProgressBar *pbIp;
	TsuiProgressBar *pbArp;
	TLabel *Label9;
	TLabel *Label10;
	TLabel *Label11;
	TStaticText *stTotalNetTran;
	TsuiProgressBar *pbIcmp;
	TsuiProgressBar *pbIgmp;
	TLabel *Label13;
	TsuiProgressBar *pbTcp;
	TsuiProgressBar *pbUdp;
	TLabel *Label14;
	TStaticText *stIp;
	TStaticText *stArp;
	TStaticText *stRarp;
	TStaticText *stOthers;
	TStaticText *StaticText7;
	TStaticText *StaticText8;
	TStaticText *StaticText9;
	TStaticText *StaticText10;
	TStaticText *stTcp;
	TStaticText *stUdp;
	TStaticText *stIcmp;
	TStaticText *stIgmp;
	TsuiButton *btnRefresh;
	TsuiProgressBar *pbRarp;
	TTimer *Timer;
    TLabel *LabelIgmp;
    TsuiFileTheme *FileTheme;
	void __fastcall btnOkClick(TObject *Sender);
	void __fastcall btnRefreshClick(TObject *Sender);
	void __fastcall TimerTimer(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TfrmStatistic(TComponent* Owner);
	void Refresh();
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmStatistic *frmStatistic;
//---------------------------------------------------------------------------
#endif
