#include "Paste.h"
#include "addstart.h"
#include "../ApplicationManager.h"
#include "../GUI\Input.h"
#include "../GUI\Output.h"
#include "../Statements/startstat.h"

Paste::Paste(ApplicationManager* pAppManager):Action(pAppManager)
{
}
void Paste::ReadActionParameters()
{
	
	Input *pIn = pManager->GetInput();
	Output *pOut = pManager->GetOutput();


		Statement * clpbrd = pManager->GetClipboard();
		if(clpbrd==NULL)
		{
						position.x=-1;

				pOut->PrintMessage("ERROR clipboardempty!!saly 3la elnaby enta btpaste abl ama tcopy??");
				Sleep(2000);
					pOut->ClearStatusBar();		

			return;
		}
	//Read the (Position) parameter
	pOut->PrintMessage("Click to add the copied statement ");

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
void::Paste::Execute()
{
	ReadActionParameters();
	if(position.x==-1)
	{

		return;
	}
	Statement * clpbrd = pManager->GetClipboard();
	Statement * x = clpbrd->paste(position);
	pManager->AddStatement(x);
}
Paste::~Paste(void)
{
}
