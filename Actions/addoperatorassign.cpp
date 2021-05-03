#include "addoperatorassign.h"
#include "../ApplicationManager.h"
#include "../GUI\Input.h"
#include "../GUI\Output.h"
#include "../Statements/operatorassign.h"

addoperatorassign::addoperatorassign(ApplicationManager* pmanager):Action(pmanager)
{
}

void addoperatorassign::ReadActionParameters()
{
	Input *pIn = pManager->GetInput();
	Output *pOut = pManager->GetOutput();
	
	//Read the (Position) parameter
	pOut->PrintMessage("operator Assignment Statement: Click to add the statement");

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
	pOut->PrintMessage("Please enter the LHS data member(variable)");
	LHS=pIn->Getvariable(pOut);
	//TODO: Ask the user in the status bar to enter the RHS and set the data member
	pOut->PrintMessage("Please enter the fist data member(variable or number) to make the op ");
	lop=pIn->GetString(pOut);

	while(ValueOrVariable(lop)==INVALID_OP)
	{
						pOut->PrintMessage("ERROR Please enter the first variable or number to make the op");

			lop=pIn->GetString(pOut);

	}

	pOut->PrintMessage("Please enter the operation needed");
	op=pIn->Getarithoperator(pOut);
		pOut->PrintMessage("Please enter the second variable or number to make the op");

		rop=pIn->GetString(pOut);

	while(ValueOrVariable(rop)==INVALID_OP)
	{
				pOut->PrintMessage("ERROR Please enter the second variable or number to make the op");

			rop=pIn->GetString(pOut);

	}



		pOut->ClearStatusBar();	


		Point Corner;
	Corner.x = position.x - UI.ASSGN_WDTH/2;
	Corner.y = position.y ;

		operatorassign *temp = new operatorassign(Corner,lop,op,rop);


			// check if after the entered length is so large it does not fit in the drawing area
			if ( !(position.y >= UI.ToolBarHeight && position.y+UI.ASSGN_HI < UI.height - UI.StatusBarHeight && position.x+temp->getwidth()/2 <= UI.DrawingAreaWidth&&position.x-temp->getwidth()/2>0))
	      {
			pOut->PrintMessage("ERROR OUT of drawing area because statement is so long !!");
			position.x=-1;

				return;

	       }

			delete temp;


}

void addoperatorassign::Execute()
{
		
	
	//Calculating left corner of assignement statement block
	ReadActionParameters();
	if(position.x==-1)
	{

		return;
	}
	
	Point Corner;
	Corner.x = position.x - UI.ASSGN_WDTH/2;
	Corner.y = position.y ;
	
	operatorassign *pAssign = new operatorassign(Corner,LHS,lop,op,rop);
	
	pManager->AddStatement(pAssign); // Adds the created statement to application manger's statement list
}


addoperatorassign::~addoperatorassign()
{
}
