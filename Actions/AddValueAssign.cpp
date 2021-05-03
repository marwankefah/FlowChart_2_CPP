#include "AddValueAssign.h"



#include "..\ApplicationManager.h"

#include "..\GUI\input.h"
#include "..\GUI\Output.h"
#include <sstream>
using namespace std;

//constructor: set the ApplicationManager pointer inside this action
AddValueAssign::AddValueAssign(ApplicationManager *pAppManager):Action(pAppManager)
{}

void AddValueAssign::ReadActionParameters()
{
	Input *pIn = pManager->GetInput();
	Output *pOut = pManager->GetOutput();
	
	//Read the (Position) parameter
	pOut->PrintMessage("Value Assignment Statement: Click to add the statement");

	pIn->GetPointClicked(Position);
	pOut->ClearStatusBar();		
	if ( !(Position.y >= UI.ToolBarHeight && Position.y< UI.height - UI.StatusBarHeight && Position.x <= UI.DrawingAreaWidth ))
	{
			pOut->PrintMessage("ERROR OUT of drawing area !!");
			Position.x=-1;

				return;

	}

	if ( !(Position.y+UI.ASSGN_HI < UI.height - UI.StatusBarHeight && Position.x+UI.ASSGN_WDTH/2 <= UI.DrawingAreaWidth &&Position.x-UI.ASSGN_WDTH/2 >=0))
	{
			pOut->PrintMessage("ERROR if drawn at  default it would be OUT of drawing area !!");
			Position.x=-1;

				return;

	}

	//TODO: Ask the user in the status bar to enter the LHS and set the data member
	pOut->PrintMessage("Please enter the LHS data member");
	LHS=pIn->Getvariable(pOut);
	//TODO: Ask the user in the status bar to enter the RHS and set the data member
	pOut->PrintMessage("Please enter the RHS data member");
	RHS=pIn->GetValue(pOut);
	//Note: You should validate the LHS to be variable name and RHS to be a value
	//      Call the appropriate functions for this.
		pOut->ClearStatusBar();		


			Point Corner;
	Corner.x = Position.x - UI.ASSGN_WDTH/2;
	Corner.y = Position.y ;

	ValueAssign *temp = new ValueAssign(Corner,LHS,RHS);


			// check if after the entered length is so large it does not fit in the drawing area
			if ( !(Position.y >= UI.ToolBarHeight && Position.y+UI.ASSGN_HI < UI.height - UI.StatusBarHeight && Position.x+temp->getwidth()/2 <= UI.DrawingAreaWidth&&Position.x-temp->getwidth()/2>0))
	      {
			pOut->PrintMessage("ERROR OUT of drawing area because statement is so long !!");
			Position.x=-1;

				return;

	       }

			delete temp;

}

void AddValueAssign::Execute()
{
	ReadActionParameters();
		
	if(Position.x==-1)
	{

		return;
	}
	
	//Calculating left corner of assignement statement block
	Point Corner;
	Corner.x = Position.x - UI.ASSGN_WDTH/2;
	Corner.y = Position.y ;
	
	ValueAssign *pAssign = new ValueAssign(Corner, "", 0);
	pAssign->setLHS(LHS);
	pAssign->setRHS(RHS);
	//TODO: should set the LHS and RHS of pAssign statement
	//      with the data members set and validated before in ReadActionParameters()

	pManager->AddStatement(pAssign); // Adds the created statement to application manger's statement list
}

 AddValueAssign:: ~ AddValueAssign()
 {


 }

