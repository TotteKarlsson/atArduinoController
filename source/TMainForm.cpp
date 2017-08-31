#include <vcl.h>
#pragma hdrstop
#include "TMainForm.h"
#include "TMemoLogger.h"
#include "mtkStringList.h"
#include "Core/atUtilities.h"
#include "mtkVCLUtils.h"
#include "mtkLogger.h"
#include <bitset>
#include "mtkMathUtils.h"
#include "Core/atExceptions.h"
#include "TLightsArduinoFrame.h"
#include "TSensorsArduinoFrame.h"
#include "TATDBDataModule.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "TIntegerLabeledEdit"
#pragma link "TFloatLabeledEdit"
#pragma link "TSTDStringLabeledEdit"
#pragma link "mtkFloatLabel"
#pragma link "TIntLabel"
#pragma link "TPropertyCheckBox"
#pragma link "TArrayBotBtn"
#pragma link "TATDBConnectionFrame"
#pragma resource "*.dfm"
//---------------------------------------------------------------------------
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
    mSensorsArduino(mArduinoServer.getSensorsArduino()),
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

	TATDBConnectionFrame* f = TATDBConnectionFrame1;
	mProperties.add((BaseProperty*)  &f->mServerIPE->getProperty()->setup( 	    	"MYSQL_SERVER_IP",              	"127.0.0.1"));
	mProperties.add((BaseProperty*)  &f->mDBUserE->getProperty()->setup( 	   		"ATDB_USER_NAME",                   "none"));
	mProperties.add((BaseProperty*)  &f->mPasswordE->getProperty()->setup( 	    	"ATDB_USER_PASSWORD",               "none"));
	mProperties.add((BaseProperty*)  &f->mDatabaseE->getProperty()->setup( 	    	"ATDB_DB_NAME",    			        "none"));

    mProperties.read();
	mArduinoServerPortE->update();
    f->mDBUserE->update();
    f->mPasswordE->update();
    f->mDatabaseE->update();
	f->mServerIPE->update();

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

    if(atdbDM)
    {
	    atdbDM->SQLConnection1->AfterConnect 	= afterDBServerConnect;
    	atdbDM->SQLConnection1->AfterDisconnect = afterDBServerDisconnect;
		TATDBConnectionFrame1->mATDBServerBtnConnectClick(NULL);
    }

}

//---------------------------------------------------------------------------
void __fastcall	TMainForm::setupUIFrames()
{
    mLightsArduino.setName("LIGHTS_ARDUINO");
    TLightsArduinoFrame* af1 = new TLightsArduinoFrame(mArduinoServer, mLightsArduino, mIniFile, this);
    af1->Parent =  mArduinoSB;
    af1->Align = alLeft;
    af1->ConnectBtnClick(NULL);
    mFrames.push_back(af1);

    mSensorsArduino.setName("SENSORS_ARDUINO");
    TSensorsArduinoFrame* af2 = new TSensorsArduinoFrame(mArduinoServer, mSensorsArduino, mIniFile, this);
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
        TMainForm* mf;
        void __fastcall onMsg()
        {
            //Parse the message
            mf->mArduinoServer.broadcast(msg);

        	StringList l(msg, ',');
			if(l.size() && l[0] == "DHT22_DATA")
            {
                if(atdbSensorsDM)
                {
					if(l.size() == 4)
                    {
                    	//Post message to db populator
                        atdbSensorsDM->insertSensorData(toInt(l[3]), toDouble(l[1]), toDouble(l[2]));
                    }
                }
            }
        }
    };

    TLocalArgs args;
    args.msg = new_msg;
    args.mf = this;


    //This causes this function to be called in the UI thread
 	TThread::Synchronize(NULL, &args.onMsg);
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::UIUpdateTimerTimer(TObject *Sender)
{
   	mArduinoServerStartBtn->Caption = mArduinoServer.isRunning() 		? "Stop" : "Start";
	mArduinoServerPortE->Enabled 	= !mArduinoServer.isRunning();
    NrOfServerClients->setValue(mArduinoServer.getNumberOfClients());
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::mArduinoServerStartBtnClick(TObject *Sender)
{
	if(mArduinoServerStartBtn->Caption == "Stop")
    {
    	mArduinoServer.shutDown();
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

//---------------------------------------------------------------------------
void __fastcall TMainForm::TATDBConnectionFrame1mATDBServerBtnConnectClick(TObject *Sender)
{
	TATDBConnectionFrame1->mATDBServerBtnConnectClick(Sender);
}


//---------------------------------------------------------------------------
void __fastcall	TMainForm::afterDBServerConnect(System::TObject* Sender)
{
	Log(lInfo) << "Succesfully connected to DB Server";

	atdbDM->afterConnect();
	TATDBConnectionFrame1->afterConnect();

//	//Setup UI
//    mUsersCB->KeyValue = mDBUserID.getValue();
//    mBlockProcessIDCB->KeyValue = mProcessID.getValue();
//    BlockIDCB->KeyValue = mBlockID.getValue();
//    enableDisableGroupBox(BlockSelectionGB, true);
//    enableDisableGroupBox(BlocksGB, true);
//    enableDisableGroupBox(RibbonsDataGB, true);
//
//    mRegisterRibbonBtn->Enabled = true;
}

//---------------------------------------------------------------------------
void __fastcall	TMainForm::afterDBServerDisconnect(System::TObject* Sender)
{
	Log(lInfo) << "Disconnected from the DB Server";
	TATDBConnectionFrame1->afterDisconnect();

//    enableDisableGroupBox(BlocksGB, false);
//    enableDisableGroupBox(BlockSelectionGB, false);
//    enableDisableGroupBox(RibbonsDataGB, false);
//    mRegisterRibbonBtn->Enabled = false;
}

