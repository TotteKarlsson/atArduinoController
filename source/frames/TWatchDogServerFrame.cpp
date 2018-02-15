//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "TWatchDogServerFrame.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "TSTDStringLabeledEdit"
#pragma link "TArrayBotBtn"
#pragma resource "*.dfm"
TWatchDogServerFrame *WatchDogServerFrame;
//---------------------------------------------------------------------------
__fastcall TWatchDogServerFrame::TWatchDogServerFrame(TComponent* Owner)
	: TFrame(Owner)
{
}
//---------------------------------------------------------------------------
