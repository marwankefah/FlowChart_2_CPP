#include "ActionSave.h"
#include"../ApplicationManager.h"
#include <iostream>
using namespace std;
#include<fstream>

ActionSave::ActionSave(ApplicationManager * pManager):Action(pManager)
{
}
void ActionSave::ReadActionParameters(void)
{
Input *pIn = pManager->GetInput();
	Output *pOut = pManager->GetOutput();
	pOut->PrintMessage("ENTER THE FILE NAME :D");
	filename=pIn->GetString(pOut);
	

	
}
void ActionSave::Execute(void)

{
	ReadActionParameters();
    ofstream file;
    file.open(filename.c_str());
	if(file.is_open() == true )	
{	pManager -> Save(file);
    file.close();
	Output *pOut = pManager->GetOutput();
	pOut->PrintMessage("SAVED");
	

}
	else
	{	Output *pOut = pManager->GetOutput();
	pOut->PrintMessage("NOTSAVED");
	}
		
}

ActionSave::~ActionSave(void)
{
}
