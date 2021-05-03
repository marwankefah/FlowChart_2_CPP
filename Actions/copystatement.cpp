#include "copystatement.h"


copystatement::copystatement(ApplicationManager* pAppManager):Action(pAppManager),target(pManager->GetSelectedStatement())
{


}

void copystatement::ReadActionParameters()
{
	

}
void copystatement::Execute()
{
	ReadActionParameters();	
	Output *pOut = pManager->GetOutput();

	if(target!=NULL)
{
	if(pManager->GetClipboard())
	{
	delete (pManager->GetClipboard());
	}
	Statement * u = target->ClpbrdHelper();
	pManager->SetClipboard(u);
	pOut->PrintMessage("Statement copied to clipboard");
}
	else
	{
			pOut->PrintMessage("no stat selected");


	}
}
copystatement::~copystatement(void)
{

}
