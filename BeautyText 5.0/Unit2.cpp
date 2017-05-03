//---------------------------------------------------------------------------

#include <System.hpp>
#pragma hdrstop

#include "Unit2.h"
#include "Unit1.h"
#include "TGetWikiText.h"
#include "TSendStatistics.h"
#include "TTesuck.h"
#include "BTUpdate.h"
#include "IniFiles.hpp"
#include <memory>
#pragma package(smart_init)
//---------------------------------------------------------------------------

//   Important: Methods and properties of objects in VCL can only be
//   used in a method called using Synchronize, for example:
//
//      Synchronize(&UpdateCaption);
//
//   where UpdateCaption could look like:
//
//      void __fastcall TWikiThread::UpdateCaption()
//      {
//        Form1->Caption = "Updated in a thread";
//      }

extern bool getWiki;
extern bool getTesuckSummarize;
extern bool getTesuckWords;
extern bool checkNet;
extern bool bCheckUpdate;


const UnicodeString firstStartStatAdress="http://xn--e1alheohn5d.xn--p1ai/st/BeautyTextFirstStart.html";
const UnicodeString startStatAdress="http://xn--e1alheohn5d.xn--p1ai/st/BeautyTextStart.html";

extern bool bFirstStart;

//---------------------------------------------------------------------------
UnicodeString __fastcall deleteQuotes(const UnicodeString& aStr)
{
	UnicodeString result=aStr;
	while(result.Pos("\"")!=0)
		result.Delete(result.Pos("\""),1);
	return result;
}
//---------------------------------------------------------------------------
const bool __fastcall networkAvailable()
{
	TIdHTTP *http=new TIdHTTP;
	TIdSSLIOHandlerSocketOpenSSL *ssl=new TIdSSLIOHandlerSocketOpenSSL;

	http->IOHandler=ssl;
	http->HandleRedirects=true;

	CoInitialize(NULL);

	try{
		http->Get("https://www.google.com");
	}
	catch(...){
		delete ssl;
		delete http;
		return false;
	}
	delete ssl;
	delete http;
	return true;
}
//---------------------------------------------------------------------------
void __fastcall checkNetwork(){
	if(networkAvailable()){
		Form1->TabSheet2->TabVisible=true;
		Form1->TabSheet3->TabVisible=true;
		Form1->TabSheet4->TabVisible=false;

		Form1->WebBrowser1->Navigate(ExtractFilePath(Application->ExeName)+"html/loadingWiki.html");
		Form1->Edit1->Text="Случайная статья";
		getWiki=true;
	}
	else{
		Form1->TabSheet2->TabVisible=false;
		Form1->TabSheet3->TabVisible=false;
		Form1->TabSheet4->TabVisible=true;
		Form1->PageControl1->ActivePage=Form1->TabSheet4;
	}
}
//---------------------------------------------------------------------------
__fastcall TWikiThread::TWikiThread(bool CreateSuspended)
	: TThread(CreateSuspended)
{
}
//---------------------------------------------------------------------------
void __fastcall TWikiThread::Execute()
{
    Sleep(500);
	if(bFirstStart){
		TSendStatistics *sendSt=new TSendStatistics(firstStartStatAdress);
		sendSt->send("FirstStartBeautyText");
		delete sendSt;
	}
	else{
		TSendStatistics *sendSt=new TSendStatistics(startStatAdress);
		sendSt->send("StartBeautyText");
		delete sendSt;
    }


	//---- Place thread code here ----
	while(1){
		if(getWiki){
			getWiki=false;
			if(networkAvailable()){
				std::tr1::shared_ptr<TGetWikiText> wt(new TGetWikiText);
				wt->GetHTMLWikiPage(Form1->Edit1->Text);
				if(Terminated)
					return;

				Form1->WebBrowser1->Navigate(ExtractFilePath(Application->ExeName)+"after.html");

				//переместить фокус на webbrowser
				POINT oldPos;
				GetCursorPos(&oldPos);
				SetCursorPos(Form1->Left+50,Form1->Top+200);
				mouse_event(MOUSEEVENTF_LEFTDOWN,0,0,0,0); // нажали левую копку мыши
				mouse_event(MOUSEEVENTF_LEFTUP,0,0,0,0); // отпустили левую кнопку мыши ( НЕ ЗАБЫВАТЬ )
				SetCursorPos(oldPos.x,oldPos.y);


				if(Form1->Edit1->Text.LowerCase()!="случайная статья")
					Form1->Label2->Visible=true;
				else
					Form1->Label2->Visible=false;
			}
            else{
				Synchronize(&hideTabsOnForm);
			}
		}

		if(getTesuckSummarize){
			getTesuckSummarize=false;
			if(networkAvailable()){
				std::tr1::shared_ptr<TTesuck> tesuck(new TTesuck);
				Form1->RichEdit2->Text=tesuck->getSummarize(Form1->RichEdit3->Text,StrToIntDef(Form1->ComboBox1->Text,0));
			}
            else{
				Synchronize(&hideTabsOnForm);
			}
		}

		if(getTesuckWords){
			getTesuckWords=false;
			if(networkAvailable()){
				std::tr1::shared_ptr<TTesuck> tesuck(new TTesuck);
				UnicodeString tesWords=tesuck->getWords(Form1->RichEdit3->Text);
				Form1->RichEdit2->Text=deleteQuotes(tesWords);
            }
			else{
				Synchronize(&hideTabsOnForm);
			}
		}

		if(checkNet){
			checkNet=false;
			if(networkAvailable()){
				Synchronize(&showTabsOnForm);
			}
			else{
				Synchronize(&hideTabsOnForm);
			}
		}

		if(bCheckUpdate){
			bCheckUpdate=false;
			Synchronize(&writeUpdateStatus);
		}

		if(Terminated){
			break;
		}
		Sleep(1);
	}
}
//---------------------------------------------------------------------------
void __fastcall TWikiThread::showTabsOnForm()
{
	Form1->TabSheet2->TabVisible=true;
	Form1->TabSheet3->TabVisible=true;
	Form1->TabSheet4->TabVisible=false;

	Form1->WebBrowser1->Navigate(ExtractFilePath(Application->ExeName)+"html/loadingWiki.html");
	Form1->Edit1->Text="Случайная статья";
	getWiki=true;
}
//---------------------------------------------------------------------------
void __fastcall TWikiThread::hideTabsOnForm()
{
	Form1->TabSheet2->TabVisible=false;
	Form1->TabSheet3->TabVisible=false;
	Form1->TabSheet4->TabVisible=true;
	Form1->PageControl1->ActivePage=Form1->TabSheet4;
}
//---------------------------------------------------------------------------
void __fastcall TWikiThread::writeUpdateStatus()
{
	TIniFile *Ini=new TIniFile(ExtractFilePath(Application->ExeName)+"BeautySettings.ini");
	const UnicodeString pathNewVer=Ini->ReadString("settings","pathWithNewVersionInfo","null");
	delete Ini;

	if(pathNewVer=="null"){
		Form1->Label10->Caption="Обновление недоступно";
		return;
	}

	std::tr1::shared_ptr<TBTextUpdater> btUpd(new TBTextUpdater);
	Form1->Label10->Caption=btUpd->checkUpdate(pathNewVer);
}
