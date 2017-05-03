//---------------------------------------------------------------------------

#pragma hdrstop

#include "TGetWikiText.h"
#include "TBeautyText.h"
#include "Unit1.h"
#include <memory>
//---------------------------------------------------------------------------
#pragma package(smart_init)

UnicodeString vecToStr(vector<int> aVec)
{
	UnicodeString result;
	for(UINT i=0;i<aVec.size();i++){
		result+=IntToStr(aVec[i]);
		result+="; ";
	}
	return result;
}
//---------------------------------------------------------------------------
UnicodeString vecPairToStr(vector<PairTags> aVec)
{
	UnicodeString result;
	for(UINT i=0;i<aVec.size();i++){
		result+=IntToStr(aVec[i].start);
		result+="-";
		result+=IntToStr(aVec[i].end);
		result+="; ";
	}
	return result;
}
//---------------------------------------------------------------------------
UnicodeString __fastcall TGetWikiText::GetWikiText(UnicodeString aArtName)
{
	FillWikiText(aArtName);

	FConvertCodeToOpenTags();
	FChangeDates();
	FChangeAlternateLangName();
	FDeleteDoubleFiguresTags();
	this->FDeleteHrefTags();
//	FDeleteAloneHref();

	FDeleteFileBox();
	FDeleteSpecialBox();
	FChangeDoubleSq();
	FDeleteAloneFigure();
	FDeleteHeader();
	FDeleteFooter();

//	FWikiText=beautyText->BeautyText(FWikiText);

	FConvertToBrTags();
	FReplaceHeadTags();

//	delete beautyText;
	return this->FWikiText;

}
//---------------------------------------------------------------------------
UnicodeString __fastcall TGetWikiText::GetHTMLWikiText(UnicodeString aArtName)
{
	UnicodeString result="";
	result+="<!DOCTYPE HTML><html><head><title>Wiki Text</title><style>h1,h2,h3,h4,h5,h6{margin-left:25px;margin-top:25px;margin-bottom:0px;line-height: 1.5;} p { text-indent: 25px; line-height: 1.5;font-family: \"Times New Roman\", Georgia, Serif; margin-top: 0;  margin-bottom: 0;}body{font-size:14px;}	</style><meta charset=\"utf-8\"></head><body>";
	result+=GetWikiText(aArtName);
	FDocumentPath=StringReplace(FDocumentPath,"_"," ",TReplaceFlags()<< rfReplaceAll);
	result.Insert("<h1>"+FDocumentPath+"</h1><p>",result.Pos("<body>"));
	result+="</body></html>";

	return result;
}
//---------------------------------------------------------------------------
void __fastcall TGetWikiText::GetHTMLWikiPage(UnicodeString aStr)
{
	UnicodeString result="";
	result+=GetHTMLWikiText(aStr);
	TStringStream *r2= new TStringStream(result,TEncoding::UTF8,true);
	r2->SaveToFile("after.html");
	delete r2;
//	ShellExecute( NULL,"open","after.html",NULL,NULL,SW_SHOW);
}
//---------------------------------------------------------------------------
void __fastcall TGetWikiText::FillWikiText(UnicodeString aArtName)
{
	if(aArtName.LowerCase()=="случайная статья"){
		aArtName="https://ru.wikipedia.org/wiki/%D0%A1%D0%BB%D1%83%D0%B6%D0%B5%D0%B1%D0%BD%D0%B0%D1%8F:%D0%A1%D0%BB%D1%83%D1%87%D0%B0%D0%B9%D0%BD%D0%B0%D1%8F_%D1%81%D1%82%D1%80%D0%B0%D0%BD%D0%B8%D1%86%D0%B0";
	}

	TIdHTTP *HTTP =new TIdHTTP;
	TIdSSLIOHandlerSocketOpenSSL *IoHandlerSSL1=new TIdSSLIOHandlerSocketOpenSSL;
	HTTP->IOHandler=IoHandlerSSL1;
	HTTP->HandleRedirects=true;

	UnicodeString url="https://ru.wikipedia.org/w/api.php?action=query&titles=";

	try{
		HTTP->Get(aArtName);
		FDocumentPath=HTTP->URL->URLDecode(HTTP->URL->Document);
	}
	catch(...){
		aArtName[1]=aArtName.UpperCase()[1];
		FDocumentPath=aArtName;
	}

	url+=FDocumentPath;

//	Form1->Memo1->Lines->Add(FDocumentPath);

	url+="&prop=revisions&rvprop=content&format=xml";
	url = HTTP->URL->URLEncode(url);

	try{
		FWikiText=HTTP->Get(url);
	}
	catch(Exception *ex){
		FWikiText="Проблемы с подключением к серверу. ";
		FWikiText+=ex->Message;
	}

	if(FWikiText.Pos("#REDIRECT")){
		FWikiText.Delete(1,FWikiText.Pos("#REDIRECT"));
		int start=FWikiText.Pos("[[");
		int end=FWikiText.Pos("]]")+2;
		aArtName=FGetDataFromDouble(FWikiText.SubString(start,end-start));
		FillWikiText(aArtName);
	}
	else{
		if(FWikiText.Pos("#перенаправление")){
			FWikiText.Delete(1,FWikiText.Pos("#перенаправление"));
			int start=FWikiText.Pos("[[");
			int end=FWikiText.Pos("]]")+2;
			aArtName=FGetDataFromDouble(FWikiText.SubString(start,end-start));
			FillWikiText(aArtName);
		}
		else{
			if(FWikiText.Pos("#Redirect")){
				FWikiText.Delete(1,FWikiText.Pos("#Redirect"));
				int start=FWikiText.Pos("[[");
				int end=FWikiText.Pos("]]")+2;
				aArtName=FGetDataFromDouble(FWikiText.SubString(start,end-start));
				FillWikiText(aArtName);
			}
		}
    }

	HTTP->Disconnect();
	try{
		HTTP->Socket->Close();
	}
	catch(...){
		HTTP->Disconnect();
	}
	delete IoHandlerSSL1;
	delete HTTP;
}
//---------------------------------------------------------------------------
void __fastcall TGetWikiText::FFillOpenDoubleFigure()
{
	FOpenTagsVec.clear();
	UnicodeString copyFWT=FWikiText;
	while(copyFWT.Pos("{{")){
		int pos=copyFWT.Pos("{{");
		FOpenTagsVec.push_back(pos);
		copyFWT.Delete(pos,2);
		copyFWT.Insert("__",pos);
	}
	return;
}
//---------------------------------------------------------------------------
void __fastcall TGetWikiText::FFillCloseDoubleFigure()
{
	FCloseTagsVec.clear();
	UnicodeString copyFWT=FWikiText;
	while(copyFWT.Pos("}}")){
		int pos=copyFWT.Pos("}}");
		FCloseTagsVec.push_back(pos);
		copyFWT.Delete(pos,2);
		copyFWT.Insert("__",pos);
	}
	return;
}
//---------------------------------------------------------------------------
void __fastcall TGetWikiText::FFillPairsVec()
{
	FPairsVec.clear();
	PairTags pairTag;
	for(UINT i=0;i<FCloseTagsVec.size();i++){
		pairTag.end=FCloseTagsVec[i];
		pairTag.start=FFindStartPosForPairsVec(pairTag.end);
		this->FDeleteInnerTags(pairTag);
		FPairsVec.push_back(pairTag);
		FCloseTagsVec.erase(FCloseTagsVec.begin()+i);
		i--;
	}
}
//---------------------------------------------------------------------------
int __fastcall TGetWikiText::FFindStartPosForPairsVec(int aEndPos)
{
	int result=0;

	if(FOpenTagsVec.size()==0){
		return result;
	}
	if(FOpenTagsVec.size()==1){
		result=FOpenTagsVec[0];
		FOpenTagsVec.erase(FOpenTagsVec.begin());
		return result;
	}

	for(UINT i=0;i<FOpenTagsVec.size();i++){
		if(FOpenTagsVec[i]>aEndPos){
			result=FOpenTagsVec[i-1];
			FOpenTagsVec.erase(FOpenTagsVec.begin()+(i-1));
			return result;
		}
	}
	result=FOpenTagsVec[FOpenTagsVec.size()-1];
	FOpenTagsVec.erase(FOpenTagsVec.end());
	return result;
}
//---------------------------------------------------------------------------
void __fastcall TGetWikiText::FDeleteInnerTags(PairTags aPairTag)
{
	for(UINT i=0;i<FPairsVec.size();i++){
		if(aPairTag.start<FPairsVec[i].start&&
		   aPairTag.end>FPairsVec[i].end){
			FPairsVec.erase(FPairsVec.begin()+i);
			i--;
		}
	}
}
//---------------------------------------------------------------------------
void __fastcall TGetWikiText::FDeleteDoubleFiguresTags()
{
	FFillOpenDoubleFigure();
	FFillCloseDoubleFigure();
	FFillPairsVec();

	int delLen=0;
	for(UINT i=0;i<FPairsVec.size();i++){
		int start=FPairsVec[i].start-delLen;
		int end=FPairsVec[i].end-delLen+2;
		FWikiText.Delete(start,end-start);
		delLen+=(end-start);
	}
}
//---------------------------------------------------------------------------
void __fastcall TGetWikiText::FFillOpenHref()
{
	FOpenTagsVec.clear();
	UnicodeString copyFWT=FWikiText;
	while(copyFWT.Pos("<ref")){
		int pos=copyFWT.Pos("<ref");
		FOpenTagsVec.push_back(pos);
		copyFWT.Delete(pos,4);
		copyFWT.Insert("____",pos);
	}
	return;
}
//---------------------------------------------------------------------------
void __fastcall TGetWikiText::FFillCloseHref()
{
	FCloseTagsVec.clear();
	UnicodeString copyFWT=FWikiText;
	while(copyFWT.Pos("</ref>")){
		int pos=copyFWT.Pos("</ref>");
		FCloseTagsVec.push_back(pos);
		copyFWT.Delete(pos,6);
		copyFWT.Insert("______",pos);
	}
	return;
}
//---------------------------------------------------------------------------
void __fastcall TGetWikiText::FDeleteHrefTags()
{
	FFillOpenHref();
	FFillCloseHref();
	FFillPairsVec();

	int delLen=0;
	for(UINT i=0;i<FPairsVec.size();i++){
		int start=FPairsVec[i].start-delLen;
		int end=FPairsVec[i].end-delLen+6;
		FWikiText.Delete(start,end-start);
		delLen+=(end-start);
	}
}
//---------------------------------------------------------------------------
void __fastcall TGetWikiText::FDeleteAloneHref()
{
	while(FWikiText.Pos("<br />")){
		FWikiText.Delete(FWikiText.Pos("<br />"),6);
	}
	while(FWikiText.Pos("<ref")){
		int start=FWikiText.Pos("<ref");
		int end=FWikiText.Pos("/>");
		if(end<start){
			FWikiText.Delete(end,2);
			FWikiText.Insert("MtQs",end);
			continue;
		}		
		FWikiText.Delete(start,(end+2)-start);
	}
	while(FWikiText.Pos("MtQs")){
		int pos=FWikiText.Pos("MtQs");
		FWikiText.Delete(pos,4);
		FWikiText.Insert("/>",pos);
	}
}
//---------------------------------------------------------------------------
void __fastcall TGetWikiText::FChangeDoubleSq()
{
	while(FWikiText.Pos("[[")){
		int start=FWikiText.Pos("[[");
		int end=FWikiText.Pos("]]");
		if(end<start){
			if(end==0){
				FWikiText.Delete(start,2);
				continue;
			}
			FWikiText.Delete(end,2);
			continue;
		}

		UnicodeString toPaste=this->FGetDataFromDouble(FWikiText.SubString(start,(end+2)-start));
		FWikiText.Delete(start,(end+2)-start);
		FWikiText.Insert(toPaste,start);
	}
}
//---------------------------------------------------------------------------
UnicodeString __fastcall TGetWikiText::FGetDataFromDouble(UnicodeString aStr)
{
	while(aStr.Pos('|'))
		aStr.Delete(1,aStr.Pos('|'));

	while(aStr.Pos("[["))
		aStr.Delete(aStr.Pos("[["),2);

	while(aStr.Pos("]]"))
		aStr.Delete(aStr.Pos("]]"),2);
	return aStr;
}
//---------------------------------------------------------------------------
void __fastcall TGetWikiText::FDeleteFileBox()
{
	int numOpen=0;
	while(1){
		int pos=FWikiText.Pos("[[Файл:");
		if(!pos)
			pos=FWikiText.Pos("[[File:");
		if(!pos)
			break;
		for(UINT i=pos;i<FWikiText.Length();i++){
			if(FWikiText[i]=='['&&FWikiText[i+1]=='[')
				numOpen++;
			if(FWikiText[i]==']'&&FWikiText[i+1]==']'){
				numOpen--;
				if(!numOpen){
					FWikiText.Delete(i,2);
					break;
				}
				else{
					FWikiText.Delete(i,2);
					i--;
					continue;
				}
					
			}
			FWikiText.Delete(i,1);			
			i--;
		}
	}
}
//---------------------------------------------------------------------------
void __fastcall TGetWikiText::FDeleteAloneFigure()
{
	int numOpen=0;
	while(FWikiText.Pos('{')){
		for(UINT i=FWikiText.Pos('{');i<FWikiText.Length();i++){
			if(FWikiText[i]=='{')
				numOpen++;
			if(FWikiText[i]=='}'){
				numOpen--;
				if(!numOpen){
					FWikiText.Delete(i,1);
					break;
				}
			}
			FWikiText.Delete(i,1);			
			i--;
		}
	} 
}
//---------------------------------------------------------------------------
void __fastcall TGetWikiText::FDeleteHeader()
{
	int pos=FWikiText.Pos("'''");
	FWikiText.Delete(1,pos-1);
}
//---------------------------------------------------------------------------
void __fastcall TGetWikiText::FDeleteFooter()
{
	int pos=0;
	int a=FWikiText.Pos("== Примечания ==");
		if(!a)
			a=FWikiText.Length();
	int b=FWikiText.Pos("== Литература ==");
		if(!b)
			b=FWikiText.Length();
	int c=FWikiText.Pos("== Ссылки ==");
		if(!c)
			c=FWikiText.Length();
	int d=FWikiText.Pos("</rev>");
		if(!d)
			d=FWikiText.Length();
	pos=min<int>(a,min<int>(b,min<int>(c,d)));
	if(!pos)
		return;
	FWikiText.Delete(pos,FWikiText.Length()-pos+1);
}
//---------------------------------------------------------------------------
void __fastcall TGetWikiText::FConvertCodeToOpenTags()
{
	int pos=0;
	while(FWikiText.Pos("&amp;lt;")){
		pos=FWikiText.Pos("&amp;lt;");
		FWikiText.Delete(pos,8);
		FWikiText.Insert("<",pos);
	}
	while(FWikiText.Pos("&amp;gt;")){
		pos=FWikiText.Pos("&amp;gt;");
		FWikiText.Delete(pos,8);
		FWikiText.Insert(">",pos);
	}

	while(FWikiText.Pos("&gt;")){
		pos=FWikiText.Pos("&gt;");
		FWikiText.Delete(pos,4);
		FWikiText.Insert(">",pos);
	}

	while(FWikiText.Pos("&lt;")){
		pos=FWikiText.Pos("&lt;");
		FWikiText.Delete(pos,4);
		FWikiText.Insert("<",pos);
	}
	while(FWikiText.Pos("&amp;quot;")){
		pos=FWikiText.Pos("&amp;quot;");
		FWikiText.Delete(pos,10);
		FWikiText.Insert("\"",pos);
	}
	while(FWikiText.Pos("&quot;")){
		pos=FWikiText.Pos("&quot;");
		FWikiText.Delete(pos,6);
		FWikiText.Insert("\"",pos);
	}
	while(FWikiText.Pos("&nbsp;")){
		pos=FWikiText.Pos("&nbsp;");
		FWikiText.Delete(pos,6);
		FWikiText.Insert(" ",pos);
	}
}
//---------------------------------------------------------------------------
void __fastcall TGetWikiText::FConvertToBrTags()
{
	int pos=0;
	while(FWikiText.Pos("\r\n")){
		pos=FWikiText.Pos("\r\n");
		FWikiText.Delete(pos,2);
		FWikiText.Insert("</p><p>",pos);

	}
	while(FWikiText.Pos("\n")){
		pos=FWikiText.Pos("\n");
		FWikiText.Delete(pos,1);
		FWikiText.Insert("</p><p>",pos);
	}
}
//---------------------------------------------------------------------------
 void __fastcall TGetWikiText::FReplaceHeadTags()
 {
	int pos=0;
	while(FWikiText.Pos("======")){
		pos=FWikiText.Pos("======");
		FWikiText.Delete(pos,6);
		FWikiText.Insert("<h6>",pos);
		pos=FWikiText.Pos("======");
		FWikiText.Delete(pos,6);
		FWikiText.Insert("</h6>",pos);
	}
	while(FWikiText.Pos("=====")){
		pos=FWikiText.Pos("=====");
		FWikiText.Delete(pos,5);
		FWikiText.Insert("<h5>",pos);
		pos=FWikiText.Pos("=====");
		FWikiText.Delete(pos,5);
		FWikiText.Insert("</h5>",pos);
	}
	while(FWikiText.Pos("====")){
		pos=FWikiText.Pos("====");
		FWikiText.Delete(pos,4);
		FWikiText.Insert("<h4>",pos);
		pos=FWikiText.Pos("====");
		FWikiText.Delete(pos,4);
		FWikiText.Insert("</h4>",pos);
	}
	while(FWikiText.Pos("===")){
		pos=FWikiText.Pos("===");
		FWikiText.Delete(pos,3);
		FWikiText.Insert("<h3>",pos);
		pos=FWikiText.Pos("===");
		FWikiText.Delete(pos,3);
		FWikiText.Insert("</h3>",pos);
	}
	while(FWikiText.Pos("==")){
		pos=FWikiText.Pos("==");
		FWikiText.Delete(pos,2);
		FWikiText.Insert("<h2>",pos);
		pos=FWikiText.Pos("==");
		FWikiText.Delete(pos,2);
		FWikiText.Insert("</h2>",pos);
	}
	while(FWikiText.Pos("'''''")){
		pos=FWikiText.Pos("'''''");
		FWikiText.Delete(pos,5);
		FWikiText.Insert("<b><i>",pos);
		pos=FWikiText.Pos("'''''");
		FWikiText.Delete(pos,5);
		FWikiText.Insert("</i></b>",pos);
	}
	while(FWikiText.Pos("'''")){
		pos=FWikiText.Pos("'''");
		FWikiText.Delete(pos,3);
		FWikiText.Insert("<b>",pos);
		pos=FWikiText.Pos("'''");
		FWikiText.Delete(pos,3);
		FWikiText.Insert("</b>",pos);
	}
	while(FWikiText.Pos("''")){
		pos=FWikiText.Pos("''");
		FWikiText.Delete(pos,2);
		FWikiText.Insert("<i>",pos);
		pos=FWikiText.Pos("''");
		FWikiText.Delete(pos,2);
		FWikiText.Insert("</i>",pos);
	}
//	for(UINT i=1;i<FWikiText.Length();i++){ //удаление знаков ударения
//		if((int)FWikiText[i] ==769)
//			FWikiText.Delete(i,1);
//	}
 }
