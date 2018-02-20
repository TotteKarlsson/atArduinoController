#ifndef TWatchDogSensorFrameH
#define TWatchDogSensorFrameH
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include "core/WatchDogSensor.h"
#include "TFloatLabeledEdit.h"
#include "TSTDStringLabeledEdit.h"
#include <Vcl.ExtCtrls.hpp>
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
class TWatchDogSensorFrame : public TFrame
{
    __published:
	TGroupBox *GroupBox1;
	TSTDStringLabeledEdit *DeviceID;
	TSTDStringLabeledEdit *DeviceAlias;
	TFloatLabeledEdit *TemperatureE;
	TFloatLabeledEdit *HumidityE;
	TFloatLabeledEdit *DewPointE;
	TLabel *IsConnectedLbl;
	TLabel *Lbl;

    private:
		WatchDogSensor*				mSensor;

    public:
        		__fastcall 			TWatchDogSensorFrame(TComponent* Owner);
        void						populate(WatchDogSensor* s);
        WatchDogSensor*				getSensor(){return mSensor;}
};

extern PACKAGE TWatchDogSensorFrame *WatchDogSensorFrame;

#endif
