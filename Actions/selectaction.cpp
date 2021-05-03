#include "selectaction.h"
#include "../ApplicationManager.h"
#include "../GUI\Input.h"
#include "../GUI\Output.h"


selectaction:: selectaction(ApplicationManager* pmanager):Action(pmanager)
{
	
}


	 void selectaction::  ReadActionParameters()
	{
			Input *pIn = pManager->GetInput();

			Output* pOut = pManager->GetOutput();
	pOut->PrintMessage("Select a statement or a connector");
			pIn->GetPointClicked(p);

			if ( !(p.y >= UI.ToolBarHeight && p.y< UI.height - UI.StatusBarHeight && p.x <= UI.DrawingAreaWidth ))
	{
			pOut->PrintMessage("ERROR OUT of drawing area !!");
			p.x=-1;

				return;

	}

			pOut->ClearStatusBar();		
		

			

	}



	 void selectaction:: Execute()
	{

		ReadActionParameters();
		if(p.x==-1)
	{

		return;
	}
					Output* pOut = pManager->GetOutput();

			Statement *s1=pManager->GetStatement(p);
			Connector* c1=pManager->GetConnector(p);
			if(s1!=NULL)
			{
				if(s1->IsSelected())
				{
				pManager->GetSelectedStatement()->SetSelected(false);
				pManager->SetSelectedStatement(NULL);
				return;
				}

				if(pManager->GetSelectedStatement()!=NULL)
				{

					pManager->GetSelectedStatement()->SetSelected(false);

				}

				           s1->SetSelected(!s1->IsSelected());
							pOut->PrintMessage("statement is selected");
						
							pManager->SetSelectedStatement(s1);
						
							if(pManager->getselectedconnector()!=NULL)
							{
							pManager->getselectedconnector()->SetSelected(false);
							}
							pManager->setselectedconnector(NULL);
							return;
			}

			else if(c1!=NULL)
			{
				if(c1->IsSelected())
				{
					pManager->getselectedconnector()->SetSelected(false);
					pManager->setselectedconnector(NULL);
				return;
				}

				if(pManager->getselectedconnector()!=NULL)
				{

					pManager->getselectedconnector()->SetSelected(false);

				}
				
					pOut->PrintMessage("connector is selected");
					c1->SetSelected(!c1->IsSelected());

					

					if(pManager->GetSelectedStatement()!=NULL)
							{
								pManager->GetSelectedStatement()->SetSelected(false);
							}
					pManager->SetSelectedStatement(NULL);
				pManager->setselectedconnector(c1);
							return;


			}
			else
			{
									pOut->PrintMessage("Nothing  is selected");


			}

		return;




	}


selectaction::~selectaction(void)
{
}
