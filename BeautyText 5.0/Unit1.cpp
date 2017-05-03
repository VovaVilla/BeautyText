//---------------------------------------------------------------------------
//Версия для хранения в GIT

#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
#include "Unit2.h"
#include "TBeautyText.h"
#include "TGetWikiText.h"
#include "TTesuck.h"
#include "BTUpdate.h"
#include <Clipbrd.hpp>
#include <vector>
#include <Registry.hpp>
#include <memory>
#include "IniFiles.hpp"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;

bool getWiki=false;
bool getTesuckSummarize=false;
bool getTesuckWords=false;
bool checkNet=false;
bool bCheckUpdate=false;
std::tr1::shared_ptr<TWikiThread> wikiThread(new TWikiThread(false));
std::vector<UnicodeString> textHistoryVec;
bool bFirstStart=false;
String aboutPath;

//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button1Click(TObject *Sender)
{
	TBeautyText *bt=new TBeautyText;
	RichEdit1->Text=bt->BeautyText(RichEdit1->Text);
	delete bt;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button2Click(TObject *Sender)
{
	try{
		Clipboard()->AsText=RichEdit1->Text;
	}
	catch(...){
		//
	}
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button3Click(TObject *Sender)
{
	try{
		RichEdit1->Text=Clipboard()->AsText;
	}
	catch(...){
		//
	}
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button4Click(TObject *Sender)
{
	TBeautyText *bt=new TBeautyText;
	RichEdit1->Text=bt->ChangeLanguage(RichEdit1->Text,"1033");
	delete bt;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button5Click(TObject *Sender)
{
	TBeautyText *bt=new TBeautyText;
	RichEdit1->Text=bt->ChangeLanguage(RichEdit1->Text,"1049");
	delete bt;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button6Click(TObject *Sender)
{
	TBeautyText *bt=new TBeautyText;
	RichEdit1->Text=bt->ChangeRegister(RichEdit1->Text,2);
	delete bt;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button7Click(TObject *Sender)
{
	TBeautyText *bt=new TBeautyText;
	RichEdit1->Text=bt->ChangeRegister(RichEdit1->Text,3);
	delete bt;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button8Click(TObject *Sender)
{
	TBeautyText *bt=new TBeautyText;
	RichEdit1->Text=bt->ChangeRegister(RichEdit1->Text,1);
	delete bt;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button9Click(TObject *Sender)
{
	TBeautyText *bt=new TBeautyText;
	RichEdit1->Text=bt->ChangeRegister(RichEdit1->Text,0);
	delete bt;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button10Click(TObject *Sender)
{
	WebBrowser1->Navigate(ExtractFilePath(Application->ExeName)+"html/loadingWiki.html");
	getWiki=true;
	return;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button11Click(TObject *Sender)
{
	RichEdit2->Text="Пожалуйста, подождите";
	getTesuckSummarize=true;


//	Timer2->Enabled=true;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button12Click(TObject *Sender)
{
	RichEdit2->Text="Пожалуйста, подождите";
	getTesuckWords=true;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormCreate(TObject *Sender)
{
	TIniFile *Ini=new TIniFile(ExtractFilePath(Application->ExeName)+"BeautySettings.ini");
	TFileStream *fS;
	try{
		fS=new TFileStream(ExtractFilePath(Application->ExeName)+"BeautySettings.ini",fmOpenRead);
		delete fS;
	}
	catch(...){
		TFileStream *fS=new TFileStream(ExtractFilePath(Application->ExeName)+"BeautySettings.ini",fmCreate);
		delete fS;

		Ini->WriteBool("settings","autoupdate",true);
		Ini->WriteInteger("settings","activepage",5);
		Ini->WriteString("settings","pathWithNewVersionInfo","http://xn--e1alheohn5d.xn--p1ai/forPrograms/beautytext/lastVersion.txt");
		Ini->WriteString("settings","aboutPath","http://xn--e1alheohn5d.xn--p1ai/programs/beautytext/");

		bFirstStart=true;
	}

	CheckBox1->Checked=Ini->ReadBool("settings","autoupdate",false);
	int actPage=Ini->ReadInteger("settings","activepage",5);

	aboutPath=Ini->ReadString("settings","aboutPath","http://xn--e1alheohn5d.xn--p1ai/programs/beautytext/");

	try{
		switch(actPage){
			case 1:{
				PageControl1->ActivePage=Form1->TabSheet1;
				break;
			}
			case 2:{
				PageControl1->ActivePage=Form1->TabSheet2;
				break;
			}
			case 3:{
				PageControl1->ActivePage=Form1->TabSheet3;
				break;
			}
			case 4:{
				PageControl1->ActivePage=Form1->TabSheet4;
				break;
			}
			case 5:{
				PageControl1->ActivePage=Form1->TabSheet5;
				break;
			}
		}
	}
	catch(...){
		PageControl1->ActivePage=Form1->TabSheet5;
	}

	if(CheckBox1->Checked)
		bCheckUpdate=true;

	TBTextUpdater *forVersion=new TBTextUpdater;
	Label27->Caption="  BeautyText 5 version "+IntToStr(forVersion->getCurrentVer());
	Form1->Caption="BeautyText 5."+IntToStr(forVersion->getCurrentVer());
	delete forVersion;

	checkNet=true;

	delete Ini;

	textHistoryVec.clear();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button14Click(TObject *Sender)
{

	Label10->Caption="";

	bCheckUpdate=true;
	checkNet=true;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Edit1Change(TObject *Sender)
{
	if(Edit1->Text=="")
		Button10->Enabled=false;
	else
		Button10->Enabled=true;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Label2Click(TObject *Sender)
{
	ShellExecute(NULL,"open",(AnsiString("https://ru.wikipedia.org/wiki/"+Edit1->Text)).c_str() ,NULL,NULL,SW_SHOW);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button15Click(TObject *Sender)
{
	WebBrowser1->Navigate(ExtractFilePath(Application->ExeName)+"html/loadingWiki.html");
	Edit1->Text="Случайная статья";
	getWiki=true;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button1MouseEnter(TObject *Sender)
{
	Label6->Caption="Убрать из текста лишние и добавить нужные пробелы, отступы и т.д.";
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button1MouseLeave(TObject *Sender)
{
	Label6->Caption="Вставьте текст для исправления в поле выше";
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button2MouseEnter(TObject *Sender)
{
	Label6->Caption="Копировать весь текст в буфер обмена";
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button3MouseEnter(TObject *Sender)
{
    Label6->Caption="Вставить текст из буфера обмена";
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button4MouseEnter(TObject *Sender)
{
	Label6->Caption="Пример: Plhfdcndeqnt -> Здравствуйте";
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button5MouseEnter(TObject *Sender)
{
	Label6->Caption="Пример: Руддщ -> Hello";
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button6MouseEnter(TObject *Sender)
{
	Label6->Caption="Пример: СЛучайное ПредложеНие -> случайное предложение";
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button7MouseEnter(TObject *Sender)
{
	Label6->Caption="Пример: СЛучайное ПредложеНие -> СЛУЧАЙНОЕ ПРЕДЛОЖЕНИЕ";
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button8MouseEnter(TObject *Sender)
{
	Label6->Caption="Пример: СЛучайное ПредложеНие -> Случайное предложение";
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button9MouseEnter(TObject *Sender)
{
	Label6->Caption="Пример: СЛучайное ПредложеНие -> слУЧАЙНОЕ пРЕДЛОЖЕнИЕ";
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button16Click(TObject *Sender)
{
	RichEdit1->Clear();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button16MouseEnter(TObject *Sender)
{
	Label6->Caption="Очистить поле для текста";
}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormCloseQuery(TObject *Sender, bool &CanClose)
{
	wikiThread->Terminate();
    Form1->WebBrowser1->Stop();
	Form1->WebBrowser1->Free();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button11MouseLeave(TObject *Sender)
{
	Label8->Caption="Вставьте текст для сжатия в верхнее поле";
}
//---------------------------------------------------------------------------
void __fastcall TForm1::ComboBox1MouseEnter(TObject *Sender)
{
	Label8->Caption="Оставить n % текста";
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button12MouseEnter(TObject *Sender)
{
	Label8->Caption="Получить ключевые слова из текста";
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button18MouseEnter(TObject *Sender)
{
	Label8->Caption="Копировать результат в буфер обмена";
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button17MouseEnter(TObject *Sender)
{
	Label8->Caption="Вставить текст из буфера обмена";
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button19MouseEnter(TObject *Sender)
{
    Label8->Caption="Очистить оба поля";
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button18Click(TObject *Sender)
{
    try{
		Clipboard()->AsText=RichEdit2->Text;
	}
	catch(...){
		//
	}
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button17Click(TObject *Sender)
{
    try{
		RichEdit3->Text=Clipboard()->AsText;
	}
	catch(...){
		//
	}
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button19Click(TObject *Sender)
{
	RichEdit2->Clear();
	RichEdit3->Clear();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button20Click(TObject *Sender)
{
	checkNet=true;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::CheckBox1Click(TObject *Sender)
{
	TIniFile *Ini=new TIniFile(ExtractFilePath(Application->ExeName)+"BeautySettings.ini");
	Ini->WriteBool("settings","autoupdate",CheckBox1->Checked);
	delete Ini;
}
//---------------------------------------------------------------------------
const int __fastcall numPage()
{
	if(Form1->PageControl1->ActivePage==Form1->TabSheet1)
		return 1;
	if(Form1->PageControl1->ActivePage==Form1->TabSheet2)
		return 2;
	if(Form1->PageControl1->ActivePage==Form1->TabSheet3)
		return 3;
	if(Form1->PageControl1->ActivePage==Form1->TabSheet4)
		return 4;
	return 5;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::PageControl1Change(TObject *Sender)
{
	TIniFile *Ini=new TIniFile(ExtractFilePath(Application->ExeName)+"BeautySettings.ini");
	Ini->WriteInteger("settings","activepage",numPage());
	delete Ini;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Label13Click(TObject *Sender)
{
	ShellExecute(0,"open",AnsiString(aboutPath).c_str(),NULL,0,SW_SHOW);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::RichEdit1Change(TObject *Sender)
{
	if(RichEdit1->Text.Length()==0){
		Panel9->Caption="Символов: 0  Без пробелов: 0  Слов: 0  Предложений: 0";
		return;
	}

	UnicodeString text=RichEdit1->Text;
	TBeautyText *bt=new TBeautyText;
	text=bt->BeautyText(text);
	delete bt;

	int numSymb=text.Length();
	int numSpace=0;
	int numTabs=0;


	for(UINT i=1;i<text.Length();i++){
		if(text[i]==' ')
			numSpace++;
	}

    for(UINT i=1;i<text.Length();i++){
		if(text[i]=='\t')
			numTabs++;
	}

	int numWords=numSpace+numTabs;//+1;
	int numSentences=0;

	for(UINT i=1;i<=text.Length();i++){
		if(i<text.Length()-3){
			if((text[i]=='.'&&text[i+1]==' '&&text[i+2]==text.UpperCase()[i+2]) ||text[i]=='!'||text[i]=='?'||text[i]=='\t')
				numSentences++;
		}
	}

	Panel9->Caption="Символов: "+(IntToStr(numSymb-1))+"  Без пробелов: "+IntToStr(numSymb-numSpace-1)+"  Слов: "+IntToStr(numWords)+"  Предложений: ~"+IntToStr(numSentences);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button21Click(TObject *Sender)
{
	Edit1->Text="";
	Edit1->SetFocus();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Edit1KeyPress(TObject *Sender, System::WideChar &Key)
{
	if(Key==VK_RETURN){
		if(Button10->Enabled){
			Button10->Click();
		}
	}
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button22Click(TObject *Sender)
{
	RichEdit1->Text=textHistoryVec[textHistoryVec.size()-1];
	textHistoryVec.pop_back();
	if(!textHistoryVec.size()){
		Button22->Enabled=false;
	}
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button13Click(TObject *Sender)
{
	TBeautyText *bt=new TBeautyText;
	RichEdit1->Text=bt->Alphabetically(RichEdit1->Text);
	delete bt;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button13MouseEnter(TObject *Sender)
{
	Label6->Caption="Расположить строки в алфавитном порядке";
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button22MouseEnter(TObject *Sender)
{
	Label6->Caption="Отменить последнее действие";
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button1MouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y)
{
	textHistoryVec.push_back(RichEdit1->Text);
	if(textHistoryVec.size()>10){
		textHistoryVec.erase(textHistoryVec.begin());
	}
	Button22->Enabled=true;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button23MouseEnter(TObject *Sender)
{
	Label6->Caption="Удалить повторяющиеся строки";
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button23Click(TObject *Sender)
{
	TBeautyText *bt=new TBeautyText;
	RichEdit1->Text=bt->DeleteDuplicatesStrings(RichEdit1->Text);
	delete bt;
}
//---------------------------------------------------------------------------


