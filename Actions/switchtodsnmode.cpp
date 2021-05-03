#include "switchtodsnmode.h"
#include "../GUI\Output.h"
#include "../ApplicationManager.h"
switchtodsnmode::switchtodsnmode(ApplicationManager *p):Action(p)
{
}


void switchtodsnmode:: ReadActionParameters()
{

	return;

}

void switchtodsnmode:: Execute()
{

	Output* pout=pManager->GetOutput();
	
	pout->CreateDesignToolBar();
	pout->PrintMessage("DESIGN MODE");


		Sleep(1000);


}



switchtodsnmode::~switchtodsnmode()
{
}
