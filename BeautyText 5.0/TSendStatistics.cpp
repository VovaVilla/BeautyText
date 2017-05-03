//---------------------------------------------------------------------------

#pragma hdrstop

#include "TSendStatistics.h"
#include <IdHTTP.hpp>
//---------------------------------------------------------------------------
#pragma package(smart_init)


__fastcall TSendStatistics::TSendStatistics(const UnicodeString& aAdress)
{
	this->adress=aAdress;
}
//---------------------------------------------------------------------------
void __fastcall TSendStatistics::send(const UnicodeString& aMessage, const TDateTime& aDate)
{
	const UnicodeString message=this->adress+"?_message:"+aMessage+"_date:"+DateTimeToStr(aDate);
	TIdHTTP* http=new TIdHTTP;
	try{
		http->Get(message);
	}
	catch(...){
		//
	}
	delete http;
}
//---------------------------------------------------------------------------
