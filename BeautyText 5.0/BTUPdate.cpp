//---------------------------------------------------------------------------

#pragma hdrstop

#include "BTUPdate.h"
#include "Unit1.h"

//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//	Определяется версия файла программы (точнее цифры после последней точки
//	в номере версии программы), если она меньше, чем версия, написанная в файле
//	на сайте, то запускается программа обновления, а эта закрывается.

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
const int __fastcall TBTextUpdater::getCurrentVer()
{
	DWORD h;
	DWORD Size=GetFileVersionInfoSize(AnsiString(Application->ExeName).c_str(), &h);
	if(Size==0)
		return 0;
	char *buf;
	buf=(char *)GlobalAlloc(GMEM_FIXED, Size);
	if (GetFileVersionInfo(AnsiString(Application->ExeName).c_str(),h,Size,buf)!=0){
		char *ValueBuf;
		UINT Len;
		VerQueryValue(buf, "\\VarFileInfo\\Translation", &(void *)ValueBuf,&Len);
		if (Len>=4){
			AnsiString CharSet=IntToHex((int )MAKELONG(*(int *)(ValueBuf+2),*(int *)ValueBuf), 8);
			if (VerQueryValue(buf,AnsiString("\\StringFileInfo\\"+CharSet+"\\FileVersion").c_str(),&(void*)ValueBuf,&Len)!=0){
				AnsiString ver=ValueBuf;
				ver=ver.SubString(LastDelimiter('.',ver)+1,10);
				return StrToIntDef(ver,0);
			}
		}
	}
	GlobalFree(buf);
	return 0;
}
//---------------------------------------------------------------------------
const int __fastcall TBTextUpdater::getNewVer(const UnicodeString& aPathToVerInfo)
{
	//PathToVerInfo - путь к txt файлу на сервере, в котором написана последняя
	//версия программы
	TIdHTTP *IdHTTP1 =new TIdHTTP;
	UnicodeString newVersion="";
	try{
		newVersion=IdHTTP1->Get(aPathToVerInfo);
	}
	catch(...){
		delete IdHTTP1;
		return 0;
		//"Проблемы с интернетом или сервером.\nПодключите ваш ПК к сети Интернет или попробуйте обновить программу позже.";
	}

	for(UINT i=1;i<=newVersion.Length();i++){
		if(StrToIntDef(newVersion[i],-1)==-1){
			newVersion.Delete(i,1);
			i--;
		}
	}

	delete IdHTTP1;
	return StrToIntDef(newVersion,0);
}
//---------------------------------------------------------------------------
const bool __fastcall TBTextUpdater::updateAvailable(const UnicodeString& aPathToVerInfo)
{
	const int ver=getCurrentVer();
	int newVer=getNewVer(aPathToVerInfo);

	if(ver==0||newVer==0)
		return false;

	if(ver<newVer)
		return true;

	return false;
}
//---------------------------------------------------------------------------
const UnicodeString __fastcall TBTextUpdater::checkUpdate(const UnicodeString& aPathToVerInfo)
{
	if(updateAvailable(aPathToVerInfo)){
		if(MessageBox(Form1->Handle,"Доступно обновление. Обновить сейчас?","BeautyText",MB_YESNO|MB_ICONQUESTION)==IDYES){
			const char* path=AnsiString(ExtractFilePath(Application->ExeName)+"BeautyTextUpdater.exe").c_str();
			ShellExecute(0,"open",path,NULL,0,SW_SHOW);
			delete path;
			Form1->Close();
			return "Доступно обновление";
		}
		else{
			return "Доступно обновление";
		}
	}
	else{
		return "Обновление недоступно";
	}
}
