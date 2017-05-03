//---------------------------------------------------------------------------

#ifndef TTesuckH
#define TTesuckH

#include <vcl.h>
#include <IdBaseComponent.hpp>
#include <IdComponent.hpp>
#include <IdHTTP.hpp>
#include <IdIOHandler.hpp>
#include <IdIOHandlerSocket.hpp>
#include <IdIOHandlerStack.hpp>
#include <IdSSL.hpp>
#include <IdSSLOpenSSL.hpp>
#include <IdTCPClient.hpp>
#include <IdTCPConnection.hpp>
#include <system.JSON.hpp>
//---------------------------------------------------------------------------
class TTesuck{
public:
	_fastcall TTesuck();
	_fastcall ~TTesuck();
	UnicodeString _fastcall getSummarize(UnicodeString,int);
	UnicodeString _fastcall getWords(UnicodeString);
private:
	TIdHTTP *IdHTTP1;
	TIdSSLIOHandlerSocketOpenSSL *IdSSLIOHandlerSocketOpenSSL1;
	TStringStream *sStreamIn;
	TStringStream *sStreamOut;
	AnsiString _fastcall JSONToString(UnicodeString);
	int _fastcall getNum—lauses(UnicodeString);
	UnicodeString _fastcall ampToSpecSymb(UnicodeString aStr);
	UnicodeString _fastcall specSymbToAmp(UnicodeString aStr);
};



#endif
