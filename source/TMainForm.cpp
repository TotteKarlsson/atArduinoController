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
#include "TSensorsDataModule.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "TIntegerLabeledEdit"
#pragma link "TFloatLabeledEdit"
#pragma link "TSTDStringLabeledEdit"
#pragma link "mtkFloatLabel"
#pragma link "TIntLabel"
#pragma link "TPropertyCheckBox"
#pragma link "TArrayBotBtn"
#pragma link "TPGConnectionFrame"
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
{}

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


    if(pgDM)
    {
	    pgDM->SQLConnection1->AfterConnect 	= afterDBServerConnect;
    	pgDM->SQLConnection1->AfterDisconnect = afterDBServerDisconnect;
   		TPGConnectionFrame1->init(&mIniFile, "POSTGRESDB_CONNECTION");
	    TPGConnectionFrame1->ConnectA->Execute();
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
			if(l.size() == 4 && l[0] == "DHT22_DATA" && sensorsDM)
            {
                //Post message to db populator
                sensorsDM->insertSensorData(toInt(l[3]), toDouble(l[1]), toDouble(l[2]));
            }

			if(l.size() == 3 && l[0] == "AB_LIGHTS_DATA")
            {
            	StringList v1(l[1],'=');
                if(v1.size() == 2)
                {
                	int val = toInt(v1[1]);
                	mf->LEDDriveE->setValue(val);
                    mf->DriveTB->Tag = 1;
                    mf->DriveTB->Position = val;
                }

            	StringList v2(l[2],'=');

                //Is LED On?
                if(v2.size() == 2)
                {
                	if(compareNoCase(v2[1], "True"))
                    {
                    	mf->LEDBtn->Caption = "Flip LEDs OFF";
                    }
                    else
                    {
                    	mf->LEDBtn->Caption = "Flip LEDs ON";
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
    if(b == LEDBtn )
    {
    	static string cap = "ON";
	   	if(contains("OFF", cap))
        {
        	LEDBtn->Caption = "Flip LEDs ON";
            cap = "ON";
        	mArduinoServer.request("TURN_ON_LED_LIGHTS");
        }
        else
        {
        	LEDBtn->Caption = "Flip LEDs OFF";
            cap = "OFF";
        	mArduinoServer.request("TURN_OFF_LED_LIGHTS");
        }
    }
    else if(b == RequestInfoBtn)
    {
    	mArduinoServer.request("GET_LIGHTS_ARDUINO_STATUS");
    }
}

//---------------------------------------------------------------------------
void __fastcall	TMainForm::afterDBServerConnect(System::TObject* Sender)
{
	Log(lInfo) << "Succesfully connected to DB Server";

	pgDM->afterConnect();
	TPGConnectionFrame1->afterConnect();
}

//---------------------------------------------------------------------------
void __fastcall	TMainForm::afterDBServerDisconnect(System::TObject* Sender)
{
	Log(lInfo) << "Disconnected from the DB Server";
	TPGConnectionFrame1->afterDisconnect();
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::DriveTBChange(TObject *Sender)
{
	static int pos(0);
    if(DriveTB->Position != pos)
    {
        pos = DriveTB->Position;
        if(DriveTB->Tag != 1)
        {
			mLightsArduino.setLEDDrive(pos);
        }
        else
        {
	        DriveTB->Tag = 0;
        }
    }
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::LEDDriveEKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)
{
	if(Key == VK_RETURN)
    {
		DriveTB->Position  = LEDDriveE->getValue();
    }
}



