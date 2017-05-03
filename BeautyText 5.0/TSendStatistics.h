//---------------------------------------------------------------------------

#ifndef TSendStatisticsH
#define TSendStatisticsH
#include <vcl.h>

//---------------------------------------------------------------------------

class TSendStatistics{
private:
	UnicodeString adress;
public:
	__fastcall TSendStatistics(const UnicodeString& aAdress);
	void __fastcall send(const UnicodeString& aMessage, const TDateTime& aDate=Now());
};
#endif
