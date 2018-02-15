//---------------------------------------------------------------------------

#ifndef TWatchDogServerFrameH
#define TWatchDogServerFrameH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include "TSTDStringLabeledEdit.h"
#include <Vcl.ExtCtrls.hpp>
#include "TArrayBotBtn.h"
#include <Vcl.Buttons.hpp>
//---------------------------------------------------------------------------
class TWatchDogServerFrame : public TFrame
{
__published:	// IDE-managed Components
	TSTDStringLabeledEdit *STDStringLabeledEdit1;
	TGroupBox *GroupBox1;
	TGroupBox *GroupBox2;
	TSTDStringLabeledEdit *mMIBRoot;
	TArrayBotButton *ArrayBotButton1;
	TSTDStringLabeledEdit *STDStringLabeledEdit3;
private:	// User declarations
public:		// User declarations
	__fastcall TWatchDogServerFrame(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TWatchDogServerFrame *WatchDogServerFrame;
//---------------------------------------------------------------------------
#endif
