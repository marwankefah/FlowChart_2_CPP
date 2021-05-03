#pragma once
#include "Action.h"
class switchtosimmode :
	public Action
{
public:
	switchtosimmode(ApplicationManager *pmmanger);
	virtual void ReadActionParameters();
	
	virtual void Execute() ;
	~switchtosimmode();
};

