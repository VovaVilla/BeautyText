//---------------------------------------------------------------------------

#pragma hdrstop

#include "TTranslate.h"
#pragma package(smart_init)
//---------------------------------------------------------------------------
_fastcall TTranslate::TTranslate()
{
	IdHTTP1=new TIdHTTP(NULL);
	IdSSLIOHandlerSocketOpenSSL1=new TIdSSLIOHandlerSocketOpenSSL(NULL);
	IdHTTP1->IOHandler=IdSSLIOHandlerSocketOpenSSL1;
}
//---------------------------------------------------------------------------
_fastcall TTranslate::~TTranslate()
{
	delete IdSSLIOHandlerSocketOpenSSL1;
	delete IdHTTP1;
}
//---------------------------------------------------------------------------
UnicodeString __fastcall TTranslate::GetTranslateRuToEn(UnicodeString aStr)
{
	if(aStr.IsEmpty()){
		aStr="Пустая строка запроса";
		return aStr;
	}
	UnicodeString result="";
	UnicodeString request="https://translate.google.ru/translate_a/single?client=t&sl=ru&tl=en&hl=ru&dt=bd&dt=ex&dt=ld&dt=md&dt=qca&dt=rw&dt=rm&dt=ss&dt=t&dt=at&ie=UTF-8&oe=UTF-8&trs=1&inputm=1&ssel=5&tsel=5&swap=1&otf=1&kc=1&tk=286877.148738&q=";
	request+=aStr;

	request=IdHTTP1->URL->URLEncode(request);

	try{
		result=IdHTTP1->Get(request);
	}
	catch(...){
		aStr="Проблемы с сервером.\n Проверьте соединение с Интренетом или попробуйте повторить запрос позже.";
		delete IdSSLIOHandlerSocketOpenSSL1;
		delete IdHTTP1;
		return aStr;
	}
	FParseResponse(result);
	return result;

	delete IdSSLIOHandlerSocketOpenSSL1;
	delete IdHTTP1;
}
//---------------------------------------------------------------------------
UnicodeString __fastcall TTranslate::GetTranslateEnToRu(UnicodeString aStr)
{
	if(aStr.IsEmpty()){
		aStr="Пустая строка запроса";
		return aStr;
	}


	UnicodeString result="";
	UnicodeString request="https://translate.google.ru/translate_a/single?client=t&sl=ru&tl=en&hl=ru&dt=bd&dt=ex&dt=ld&dt=md&dt=qca&dt=rw&dt=rm&dt=ss&dt=t&dt=at&ie=UTF-8&oe=UTF-8&otf=1&trs=1&inputm=1&ssel=6&tsel=3&kc=1&tk=258007.379305&q=";
	request+=aStr;

	request=IdHTTP1->URL->URLEncode(request);

	IdHTTP1->Request->UserAgent="123";

	try{
		result=IdHTTP1->Get(request);
	}
	catch(...){
		aStr="Проблемы с сервером.\n Проверьте соединение с Интренетом или попробуйте повторить запрос позже.";
		delete IdSSLIOHandlerSocketOpenSSL1;
		delete IdHTTP1;
		return aStr;
	}
	FParseResponse(result);
	return result;

	delete IdSSLIOHandlerSocketOpenSSL1;
	delete IdHTTP1;
}
//---------------------------------------------------------------------------
void __fastcall TTranslate::FParseResponse(UnicodeString & aStr)
{
	aStr.Delete(1,aStr.Pos("\""));
	aStr.Delete(aStr.Pos("\""),aStr.Length());
	return;
}
//---------------------------------------------------------------------------


