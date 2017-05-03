//---------------------------------------------------------------------------


#pragma hdrstop

#include "TTesuck.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)
//---------------------------------------------------------------------------
_fastcall TTesuck::TTesuck()
{
	IdHTTP1=new TIdHTTP(NULL);
	IdSSLIOHandlerSocketOpenSSL1=new TIdSSLIOHandlerSocketOpenSSL(NULL);
	IdHTTP1->IOHandler=IdSSLIOHandlerSocketOpenSSL1;
	sStreamOut = new TStringStream;
}
//---------------------------------------------------------------------------
_fastcall TTesuck::~TTesuck()
{
	delete IdHTTP1;
	delete IdSSLIOHandlerSocketOpenSSL1;
	delete sStreamOut;
}
//---------------------------------------------------------------------------
UnicodeString _fastcall TTesuck::getSummarize(UnicodeString aStr,int Percent)
{
	aStr=ampToSpecSymb(aStr);
	aStr.Insert("text=",1);
	if(Percent){
		int col=getNum—lauses(aStr)/100.0*Percent;
		aStr+="&sentences=";
		aStr+=IntToStr(col);
	}
	sStreamOut->Clear();
	sStreamIn=new TStringStream(aStr, TEncoding::UTF8,true);
	try{
		IdHTTP1->Post("http://tesuck.eveel.ru/summarize.json",sStreamIn,sStreamOut);
	}
	catch(...){
		return "Internet or/and server error";
	}
	delete sStreamIn;
	return JSONToString(UTF8ToUnicodeString(specSymbToAmp(sStreamOut->DataString)));
}
//---------------------------------------------------------------------------
UnicodeString _fastcall TTesuck::getWords(UnicodeString aStr)
{
	aStr=ampToSpecSymb(aStr);
	aStr.Insert("text=",1);
	sStreamOut->Clear();
	sStreamIn=new TStringStream(aStr, TEncoding::UTF8,true);
	sStreamIn->WriteString(aStr);
	try{
		IdHTTP1->Post("http://tesuck.eveel.ru/extract.json",sStreamIn,sStreamOut);
	}
	catch(...){
		return "Internet or/and server error";
	}
	return JSONToString(UTF8ToUnicodeString(specSymbToAmp(sStreamOut->DataString)));
}
//---------------------------------------------------------------------------
AnsiString _fastcall TTesuck::JSONToString(UnicodeString aStr)
{
	UnicodeString result="";
	TJSONObject *jsObj =(TJSONObject*)TJSONObject::ParseJSONValue(aStr);
	for(UINT i=0;i<jsObj->Count;i++){
		result+=jsObj->Pairs[i]->JsonString->ToString();
		result+="\n";
	}
	delete jsObj;
	return result;
}
//---------------------------------------------------------------------------
int _fastcall TTesuck::getNum—lauses(UnicodeString aStr)
{
	int result=0;
	for(UINT i=1;i<=aStr.Length();i++){
		if(aStr[i]=='.'||aStr[i]=='!'||aStr[i]=='?'){
			result++;
			while(i<=aStr.Length()&&(aStr[i]=='.'||aStr[i]=='!'||aStr[i]=='?')){
				i++;
			}
		}
	}
	return result;
}
//---------------------------------------------------------------------------
UnicodeString _fastcall TTesuck::ampToSpecSymb(UnicodeString aStr)
{
	for(UINT i=1;i<=aStr.Length();i++){
		if(aStr[i]=='&')
			aStr[i]='~';
	}
	return aStr;
}
//---------------------------------------------------------------------------
UnicodeString _fastcall TTesuck::specSymbToAmp(UnicodeString aStr)
{
	for(UINT i=1;i<=aStr.Length();i++){
		if(aStr[i]=='~')
			aStr[i]='&';
	}
	return aStr;
}

