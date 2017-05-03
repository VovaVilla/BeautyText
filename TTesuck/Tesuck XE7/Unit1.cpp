//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
#include "TTesuck.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button1Click(TObject *Sender)
{
TStringStream *sStreamIn = new TStringStream;
TStringStream *sStreamOut = new TStringStream;
sStreamIn->LoadFromFile("inRef.txt");
TTesuck *tesuck=new TTesuck;
//UnicodeString result=tesuck->getSummarize(sStreamIn->DataString,20);
UnicodeString result=tesuck->getWords(sStreamIn->DataString);

delete sStreamIn;
delete sStreamOut;
delete tesuck;


ShowMessage(result);


//sStreamOut->SaveToFile("resRef.txt");
}
//---------------------------------------------------------------------------
