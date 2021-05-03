#include "operatorassign.h"
#include <sstream>
#include<fstream>

using namespace std;

operatorassign::operatorassign(Point Lcorner, string LeftHS,string lp, string op1,string rp)
{
	// Note: The LeftHS and RightHS should be validated inside (Addoperatorassign) action
	//       before passing it to the constructor of operatorassign
	LHS = LeftHS;
	rop=rp;
	lop=lp;
	op=op1;
	UpdateStatementText();
		 width=UI.ASSGN_WDTH+returnpixelscount()*2;

	LeftCorner = Lcorner;
	
	pOutConn = NULL;	//No connectors yet
	branchno=0;
	Inlet.x = LeftCorner.x + width /2;
	Inlet.y = LeftCorner.y;

	Outlet.x = Inlet.x;
	Outlet.y = LeftCorner.y + UI.ASSGN_HI;	
}
Statement * operatorassign::ClpbrdHelper(void)
{
	operatorassign * u = new operatorassign(LeftCorner,LHS,lop,op,rop);
	return u;
}
void operatorassign::Edit(Output* pOut,Input * pIn)
{
	string tempLHS;
	string tempLOP;
	string tempROP;
	string tempOP;
	//TODO: Ask the user in the status bar to enter the LHS and set the data member
	pOut->PrintMessage("Please enter the LHS data member(variable)");
	tempLHS=pIn->Getvariable(pOut);
	//TODO: Ask the user in the status bar to enter the RHS and set the data member
	pOut->PrintMessage("Please enter the fist data member(variable or number) to make the op ");
	tempLOP=pIn->GetString(pOut);

	while(ValueOrVariable(lop)==INVALID_OP)
	{
						pOut->PrintMessage("ERROR Please enter the first variable or number to make the op");

			tempLOP=pIn->GetString(pOut);

	}

	pOut->PrintMessage("Please enter the operation needed");
	tempOP=pIn->Getarithoperator(pOut);
		pOut->PrintMessage("Please enter the second variable or number to make the op");

		tempROP=pIn->GetString(pOut);

	while(ValueOrVariable(rop)==INVALID_OP)
	{
				pOut->PrintMessage("ERROR Please enter the second variable or number to make the op");

			tempROP=pIn->GetString(pOut);

	}



		pOut->ClearStatusBar();	



		operatorassign *temp = new operatorassign(LeftCorner,lop,op,rop);


			// check if after the entered length is so large it does not fit in the drawing area
			if ( !(LeftCorner.y >= UI.ToolBarHeight && LeftCorner.y+UI.ASSGN_HI < UI.height - UI.StatusBarHeight && LeftCorner.x+temp->getwidth()/2 <= UI.DrawingAreaWidth&&LeftCorner.x-temp->getwidth()/2>0))
	      {
			pOut->PrintMessage("ERROR OUT of drawing area because statement is so long !!");
			delete temp;
				return;

	       }
		lop=tempLOP;
		rop=tempROP;
		op=tempOP;
		LHS=tempLHS;
		delete temp;
		UpdateStatementText();
		width=UI.ASSGN_WDTH+returnpixelscount()*2;

}

void operatorassign:: Save(ofstream &OutFile)
{
	if(OutFile.is_open() == true )
		OutFile << "OP_ASSIGN\t" << ID <<"\t"<< LeftCorner.x <<"\t"<< LeftCorner.y <<"\t"<<LHS<<"\t"<<lop<<"\t";
	if(op=="*")
		OutFile<<"MUL"<<"\t"<<rop<<"\t"<<endl;
	if(op=="/")
		OutFile<<"DIV"<<"\t"<<rop<<"\t"<<endl;
	if(op=="+")
		OutFile<<"ADD"<<"\t"<<rop<<"\t"<<endl;
	if(op=="-")
		OutFile<<"SUB"<<"\t"<<rop<<"\t"<<endl;
	

}

void operatorassign:: Load(ifstream &InFile)
{
	if(InFile.is_open() == true )
		
	{
		InFile >> ID >> LeftCorner.x >> LeftCorner.y >> LHS >> lop >> op >> rop ;

	}
	if(op=="MUL")
		op="*";
	if(op=="DIV")
		op="/";
		if(op=="ADD")
			op="+";
		if(op=="SUB")
			op="-";
		
	Inlet.x = LeftCorner.x + width /2;
	Inlet.y = LeftCorner.y;

	Outlet.x = Inlet.x;
	Outlet.y = LeftCorner.y + UI.ASSGN_HI;	
	UpdateStatementText();
	 width=UI.ASSGN_WDTH+returnpixelscount()*2;
			
}
void operatorassign::setLHS(const string &L)
{
	LHS = L;
	UpdateStatementText();
}

void operatorassign::setlop(string R)
{
	
	UpdateStatementText();
}
Connector* operatorassign:: getpoutconnect(int branch) const
{
	return pOutConn;



}
bool operatorassign:: isconnoutvalid() const
{
	if(pOutConn!=NULL)
	{

		return true;
	}
	return false;


}
void operatorassign::setop(string R)
{
	
	UpdateStatementText();
}
void operatorassign::setrop(string R)
{
	
	UpdateStatementText();
}

