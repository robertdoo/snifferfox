//---------------------------------------------------------------------------

#ifndef AuthorWinH
#define AuthorWinH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "SUIButton.hpp"
#include "SUIForm.hpp"
#include <ExtCtrls.hpp>
#include <Graphics.hpp>
#include "SUIURLLabel.hpp"
#include "SUIMgr.hpp"
#include "Constant.h"

//---------------------------------------------------------------------------
class TfrmAuthor : public TForm
{
__published:	// IDE-managed Components
	TsuiForm *suiForm1;
	TsuiButton *suiButton1;
	TLabel *Label1;
	TsuiURLLabel *suiURLLabel1;
	TsuiURLLabel *suiURLLabel2;
	TsuiURLLabel *suiURLLabel3;
	TsuiURLLabel *suiURLLabel4;
    TsuiThemeManager *ThemeManager;
	TLabel *lblVersion;
	TLabel *Label3;
    TsuiFileTheme *FileTheme;
    TsuiURLLabel *suiURLLabel5;
    TsuiURLLabel *suiURLLabel6;
    TLabel *lbl1;
    TLabel *lbl2;
	void __fastcall suiButton1Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
	void Refresh();
	__fastcall TfrmAuthor(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmAuthor *frmAuthor;
//---------------------------------------------------------------------------
#endif
