#include "LoadAction.h"
#include"../ApplicationManager.h"
#include <iostream>
#include<fstream>
using namespace std;


LoadAction::LoadAction(ApplicationManager* pManager):Action(pManager)
{
}
void LoadAction::ReadActionParameters(void)
{
	Input *pIn = pManager->GetInput();
	Output *pOut = pManager->GetOutput();
	pOut->PrintMessage("ENTER THE FILE NAME TO LOAD FROM :D");
	filename=pIn->GetString(pOut);
	file.open(filename.c_str());
	if(file.is_open() == false )	
	{
	Output *pOut = pManager->GetOutput();
	pOut->PrintMessage("no file with this name exists");
	}

	
}

void LoadAction::Execute()
{ 	
	 ReadActionParameters();

	if(file.is_open())	
	{
	pManager->ClearForLoad();
	int x=pManager->Load(file);
	pManager->loadConn(x,file);
	file.close();
       }
}
LoadAction::~LoadAction(void)
{
}
