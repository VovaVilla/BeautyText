//---------------------------------------------------------------------------

#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ComCtrls.hpp>
#include <Vcl.ExtCtrls.hpp>
#include "siComp.hpp"
#include <SHDocVw.hpp>
#include <Vcl.OleCtrls.hpp>
#include <Vcl.Dialogs.hpp>
#include <Vcl.Imaging.jpeg.hpp>
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
	TPageControl *PageControl1;
	TTabSheet *TabSheet1;
	TPanel *Panel7;
	TButton *Button1;
	TButton *Button2;
	TButton *Button3;
	TButton *Button4;
	TButton *Button5;
	TButton *Button6;
	TButton *Button7;
	TButton *Button8;
	TButton *Button9;
	TPanel *Panel8;
	TRichEdit *RichEdit1;
	TTabSheet *TabSheet2;
	TPanel *Panel4;
	TLabel *Label1;
	TEdit *Edit1;
	TButton *Button10;
	TTabSheet *TabSheet3;
	TPanel *Panel2;
	TButton *Button11;
	TComboBox *ComboBox1;
	TButton *Button12;
	TPanel *Panel1;
	TPanel *Panel3;
	TRichEdit *RichEdit2;
	TRichEdit *RichEdit3;
	TTabSheet *TabSheet5;
	TWebBrowser *WebBrowser1;
	TLabel *Label2;
	TButton *Button15;
	TLabel *Label4;
	TLabel *Label5;
	TLabel *Label6;
	TButton *Button16;
	TLabel *Label7;
	TLabel *Label8;
	TButton *Button17;
	TButton *Button18;
	TButton *Button19;
	TTabSheet *TabSheet4;
	TLabel *Label9;
	TButton *Button20;
	TPanel *Panel5;
	TButton *Button14;
	TCheckBox *CheckBox1;
	TLabel *Label10;
	TLabel *Label3;
	TLabel *Label11;
	TLabel *Label12;
	TLabel *Label13;
	TPanel *Panel6;
	TLabel *Label14;
	TLabel *Label16;
	TLabel *Label15;
	TLabel *Label17;
	TLabel *Label18;
	TLabel *Label19;
	TLabel *Label20;
	TLabel *Label21;
	TLabel *Label23;
	TLabel *Label22;
	TLabel *Label24;
	TLabel *Label25;
	TLabel *Label26;
	TLabel *Label27;
	TPanel *Panel9;
	TLabel *Label28;
	TLabel *Label29;
	TSaveDialog *SaveDialog1;
	TButton *Button21;
	TButton *Button13;
	TButton *Button22;
	TButton *Button23;
	void __fastcall Button1Click(TObject *Sender);
	void __fastcall Button2Click(TObject *Sender);
	void __fastcall Button3Click(TObject *Sender);
	void __fastcall Button4Click(TObject *Sender);
	void __fastcall Button5Click(TObject *Sender);
	void __fastcall Button6Click(TObject *Sender);
	void __fastcall Button7Click(TObject *Sender);
	void __fastcall Button8Click(TObject *Sender);
	void __fastcall Button9Click(TObject *Sender);
	void __fastcall Button10Click(TObject *Sender);
	void __fastcall Button11Click(TObject *Sender);
	void __fastcall Button12Click(TObject *Sender);
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall Button14Click(TObject *Sender);
	void __fastcall Edit1Change(TObject *Sender);
	void __fastcall Label2Click(TObject *Sender);
	void __fastcall Button15Click(TObject *Sender);
	void __fastcall Button1MouseEnter(TObject *Sender);
	void __fastcall Button1MouseLeave(TObject *Sender);
	void __fastcall Button2MouseEnter(TObject *Sender);
	void __fastcall Button3MouseEnter(TObject *Sender);
	void __fastcall Button4MouseEnter(TObject *Sender);
	void __fastcall Button5MouseEnter(TObject *Sender);
	void __fastcall Button6MouseEnter(TObject *Sender);
	void __fastcall Button7MouseEnter(TObject *Sender);
	void __fastcall Button8MouseEnter(TObject *Sender);
	void __fastcall Button9MouseEnter(TObject *Sender);
	void __fastcall Button16Click(TObject *Sender);
	void __fastcall Button16MouseEnter(TObject *Sender);
	void __fastcall FormCloseQuery(TObject *Sender, bool &CanClose);
	void __fastcall Button11MouseLeave(TObject *Sender);
	void __fastcall ComboBox1MouseEnter(TObject *Sender);
	void __fastcall Button12MouseEnter(TObject *Sender);
	void __fastcall Button18MouseEnter(TObject *Sender);
	void __fastcall Button17MouseEnter(TObject *Sender);
	void __fastcall Button19MouseEnter(TObject *Sender);
	void __fastcall Button18Click(TObject *Sender);
	void __fastcall Button17Click(TObject *Sender);
	void __fastcall Button19Click(TObject *Sender);
	void __fastcall Button20Click(TObject *Sender);
	void __fastcall CheckBox1Click(TObject *Sender);
	void __fastcall PageControl1Change(TObject *Sender);
	void __fastcall Label13Click(TObject *Sender);
	void __fastcall RichEdit1Change(TObject *Sender);
	void __fastcall Button21Click(TObject *Sender);
	void __fastcall Edit1KeyPress(TObject *Sender, System::WideChar &Key);
	void __fastcall Button22Click(TObject *Sender);
	void __fastcall Button13Click(TObject *Sender);
	void __fastcall Button13MouseEnter(TObject *Sender);
	void __fastcall Button22MouseEnter(TObject *Sender);
	void __fastcall Button1MouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);
	void __fastcall Button23MouseEnter(TObject *Sender);
	void __fastcall Button23Click(TObject *Sender);


private:	// User declarations
public:		// User declarations
	__fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
