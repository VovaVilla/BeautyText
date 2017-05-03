//---------------------------------------------------------------------------

#ifndef TBeautyTextH
#define TBeautyTextH
#include <vcl.h>
//---------------------------------------------------------------------------

class TBeautyText{
public:
	UnicodeString __fastcall ChangeLanguage (UnicodeString str,UnicodeString toLang);
	UnicodeString __fastcall BeautyText (UnicodeString st);
	UnicodeString __fastcall ChangeRegister (UnicodeString st, int reg);
};


#endif
