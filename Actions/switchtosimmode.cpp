#include "switchtosimmode.h"
#include "../GUI\Output.h"
#include "../ApplicationManager.h"
switchtosimmode::switchtosimmode(ApplicationManager *p):Action(p)
{
}


void switchtosimmode:: ReadActionParameters()
{

	return;

}

void switchtosimmode:: Execute()
{

	Output* pout=pManager->GetOutput();
	
	pout->CreateSimulationToolBar();
	pout->PrintMessage("SIMULATION MODE");


		Sleep(1000);


}



switchtosimmode::~switchtosimmode()
{
}
