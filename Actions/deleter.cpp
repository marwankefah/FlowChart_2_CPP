#include "deleter.h"
#include "../ApplicationManager.h"
#include "../Connector.h"
#include <sstream>
#include "../Statements\Statement.h"
#include "../Statements/condstat.h"
deleter::deleter(ApplicationManager* pAppManager):Action(pAppManager)
{
	deadStat = NULL;
	deadConn = NULL;
}

 void deleter::ReadActionParameters()
{
	deadConn = pManager->getselectedconnector();
	deadStat = pManager->GetSelectedStatement();


}
 void deleter::Execute()
{
	ReadActionParameters();
	Output *pout=pManager->GetOutput();
	if(deadConn==NULL&&deadStat==NULL)
	{
		pout->PrintMessage("NOTHING TO DELETE select 3edl ya bashmo");
		Sleep(1000);
		pout->ClearStatusBar();
		return;
	}
	if(deadConn != NULL)
	{
	

		pManager->DeleteConnector(deadConn);


	}
	else
		{
			pManager->DeleteStatement(deadStat);
		}
}
deleter::~deleter(void)
{

}
