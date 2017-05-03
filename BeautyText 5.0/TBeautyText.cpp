//---------------------------------------------------------------------------

#pragma hdrstop

#include "TBeautyText.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

const UnicodeString __fastcall TBeautyText::ChangeLanguage (const UnicodeString& aStr,const UnicodeString& toLang)
{
    if(aStr=="")
		return "";

	UnicodeString result=aStr;

	/* определение раскладки
	 если lang == 1033 - английска€
	 если 1049 - русска€
	 */
	UnicodeString ENG =
		"`1234567890-=\\qwertyuiop[]asdfghjkl;'zxcvbnm,./~!@#$%^&*()_+|QWERTYUIOP{}ASDFGHJKL:\"ZXCVBNM<>?";
	UnicodeString RUS =
		"Є1234567890-=\\йцукенгшщзхъфывапролджэ€чсмитьбю.®!\"є;%:?*()_+/…÷” ≈Ќ√Ўў«’Џ‘џ¬јѕ–ќЋƒ∆Ёя„—ћ»“№Ѕё,";

	if (toLang == "1033") {
		for (int i = 1; i <= result.Length(); i++) {
			for (int j = 1; j <= ENG.Length(); j++) {
				if (result[i] == ENG[j]) {
					result[i] = RUS[j];
					break;
				}
			}
		}
	}

	if (toLang == "1049") {
		for (int i = 1; i <= result.Length(); i++) {
			for (int j = 1; j <= ENG.Length(); j++) {
				if (result[i] == RUS[j]) {
					result[i] = ENG[j];
					break;
				}
			}
		}
	}
	return result;
}
//---------------------------------------------------------------------------
const UnicodeString __fastcall TBeautyText::BeautyText (const UnicodeString& aStr)
{            
    if(aStr=="")
		return "";

	UnicodeString result=aStr;

	if(result.IsEmpty())
		return "";
	try{
		for (int i = 1; i < result.Length(); i++) { // удаление повтор€ющихс€

		if(i==3105)
			int y=8;

			if (result[i] == ' ') {
				if (result[i + 1] == ' ') {
					result.Delete(i, 1);
					i--;
					continue;
				}
			}

			if (result[i] == '\n' || result[i] == '\r') {
				if (result[i + 1] == '\n' || result[i + 1] == '\r') {
					result.Delete(i, 1);
					i--;
					continue;
				}
			}
			if (result[i] == '\n' || result[i] == '\r') {
				if (result[i + 1] == ' ') {
					result.Delete(i + 1, 1);
					i--;
					continue;
				}
			}
			if (result[i] == '\t') {
				if (result[i + 1] == '\t'||result[i+1]==' ') {
					result.Delete(i, 1);
					i--;
					continue;
				}
			}
			if (result[i] == '!' || result[i] == '.' || result[i] == ',' || result[i] == ':' ||
				result[i] == '?' || result[i] == ';' || result[i] == ')') {
				if (i != 1) {
					if (result[i - 1] == ' ' || result[i - 1] == '\t'|| result[i - 1] == ',') {
						result.Delete(i - 1, 1);
						i--;
						continue;
					}
				}
				if (result[i + 1] != ' ') {
					result.Insert(' ', i);
					i--;
					continue;
				}
			}
			if (result[i] == '(') {
				if (i != 1) {
					if (result[i - 1] != ' ') {
						result.Insert(' ', i);
						i++;
					}
				}
				if (result[i + 1] == ' '||result[i + 1] == ';'||result[i + 1] == ','||result[i + 1] == '.') {
					result.Delete(i + 1, 1);
				}
			}
		}
	}
	catch(...){
		return "";
	}
	if (result[1] != '\t')          //добавление \t
		result.Insert("\t", 1);
	for (int i = 1; i < result.Length(); i++) {
		if (result[i] == '\n' || result[i] == '\r') {
			if (result[i + 1] != '\t')
				result.Insert("\t", i + 1);
		}
	}
	return result;
}
//---------------------------------------------------------------------------
const UnicodeString __fastcall TBeautyText::ChangeRegister (const UnicodeString& aStr, const int& reg)
{
	if(aStr=="")
		return "";

	UnicodeString result=aStr;

	bool first = true;
	UnicodeString small = "Єйцукенгшщзхъфывапролджэ€чсмитьбю";
	UnicodeString great = "®…÷” ≈Ќ√Ўў«’Џ‘џ¬јѕ–ќЋƒ∆Ёя„—ћ»“№Ѕё";
	UnicodeString small_en = "qwertyuiopasdfghjklzxcvbnm-------";
	UnicodeString great_en = "QWERTYUIOPASDFGHJKLZXCVBNM-------";

	if (reg == 0) { // зеркальный регистр
		for (int i = 1; i <= result.Length(); i++) {
			for (int j = 1; j <= small.Length(); j++) {
				if (result[i] == great[j]) {
					result[i] = small[j];
					break;
				}
				if (result[i] == small[j]) {
					result[i] = great[j];
					break;
				}
				if (result[i] == great_en[j]) {
					result[i] = small_en[j];
					break;
				}
				if (result[i] == small_en[j]) {
					result[i] = great_en[j];
					break;
				}
			}
		}
	}

	if (reg == 1) { // как в предложени€х
		for (int i = 1; i <= result.Length(); i++) {
			if (result[i] == '.' || result[i] == '?' || result[i] == '!' || result[i] == '\n') {
				first = true; /* i++; */ }
			for (int j = 1; j <= small.Length(); j++) {
				if (first) {
					if (result[i] == small[j]) {
						result[i] = great[j];
						first = false;
						break;
					}
					if (result[i] == great[j]) {
						first = false;
						break;
					}
					if (result[i] == small_en[j]) {
						result[i] = great_en[j];
						first = false;
						break;
					}
					if (result[i] == great_en[j]) {
						first = false;
						break;
					}
				}
				else {
					if (result[i] == great[j]) {
						result[i] = small[j];
						break;
					}
					if (result[i] == great_en[j]) {
						result[i] = small_en[j];
						break;
					}
				}
			}
		}
	}

	if (reg == 2) { // все маленькие
		for (int i = 1; i <= result.Length(); i++) {
			for (int j = 1; j <= small.Length(); j++) {
				if (result[i] == great[j]) {
					result[i] = small[j];
					break;
				}
				if (result[i] == great_en[j]) {
					result[i] = small_en[j];
					break;
				}
			}
		}
	}

	if (reg == 3) { // все большие
		for (int i = 1; i <= result.Length(); i++) {
			for (int j = 1; j <= great.Length(); j++) {
				if (result[i] == small[j]) {
					result[i] = great[j];
					break;
				}
				if (result[i] == small_en[j]) {
					result[i] = great_en[j];
					break;
				}
			}
		}
	}
	return result;
}
//---------------------------------------------------------------------------
const UnicodeString __fastcall TBeautyText::Alphabetically(const UnicodeString& aStr)
{
	if(aStr=="")
		return "";

	TStringList *sList=new TStringList;
	UnicodeString result="";
	sList->Text=aStr;
	sList->Sorted=true;
	result=sList->Text;
	delete sList;
	return result;
}
//---------------------------------------------------------------------------
const UnicodeString __fastcall TBeautyText::DeleteDuplicatesStrings(const UnicodeString& aStr)
{
	if(aStr=="")
		return "";

	UnicodeString result="";
	TStringList *sList=new TStringList;
	sList->Text=aStr;

	for(UINT i=0;i<sList->Count;i++){
		for(UINT j=i+1;j<sList->Count;j++){
			if(sList->Strings[i].Trim()==sList->Strings[j].Trim()){
				sList->Delete(j);
				j--;
			}
		}	
	}                
	result=sList->Text;
	delete sList;
	return result;
}
//---------------------------------------------------------------------------
