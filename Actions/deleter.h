#pragma once
#include "Action.h"
#include "../Statements\Statement.h"
#include "../Connector.h"

class deleter :
	public Action
{
private:
	Statement * deadStat;
	Connector * deadConn;
public:
	deleter(ApplicationManager* pAppManager);
	virtual void ReadActionParameters();
	virtual void Execute();
	~deleter();
};

