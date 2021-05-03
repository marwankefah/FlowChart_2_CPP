#include "addvariableassign.h"
#include "../ApplicationManager.h"
#include "../GUI\Input.h"
#include "../GUI\Output.h"
#include "../Statements/variableassign.h"

addvariableassign::addvariableassign(ApplicationManager* pmanager):Action(pmanager)
{
}

void addvariableassign::ReadActionParameters()
{
	Input *pIn = pManager->GetInput();
	Output *pOut = pManager->GetOutput();
	
	//Read the (Position) parameter
	pOut->PrintMessage("variable Assignment Statement: Click to add the statement");

	pIn->GetPointClicked(position);
	pOut->ClearStatusBar();		
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

	//TODO: Ask the user in the status bar to enter the LHS and set the data member
	pOut->PrintMessage("Please enter the LHS data member");
	LHS=pIn->Getvariable(pOut);
	//TODO: Ask the user in the status bar to enter the RHS and set the data member
	pOut->PrintMessage("Please enter the RHS data member");
	RHS=pIn->Getvariable(pOut);
		pOut->ClearStatusBar();		

	//Note: You should validate the LHS to be variable name and RHS to be a value
	//      Call the appropriate functions for this.

			Point Corner;
	Corner.x = position.x - UI.ASSGN_WDTH/2;
	Corner.y = position.y ;

	variableassign *temp = new variableassign(Corner,LHS,RHS);


			// check if after the entered length is so large it does not fit in the drawing area
			if ( !(position.y >= UI.ToolBarHeight && position.y+UI.ASSGN_HI < UI.height - UI.StatusBarHeight && position.x+temp->getwidth()/2 <= UI.DrawingAreaWidth&&position.x-temp->getwidth()/2>0))
	      {
			pOut->PrintMessage("ERROR OUT of drawing area because statement is so long !!");
			position.x=-1;

				return;

	       }
			delete temp;

}

void addvariableassign::Execute()
{
	ReadActionParameters();
		
	if(position.x==-1)
	{

		return;
	}
	
	//Calculating left corner of assignement statement block
	Point Corner;
	Corner.x = position.x - UI.ASSGN_WDTH/2;
	Corner.y = position.y ;
	

	variableassign *pAssign = new variableassign(Corner,"","");
	pAssign->setLHS(LHS);
	pAssign->setRHS(RHS);
	//TODO: should set the LHS and RHS of pAssign statement
	//      with the data members set and validated before in ReadActionParameters()

	pManager->AddStatement(pAssign); // Adds the created statement to application manger's statement list
}


addvariableassign::~addvariableassign()
{
}
