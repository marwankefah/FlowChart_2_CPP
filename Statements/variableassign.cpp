#include "variableassign.h"
#include <sstream>
#include<fstream>

using namespace std;

variableassign::variableassign(Point Lcorner, string LeftHS, string RightHS)
{
	// Note: The LeftHS and RightHS should be validated inside (Addvariableassign) action
	//       before passing it to the constructor of variableassign
	LHS = LeftHS;
	RHS = RightHS;
	branchno=0;
	UpdateStatementText();
		 width=UI.ASSGN_WDTH+returnpixelscount()*2;

	LeftCorner = Lcorner;
	
	pOutConn = NULL;	//No connectors yet

	Inlet.x = LeftCorner.x + width/2;
	Inlet.y = LeftCorner.y;

	Outlet.x = Inlet.x;
	Outlet.y = LeftCorner.y + UI.ASSGN_HI;	
}
Statement * variableassign::ClpbrdHelper(void)
{
	variableassign * u = new variableassign(LeftCorner,LHS,RHS);
	return u;
}

void variableassign:: Save(ofstream &OutFile)
		{
	if(OutFile.is_open() == true )
		OutFile << "VAR\t" << ID <<"\t"<<LeftCorner.x <<"\t"<< LeftCorner.y <<"\t"<<LHS<<"\t"<<RHS<<"\t"<<endl;
		}
 void variableassign:: Load(ifstream &InFile)
{
	if(InFile.is_open() == true )
		
	{
		InFile >> ID >> LeftCorner.x >> LeftCorner.y >> LHS >> RHS  ;
	}
	Inlet.x = LeftCorner.x + width/2;
	Inlet.y = LeftCorner.y;

	Outlet.x = Inlet.x;
	Outlet.y = LeftCorner.y + UI.ASSGN_HI;	
	UpdateStatementText();
	width=UI.ASSGN_WDTH+returnpixelscount()*2;
}void variableassign::setLHS(const string &L)
{
	LHS = L;
	UpdateStatementText();
}

void variableassign::setRHS(string R)
{
	RHS = R;
	UpdateStatementText();
}


void variableassign::Draw(Output* pOut) const
{
	//Call Output::DrawAssign function to draw assignment statement 

	pOut->DrawAssign(LeftCorner,Text,Selected,width,UI.ASSGN_HI);



}

int variableassign:: caniout()  const
{
	if(pOutConn==NULL)
	{
	return 1;

	}

	return 0;
	


}


	 bool variableassign:: is_p_here(Point p) 
	 {

				if(p.x> LeftCorner.x && p.y>LeftCorner.y  &&p.y < LeftCorner.y+UI.ASSGN_HI&&p.x<=width+LeftCorner.x)
		 {
			return true;


	     }
		 return false;
	 }

	 void variableassign:: setoutconnector(Connector *c,int branch)
	{
		if(pOutConn!=NULL)
		{

			return;

		}
		if(branch==0&&c->getSrcStat()==this)   /// branch is empty
		{
			c->setStartPoint(Outlet);
						pOutConn=c;

			return;

		}
		



 }
	 Connector* variableassign ::runstat(ApplicationManager*ptr,int &c)
	 {


	 double val=ptr->getvarvalue(RHS);
	if(ptr->isinarr(LHS))  // lhs already in array
	{

		ptr->updatevarval(LHS,val);
	}
	else   // not in array
	{
		Var temp(LHS,val,true);

		ptr->addtovararr(&temp);



	}


	return getpoutconnect(0);

	 }
	 bool variableassign:: playwithvararr(ApplicationManager *ptr,Var **vararr,int arrsize)
{
	
	if(!ptr->isinarr(RHS))
	{

		Output*pout=ptr->GetOutput();
					string text="VARIABLE  STATEMENT HAS A PROBLEM  VARIABLE  "+RHS+" is Not initalized";
					Sleep(1000);
					pout->PrintMessage(text);
						Sleep(2000);
			return false;
	}
	
	double val=ptr->getvarvalue(RHS);
	if(ptr->isinarr(LHS))  // lhs already in array
	{

		ptr->updatevarval(LHS,val);
	}
	else   // not in array
	{
		Var temp(LHS,val,true);

		ptr->addtovararr(&temp);



	}



	return true;




}

	 void variableassign::removepout(Connector *C)
{
	pOutConn=NULL;
	


}

	 Connector* variableassign:: getpoutconnect(int branch) const
{
	return pOutConn;



}
	 void variableassign::Edit(Output* pOut,Input * pIn)
{
	string tempLHS;
	string tempRHS;
	//TODO: Ask the user in the status bar to enter the LHS and set the data member
	pOut->PrintMessage("Please enter the LHS data member");
	tempLHS=pIn->Getvariable(pOut);
	//TODO: Ask the user in the status bar to enter the RHS and set the data member
	pOut->PrintMessage("Please enter the RHS data member");
	tempRHS=pIn->Getvariable(pOut);
		pOut->ClearStatusBar();		

	//Note: You should validate the LHS to be variable name and RHS to be a value
	//      Call the appropriate functions for this.


	variableassign *temp = new variableassign(LeftCorner,tempLHS,tempRHS);


			// check if after the entered length is so large it does not fit in the drawing area
			if ( !(LeftCorner.y >= UI.ToolBarHeight && LeftCorner.y+UI.ASSGN_HI < UI.height - UI.StatusBarHeight && LeftCorner.x+temp->getwidth()/2 <= UI.DrawingAreaWidth&&LeftCorner.x-temp->getwidth()/2>0))
	      {
			pOut->PrintMessage("ERROR OUT of drawing area because statement is so long !!");
				delete temp;
				return;

	       }
	RHS = tempRHS;
	LHS = tempLHS;
	delete temp;
	UpdateStatementText();
	width=UI.ASSGN_WDTH+returnpixelscount()*2;


}

	 bool variableassign:: isconnoutvalid() const
{
	if(pOutConn!=NULL)
	{

		return true;
	}
	return false;


}

	 Statement * variableassign::paste(Point dest)
{
	variableassign * x = new variableassign(dest,LHS,RHS);
	return x;
}
	 void variableassign:: setinconnector(Connector *c)
	{
		if(c->getDstStat()==this)
		{

			c->setEndPoint(Inlet);

		}
	


 }
	 int variableassign ::getwidth() const
		{
			return width;


		}
//This function should be called when LHS or RHS changes
void variableassign::UpdateStatementText()
{
	//Build the statement text: Left handside then equals then right handside
	ostringstream T;
	T<<LHS<<" = "<<RHS;	
	Text = T.str();	 
}

variableassign::~variableassign()
{



}