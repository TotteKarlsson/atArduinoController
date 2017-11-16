#ifndef TMainFormH
#define TMainFormH
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ComCtrls.hpp>
#include <Vcl.ToolWin.hpp>
#include <Vcl.Buttons.hpp>
#include <System.Actions.hpp>
#include <Vcl.ActnList.hpp>
#include "mtkLogFileReader.h"
#include <Vcl.ExtCtrls.hpp>
#include "TIntegerLabeledEdit.h"
#include "TFloatLabeledEdit.h"
#include <Vcl.AppEvnts.hpp>
#include "Poco/Timestamp.h"
#include "TSTDStringLabeledEdit.h"
#include "TRegistryForm.h"
#include "mtkIniFileProperties.h"
#include <Vcl.StdActns.hpp>
#include <Vcl.Menus.hpp>
#include <Vcl.Mask.hpp>
#include "mtkLogLevel.h"
#include "abUIDataStructures.h"
#include "abApplicationMessages.h"
#include "mtkIniFile.h"
#include "arduino/atArduinoServer.h"
#include "mtkFloatLabel.h"
#include "TIntLabel.h"
#include "TPropertyCheckBox.h"
#include "TArrayBotBtn.h"
#include "arduino/atLightsArduino.h"
#include <Data.Bind.Components.hpp>
#include <Data.Bind.EngExt.hpp>
#include <System.Bindings.Outputs.hpp>
#include <System.Rtti.hpp>
#include <Vcl.Bind.DBEngExt.hpp>
#include <Vcl.Bind.Editors.hpp>
#include "TPGConnectionFrame.h"

using Poco::Timestamp;
using mtk::IniFileProperties;
using mtk::IniFile;

class TABProcessSequencerFrame;
class TRibbonLifterFrame;
class TXYZUnitFrame;
class TSequencerButtonsFrame;

//---------------------------------------------------------------------------
class TMainForm : public TRegistryForm
{
    __published:	// IDE-managed Components
        TActionList *ActionList1;
        TAction *checkForDevices;
        TAction *addDevicesToListBox;
        TTimer *ShutDownTimer;
        TAction *identifyCurrent;
        TAction *homeDevice;
        TAction *jogForward;
        TAction *jogBackwards;
        TAction *moveForward;
        TAction *moveBackward;
        TAction *stopAllA;
        TApplicationEvents *ApplicationEvents1;
	TAction *reInitBotA;
        TAction *ShutDownA;
	TFileExit *FileExit1;
	TTimer *UIUpdateTimer;
	TAction *abortLiftA;
	TAction *liftA;
	TPanel *BottomPanel;
	TMemo *infoMemo;
	TToolBar *ToolBar1;
	TBitBtn *mClearLogMemoBtn;
	TComboBox *LogLevelCB;
	TSplitter *Splitter1;
	TScrollBox *mArduinoSB;
	TPageControl *PageControl1;
	TTabSheet *TabSheet1;
	TTabSheet *TabSheet2;
	TPanel *TopPanel;
	TArrayBotButton *Button1;
	TArrayBotButton *Button5;
	TArrayBotButton *LEDBtn;
	TGroupBox *GroupBox1;
	TIntegerLabeledEdit *mArduinoServerPortE;
	TButton *mArduinoServerStartBtn;
	TPanel *Panel2;
	TGroupBox *GroupBox4;
	TToolBar *ToolBar2;
	TBitBtn *mHideBottomPanelBtn;
	TPanel *Panel1;
	TButton *mShowBottomPanelBtn;
	TTabSheet *TabSheet3;
	TIntLabel *NrOfServerClients;
	TLabel *Label1;
	TArrayBotButton *RequestInfoBtn;
	TIntegerLabeledEdit *LEDDriveE;
	TTrackBar *DriveTB;
	TBindingsList *BindingsList1;
	TPGConnectionFrame *TPGConnectionFrame1;
    void __fastcall FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
    void __fastcall FormCreate(TObject *Sender);
    void __fastcall FormCloseQuery(TObject *Sender, bool &CanClose);
    void __fastcall ShutDownTimerTimer(TObject *Sender);
    void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
    void __fastcall ApplicationEvents1Exception(TObject *Sender, Exception *E);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall LogLevelCBChange(TObject *Sender);
	void __fastcall mAboutBtnClick(TObject *Sender);
	void __fastcall MiscBtnClick(TObject *Sender);
	void __fastcall UIUpdateTimerTimer(TObject *Sender);
	void __fastcall mArduinoServerStartBtnClick(TObject *Sender);
	void __fastcall LigthsBtnsClick(TObject *Sender);
	void __fastcall mShowBottomPanelBtnClick(TObject *Sender);
	void __fastcall DriveTBChange(TObject *Sender);
	void __fastcall LEDDriveEKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);

    private:
        LogFileReader                       mLogFileReader;
        void __fastcall                     logMsg();

		void 						        setupWindowTitle();
        void __fastcall					    setupUIFrames();

        IniFile						        mIniFile;
        IniFileProperties  			        mProperties;
		mtk::Property<mtk::LogLevel>        mLogLevel;
		mtk::Property<int>        			mBottomPanelHeight;
		mtk::Property<bool>        			mBottomPanelVisible;

		void __fastcall		                OnException();

        vector<TFrame*>					    mFrames;
	  	void								onUpdatesFromArduinoServer(const string& msg);
		void __fastcall						afterDBServerConnect(System::TObject* Sender);
		void __fastcall						afterDBServerDisconnect(System::TObject* Sender);

	public:
		__fastcall 					        TMainForm(TComponent* Owner);
		__fastcall 					        ~TMainForm();

		void __fastcall                 	AppInBox(mlxStructMessage &Msg);
        ArduinoServer					    mArduinoServer;

           									//References to arduino objects
        LightsArduino&					    mLightsArduino;
       	SensorsArduino&					    mSensorsArduino;

        BEGIN_MESSAGE_MAP
            MESSAGE_HANDLER(UWM_MESSAGE,    mlxStructMessage,         AppInBox);
        END_MESSAGE_MAP(TForm)
};

extern PACKAGE TMainForm *MainForm;
#endif
