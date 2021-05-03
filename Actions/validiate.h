#pragma once
#include "Action.h"
#include "../Var.h"
class validiate :
	public Action
{
	

public:
	validiate(ApplicationManager*pmanager);
    virtual void ReadActionParameters();
	virtual void Execute();


	~validiate(void);
};

