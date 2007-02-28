//---------------------------------------------------------------------------

#ifndef GotoWinH
#define GotoWinH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "SUIButton.hpp"
#include "SUIForm.hpp"
#include "SUITrackBar.hpp"
#include <ExtCtrls.hpp>
#include <Graphics.hpp>
#include "SUIMgr.hpp"
//---------------------------------------------------------------------------
class TfrmGoto : public TForm
{
__published:	// IDE-managed Components
    TsuiForm *frmGoto;
    TsuiTrackBar *trPos;
    TsuiButton *btnOk;
    TLabel *lblPos;
    TLabel *lblPosPer;
    TsuiThemeManager *ThemeManager;
    TsuiFileTheme *FileTheme;
    void __fastcall FormCreate(TObject *Sender);
    void __fastcall btnOkClick(TObject *Sender);
    void __fastcall trPosChange(TObject *Sender);
private:	// User declarations
public:		// User declarations
    __fastcall TfrmGoto(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmGoto *frmGoto;
//---------------------------------------------------------------------------
#endif
