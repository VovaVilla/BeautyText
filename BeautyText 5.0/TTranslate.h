//---------------------------------------------------------------------------

#ifndef TTranslateH
#define TTranslateH

#include <IdHTTP.hpp>
#include <IdIOHandler.hpp>
#include <IdIOHandlerSocket.hpp>
#include <IdIOHandlerStack.hpp>
#include <IdSSL.hpp>
#include <IdSSLOpenSSL.hpp>
#include <IdTCPClient.hpp>
#include <IdTCPConnection.hpp>

//---------------------------------------------------------------------------
class TTranslate{
public:
	__fastcall TTranslate();
	__fastcall ~TTranslate();
	UnicodeString __fastcall GetTranslateRuToEn(UnicodeString);
	UnicodeString __fastcall GetTranslateEnToRu(UnicodeString);
private:
	TIdHTTP *IdHTTP1;
	TIdSSLIOHandlerSocketOpenSSL *IdSSLIOHandlerSocketOpenSSL1;
	void __fastcall FParseResponse(UnicodeString &);
};


#endif
