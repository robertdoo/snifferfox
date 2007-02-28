//---------------------------------------------------------------------------

#ifndef CoverWinH
#define CoverWinH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <jpeg.hpp>
#include <Graphics.hpp>
//---------------------------------------------------------------------------
class TfrmCover : public TForm
{
__published:	// IDE-managed Components
	TImage *Image1;
    TLabel *lblSoftName;
    TLabel *lbl1;
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall Image1Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TfrmCover(TComponent* Owner);
    void CloseWindow();
    void ShowSplash(int para=0);  
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmCover *frmCover;
//---------------------------------------------------------------------------
#endif
