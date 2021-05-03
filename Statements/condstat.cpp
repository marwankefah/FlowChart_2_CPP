#include "condstat.h"
#include <sstream>
#include <fstream>

condstat:: condstat(Point center, string Left, string mid, string Right)
{

	LHS=Left;
	cond=mid;
	RHS=Right;
	UpdateStatementText();
	width=UI.ASSGN_WDTH+returnpixelscount()*2;
	topcenter = center;
	
	pOutConn[0] = NULL;	//No connectors yet
	pOutConn[1] = NULL;
	Inlet.x = center.x;
	Inlet.y = center.y;

	Outlet1.x = topcenter.x+width/2 ;
	Outlet1.y = topcenter.y + UI.ASSGN_HI/2;	
	Outlet2.x = topcenter.x-width/2;
	Outlet2.y = topcenter.y + UI.ASSGN_HI/2;
	branchno=-1;
}
Statement * condstat::ClpbrdHelper()
{
	condstat * u = new condstat(topcenter,LHS,cond,RHS);
	return u;
}

	 void condstat:: Save(ofstream &OutFile)
{
	if(OutFile.is_open() == true )
		OutFile << "COND\t" << ID <<"\t"<<topcenter.x <<"\t"<< topcenter.y <<"\t"<<LHS<<"\t";
	if(cond==">")
		 {	OutFile<<"GRT"<<"\t";
	OutFile<<RHS<<"\t"<<endl;
	}
	if(cond=="<")
	{
	OutFile<<"LESS"<<"\t";
	OutFile<<RHS<<"\t" <<endl;
	
	}
	if(cond=="=")
	{	OutFile<<"EQL"<<"\t";
	OutFile<<RHS<<"\t"<<endl;
	}
}
 void condstat:: Load(ifstream &InFile)
{
	if(InFile.is_open() == true )
		
	{
		InFile >> ID >> topcenter.x >> topcenter.y >> LHS >> cond>> RHS;
	}
	if(cond=="GRT")
		cond=">";
	if(cond=="LESS")
		cond="<";
		if(cond=="EQL")
			cond="=";
	Inlet.x = topcenter.x;
	Inlet.y = topcenter.y;

	Outlet1.x = topcenter.x+width/2 ;
	Outlet1.y = topcenter.y + UI.ASSGN_HI/2;	
	Outlet2.x = topcenter.x-width/2;
	Outlet2.y = topcenter.y + UI.ASSGN_HI/2;	
		UpdateStatementText();
		width=UI.ASSGN_WDTH+returnpixelscount()*2;
		
		
}
 bool condstat:: is_p_here(Point p) 
{

	 // x/a +y/b <=1 this is the equation of the first plane of the rhombus all will be the same in the four sections a is the horizontal distance between the center and corner and b is the vertical dist
			 if( p.x>= topcenter.x-width/2  && p.x<=topcenter.x+width/2&& p.y>=topcenter.y&&p.y <= topcenter.y+UI.ASSGN_HI)  // it is in the x coordinates and y
	{
		double x1=width/2;
		double y1=UI.ASSGN_HI/2;
		double x= (p.x-topcenter.x)/(x1-topcenter.x);
		double y=(p.y-(topcenter.y+y1))/(y1);
		double l=abs(x)+abs(y);
		if(l <0.99999999)
		{
			if(p.x <= topcenter.x)
			{
				branchno=1;
			}
			else
			{
				branchno=2;

			}
			



			return true;

		}


	}
			
	return false;

}

 int condstat:: caniout()  const
{
	if(pOutConn[0]==NULL &&pOutConn[1]==NULL)
	{
		return 3;  // place for both


	}
	if(pOutConn[0]==NULL)  // place for only the yes
	{
		return 1;


	}
	if(pOutConn[1]==NULL)  // place for only the np
	{
		return 2;


	}

	return 0;
	


}
	void condstat:: setLHS(const string &L)// why is this const &
	{
		LHS=L;

	}
	void  condstat:: setcond(string mid)
	{
		cond=mid;

	}
	void condstat:: setRHS(string R)
	{
		RHS=R;

	}

	 void condstat:: Draw(Output* pOut) const
	 {

		 pOut->DrawConditionalstat(topcenter,Text,Selected,width);

	 }
	
void condstat:: setoutconnector(Connector *c,int branch)
	{
		if(pOutConn[0]!=NULL && pOutConn[1]!=NULL)
		{

			return;

		}
		if(branch==1&&pOutConn[0]==NULL)   /// branch is empty
		{
			c->setStartPoint(Outlet2);
			pOutConn[0]=c;
			return;

		}
			if(branch==2&&pOutConn[1]==NULL)   /// branch is empty
		{
			c->setStartPoint(Outlet1);
			pOutConn[1]=c;
			return;

		}


 }

bool condstat::playwithvararr(ApplicationManager *ptr,Var **x,int arrsize)
	{

		if(!IsValue(LHS)&&!ptr->isinarr(LHS))  // lhs not in the array
		{
					Output*pout=ptr->GetOutput();
					string text="CONDINIONAL STATEMENT HAS A PROBLEM  VARIABLE  "+LHS+" is Not initalized";
					Sleep(1000);
					pout->PrintMessage(text);
						Sleep(2000);
			return false;

		}

		if(!IsValue(RHS)&&!ptr->isinarr(RHS))  // lhs not in the array
		{
					Output*pout=ptr->GetOutput();
					string text="CONDINIONAL STATEMENT HAS A PROBLEM  VARIABLE  "+RHS+" is Not initalized";
					Sleep(700);
					pout->PrintMessage(text);
						Sleep(2000);
			return false;

		}



		return true; 



	}

