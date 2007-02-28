// $Author: zhengsh $
// $Date: 2006/09/29 15:31:35 $
// $Id: MainWin.h,v 1.40 2006/09/29 15:31:35 zhengsh Exp $
//---------------------------------------------------------------------------

#ifndef MainWinH
#define MainWinH
#include "StatusWin.h"
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "SUIForm.hpp"
#include <ExtCtrls.hpp>
#include "SUIMainMenu.hpp"
#include <Menus.hpp>
#include "SUIGrid.hpp"
#include <Grids.hpp>
#include "SUIButton.hpp"
#include "SUIPageControl.hpp"
#include "SUITabControl.hpp"
#include "SUIMgr.hpp"
#include "SUIPopupMenu.hpp"
#include "SUIToolBar.hpp"
#include <ComCtrls.hpp>
#include <ToolWin.hpp>
#include "SUIGroupBox.hpp"
#include "SUIImagePanel.hpp"
#include "SUIComboBox.hpp"
#include "SUIListBox.hpp"
#include "RecvThread.h"
#include "SUIDlg.hpp"
#include <pcap.h>
#include "SUIEdit.hpp"
#include "SUIScrollBar.hpp"
#include "SUIMemo.hpp"
#include "trayicon.h"
#include <ImgList.hpp>
#include "EtherDataGram.h"
#include "EtherList.h"
#include "MsgDialog.h"
#include <Graphics.hpp>
#include "SUITrackBar.hpp"
#include "SUIURLLabel.hpp"
#include <Dialogs.hpp>
#include <Buttons.hpp>
#include "SUITitleBar.hpp"


