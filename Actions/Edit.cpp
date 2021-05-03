#include "Edit.h"
#include "../ApplicationManager.h"


Edit::Edit(ApplicationManager* pAppManager):Action(pAppManager)
{}
void Edit::ReadActionParameters(void)
{
	pIn = pManager->GetInput();
	pout=pManager->GetOutput();
	target = pManager->GetSelectedStatement();
	if(target==NULL)
	{
		pout->PrintMessage("No Selected Statement");
		Sleep(1000);
		pout->ClearStatusBar();
		return;
	}
}
void Edit::Execute(void)
{
	ReadActionParameters();
	if(target==NULL)
	{
		return;
	}
	else
	{
		target->Edit(pout,pIn);
		pManager->UpdateInterface();
	}
	
}

Edit::~Edit(void)
{
}
