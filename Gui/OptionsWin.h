//---------------------------------------------------------------------------

#ifndef OptionsWinH
#define OptionsWinH
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
#include "SUIEdit.hpp"
#include <IdBaseComponent.hpp>
#include <IdComponent.hpp>
#include <IdIPWatch.hpp>
#include "SUITrackBar.hpp"
#include <Graphics.hpp>
#include <Dialogs.hpp>
#include "SUIComboBox.hpp"
//---------------------------------------------------------------------------
class TfrmOptions : public TForm
{
__published:	// IDE-managed Components
    TsuiForm *frmOptions;
    TsuiPageControl *pcOptions;
    TsuiTabSheet *tsFilter;
    TsuiGroupBox *suiGroupBox1;
    TsuiButton *btnSave;
    TsuiButton *btnCancel;
    TsuiThemeManager *ThemeManager;
	TsuiGroupBox *gbNetTran;
    TsuiButton *btnRestore;
	TsuiTabSheet *tsAddrFilter;
	TsuiGroupBox *gbDataLink;
	TsuiCheckBox *cbIp;
	TsuiCheckBox *cbArp;
	TsuiCheckBox *cbOthers;
	TsuiCheckBox *cbRarp;
	TsuiCheckBox *cbTcp;
	TsuiCheckBox *cbUdp;
	TsuiCheckBox *cbIcmp;
	TsuiCheckBox *cbIgmp;
	TsuiGroupBox *gbAppLayer;
	TsuiGroupBox *gbSrc;
	TsuiGroupBox *gbDest;
	TsuiRadioButton *rbSrcAll;
	TsuiRadioButton *rbSrcOnly;
	TsuiRadioButton *rbSrcSeg;
	TsuiEdit *edtSrcOnly;
    TLabel *lblSrcAddr;
	TLabel *Label1;
	TsuiEdit *edtSrcFrom;
	TLabel *Label2;
	TsuiEdit *edtSrcTo;
	TsuiRadioButton *rbDestAll;
	TsuiRadioButton *rbDestOnly;
	TsuiRadioButton *rbDestSeg;
	TsuiEdit *edtDestOnly;
	TLabel *Label4;
	TsuiEdit *edtDestFrom;
	TLabel *Label5;
	TsuiEdit *edtDestTo;
	TsuiTabSheet *tsSave;
	TLabel *Label3;
	TsuiTrackBar *tbRecordPerPage;
	TStaticText *stRercorPerPage;
	TsuiGroupBox *suiGroupBox2;
	TsuiGroupBox *suiGroupBox3;
	TsuiRadioButton *rbDropBuffer;
	TsuiRadioButton *rbSaveBuffer;
	TsuiRadioButton *rbForceId;
	TsuiRadioButton *rbUniqueId;
	TsuiCheckBox *cbClearCache;
	TsuiCheckBox *cbFtp;
	TsuiCheckBox *cbSsh;
	TsuiCheckBox *cbTelnet;
	TsuiCheckBox *cbSmtp;
	TsuiCheckBox *cbDns;
	TsuiCheckBox *cbGopher;
	TsuiCheckBox *cbHttp;
	TsuiCheckBox *cbPop3;
	TsuiCheckBox *cbFinger;
	TsuiCheckBox *cbLdap;
	TsuiCheckBox *cbTftp;
	TsuiCheckBox *cbAppOthers;
    TLabel *lblDestAddr;
        TsuiEdit *edtPorts;
        TLabel *lblPort;
    TsuiFileTheme *FileTheme;
    TsuiTabSheet *tsMisc;
    TsuiGroupBox *gbUIRules;
    TsuiCheckBox *cbShowSplash;
    TsuiCheckBox *cbMinStart;
    TsuiCheckBox *cbDispStatus;
    TsuiGroupBox *gbAutoSave;
    TsuiCheckBox *cbAutoSniffer;
    TsuiCheckBox *cbDispIcon;
    TsuiEdit *edtAutoSaveFile;
    TLabel *lblAutoSaveFile;
    TsuiCheckBox *cbAutoRun;
    TsuiGroupBox *gbHotKey;
    TLabel *lblKeyDispMain;
    TsuiEdit *edtMainHotKey;
    TLabel *lblKeyDispStatus;
    TsuiEdit *suiEdit3;
    TsuiCheckBox *cbExitConfirm;
    TsuiButton *btnAutoSave;
    TSaveDialog *dlgSaveAutoSave;
    TsuiComboBox *cbNicList;
    TLabel *lblNicList;
    void __fastcall FormCreate(TObject *Sender);
    void __fastcall FormResize(TObject *Sender);
    void __fastcall btnSaveClick(TObject *Sender);
    void __fastcall btnCancelClick(TObject *Sender);
	void __fastcall rbSrcOnlyClick(TObject *Sender);
	void __fastcall rbSrcSegClick(TObject *Sender);
	void __fastcall rbDestOnlyClick(TObject *Sender);
	void __fastcall rbDestSegClick(TObject *Sender);
	void __fastcall btnRestoreClick(TObject *Sender);
	void __fastcall rbSrcAllClick(TObject *Sender);
	void __fastcall rbDestAllClick(TObject *Sender);
	void __fastcall tbRecordPerPageChange(TObject *Sender);
	void __fastcall cbIpClick(TObject *Sender);
	void __fastcall cbTcpUdpClick(TObject *Sender);
    void __fastcall btnAutoSaveClick(TObject *Sender);
    void __fastcall cbAutoSnifferClick(TObject *Sender);
    void __fastcall edtMainHotKeyKeyPress(TObject *Sender, char &Key);
private:	// User declarations
    int nWidth,nHeight;

    void formatPortList();
public:		// User declarations
    __fastcall TfrmOptions(TComponent* Owner);
    void Refresh();
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmOptions *frmOptions;
//---------------------------------------------------------------------------
#endif
