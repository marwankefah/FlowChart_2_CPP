#include "addcondstat.h"
#include "ActionSave.h"
#include"../ApplicationManager.h"
#include "../GUI\Input.h"
#include "../GUI\Output.h"
#include "../Statements/condstat.h"

addcondstat::addcondstat(ApplicationManager* pmanager):Action(pmanager)
{
}

void addcondstat::ReadActionParameters()
{
	Input *pIn = pManager->GetInput();
	Output *pOut = pManager->GetOutput();
	
	//Read the (Position) parameter
	pOut->PrintMessage("cond Assignment Statement: Click to add the statement");

	pIn->GetPointClicked(position);
	

	                 

	if ( !(position.y >= UI.ToolBarHeight && position.y< UI.height - UI.StatusBarHeight && position.x <= UI.DrawingAreaWidth ))
	{
			pOut->PrintMessage("ERROR OUT of drawing area !!");
			position.x=-1;

				return;

	}
	if ( !(position.y+UI.ASSGN_HI < UI.height - UI.StatusBarHeight && position.x+UI.ASSGN_WDTH/2 <= UI.DrawingAreaWidth &&position.x-UI.ASSGN_WDTH/2 >=0))
	{
			pOut->PrintMessage("ERROR if drawn at  default it would be OUT of drawing area !!");
			position.x=-1;

				return;

	}

	pOut->ClearStatusBar();		

	//TODO: Ask the user in the status bar to enter the LHS and set the data member
	pOut->PrintMessage("Please enter the LHS data member(variable or number)");
	LHS=pIn->Getvariable(pOut);
	while(ValueOrVariable(LHS)==INVALID_OP)
	{
			pOut->PrintMessage("ERROR Please enter the first variable or number to make the cond");

			LHS=pIn->GetString(pOut);

	}

		pOut->ClearStatusBar();		

	pOut->PrintMessage("Please enter the condition to check ex:==");
	cond=pIn->GetCompOperator(pOut);

		pOut->ClearStatusBar();		

	pOut->PrintMessage("Please enter the second variable or number to make the cond");

		RHS=pIn->GetString(pOut);

	while(ValueOrVariable(RHS)==INVALID_OP)
	{
				pOut->PrintMessage("ERROR Please enter the second variable or number to make the cond");

			RHS=pIn->GetString(pOut);

	}
	
				pOut->ClearStatusBar();		

		condstat *temp = new condstat(position,LHS,cond,RHS);


			// check if after the entered length is so large it does not fit in the drawing area
		if ( !(position.y >= UI.ToolBarHeight && position.y+UI.ASSGN_HI < UI.height - UI.StatusBarHeight && position.x+temp->getwidth()/2 <= UI.DrawingAreaWidth&&position.x-temp->getwidth()/2>0))
	      {
			pOut->PrintMessage("ERROR OUT of drawing area because statement is so long !!");
			position.x=-1;

				return;

	       }
}

void addcondstat::Execute()
{
	ReadActionParameters();
	if(position.x==-1)
	{

		return;
	}
	
	condstat *pAssign = new condstat(position,LHS,cond,RHS);
	pManager->AddStatement(pAssign); // Adds the created statement to application manger's statement list
}


addcondstat::~addcondstat()
{
	
}
