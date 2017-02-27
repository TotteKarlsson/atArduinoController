#include <vcl.h>
#pragma hdrstop
#include "MainForm.h"
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
TMain *Main;

extern string           gLogFileLocation;
extern string           gLogFileName;
extern string           gAppDataFolder;
extern string 			gApplicationRegistryRoot;
extern bool             gAppIsStartingUp;
using namespace mtk;

//---------------------------------------------------------------------------
__fastcall TMain::TMain(TComponent* Owner)
:
	TRegistryForm(gApplicationRegistryRoot, "MainForm", Owner),
	mLogFileReader(joinPath(getSpecialFolder(CSIDL_LOCAL_APPDATA), "ArrayBot", gLogFileName), &logMsg),
    mIniFile(joinPath(gAppDataFolder, "ArduinoController.ini"), true, true),
    mLogLevel(lAny),
    mArduinoServer(-1),
    mPufferArduino(mArduinoServer.getPufferArduino()),
    mLightsArduino(mArduinoServer.getLightsArduino()),
    mSensorsArduino(mArduinoServer.getSensorsArduino())
{
	TMemoLogger::mMemoIsEnabled = false;
   	mLogFileReader.start(true);

	//Setup UI/INI properties
    mProperties.setSection("UI");
	mProperties.setIniFile(&mIniFile);
	mProperties.add((BaseProperty*)  &mLogLevel.setup( 	                    		"LOG_LEVEL",    	 lAny));
	mProperties.add((BaseProperty*)  &mArduinoServerPortE->getProperty()->setup(	"SERVER_PORT",    	 50000));

    mProperties.read();
	mArduinoServerPortE->update();

    //This will update the UI from a thread
    mArduinoServer.assignOnUpdateCallBack(onUpdatesFromArduinoServer);
}

__fastcall TMain::~TMain()
{
	mProperties.write();
    mIniFile.save();
}

//---------------------------------------------------------------------------
void __fastcall TMain::FormCreate(TObject *Sender)
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
void __fastcall	TMain::setupUIFrames()
{
    mPufferArduino.setName("PUFFER_ARDUINO");


    mLightsArduino.setName("LIGHTS_ARDUINO");
    TLightsArduinoFrame* af2 = new TLightsArduinoFrame(mArduinoServer, mLightsArduino, mIniFile, this);
    af2->Parent =  mArduinoSB;
    af2->Align = alLeft;
    af2->ConnectBtnClick(NULL);
    mFrames.push_back(af2);

    mSensorsArduino.setName("SENSORS_ARDUINO");
    TSensorsArduinoFrame* af3 = new TSensorsArduinoFrame(mArduinoServer, mSensorsArduino, mIniFile, this);
    af3->Parent =  mArduinoSB;
    af3->Align = alLeft;
    af3->ConnectBtnClick(NULL);
    mFrames.push_back(af3);
}

//This callback is called from the arduino server
//Its purpose is to update the servers UI.
void TMain::onUpdatesFromArduinoServer(const string& new_msg)
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
void __fastcall TMain::UIUpdateTimerTimer(TObject *Sender)
{
   	mArduinoServerStartBtn->Caption = mArduinoServer.isRunning() 		? "Stop" : "Start";
	mArduinoServerPortE->Enabled 	= !mArduinoServer.isRunning();
}

//---------------------------------------------------------------------------
void __fastcall TMain::mArduinoServerStartBtnClick(TObject *Sender)
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
void __fastcall TMain::LigthsBtnsClick(TObject *Sender)
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
    else if(b == mCoaxLightBtn)
    {
    	static string ccap = "ON";
	   	if(contains("OFF", ccap))
        {
        	mCoaxLightBtn->Caption = "Flip CoaxLight ON";
            ccap = "ON";
        	mArduinoServer.request("TURN_ON_COAX_LIGHT");
        }
        else
        {
        	mCoaxLightBtn->Caption = "Flip CoaxLight OFF";
            ccap = "OFF";
        	mArduinoServer.request("TURN_OFF_COAX_LIGHT");
        }
    }
}