//---------------------------------------------------------------------------
class TfrmMain : public TForm
{
__published:	// IDE-managed Components
    TsuiForm *frmMain;
    TsuiButton *suiButton1;
    TsuiThemeManager *ThemeManager;
    TsuiPopupMenu *PopupMenu;
    TMenuItem *miStyle;
    TMenuItem *WinXp1;
    TMenuItem *MacOS1;
    TMenuItem *Protein1;
    TMenuItem *DeepBlue1;
    TMenuItem *BlueGlass1;
    TsuiGroupBox *suiGroupBox1;
    TLabel *Label1;
    TsuiComboBox *cbNicList;
    TMenuItem *miLang;
    TMenuItem *miChinese;
    TsuiButton *btnNicDetail;
    TsuiButton *btnStartPause;
    TMenuItem *miEnglish;
    TsuiStringGrid *sgDataList;
    TTrayIcon *TrayIcon;
    TImageList *ImageList;
    TsuiGroupBox *suiGroupBox2;
    TImage *imgUpDown;
	TMenuItem *N8;
	TMenuItem *miStatusWindow1;
	TMenuItem *miDetailPanel1;
	TsuiTrackBar *suiTrackBar1;
	TMenuItem *miMainWin;
	TMenuItem *N9;
	TMenuItem *miStart;
	TMenuItem *N10;
	TMenuItem *miExit1;
	TMenuItem *miClearAllPacket;
	TsuiURLLabel *suiURLLabel1;
	TsuiButton *btnNext;
	TsuiButton *btnLast;
	TsuiButton *btnPrevious;
	TsuiButton *btnFirst;
	TOpenDialog *OpenDialog;
	TSaveDialog *SaveDialog;
	TLabel *lblStatus;
	TSaveDialog *SaveAs;
    TLabel *lblCurPos;
    TTimer *Timer1;
    TsuiFileTheme *FileTheme;
    TsuiMainMenu *MainMenu;
    TMenuItem *miFile;
    TMenuItem *miOpen;
    TMenuItem *OpenText1;
    TMenuItem *Reopen1;
    TMenuItem *sdfdsf1;
    TMenuItem *N1;
    TMenuItem *Save1;
    TMenuItem *SaveAs1;
    TMenuItem *SaveAsText1;
    TMenuItem *N2;
    TMenuItem *miClose;
    TMenuItem *miExit;
    TMenuItem *miEdit;
    TMenuItem *Find1;
    TMenuItem *N3;
    TMenuItem *miClearAll;
    TMenuItem *N7;
    TMenuItem *miGoTo;
    TMenuItem *miGoToTop;
    TMenuItem *miGoToBottom;
    TMenuItem *N6;
    TMenuItem *FirstPage1;
    TMenuItem *Prevous1;
    TMenuItem *NextPage1;
    TMenuItem *LastPage1;
    TMenuItem *Sort1;
    TMenuItem *SorceMac1;
    TMenuItem *SourceIp1;
    TMenuItem *miView;
    TMenuItem *miStat;
    TMenuItem *miNicList;
    TMenuItem *N4;
    TMenuItem *miOptions;
    TMenuItem *miInterface;
    TMenuItem *miMainStyle;
    TMenuItem *miWinXp;
    TMenuItem *miMacOS;
    TMenuItem *miProtein;
    TMenuItem *miDeepBlue;
    TMenuItem *miBlueGlass;
    TMenuItem *miLanguage;
    TMenuItem *Chinese1;
    TMenuItem *English1;
    TMenuItem *N5;
    TMenuItem *miMainWindow;
    TMenuItem *miDetailPanel;
    TMenuItem *miStatusWindow;
    TMenuItem *miHelp;
    TMenuItem *miSniHelp;
    TMenuItem *miTurtorial;
    TMenuItem *miAbout;
    TMenuItem *miAuthor;
    TMenuItem *miFeedBack;
    TMenuItem *miGetSource;
    TsuiPageControl *pcDataInfo;
    TsuiTabSheet *tsIcmp;
    TLabel *lblIcmpType;
    TLabel *lblIcmpCrc;
    TLabel *lblIcmpCode;
    TLabel *lblIcmpDesc;
    TsuiEdit *edtIcmpType;
    TsuiEdit *edtIcmpCrc;
    TsuiEdit *edtIcmpCode;
    TsuiEdit *edtIcmpDesc;
    TsuiTabSheet *tsArpHeader;
    TLabel *lblProtocolType;
    TLabel *lblArpSrcMac;
    TLabel *lblArpSrcAddr;
    TLabel *Label7;
    TLabel *lblArpDestMac;
    TsuiEdit *edtProtocolType;
    TsuiEdit *edtArpSrcAddr;
    TsuiEdit *edtArpSrcMac;
    TsuiEdit *edtArpDestAddr;
    TsuiEdit *edtArpDestMac;
    TsuiTabSheet *tsUdp;
    TLabel *lblUdpSrcPort;
    TLabel *lblUdpDestPort;
    TLabel *lblUdpLength;
    TLabel *lblUdpCrc;
    TLabel *lblUdpProtoName;
    TsuiEdit *edtUdpSrcPort;
    TsuiEdit *edtUdpDestPort;
    TsuiEdit *edtUdpLength;
    TsuiEdit *edtUdpCrc;
    TsuiEdit *edtUdpProtoName;
    TsuiTabSheet *tsData;
    TLabel *lblBinary;
    TLabel *Label2;
    TsuiMemo *mmoBin;
    TsuiMemo *mmoText;
    TsuiTabSheet *tsTcp;
    TLabel *lblTcpSrcPort;
    TLabel *lblTcpDestPort;
    TLabel *lblTcpWinSize;
    TLabel *lblTcpSeqNum;
    TLabel *lblAckSeq;
    TLabel *lblTcpProtoName;
    TsuiEdit *edtTcpSrcPort;
    TsuiEdit *edtTcpDestPort;
    TsuiEdit *edtTcpWinSize;
    TsuiEdit *edtTcpSeqNum;
    TsuiEdit *edtAckSeq;
    TsuiEdit *edtTcpProtoName;
    TsuiTabSheet *tsIpHeader;
    TLabel *lblVersion;
    TLabel *lblIhl;
    TLabel *lblTos;
    TLabel *lblTotalLength;
    TLabel *lblId;
    TLabel *lblFlags;
    TLabel *lblHeaderCrc;
    TLabel *lblProtocol;
    TLabel *lblTimeToLive;
    TLabel *lblFragOffset;
    TLabel *lblSrcAddr;
    TLabel *lblDestAddr;
    TsuiEdit *edtVersion;
    TsuiEdit *edtIhl;
    TsuiEdit *edtTos;
    TsuiEdit *edtTotalLength;
    TsuiEdit *edtId;
    TsuiEdit *edtFlags;
    TsuiEdit *edtHeaderCrc;
    TsuiEdit *edtOffset;
    TsuiEdit *edtTtl;
    TsuiEdit *edtProtocol;
    TsuiEdit *edtSrcAddr;
    TsuiEdit *edtDestAddr;
    TsuiTabSheet *tsEtherHeader;
    TLabel *lblSrcMac;
    TLabel *lblDestMac;
    TLabel *lblType;
    TLabel *lblTimeStamp;
    TLabel *lblActLen;
    TLabel *lblCapLen;
    TsuiEdit *edtSrcMac;
    TsuiEdit *edtDestMac;
    TsuiEdit *edtType;
    TsuiEdit *edtTimeStamp;
    TsuiEdit *edtActLen;
    TsuiEdit *edtCapLen;
    TMenuItem *miSortBy;
    TMenuItem *miSortById;
    TMenuItem *miSortByTTL;
    TMenuItem *miSortBySize;
    TMenuItem *miDestMac;
    TMenuItem *miSrcMac;
    TMenuItem *miDestHost;
    TMenuItem *miSrcHost;
    TMenuItem *miProtocol;
    TMenuItem *miTimestamp;
    TMenuItem *mniN11;
    TMenuItem *mniN12;
    TMenuItem *mniN13;
    void __fastcall WinXp1Click(TObject *Sender);
    void __fastcall Protein1Click(TObject *Sender);
    void __fastcall BlueGlass1Click(TObject *Sender);
    void __fastcall DeepBlue1Click(TObject *Sender);
    void __fastcall MacOS1Click(TObject *Sender);
    void __fastcall cbNicListDropDown(TObject *Sender);
    void __fastcall btnNicDetailClick(TObject *Sender);
    void __fastcall miChineseClick(TObject *Sender);
    void __fastcall miEnglishClick(TObject *Sender);
    void __fastcall suiButton1Click(TObject *Sender);
    void __fastcall btnStartPauseClick(TObject *Sender);
    void __fastcall miOptionsClick(TObject *Sender);
    void __fastcall miExitClick(TObject *Sender);
    void __fastcall suiButton2Click(TObject *Sender);
    void __fastcall miGoToTopClick(TObject *Sender);
    void __fastcall miGoToBottomClick(TObject *Sender);
    //void __fastcall Button1Click(TObject *Sender);
    void __fastcall imgUpDownClick(TObject *Sender);
    void __fastcall FormCloseQuery(TObject *Sender, bool &CanClose);
    void __fastcall ShowNicDetail(TObject *Sender);
    void __fastcall miNicListClick(TObject *Sender);
    void __fastcall sgDataListDblClick(TObject *Sender);
    void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall miStatClick(TObject *Sender);
	void __fastcall PopupMenuPopup(TObject *Sender);
	void __fastcall miMainStyleClick(TObject *Sender);
	void __fastcall miLanguageClick(TObject *Sender);
	void __fastcall miInterfaceClick(TObject *Sender);
	void __fastcall miDetailPanelClick(TObject *Sender);
	void __fastcall miEditClick(TObject *Sender);
	void __fastcall TrayIconMinimize(TObject *Sender);
	void __fastcall TrayIconDeactivate(TObject *Sender);
	void __fastcall miStatusWindowClick(TObject *Sender);
	void __fastcall sgDataListMouseDown(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y);
	void __fastcall miMainWindowClick(TObject *Sender);
	void __fastcall miExit1Click(TObject *Sender);
	void __fastcall miSniHelpClick(TObject *Sender);
	void __fastcall ClearAll(TObject *Sender);
	void __fastcall sgDataListMouseMove(TObject *Sender, TShiftState Shift,
          int X, int Y);
	void __fastcall miOpenClick(TObject *Sender);
	void __fastcall btnFirstClick(TObject *Sender);
	void __fastcall btnPreviousClick(TObject *Sender);
	void __fastcall btnNextClick(TObject *Sender);
	void __fastcall btnLastClick(TObject *Sender);
	void __fastcall CloseFile(TObject *Sender);
	void __fastcall miFileClick(TObject *Sender);
	void __fastcall SaveAsFile(TObject *Sender);
	void __fastcall miAuthorClick(TObject *Sender);
	void __fastcall SaveFile(TObject *Sender);
	void __fastcall miViewClick(TObject *Sender);
    void __fastcall miAboutClick(TObject *Sender);
    void __fastcall miFeedBackClick(TObject *Sender);
    void __fastcall sgDataListMouseWheelUp(TObject *Sender,
          TShiftState Shift, TPoint &MousePos, bool &Handled);
    void __fastcall sgDataListClick(TObject *Sender);
    void __fastcall sgDataListMouseWheelDown(TObject *Sender,
          TShiftState Shift, TPoint &MousePos, bool &Handled);
    void __fastcall miTurtorialClick(TObject *Sender);
    void __fastcall miGoToClick(TObject *Sender);
    void __fastcall Timer1Timer(TObject *Sender);
    void __fastcall ChangeUIStyle(TObject *Sender);
    void __fastcall ChangeLanguage(TObject *Sender);
    void __fastcall miGetSourceClick(TObject *Sender);
    void __fastcall FormCreate(TObject *Sender);
    void __fastcall TrayIconClick(TObject *Sender);
    void __fastcall btn1Click(TObject *Sender);
    void __fastcall miSortByIdClick(TObject *Sender);
    void __fastcall miSrcHostClick(TObject *Sender);
    void __fastcall miDestHostClick(TObject *Sender);
    void __fastcall miSrcMacClick(TObject *Sender);
    void __fastcall miDestMacClick(TObject *Sender);
    void __fastcall miSortBySizeClick(TObject *Sender);
    void __fastcall miSortByTTLClick(TObject *Sender);
    void __fastcall miProtocolClick(TObject *Sender);
    void __fastcall miTimestampClick(TObject *Sender);
    void __fastcall TrayIconMouseMove(TObject *Sender, TShiftState Shift,
          int X, int Y);

private:	// User declarations
    pcap_if_t *m_pNicList;
    int nRecordCount;
    bool bCancelSave;
    static bool ascOrDesc[10];
	//int nNextId;
	bool protocolAllow(const struct pcap_pkthdr *header, const u_char *pkt_data);
	bool sourceAllow(const struct pcap_pkthdr *header, const u_char *pkt_data);
	bool destineAllow(const struct pcap_pkthdr *header, const u_char *pkt_data);
	void ShowNicDetail(pcap_if_t *);
	bool bThreadIsRun;
	TRecvThread *RecvThread;
	void Exchange(int Index1, int Index2);
    int len[9];
    int nCurPage;
    void PageCtrl();
    //message map
    BEGIN_MESSAGE_MAP
       MESSAGE_HANDLER(WM_HOTKEY,TMessage,OnHotKey)
    END_MESSAGE_MAP(TForm)
    void __fastcall OnHotKey(TMessage &Message);
    //响应热键消息
   // bool havestarted;
public:		// User declarations
	 __fastcall TfrmMain(TComponent* Owner);
	 pcap_if_t *GetSelectedNic();
	 //获得当前选中的网卡
	 //返回0表示用户没有选择任何网卡
	 void Refresh();
	 //刷新
	 bool DataProcess(const struct pcap_pkthdr *header, const u_char *pkt_data,int id = 0);
	 //添加记录
	 TEtherList EtherList;
	 void SetUiStyle(int ui);
	 void HidePanel();
	 void ShowPanel();

	 void Sort(int field, bool asc, bool asint);
	 bool ThreadIsRun();
	 TfrmStatus *frmStatus;
     void LoadFromList();
     void ShowDetail();
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmMain *frmMain;
//---------------------------------------------------------------------------
#endif
