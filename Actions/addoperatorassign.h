#pragma once
#include "Action.h"
class addoperatorassign :
	public Action
{
	Point position;
	string LHS;
	string lop;
	string op;
	string rop;
public:
	addoperatorassign(ApplicationManager* pmanager);
	virtual void ReadActionParameters();
	virtual void Execute();
	~addoperatorassign();
};
