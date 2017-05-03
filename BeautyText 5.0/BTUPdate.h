//---------------------------------------------------------------------------

#ifndef BTUPdateH
#define BTUPdateH
#include <vcl.h>
#include <IdHTTP.hpp>
//---------------------------------------------------------------------------

class TBTextUpdater{
	const int __fastcall getNewVer(const UnicodeString& aPathToVerInfo);
	const bool __fastcall updateAvailable(const UnicodeString& aPathToVerInfo);
public:
	const UnicodeString __fastcall checkUpdate(const UnicodeString& aPathToVerInfo);
	const int __fastcall getCurrentVer();
};

#endif
