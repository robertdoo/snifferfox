// Author: zhengsh
// Date: 2005/10/03 01:30:35
// $Id: NicDetail.h,v 1.3 2006/09/09 16:13:06 zhengsh Exp $

//---------------------------------------------------------------------------

#ifndef NicDetailH
#define NicDetailH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <pcap.h>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "SUIEdit.hpp"
#include "SUIForm.hpp"
#include <ExtCtrls.hpp>
//#include "SUIButton.hpp"
#include "SUIMgr.hpp"
#include "SUIButton.hpp"
#include "Constant.h"
//---------------------------------------------------------------------------
class TfrmNicDetail : public TForm
{
__published:	// IDE-managed Components
    TsuiForm *frmNicDetail;
    TLabel *lblNicName;
    TsuiButton *btnOk;
    TLabel *lblDesc;
    TLabel *lblLoopback;
    TLabel *lblAddrFamily;
    TStaticText *stNicName;
    TStaticText *stDesc;
    TStaticText *stLoopback;
    TStaticText *stAddrFamily;
    TLabel *lblAddr;
    TStaticText *stAddr;
    TStaticText *stNetmask;
    TLabel *lblNetmask;
    TLabel *lblBroadcast;
    TStaticText *stBroadcast;
    TsuiThemeManager *ThemeManager;
    TsuiFileTheme *FileTheme;
    void __fastcall btnOkClick(TObject *Sender);
    void __fastcall FormResize(TObject *Sender);
    void __fastcall FormCreate(TObject *Sender);
private:	// User declarations
public:		// User declarations
    __fastcall TfrmNicDetail(TComponent* Owner);
    void SetNic(pcap_if_t *d);
    void Refresh();
    int nHeight,nWidth;
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmNicDetail *frmNicDetail;
//---------------------------------------------------------------------------
#endif
