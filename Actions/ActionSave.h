#pragma once
#include "Action.h"
class ActionSave :
	public Action

{
	string filename;
public:
	ActionSave(ApplicationManager * pManager);
	virtual void ReadActionParameters(void);
	void Execute(void);
	~ActionSave(void);
};

