#pragma once
#include "Action.h"
class Paste :
	public Action
{
	Point position;
public:
	Paste(ApplicationManager* pAppManager);
	virtual void ReadActionParameters();
	virtual void Execute();
	~Paste(void);
};

