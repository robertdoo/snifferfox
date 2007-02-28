//---------------------------------------------------------------------------

#ifndef StatusWinH
#define StatusWinH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "SUIForm.hpp"
#include <ExtCtrls.hpp>
#include <jpeg.hpp>
#include "SUIMgr.hpp"
#include "SUIPopupMenu.hpp"
#include <Menus.hpp>
//---------------------------------------------------------------------------
class TfrmStatus : public TForm
{
__published:	// IDE-managed Components
	TsuiForm *frmStatus;
	TLabel *lblStatus;
	TImage *imgStatus;
	TLabel *lblTotal;
	TLabel *lblDrop;
	TLabel *lblTotalCount;
	TTimer *Timer;
	TLabel *lblDropCount;
	TsuiThemeManager *ThemeManager;
	TsuiPopupMenu *PopupMenu;
	TMenuItem *miHide;
    TsuiFileTheme *FileTheme;
	void __fastcall TimerTimer(TObject *Sender);
	void __fastcall frmStatusMouseDown(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y);
	void __fastcall miHideClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TfrmStatus(TComponent* Owner);
	void Refresh();

};
//---------------------------------------------------------------------------
extern PACKAGE TfrmStatus *frmStatus;
//---------------------------------------------------------------------------
#endif
