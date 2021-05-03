#pragma once
#include "Action.h"
class selectaction :
	public Action
{
Point p;

    public:
	selectaction(ApplicationManager * pmanager);
	virtual void ReadActionParameters();
	virtual void Execute();
	~selectaction();
};

