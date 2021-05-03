#pragma once
#include "Action.h"
class addcondstat :
	public Action
{
	Point position;  // the position is the top center
	string RHS;
	string cond;
	string LHS;

public:
	addcondstat(ApplicationManager* pmanager);
	virtual void ReadActionParameters();
	virtual void Execute();
	~addcondstat();
};

