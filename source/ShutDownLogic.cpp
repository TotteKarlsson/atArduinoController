#pragma hdrstop
#include "TMainForm.h"
#include "mtkLogger.h"
using namespace mtk;

//---------------------------------------------------------------------------
void __fastcall TMainForm::ShutDownTimerTimer(TObject *Sender)
{
	ShutDownTimer->Enabled = false;
    if(UIUpdateTimer->Enabled)
    {
        UIUpdateTimer->Enabled = false;
    }

    if(mArduinoServer.isRunning())
    {
    	mArduinoServer.shutDown();
    }

    //This will save any ini parameters in the frame
    for(int i = 0; i < mFrames.size(); i++)
    {
    	delete mFrames[i];
    }

    mFrames.clear();

	if(mLogFileReader.isRunning())
	{
		Log(lDebug) << "Shutting down log file reader";
		mLogFileReader.stop();
	}

	Close();
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::FormCloseQuery(TObject *Sender, bool &CanClose)
{
	Log(lInfo) << "Closing down....";

	//Check if we can close.. abort all threads..
	CanClose = (mLogFileReader.isRunning()) ? false : true;

	//Check if active stuff is going on.. if so call the ShutDown in the
    //Timer fire    if(
   	CanClose = (mFrames.size()
            	|| mArduinoServer.isRunning()
                ) ? false : true;


	if(CanClose == false)
	{
		ShutDownTimer->Enabled = true;
	}
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::FormClose(TObject *Sender, TCloseAction &Action)
{
	Log(lInfo) << "In FormClose";
}

