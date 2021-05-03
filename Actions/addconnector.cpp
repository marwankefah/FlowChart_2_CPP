
#include "addconnector.h"
#include "ActionSave.h"
#include"../ApplicationManager.h"
#include "../GUI\input.h"
#include "../GUI\Output.h"
#include "../Connector.h"
#include <sstream>
#include "../Statements\Statement.h"
#include "../Statements/condstat.h"
#include "../Statements/endstat.h"
#include "../Statements/startstat.h"
addconnector:: addconnector(ApplicationManager *pAppManager):Action(pAppManager)
{
	SrcStat=NULL;
	DstStat=NULL;
	Start.x=0; Start.y=0;
	End.x=0;
	End.y=0;
	branchno=-1;
}
	

// if the dest is start eng eman told us to make the validation here either we could have made an array of pointers of pin and pout and also end can not be a src and she told us to make that no stat can pout more than 1 
 void addconnector:: ReadActionParameters()
 {
	 
	 Input *pin =pManager->GetInput();
	 Output *pout=pManager->GetOutput();
	 
	 pout->PrintMessage("select the first statement for connecting out of");  
	 Point p;
	 pin->GetPointClicked(p);
	 pout->ClearStatusBar();
	if ( !(p.y >= UI.ToolBarHeight && p.y< UI.height - UI.StatusBarHeight && p.x <= UI.DrawingAreaWidth ))
	{
			pout->PrintMessage("ERROR OUT of drawing area !!");
			p.x=-1;
			Sleep(1000);
				 pout->ClearStatusBar();

				branchno=-1;
					SrcStat=NULL;
					DstStat=NULL;
					return;

	}

	Statement *temp;
	temp=pManager->GetStatement(p);
           if(temp==NULL)
	                 {
					 	 pout->PrintMessage("no stat selected");  
							 branchno=-1;
					   SrcStat=NULL;
					   DstStat=NULL;
	                  	return;

                      	}
	int tempvalid=temp->caniout();

		 
/*
			condstat * condptr = dynamic_cast<condstat *>(temp);   //

			if(condptr)
			{

			 pout->PrintMessage("choose which branch yes or no if yes enter 1 if no enter 2 ");  
			 Point c;
			 Sleep(2000);
			 branchno=pin->GetValue(pout);
			 if(branchno !=1 && branchno!=2)
			 {
				 branchno=-1;
					SrcStat=NULL;
					DstStat=NULL;
						Sleep(2000);
								 	 pout->ClearStatusBar();

				 return;
			 }
				

			}
			*/

		   branchno=temp->getbranch();
		   if(tempvalid==0)
		   {

			   pout->PrintMessage("ERROR !!you can not get a  conn out from here");  
										 Sleep(1000);
			    branchno=-1;
					SrcStat=NULL;
					DstStat=NULL;
					return;


		   }
		   else if(tempvalid!=branchno && branchno!=0&& tempvalid!=3)
		   {

			   						 	 pout->PrintMessage("ERROR !!you can not get a  conn out from here");  
										 Sleep(1000);

			       branchno=-1;
					SrcStat=NULL;
					DstStat=NULL;
					return;

		   }
		   
		   else if(branchno !=1 && branchno!=2&& branchno!=0)
			 {
				 branchno=-1;
					SrcStat=NULL;
					DstStat=NULL;
								   	 pout->PrintMessage("ERROR !!you can not get a  conn out from here");  

						Sleep(1000);
								 	 pout->ClearStatusBar();

				 return;
			 }
				
	SrcStat=temp;
	Statement * temp2;

	 pout->PrintMessage("select the second statement for connecting");

		 pin->GetPointClicked(p);

	 	temp2=pManager->GetStatement(p);
		startstat * startst = dynamic_cast<startstat *>(temp2);   // if destination is start error 
		if(startst)  // if the dest is start eng eman told us to make the validation here either we could have made an array of pointers of pin and pout
		{

			branchno=-1;
					SrcStat=NULL;
					DstStat=NULL;
								   	 pout->PrintMessage("ERROR !! 3eeb ya bashmo matsaghrnash b2a");  

						Sleep(2000);
								 	 pout->ClearStatusBar();

				 return;

		}
		if(temp2==NULL)
     	{


	 pout->PrintMessage("no stat selected");  
							 branchno=-1;
					   SrcStat=NULL;
					   DstStat=NULL;
	                  	return;
	     }
		DstStat=temp2;
		
		
 }
	
	//Create and add connector statement to the list of statements
	 void addconnector::Execute() 
	 {
		 ReadActionParameters();
		 if(SrcStat==NULL || DstStat==NULL|| branchno==-1)
		 {
			 return;

		 }
		 Connector *c=new Connector(SrcStat,DstStat);
		 c->setbranch(branchno);
		 SrcStat->setoutconnector(c,branchno);
		 DstStat->setinconnector(c);
		 pManager->AddConnector(c);

	 }


