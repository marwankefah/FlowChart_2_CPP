#pragma once
#include "Action.h"
#include "../ApplicationManager.h"
#include <sstream>
#include "../Statements\Statement.h"
class copystatement :
	public Action
{
	Statement * const target;
public:
	copystatement(ApplicationManager* pAppManager);
	virtual void ReadActionParameters();
	virtual void Execute();
	~copystatement(void);
};

