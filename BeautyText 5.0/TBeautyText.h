//---------------------------------------------------------------------------

#ifndef TBeautyTextH
#define TBeautyTextH
#include <vcl.h>
//---------------------------------------------------------------------------

class TBeautyText{
public:
	const UnicodeString __fastcall ChangeLanguage(const UnicodeString& aStr,const UnicodeString& toLang);
	const UnicodeString __fastcall BeautyText(const UnicodeString& aStr);
	const UnicodeString __fastcall ChangeRegister(const UnicodeString& aStr, const int& reg);
	const UnicodeString __fastcall DeleteDuplicatesStrings(const UnicodeString& aStr);
	const UnicodeString __fastcall Alphabetically(const UnicodeString& aStr);
};


#endif