Connector* condstat::runstat(ApplicationManager* ptr,int &C)	//run the statement and returnsthe pout connect for the next stat
	{
		

		bool x=false;
		// all the comming conditions can be made by overloading the string operator but no time to ask the instructor no email response :)
if(cond==">")
{
	if(!IsValue(RHS))
	{
		if(ptr->getvarvalue(LHS) > ptr->getvarvalue(RHS))
		{
			x=true;

		}


	}
	else
	{
		double valrhs=strtod(&RHS[0],NULL); // convert the string to double value for example "12.5" will be 12.5

		if(ptr->getvarvalue(LHS) > valrhs)
		{
			x=true;


		}


	}


}
else if(cond=="<")
{
		if(!IsValue(RHS))
	{
		if(ptr->getvarvalue(LHS) < ptr->getvarvalue(RHS))
		{
			x=true;

		}


	}
	else    // it is a value but we need to get it first
	{
		double valrhs=strtod(&RHS[0],NULL); // convert the string to double value for example "12.5" will be 12.5

		if(ptr->getvarvalue(LHS) <valrhs)
		{
			x=true;


		}


	}

}
else if(cond=="<=")
{

		if(!IsValue(RHS))
	{
		if(ptr->getvarvalue(LHS) <= ptr->getvarvalue(RHS))
		{
			x=true;

		}


	}
	else
	{
		double valrhs=strtod(&RHS[0],NULL); // convert the string to double value for example "12.5" will be 12.5

		if(ptr->getvarvalue(LHS) <= valrhs)
		{
			x=true;


		}


	}

}
else if( cond==">=")
{

		if(!IsValue(RHS))
	{
		if(ptr->getvarvalue(LHS) >= ptr->getvarvalue(RHS))
		{
			x=true;

		}


	}
	else
	{
		double valrhs=strtod(&RHS[0],NULL); // convert the string to double value for example "12.5" will be 12.5

		if(ptr->getvarvalue(LHS) >= valrhs)
		{
			x=true;


		}


	}

}
else if(cond=="==")
{

		if(!IsValue(RHS))
	{
		if(ptr->getvarvalue(LHS) == ptr->getvarvalue(RHS))
		{
			x=true;

		}


	}
	else
	{
		double valrhs=strtod(&RHS[0],NULL); // convert the string to double value for example "12.5" will be 12.5

		if(ptr->getvarvalue(LHS) == valrhs)
		{
			x=true;


		}


	}

}

if(x==true)
{
	return getpoutconnect(1); // yes connector

}


return getpoutconnect(2); // no connector
	}

bool condstat:: isconnoutvalid() const
{
	if(pOutConn[0]!=NULL && pOutConn[1]!=NULL )
	{
		return true;
	}
	return false;


}
void condstat::removepout(Connector *C)
{
	if(pOutConn[0]==C)
	{
	pOutConn[0]=NULL;
	}
	else if(pOutConn[1]==C)
	{
		pOutConn[1]=NULL;

	}


}

Connector* condstat:: getpoutconnect(int branch) const
{
	if(branch==1)
	{
	return pOutConn[0];
	}
	else if(branch==2)
	{
		return pOutConn[1];
	}
	return NULL;
}
void condstat::Edit(Output* pOut,Input * pIn)
{
	string tempLHS;
	string tempRHS;
	string tempCOND;
	pOut->PrintMessage("Please enter the LHS data member(variable or number)");
	tempLHS=pIn->Getvariable(pOut);
	while(ValueOrVariable(tempLHS)==INVALID_OP)
	{
			pOut->PrintMessage("ERROR Please enter the first variable or number to make the cond");

			tempLHS=pIn->GetString(pOut);

	}

		pOut->ClearStatusBar();		

	pOut->PrintMessage("Please enter the condition to check ex:==");
	tempCOND=pIn->GetCompOperator(pOut);

		pOut->ClearStatusBar();		

	pOut->PrintMessage("Please enter the second variable or number to make the cond");

		tempRHS=pIn->GetString(pOut);

	while(ValueOrVariable(tempRHS)==INVALID_OP)
	{
				pOut->PrintMessage("ERROR Please enter the second variable or number to make the cond");

			tempRHS=pIn->GetString(pOut);

	}
	
				pOut->ClearStatusBar();	

		condstat *temp = new condstat(topcenter,tempLHS,tempCOND,tempRHS);

			// check if after the entered length is so large it does not fit in the drawing area
	if ( !(topcenter.y >= UI.ToolBarHeight && topcenter.y+UI.ASSGN_HI < UI.height - UI.StatusBarHeight && topcenter.x+temp->getwidth()/2 <= UI.DrawingAreaWidth&&topcenter.x-temp->getwidth()/2>0))
	      {
			pOut->PrintMessage("ERROR OUT of drawing area because statement is so long !!");
			delete temp;
				return;

	       }
	delete temp;
	LHS = tempLHS;
	RHS = tempRHS;
	cond = tempCOND;
	UpdateStatementText();
	width=UI.ASSGN_WDTH+returnpixelscount()*2;

}

Statement * condstat::paste(Point dest)
{
	condstat * x =  new condstat(dest,LHS,cond,RHS);
	return x;
}
void condstat:: setinconnector(Connector *c)
	{
		if(c->getDstStat()==this)
		{

			c->setEndPoint(Inlet);

		}
	


 }


void condstat::UpdateStatementText()
{
	//Build the statement text: Left handside then equals then right handside
	ostringstream T;
	
	T<<LHS<<cond<<RHS;	
	Text = T.str();	 
}

		 int condstat ::getwidth() const
		{
			return width;


		}

condstat::~condstat()
{
}
