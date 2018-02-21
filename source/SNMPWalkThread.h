#ifndef SNMPWalkThreadH
#define SNMPWalkThreadH
#include <functional>
#include <string>
#include "mtkThread.h"
//---------------------------------------------------------------------------

using namespace mtk;
using std::string;

class SNMPWalkThread : public mtk::Thread
{
	typedef boost::function<void(int, int)> Callback;
	public:
								SNMPWalkThread(const string& executable = "c:\\usr\\bin\\snmpwalk.exe");
        void					setWalkParameters(const string& ip, const string& oidRoot);
        virtual void            run();
		void					assignCallBacks(Callback one, Callback two, Callback three);

    protected:
    	string 				    mExecutable;
        string					mIP;
        string					mOIDRoot;

	    Callback 			    onEnter;
	    Callback 			    onProgress;
	    Callback 			    onExit;
		int 					parseOutput(const string& s);
};

#endif
