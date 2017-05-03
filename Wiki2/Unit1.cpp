//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
#include "Unit2.h"
#include "TGetWikiText.h"

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

TGetWikiText *wt=new TGetWikiText;
wt->GetHTMLWikiPage(Edit1->Text);
delete wt;


// TW*tw=new TW(false);



	//{{цитата|ла-ла-ла....
	//{{цитата|<poem>"ла""ла"....
}
//---------------------------------------------------------------------------
