//---------------------------------------------------------------------------

#ifndef MsgDialogH
#define MsgDialogH
#include <vcl.h>
#include "Global.h"
#include "Constant.h"

//---------------------------------------------------------------------------
void ShowMsg(AnsiString msg,AnsiString title = "",int msgtype=MSG_INFO);
//ShowMessage
int MsgBox(AnsiString msg,AnsiString title = "",int nBtnCnt=2,int msgtype=MSG_HELP);
//msg:message
//nBtncnt:Button Count

#endif
