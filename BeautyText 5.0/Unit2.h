//---------------------------------------------------------------------------

#ifndef Unit2H
#define Unit2H
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
//---------------------------------------------------------------------------
class TWikiThread : public TThread
{
private:
	void __fastcall showTabsOnForm();
	void __fastcall hideTabsOnForm();
	void __fastcall writeUpdateStatus();
protected:
	void __fastcall Execute();

public:
	__fastcall TWikiThread(bool CreateSuspended);
};
//---------------------------------------------------------------------------
#endif