//---------------------------------------------------------------------------
UnicodeString __fastcall getCC3Date(UnicodeString aStr)
{
	aStr.Delete(aStr.Pos("{{"),2);
	aStr.Delete(1,aStr.Pos('|'));
	aStr.Delete(aStr.Pos("}}"),2);
	return aStr;
}
//---------------------------------------------------------------------------
UnicodeString __fastcall getCC2Date(UnicodeString aStr)
{
	UnicodeString result;
	aStr.Delete(1,aStr.Pos('|'));
	result+=aStr.SubString(1,aStr.Pos('|')-1);
	result+=" ";
	aStr.Delete(1,aStr.Pos('|'));
	result+=aStr.SubString(1,aStr.Pos('|')-1);
	result+=" ";
	aStr.Delete(1,aStr.Pos('|'));
	result+=aStr.SubString(1,aStr.Pos('|')-1);
	return result;
}
//---------------------------------------------------------------------------
UnicodeString __fastcall getCCDate(UnicodeString aStr)
{
	UnicodeString result;
	aStr.Delete(1,aStr.Pos('|'));
	result+=aStr.SubString(1,aStr.Pos('|')-1);
	result+=" ";
	aStr.Delete(1,aStr.Pos('|'));
	result+=aStr.SubString(1,aStr.Pos('|')-1);
	return result;
}
//---------------------------------------------------------------------------
void __fastcall TGetWikiText::FChangeDates()
{
	while(FWikiText.Pos("{{сс3|")){
		UnicodeString copyFWiki=FWikiText;
		int pos=copyFWiki.Pos("{{сс3|");
		copyFWiki.Delete(1,pos-1);
		UnicodeString temp=copyFWiki.SubString(1,copyFWiki.Pos("}}")-1+2);
		FWikiText.Delete(pos,temp.Length());
		FWikiText.Insert(getCC3Date(temp),pos);
	}
	while(FWikiText.Pos("{{СС3|")){
		UnicodeString copyFWiki=FWikiText;
		int pos=copyFWiki.Pos("{{СС3|");
		copyFWiki.Delete(1,pos-1);
		UnicodeString temp=copyFWiki.SubString(1,copyFWiki.Pos("}}")-1+2);
		FWikiText.Delete(pos,temp.Length());
		FWikiText.Insert(getCC3Date(temp),pos);
	}
	while(FWikiText.Pos("{{сс2|")){
		UnicodeString copyFWiki=FWikiText;
		int pos=copyFWiki.Pos("{{сс2|");
		copyFWiki.Delete(1,pos-1);
		UnicodeString temp=copyFWiki.SubString(1,copyFWiki.Pos("}}")-1+2);
		FWikiText.Delete(pos,temp.Length());
		FWikiText.Insert(getCC2Date(temp),pos);
	}
	while(FWikiText.Pos("{{СС2|")){
		UnicodeString copyFWiki=FWikiText;
		int pos=copyFWiki.Pos("{{СС2|");
		copyFWiki.Delete(1,pos-1);
		UnicodeString temp=copyFWiki.SubString(1,copyFWiki.Pos("}}")-1+2);
		FWikiText.Delete(pos,temp.Length());
		FWikiText.Insert(getCC2Date(temp),pos);
	}
	while(FWikiText.Pos("{{сс|")){
		UnicodeString copyFWiki=FWikiText;
		int pos=copyFWiki.Pos("{{сс|");
		copyFWiki.Delete(1,pos-1);
		UnicodeString temp=copyFWiki.SubString(1,copyFWiki.Pos("}}")-1+2);
		FWikiText.Delete(pos,temp.Length());
		FWikiText.Insert(getCCDate(temp),pos);
	}
	while(FWikiText.Pos("{{СС|")){
		UnicodeString copyFWiki=FWikiText;
		int pos=copyFWiki.Pos("{{СС|");
		copyFWiki.Delete(1,pos-1);
		UnicodeString temp=copyFWiki.SubString(1,copyFWiki.Pos("}}")-1+2);
		FWikiText.Delete(pos,temp.Length());
		FWikiText.Insert(getCCDate(temp),pos);
	}
}
//---------------------------------------------------------------------------
void __fastcall TGetWikiText::FChangeAlternateLangName()
{
	while(FWikiText.Pos("{{lang")){
		UnicodeString copyFWiki=FWikiText;
		int pos=copyFWiki.Pos("{{lang");
		copyFWiki.Delete(1,pos-1);
		UnicodeString temp=copyFWiki.SubString(1,copyFWiki.Pos("}}")-1+2);
		FWikiText.Delete(pos,temp.Length());
		FWikiText.Insert(getCC3Date(temp),pos);
	}
}
//---------------------------------------------------------------------------
void __fastcall TGetWikiText::FDeleteSpecialBox()
{
	while(FWikiText.Pos("<gallery")){
		int start=FWikiText.Pos("<gallery");
		int end=FWikiText.Pos("</gallery>")+10;
		FWikiText.Delete(start,end-start);
	}
	while(FWikiText.Pos("<timeline")){
		int start=FWikiText.Pos("<timeline");
		int end=FWikiText.Pos("</timeline>")+11;
		FWikiText.Delete(start,end-start);
	}
}
