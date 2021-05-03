#include "addstart.h"
#include "../ApplicationManager.h"
#include "../GUI\Input.h"
#include "../GUI\Output.h"
#include "../Statements/startstat.h"

addstart::addstart(ApplicationManager* pmanager):Action(pmanager)
{
}

void addstart::ReadActionParameters()
{
	Input *pIn = pManager->GetInput();
	Output *pOut = pManager->GetOutput();

	//Read the (Position) parameter
	pOut->PrintMessage("ADD START : Click to add the statement");

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


}

void addstart::Execute()
{
	ReadActionParameters();
		
	if(position.x==-1)
	{

		return;
	}
	Point center;
	center.x=position.x;
	center.y=position.y+UI.ASSGN_HI/2;


	startstat *pAssign = new startstat(center);

	pManager->AddStatement(pAssign); // Adds the created statement to application manger's statement list
}


addstart::~addstart()
{
}
