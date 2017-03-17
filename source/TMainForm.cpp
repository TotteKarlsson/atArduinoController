#include <vcl.h>
#pragma hdrstop
#include "TMainForm.h"
#include "TMemoLogger.h"
#include "mtkStringList.h"
#include "atUtilities.h"
#include "mtkVCLUtils.h"
#include "mtkLogger.h"
#include <bitset>
#include "mtkMathUtils.h"
#include "atExceptions.h"
#include "TLightsArduinoFrame.h"
#include "TSensorsArduinoFrame.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "TIntegerLabeledEdit"
#pragma link "TFloatLabeledEdit"
#pragma link "TSTDStringLabeledEdit"
#pragma link "mtkFloatLabel"
#pragma link "TIntLabel"
#pragma link "TPropertyCheckBox"
#pragma link "TArrayBotBtn"
#pragma resource "*.dfm"
TMainForm *MainForm;

extern string           gLogFileLocation;
extern string           gLogFileName;
extern string           gAppDataFolder;
extern string 			gApplicationRegistryRoot;
extern string			gAppExeName;
extern bool             gAppIsStartingUp;
using namespace mtk;

//---------------------------------------------------------------------------
__fastcall TMainForm::TMainForm(TComponent* Owner)
:
	TRegistryForm(gApplicationRegistryRoot, "MainForm", Owner),
	mLogFileReader(joinPath(getSpecialFolder(CSIDL_LOCAL_APPDATA), gAppExeName, gLogFileName), &logMsg),
    mIniFile(joinPath(gAppDataFolder, "ArduinoController.ini"), true, true),
    mLogLevel(lAny),
    mArduinoServer(-1),
    mLightsArduino(mArduinoServer.getLightsArduino()),
	mBottomPanelVisible(true),
	mBottomPanelHeight(100)
{
	TMemoLogger::mMemoIsEnabled = false;
   	mLogFileReader.start(true);

	//Setup UI/INI properties
    mProperties.setSection("UI");
	mProperties.setIniFile(&mIniFile);
	mProperties.add((BaseProperty*)  &mLogLevel.setup( 	                    		"LOG_LEVEL",    	 	lAny));
	mProperties.add((BaseProperty*)  &mArduinoServerPortE->getProperty()->setup(	"SERVER_PORT",    	 	50000));
	mProperties.add((BaseProperty*)  &mBottomPanelHeight.setup(						"BOTTOM_PANEL_HEIGHT",   100));
	mProperties.add((BaseProperty*)  &mBottomPanelVisible.setup(  					"BOTTOM_PANEL_VIBILITY", true));

    mProperties.read();
	mArduinoServerPortE->update();

    BottomPanel->Visible 	= mBottomPanelVisible;
    BottomPanel->Height 	= mBottomPanelHeight;

    if(!BottomPanel->Visible)
    {
	    mShowBottomPanelBtn->Visible = true;
    }
    //This will update the UI from a thread
    mArduinoServer.assignOnUpdateCallBack(onUpdatesFromArduinoServer);
}

__fastcall TMainForm::~TMainForm()
{

    mBottomPanelVisible = BottomPanel->Visible ;
    mBottomPanelHeight = BottomPanel->Height;

	mProperties.write();
    mIniFile.save();
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::FormCreate(TObject *Sender)
{
	setupWindowTitle();
	gAppIsStartingUp = false;

	TMemoLogger::mMemoIsEnabled = true;

	this->Visible = true;
	gLogger.setLogLevel(mLogLevel);

	LogLevelCB->ItemIndex = mLogLevel.getValue() - 2;

	TMemoLogger::mMemoIsEnabled = true;
    UIUpdateTimer->Enabled = true;

    //Setup the server
    mArduinoServer.start(mArduinoServerPortE->getValue());

	//Setup frames for the Arduinos
	setupUIFrames();
}

//---------------------------------------------------------------------------
void __fastcall	TMainForm::setupUIFrames()
{
    mLightsArduino.setName("LIGHTS_ARDUINO");
    TLightsArduinoFrame* af2 = new TLightsArduinoFrame(mArduinoServer, mLightsArduino, mIniFile, this);
    af2->Parent =  mArduinoSB;
    af2->Align = alLeft;
    af2->ConnectBtnClick(NULL);
    mFrames.push_back(af2);
}

//This callback is called from the arduino server
//Its purpose is to update the servers UI.
void TMainForm::onUpdatesFromArduinoServer(const string& new_msg)
{
	struct TLocalArgs
    {
        string msg;
        void __fastcall onMsg()
        {
            //Parse the message
        	StringList l(msg, '=');
        }
    };

    TLocalArgs args;
    args.msg = new_msg;


    //This causes this function to be called in the UI thread
 	TThread::Synchronize(NULL, &args.onMsg);
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::UIUpdateTimerTimer(TObject *Sender)
{
   	mArduinoServerStartBtn->Caption = mArduinoServer.isRunning() 		? "Stop" : "Start";
	mArduinoServerPortE->Enabled 	= !mArduinoServer.isRunning();
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::mArduinoServerStartBtnClick(TObject *Sender)
{
	if(mArduinoServerStartBtn->Caption == "Stop")
    {
    	mArduinoServer.stop();
    }
    else
    {
    	mArduinoServer.start(mArduinoServerPortE->getValue());
    }
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::LigthsBtnsClick(TObject *Sender)
{
	TArrayBotButton* b = dynamic_cast<TArrayBotButton*>(Sender);
    if(b == mFrontBackLEDBtn )
    {
    	static string cap = "ON";
	   	if(contains("OFF", cap))
        {
        	mFrontBackLEDBtn->Caption = "Flip LEDs ON";
            cap = "ON";
        	mArduinoServer.request("TURN_ON_LED_LIGHTS");
        }
        else
        {
        	mFrontBackLEDBtn->Caption = "Flip LEDs OFF";
            cap = "OFF";
        	mArduinoServer.request("TURN_OFF_LED_LIGHTS");
        }
    }
}

void __fastcall TMainForm::MiscBtnClick(TObject *Sender)
{
	TBitBtn* b = dynamic_cast<TBitBtn*>(Sender);
    if(b == mClearLogMemoBtn)
    {
		infoMemo->Clear();
    }
    else if(b == mHideBottomPanelBtn)
    {
		BottomPanel->Visible = false;
	    mShowBottomPanelBtn->Visible = true;
        this->Height -= BottomPanel->Height;
    }
}

void __fastcall TMainForm::mShowBottomPanelBtnClick(TObject *Sender)
{
    this->Height += BottomPanel->Height;
	BottomPanel->Visible = true;
    mShowBottomPanelBtn->Visible = false;
    Splitter1->Top = BottomPanel->Top - 1;
}

