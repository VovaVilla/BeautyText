//---------------------------------------------------------------------------

#ifndef TGetWikiTextH
#define TGetWikiTextH
#include <vcl.h>
#include <IdHTTP.hpp>
#include <IdIOHandler.hpp>
#include <IdIOHandlerSocket.hpp>
#include <IdIOHandlerStack.hpp>
#include <IdSSL.hpp>
#include <IdSSLOpenSSL.hpp>
#include"Wininet.h"
#include<vector>

using namespace std;
//---------------------------------------------------------------------------
struct PairTags{
	int start;
	int end;
};

class TGetWikiText{
public:
	TGetWikiText(){};

	UnicodeString __fastcall GetWikiText(UnicodeString);
	UnicodeString __fastcall GetHTMLWikiText(UnicodeString);
	void __fastcall GetHTMLWikiPage(UnicodeString);

private:
	vector<int> FOpenTagsVec;
	vector<int> FCloseTagsVec;
	vector<PairTags> FPairsVec;
	UnicodeString FWikiText;
	UnicodeString FDocumentPath;
	void __fastcall FFillOpenDoubleFigure();
	void __fastcall FFillCloseDoubleFigure();
	void __fastcall FFillOpenHref();
	void __fastcall FFillCloseHref();
	void __fastcall FillWikiText(UnicodeString);
	void __fastcall FFillPairsVec();
	int __fastcall FFindStartPosForPairsVec(int);
	void __fastcall FDeleteInnerTags(PairTags);
	void __fastcall FDeleteDoubleFiguresTags();
	void __fastcall FDeleteHrefTags();
	UnicodeString __fastcall FGetDataFromDouble(UnicodeString);
	void __fastcall FDeleteAloneHref();
	void __fastcall FChangeDoubleSq();
	void __fastcall FDeleteFileBox();
	void __fastcall FDeleteAloneFigure();
	void __fastcall FDeleteHeader();
	void __fastcall FDeleteFooter();
	void __fastcall FConvertCodeToOpenTags();
	void __fastcall FReplaceHeadTags();
	void __fastcall FConvertToBrTags();
	void __fastcall FChangeDates();
	void __fastcall FDeleteSpecialBox();
	void __fastcall FChangeAlternateLangName();
};

#endif
