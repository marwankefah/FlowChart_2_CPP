#pragma once
#include <fstream>

#include "Action.h"
class LoadAction :
	public Action
{
	string filename;
	ifstream file;

public:
	LoadAction(ApplicationManager *pManager);
	void Execute(void);
	void ReadActionParameters(void);
	~LoadAction(void);
};

