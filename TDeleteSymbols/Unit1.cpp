//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
#include "TBeautyText.h"

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
TBeautyText *bt=new TBeautyText;
UnicodeString testStr="Hello       u          )(world !\t\t   )";
//tds->deleteSymbols(testStr);
//ShowMessage(testStr);
testStr=bt->BeautyText(testStr);
ShowMessage(testStr);


TStringStream *gg=new TStringStream;
gg->WriteString(wt);
gg->SaveToFile("wiki.txt");

}
//---------------------------------------------------------------------------

