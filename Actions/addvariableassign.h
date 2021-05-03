#pragma once
#include "Action.h"
class addvariableassign :
	public Action
{
	Point position;
	string LHS;
	string RHS;
public:
	addvariableassign(ApplicationManager* pmanager);
	virtual void ReadActionParameters();
	virtual void Execute();
	~addvariableassign();
};


