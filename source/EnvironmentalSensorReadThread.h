#ifndef EnvironmentalSensorReadThreadH
#define EnvironmentalSensorReadThreadH
#include <functional>
#include <string>
#include "mtkThread.h"
#include "WatchDogSensor.h"
//---------------------------------------------------------------------------

using namespace mtk;
using std::string;

class EnvironmentalSensorReadThread : mtk::Thread
{
	typedef boost::function<void(int, int)> Callback;
	public:
								EnvironmentalSensorReadThread(const string& executable = "c:\\usr\\bin\\snmpget.exe");
		void					assignCallBacks(Callback one, Callback two, Callback three);
        void					assignSensor(WatchDogSensor* aSensor);
        virtual void            run();

    protected:
    	double					mTemperature;
    	double					mHumidity;
    	double					mDewPoint;

    	string 				    mExecutable;
        string					mGetTempMIB;
        string					mGetHumidityMIB;
        string					mGetDewPointMIB;
		string					mGetTempResponseTag;
		string					mGetHumidityResponseTag;
		string					mGetDewPointResponseTag;

	    Callback 			    onEnter;
	    Callback 			    onProgress;
	    Callback 			    onExit;
		int 					parseOutput(const string& s);
};





#endif
