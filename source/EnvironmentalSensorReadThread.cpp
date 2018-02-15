#pragma hdrstop
#include "EnvironmentalSensorReadThread.h"
#include "mtkLogger.h"
#include "core/atExceptions.h"
#include "Poco/Process.h"
#include "Poco/PipeStream.h"
#include "Poco/StreamCopier.h"
#include "mtkMoleculixException.h"
//using Poco::Path;
using namespace Poco;

//---------------------------------------------------------------------------

using namespace mtk;

EnvironmentalSensorReadThread::EnvironmentalSensorReadThread(const string& exe)
:
mExecutable(exe),
mGetTempMIB("1.3.6.1.4.1.21239.5.1.2.1.5"),
mGetTempResponseTag("21239.5.1.2.1.5"),
mGetHumidityMIB("1.3.6.1.4.1.21239.5.1.2.1.6"),
mGetHumidityResponseTag("21239.5.1.2.1.6"),
mGetDewPointMIB("1.3.6.1.4.1.21239.5.1.2.1.7"),
mGetDewPointResponseTag("21239.5.1.2.1.7"),
mTemperature(0),
mHumidity(0),
mDewPoint(0)
{

}

void EnvironmentalSensorReadThread::assignCallBacks(Callback one, Callback two, Callback three)
{
	onEnter 	= one;
    onProgress 	= two;
    onExit 		= three;
}


void EnvironmentalSensorReadThread::run()
{
	mIsStarted = true;
    if(onEnter)
    {
    	onEnter(0,0);
    }

	mIsRunning = true;

	try
    {
    	if(!fileExists(mExecutable))
        {
	        Log(lError) << "The executable: " << mExecutable << " don't exists";
            const ATException ae(string("The executable: ") +  string(" don't exists"));
            throw(ae);
        }

        //Setup arguments
        StringList args;
        args.append("-v 2c -c public 192.168.123.123");
        args.append("1.3.6.1.2.1.1.5.0");
        args.append(mGetTempMIB + ".1");
        args.append(mGetHumidityMIB + ".1");
        args.append(mGetDewPointMIB + ".1");
        Log(lDebug5) << "SNMP arguments: " << args.asString();

        //Capture output
        Pipe outPipe;

		//Capture stdout and stderr to outPipe
        ProcessHandle ph = Process::launch(mExecutable, args, NULL, &outPipe, &outPipe);

        //Use stream objects to read and write to the pipes
        PipeInputStream istr(outPipe);


		int progress(0);
        int c = istr.get();
        bool exitRequested(false);

        //Read all three values before reporting progress
        string s;
        while (!istr.eof())
        {

            s += (char) c;
            if((c == '\n' || c == '\r') && s.size() > 1)
            {
            	Log(lDebug5) << "Parsing string: "<< s;
            	progress = parseOutput(s);

                if(onProgress && progress == 3)
                {
                	string msg;
                    //Let the calling application do whatever with the data
                    //in the onProgress callback
                    stringstream m;
                    m <<"T = "<<mTemperature<<":"<<"H = "<<mHumidity<<":"<<"D = "<<mDewPoint;
                    msg = m.str();
                    onProgress(progress, (int) &msg);
                }

                //Data should be consumed by now
                s.clear();
            }

            c = istr.get();
            if(mIsTimeToDie && !exitRequested)
            {
                exitRequested = true;
            }
        }

        int rc = ph.wait();
        Log(lDebug5) <<"RC: "<<rc;
    }
    catch(...)
    {
		Log(lError) << "Unhandled exception..";
    }

	Log(lInfo) << "Exiting ENV Sensor Thread..";

    if(onExit)
    {
    	onExit(0,0);
    }

	mIsRunning = false;
	mIsFinished = true;
}

//Parsing text can be ugly..
int EnvironmentalSensorReadThread::parseOutput(const string& s)
{
	//Check string for MIB content
    try
    {
        if(contains(mGetTempResponseTag, s))
        {
            //Got a temperature
            mTemperature = toInt(s, false) / 10.0;
            return 1;
        }
        else if(contains(mGetHumidityResponseTag, s))
        {
            //Got a Humidity
            mHumidity = toInt(s, false);
            return 2;
        }
        else if(contains(mGetDewPointResponseTag, s))
        {
            //Got a Humidity
            mDewPoint = toInt(s, false) / 10.0;
            return 3;
        }

        return 0;
	}
	catch(const MoleculixException& e)
   	{
        Log(lError) << " There was a problem: "<<e.what();
   	}

}

