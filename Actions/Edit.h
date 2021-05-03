#pragma once
#include "Action.h"
#include "../Statements\Statement.h"
class Edit :
	public Action
{
	Statement * target;
	Input *pIn;
	Output *pout;
public:
	Edit(ApplicationManager* pAppManager);
	void ReadActionParameters(void);
	void Execute(void);
	~Edit(void);
};

