#include "ValueAssign.h"
#include <sstream>
#include "../Actions/validiate.h"
using namespace std;
#include <fstream>
ValueAssign::ValueAssign(Point Lcorner, string LeftHS, double RightHS)
{
	// Note: The LeftHS and RightHS should be validated inside (AddValueAssign) action
	//       before passing it to the constructor of ValueAssign
	LHS = LeftHS;
	RHS = RightHS;
	 width=UI.ASSGN_WDTH+returnpixelscount()*2;
	UpdateStatementText();

	LeftCorner = Lcorner;
	branchno=0;
	pOutConn = NULL;	//No connectors yet

	Inlet.x = LeftCorner.x + width /2;
	Inlet.y = LeftCorner.y;

	Outlet.x = Inlet.x;
	Outlet.y = LeftCorner.y + UI.ASSGN_HI;	
}
Statement * ValueAssign::ClpbrdHelper(void)
{
	ValueAssign * u = new ValueAssign(LeftCorner,LHS,RHS);
	return u;
}
void ValueAssign::setLHS(const string &L)
{
	LHS = L;
	UpdateStatementText();
}

void ValueAssign::setRHS(double R)
{
	RHS = R;
	UpdateStatementText();
}
void ValueAssign:: Save(ofstream &OutFile)
		{
	if(OutFile.is_open() == true )
		OutFile << "VAL\t" << ID <<"\t"<<LeftCorner.x <<"\t"<< LeftCorner.y <<"\t"<<LHS<<"\t"<<RHS<<"\t"<<endl;
		}
void ValueAssign:: Load(ifstream &InFile)
{
	if(InFile.is_open() == true )
		
	{
		InFile >> ID >> LeftCorner.x >> LeftCorner.y >> LHS >> RHS  ;
	}
	
	Inlet.x = LeftCorner.x + width /2;
	Inlet.y = LeftCorner.y;

	Outlet.x = Inlet.x;
	Outlet.y = LeftCorner.y + UI.ASSGN_HI;	
	UpdateStatementText();
	width=UI.ASSGN_WDTH+returnpixelscount()*2;
}
void ValueAssign:: setoutconnector(Connector *c,int branch)
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
void ValueAssign::Edit(Output* pOut,Input * pIn)
{
	string tempLHS;
	double tempRHS;
	//TODO: Ask the user in the status bar to enter the LHS and set the data member
	pOut->PrintMessage("Please enter the LHS data member");
	tempLHS=pIn->Getvariable(pOut);
	//TODO: Ask the user in the status bar to enter the RHS and set the data member
	pOut->PrintMessage("Please enter the RHS data member");
	tempRHS=pIn->GetValue(pOut);
	//Note: You should validate the LHS to be variable name and RHS to be a value
	//      Call the appropriate functions for this.
		pOut->ClearStatusBar();		


	ValueAssign *temp = new ValueAssign(LeftCorner,tempLHS,tempRHS);


			// check if after the entered length is so large it does not fit in the drawing area
			if ( !(LeftCorner.y >= UI.ToolBarHeight && LeftCorner.y+UI.ASSGN_HI < UI.height - UI.StatusBarHeight && LeftCorner.x+temp->getwidth()/2 <= UI.DrawingAreaWidth&&LeftCorner.x-temp->getwidth()/2>0))
	      {
			pOut->PrintMessage("ERROR OUT of drawing area because statement is so long !!");
			delete temp;
				return;

	       }
	LHS = tempLHS;
	RHS = tempRHS;
	delete temp;
	UpdateStatementText();
	width=UI.ASSGN_WDTH+returnpixelscount()*2;

}

void ValueAssign:: setinconnector(Connector *c)
	{
		if(c->getDstStat()==this)
		{

			c->setEndPoint(Inlet);

		}
	


 }
Connector* ValueAssign ::runstat(ApplicationManager*ptr, int &C)	//run the statement and returnsthe pout connect for the next stat
{

if(!ptr->isinarr(LHS))
	{

		Var temp(LHS,RHS,true);

		ptr->addtovararr(&temp);
		
	

	}
	else   // update its value in arr
	{

		ptr->updatevarval(LHS,RHS);
	

	}

	return getpoutconnect(0);

}

bool ValueAssign:: playwithvararr(ApplicationManager *ptr,Var **vararr,int arrsize)
{
	
	if(!ptr->isinarr(LHS))
	{

		Var temp(LHS,RHS,true);

		ptr->addtovararr(&temp);
		return true;
	

	}
	else   // update its value in arr
	{

		ptr->updatevarval(LHS,RHS);
		return true;

	}
	





}

void ValueAssign::removepout(Connector *C)
{
	pOutConn=NULL;
	


}

Connector* ValueAssign:: getpoutconnect(int branch) const
{
	return pOutConn;



}
bool ValueAssign:: isconnoutvalid() const
{
	if(pOutConn!=NULL)
	{

		return true;
	}
	return false;


}
Statement * ValueAssign::paste(Point dest)
{
	ValueAssign* x = new ValueAssign(dest,LHS,RHS);
	return x;
}

int ValueAssign ::getwidth() const
		{
			return width;


		}
void ValueAssign::Draw(Output* pOut) const
{
	//Call Output::DrawAssign function to draw assignment statement 

	pOut->DrawAssign(LeftCorner,Text,Selected,width,UI.ASSGN_HI);



}

int ValueAssign:: caniout()  const
{
	if(pOutConn==NULL)
	{
	return 1;

	}

	return 0;
	


}

bool ValueAssign:: is_p_here(Point p) 
	 {

				if(p.x> LeftCorner.x && p.y>LeftCorner.y  &&p.y < LeftCorner.y+UI.ASSGN_HI&&p.x<=width+LeftCorner.x)
		 {
			return true;


	     }
		 return false;
	 }

//This function should be called when LHS or RHS changes
void ValueAssign::UpdateStatementText()
{
	//Build the statement text: Left handside then equals then right handside
	ostringstream T;
	T<<LHS<<" = "<<RHS;	
	Text = T.str();	 
}

ValueAssign::~ValueAssign()
{


}