void operatorassign::Draw(Output* pOut) const
{
	//Call Output::DrawAssign function to draw assignment statement 

	pOut->DrawAssign(LeftCorner,Text,Selected,width,UI.ASSGN_HI);



}

bool operatorassign:: is_p_here(Point p) 
	 {

				if(p.x> LeftCorner.x && p.y>LeftCorner.y  &&p.y < LeftCorner.y+UI.ASSGN_HI&&p.x<=width+LeftCorner.x)
		 {
			return true;


	     }
		 return false;
	 }
//This function should be called when LHS or RHS changes
void operatorassign::UpdateStatementText()
{
	//Build the statement text: Left handside then equals then right handside
	ostringstream T;
	string RHS;
	RHS=lop+op+rop;
	T<<LHS<<" = "<<RHS;	
	Text = T.str();	 
}
int operatorassign ::getwidth() const
		{
			return width;


		}
int operatorassign:: caniout()  const
{
	if(pOutConn==NULL)
	{
	return 1;

	}

	return 0;
	


}
Connector* operatorassign ::runstat(ApplicationManager*ptr, int &C)	//run the statement and returnsthe pout connect for the next stat
{
	double temp1=0;
		double temp2=0;

		if(ptr->isinarr(lop))  // in the array of variable
		{
					temp1=ptr->getvarvalue(lop);

		}
		else // is not in the array of varibles must be a value cause at top we check both then return false
		
		{			 temp1=strtod(&lop[0],NULL); // convert the string to double value for example "12.5" will be 12.5


		}

		if(ptr->isinarr(rop)) // in the array of variable
		{					
			temp2=	ptr->getvarvalue(rop);

		} 
		else   // is not in the array of varibles must be a value cause at top we check both then return false
		{

			 temp2=strtod(&rop[0],NULL); // convert the string to double value for example "12.5" will be 12.5


		}





			double val=0;


			if(op=="*")    // make the val 
			{
				val=temp1*temp2;


			}
			else if(op=="/")
			{			
				val=temp1/temp2;

			}
			else if(op=="+")
			{
					val=temp1+temp2;


			}
			else if(op=="-")
			{
				val=temp1-temp2;


			}


		if(!ptr->isinarr(LHS))
		{
			
			Var m(LHS,val,true);
			ptr->addtovararr(&m);

		}
		else  // update the value
		{
			ptr->updatevarval(LHS,val);

		}


	return pOutConn;


}

void operatorassign:: setoutconnector(Connector *c,int branch)
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

    bool operatorassign::playwithvararr(ApplicationManager *ptr,Var **x,int arrsize)
	{
		/* a variable must be initalized so we must check all of this */
		if(!IsValue(lop) && !ptr->isinarr(lop))
		{

			Output*pout=ptr->GetOutput();
					string text="OPERATOR STATEMENT HAS A PROBLEM  VARIABLE  "+lop+" is Not initalized";
					Sleep(1000);
					pout->PrintMessage(text);
						Sleep(2000);
			return false;

		}

		if(!IsValue(rop) && !ptr->isinarr(rop))
		{

			Output*pout=ptr->GetOutput();
					string text="OPERATOR STATEMENT HAS A PROBLEM  VARIABLE  "+rop+" is Not initalized";
					Sleep(1000);
					pout->PrintMessage(text);
						Sleep(2000);
			return false;

		}

		double temp1=0;
		double temp2=0;

		if(ptr->isinarr(lop))  // in the array of variable
		{
					temp1=ptr->getvarvalue(lop);

		}
		else // is not in the array of varibles must be a value cause at top we check both then return false
		
		{			 temp1=strtod(&rop[0],NULL); // convert the string to double value for example "12.5" will be 12.5


		}

		if(ptr->isinarr(rop)) // in the array of variable
		{					
			temp2=	ptr->getvarvalue(lop);

		} 
		else   // is not in the array of varibles must be a value cause at top we check both then return false
		{

			 temp2=strtod(&lop[0],NULL); // convert the string to double value for example "12.5" will be 12.5


		}





			double val=0;


			if(op=="*")    // make the val 
			{
				val=temp1*temp2;


			}
			else if(op=="/")
			{			
				val=temp1/temp2;

			}
			else if(op=="+")
			{
					val=temp1+temp2;


			}
			else if(op=="-")
			{
				val=temp1-temp2;


			}


		if(!ptr->isinarr(LHS))
		{
			
			Var m(LHS,val,true);
			ptr->addtovararr(&m);

		}
		else  // update the value
		{
			ptr->updatevarval(LHS,val);

		}

				return true;


	}

Statement * operatorassign::paste(Point dest)
{
	operatorassign * x = new operatorassign(dest,LHS,lop,op,rop);
	return x;
}
void operatorassign::removepout(Connector *C)
{
	pOutConn=NULL;
	


}

void operatorassign:: setinconnector(Connector *c)
	{
		if(c->getDstStat()==this)
		{

			c->setEndPoint(Inlet);

		}
	


 }
 operatorassign:: ~operatorassign()
 {



 }
