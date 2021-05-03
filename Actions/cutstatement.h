#pragma once
#include "Action.h"
#include "../ApplicationManager.h"
#include <sstream>
#include "../Statements\Statement.h"
class cutstatement :
	public Action
{
	Statement * target;
public:
	cutstatement(ApplicationManager* pAppManager);
	virtual void ReadActionParameters();
	virtual void Execute();
	~cutstatement(void);
};

