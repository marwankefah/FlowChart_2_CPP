#include "validiate.h"


#include "../ApplicationManager.h"



validiate:: validiate(ApplicationManager *pmanager):Action(pmanager)
{
	pManager->vararrdefault();

}

void  validiate:: ReadActionParameters() // add sleep here to make visual effects
{

	Output *pout=pManager->GetOutput();
			pout->PrintMessage("VALIDIATINGGG THE CHART");
			Sleep(1000);

			if(pManager->getstartcount()!=1 &&pManager->getendcount()!=1)
			{

				pout->PrintMessage("THE CHART IS INVALID! YA BASHMO ezbot start we end MATsargnash ");
							Sleep(2000);

		return;

			}

	if(pManager->getstartcount()!=1) 
	{
				pout->PrintMessage("THE CHART IS INVALID! YA BASHMO ezbot START MATsargnash ");
							Sleep(2000);

		return;

	}
	if(pManager->getendcount()!=1)
	{

				pout->PrintMessage("THE CHART IS INVALID! YA BASHMO ezbot END OKSEMBELLAH ");
							Sleep(2000);

		return;


	}

	pManager->validit();
	bool x =pManager->getisvalidconn();   // for testing
	bool y=pManager->getisvalidvar();     
	if(!x)
	{
		pout->PrintMessage("THE CHART IS INVALID !!!ERROR TYPE:PLEASE CHECK THE OUTPUT CONNECTORS!!!!!!");
					Sleep(2000);
					return;

	}
	else if(!y)
	{
		pout->PrintMessage("THE CHART IS INVALID !!!ERROR TYPE:PLEASE CHECK THE var flow !!!!!!");
					Sleep(1000);
					return;


	
	}

				pout->PrintMessage(" CHART IS VALID ALF ALF ALF MABROOK ");

							Sleep(1500);

	

                                return;








}




	 void validiate:: Execute()
	 {


		 ReadActionParameters();



	 }
	

validiate::~validiate()
{

}
