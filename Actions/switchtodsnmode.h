#pragma once
#include "Action.h"
class switchtodsnmode :
	public Action
{
public:
	switchtodsnmode(ApplicationManager *pmmanger);
	virtual void ReadActionParameters();
	
	virtual void Execute() ;
	~switchtodsnmode();
};

