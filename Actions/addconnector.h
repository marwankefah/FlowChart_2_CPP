#ifndef add_connector_H
#define add_connector_H

#include "Action.h"
#include "../Connector.h"

class addconnector : public Action
{
private:
	Statement *SrcStat;	//The source statement of the connector
	Statement *DstStat;	//The destination statement of the connector
	Point Start;	//Start point of the connector
	Point End;		//End point of the connector
	int branchno;   // 0 for any stat 1 and 2 for cond

public:

	addconnector(ApplicationManager *pAppManager);
	
	//Read Assignemt statements position
	virtual void ReadActionParameters();
	
	//Create and add an assignemnt statement to the list of statements
	virtual void Execute() ;
	
};

#endif