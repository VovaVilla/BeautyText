//---------------------------------------------------------------------------

#pragma hdrstop

#include "TBeautyText.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

UnicodeString __fastcall TBeautyText::ChangeLanguage (UnicodeString str, UnicodeString toLang) {

	/* определение раскладки
	 если lang == 1033 - английска€
	 если 1049 - русска€
	 */
	UnicodeString ENG =
		"`1234567890-=\\qwertyuiop[]asdfghjkl;'zxcvbnm,./~!@#$%^&*()_+|QWERTYUIOP{}ASDFGHJKL:\"ZXCVBNM<>?";
	UnicodeString RUS =
		"Є1234567890-=\\йцукенгшщзхъфывапролджэ€чсмитьбю.®!\"є;%:?*()_+/…÷” ≈Ќ√Ўў«’Џ‘џ¬јѕ–ќЋƒ∆Ёя„—ћ»“№Ѕё,";

	if (toLang == "1033") {
		for (int i = 1; i <= str.Length(); i++) {
			for (int j = 1; j <= ENG.Length(); j++) {
				if (str[i] == ENG[j]) {
					str[i] = RUS[j];
					break;
				}
			}
		}
	}

	if (toLang == "1049") {
		for (int i = 1; i <= str.Length(); i++) {
			for (int j = 1; j <= ENG.Length(); j++) {
				if (str[i] == RUS[j]) {
					str[i] = ENG[j];
					break;
				}
			}
		}
	}
	return str;
}

UnicodeString __fastcall TBeautyText::BeautyText (UnicodeString st){

	try{
	for (int i = 1; i < st.Length(); i++) { // удаление повтор€ющихс€

	if(i==3105)
		int y=8;

		if (st[i] == ' ') {
			if (st[i + 1] == ' ') {
				st.Delete(i, 1);
				i--;
				continue;
			}
		}
		if (st[i] == '\n' || st[i] == '\r') {
			if (st[i + 1] == '\n' || st[i + 1] == '\r') {
				st.Delete(i, 1);
				i--;
				continue;
			}
		}
		if (st[i] == '\n' || st[i] == '\r') {
			if (st[i + 1] == ' ') {
				st.Delete(i + 1, 1);
				i--;
				continue;
			}
		}
		if (st[i] == '\t') {
			if (st[i + 1] == '\t'||st[i+1]==' ') {
				st.Delete(i, 1);
				i--;
				continue;
			}
		}
		if (st[i] == '!' || st[i] == '.' || st[i] == ',' || st[i] == ':' ||
			st[i] == '?' || st[i] == ';' || st[i] == ')') {
			if (i != 1) {
				if (st[i - 1] == ' ' || st[i - 1] == '\t'|| st[i - 1] == ',') {
					st.Delete(i - 1, 1);
					i--;
					continue;
				}
			}
			if (st[i + 1] != ' ') {
				st.Insert(' ', i);
				i--;
				continue;
			}
		}
		if (st[i] == '(') {
			if (i != 1) {
				if (st[i - 1] != ' ') {
					st.Insert(' ', i);
					i++;
				}
			}
			if (st[i + 1] == ' '||st[i + 1] == ';'||st[i + 1] == ','||st[i + 1] == '.') {
				st.Delete(i + 1, 1);
			}
		}
	}
	}
	catch(...){
    	//
	}
	if (st[1] != '\t')          //добавление \t
		st.Insert("\t", 1);
	for (int i = 1; i < st.Length(); i++) {
		if (st[i] == '\n' || st[i] == '\r') {
			if (st[i + 1] != '\t')
				st.Insert("\t", i + 1);
		}
	}
	return st;
}

UnicodeString __fastcall TBeautyText::ChangeRegister (UnicodeString st, int reg) {

	bool first = true;
	UnicodeString small = "Єйцукенгшщзхъфывапролджэ€чсмитьбю";
	UnicodeString great = "®…÷” ≈Ќ√Ўў«’Џ‘џ¬јѕ–ќЋƒ∆Ёя„—ћ»“№Ѕё";
	UnicodeString small_en = "qwertyuiopasdfghjklzxcvbnm-------";
	UnicodeString great_en = "QWERTYUIOPASDFGHJKLZXCVBNM-------";

	if (reg == 0) { // зеркальный регистр
		for (int i = 1; i <= st.Length(); i++) {
			for (int j = 1; j <= small.Length(); j++) {
				if (st[i] == great[j]) {
					st[i] = small[j];
					break;
				}
				if (st[i] == small[j]) {
					st[i] = great[j];
					break;
				}
				if (st[i] == great_en[j]) {
					st[i] = small_en[j];
					break;
				}
				if (st[i] == small_en[j]) {
					st[i] = great_en[j];
					break;
				}
			}
		}
	}

	if (reg == 1) { // как в предложени€х
		for (int i = 1; i <= st.Length(); i++) {
			if (st[i] == '.' || st[i] == '?' || st[i] == '!' || st[i] == '\n') {
				first = true; /* i++; */ }
			for (int j = 1; j <= small.Length(); j++) {
				if (first) {
					if (st[i] == small[j]) {
						st[i] = great[j];
						first = false;
						break;
					}
					if (st[i] == great[j]) {
						first = false;
						break;
					}
					if (st[i] == small_en[j]) {
						st[i] = great_en[j];
						first = false;
						break;
					}
					if (st[i] == great_en[j]) {
						first = false;
						break;
					}
				}
				else {
					if (st[i] == great[j]) {
						st[i] = small[j];
						break;
					}
					if (st[i] == great_en[j]) {
						st[i] = small_en[j];
						break;
					}
				}
			}
		}
	}

	if (reg == 2) { // все маленькие
		for (int i = 1; i <= st.Length(); i++) {
			for (int j = 1; j <= small.Length(); j++) {
				if (st[i] == great[j]) {
					st[i] = small[j];
					break;
				}
				if (st[i] == great_en[j]) {
					st[i] = small_en[j];
					break;
				}
			}
		}
	}

	if (reg == 3) { // все большие
		for (int i = 1; i <= st.Length(); i++) {
			for (int j = 1; j <= great.Length(); j++) {
				if (st[i] == small[j]) {
					st[i] = great[j];
					break;
				}
				if (st[i] == small_en[j]) {
					st[i] = great_en[j];
					break;
				}
			}
		}
	}
	return st;
}
