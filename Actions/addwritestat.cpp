#include "addwritestat.h"
#include "../ApplicationManager.h"
#include "../GUI\Input.h"
#include "../GUI\Output.h"
#include "../Statements/writestat.h"

addwritestat::addwritestat(ApplicationManager* pmanager):Action(pmanager)
{
}

void addwritestat::ReadActionParameters()
{
	Input *pIn = pManager->GetInput();
	Output *pOut = pManager->GetOutput();
	
	//write the (Position) parameter
	pOut->PrintMessage("write Statement: Click to add the statement");

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
	pOut->PrintMessage("Please enter the variable or string "   "  u want to write data member");

	RHS=pIn->GetString(pOut);
	if(!IsVariable(RHS))
	{
		while(RHS[0]!='"' || RHS[RHS.length()-1]!='"' || RHS.length()==1)    // one case if he entered only one " 
	{

	pOut->PrintMessage("ERROR !! Please enter a valid variable or string between "   "  u want to write");
		RHS=pIn->GetString(pOut);
		if(IsVariable(RHS))
		{

			break;

		}

	}
	}
		pOut->ClearStatusBar();	


		Point Corner;
	Corner.x = position.x - UI.ASSGN_WDTH/2;
	Corner.y = position.y ;

	writestat *temp = new writestat(Corner,RHS);


			// check if after the entered length is so large it does not fit in the drawing area
			if ( !(position.y >= UI.ToolBarHeight && position.y+UI.ASSGN_HI < UI.height - UI.StatusBarHeight && position.x+temp->getwidth()/2 <= UI.DrawingAreaWidth&&position.x-temp->getwidth()/2>0))
	      {
			pOut->PrintMessage("ERROR OUT of drawing area because statement is so long !!");
			position.x=-1;

				return;

	       }
			delete temp;

}

void addwritestat::Execute()
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
	

	writestat *pAssign = new writestat(Corner,RHS);



	pManager->AddStatement(pAssign); // Adds the created statement to application manger's statement list
}


addwritestat::~addwritestat()
{
}
