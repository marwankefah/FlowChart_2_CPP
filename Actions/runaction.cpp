#include "runaction.h"
#include "../ApplicationManager.h"



runaction:: runaction(ApplicationManager *pmanager):Action(pmanager)
{
	pManager->vararrdefault();


}


	 void  runaction:: ReadActionParameters()
	{

Output *pout=pManager->GetOutput();
			pout->PrintMessage("Running  the CHART");
						Sleep(1000);

   pManager->validit();
	bool y=pManager->getisvalid();
	

	if(!y)
	{
		pout->PrintMessage("THE CHART IS INVALID !!Check validity and come again :)");
					Sleep(1000);
					return;

	}
	else
	{
				pout->PrintMessage("THE CHART IS VALID !!Check outputarea and be aware of any interaction :)");


	}

	pManager->vararrdefault();
	pManager->runflowchart();




	}
	 void runaction:: Execute()
	 {

		 
		 ReadActionParameters();



	 }
runaction::~runaction()
{
}
