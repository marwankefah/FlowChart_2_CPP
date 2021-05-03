#include "cutstatement.h"
#include "copystatement.h"
#include "deleter.h"

cutstatement::cutstatement(ApplicationManager* pAppManager):Action(pAppManager)
{
}

void cutstatement::ReadActionParameters()
{
	
	Action *t1=new copystatement(pManager);
	target = pManager->GetSelectedStatement();
	t1->Execute();

	if(target!=NULL)
	{
	Action *t2=new deleter(pManager);
	t2->Execute();
	}
	
}
void cutstatement::Execute()
{		ReadActionParameters();

	/* target = pManager->GetSelectedStatement();

		Output *pOut = pManager->GetOutput();

	if(target==NULL)
	{
			pOut->PrintMessage("no  stat is selected");


	}
	else
	{
	if(pManager->GetClipboard() != NULL)
	{
	delete (pManager->GetClipboard());
	}
	Statement * u = target->ClpbrdHelper();
	pManager->SetClipboard(u);
	pManager->DeleteStatement(target);
	Output *pOut = pManager->GetOutput();
	pOut->PrintMessage("Statement moved to clipboard");
	}
	*/   // this is the previous logic of sawalhy 
}
cutstatement::~cutstatement(void)
{
}
