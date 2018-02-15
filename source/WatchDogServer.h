#ifndef WatchDogServerH
#define WatchDogServerH
#include <string>
#include <vector>
//---------------------------------------------------------------------------

using std::string;
using std::vector;

class WatchDogSensor;

class WatchDogServer
{
	public:
									WatchDogServer();
		bool						addSensor(WatchDogSensor* sensor);
        void						setIP(const string& ip);
    protected:

    	string						mIP;

    								//!These MIB's are used to query the hardware for values
        string						mMIBRoot;
    	string						mIP_MIB;
        string						mDevicePresentMIB;


        vector<WatchDogSensor*>		mSensors;
};


#endif
