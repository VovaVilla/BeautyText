//---------------------------------------------------------------------------

#include <System.hpp>
#pragma hdrstop

#include "Unit2.h"
#include "Unit1.h"
#include "TGetWikiText.h"
#pragma package(smart_init)
//---------------------------------------------------------------------------

//   Important: Methods and properties of objects in VCL can only be
//   used in a method called using Synchronize, for example:
//
//      Synchronize(&UpdateCaption);
//
//   where UpdateCaption could look like:
//
//      void __fastcall TW::UpdateCaption()
//      {
//        Form1->Caption = "Updated in a thread";
//      }
//---------------------------------------------------------------------------

__fastcall TW::TW(bool CreateSuspended)
	: TThread(CreateSuspended)
{
}
//---------------------------------------------------------------------------
void __fastcall TW::Execute()
{
	for(UINT i=0;i<1;i++){

		Form1->Memo1->Lines->Add(i);
		UnicodeString request="Месси";
//		request=Form1->Edit1->Text;
//		request="https://ru.wikipedia.org/wiki/%D0%A1%D0%BB%D1%83%D0%B6%D0%B5%D0%B1%D0%BD%D0%B0%D1%8F:%D0%A1%D0%BB%D1%83%D1%87%D0%B0%D0%B9%D0%BD%D0%B0%D1%8F_%D1%81%D1%82%D1%80%D0%B0%D0%BD%D0%B8%D1%86%D0%B0";
		UnicodeString result="";
		TGetWikiText *getWikiText=new TGetWikiText;
		result+=getWikiText->GetHTMLWikiText(request);
		delete getWikiText;
//		Sleep(random(1000));
		TStringStream *r2= new TStringStream(result,TEncoding::UTF8,true);
		r2->SaveToFile("after.html");
		delete r2;
		ShellExecute( NULL,"open","after.html",NULL,NULL,SW_SHOW);
	}
	//---- Place thread code here ----
}
//---------------------------------------------------------------------------
