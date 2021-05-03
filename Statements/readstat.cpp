#include "readstat.h"
#include <sstream>
#include <fstream>
using namespace std;

readstat::readstat(Point Lcorner, string RHS)
{
	
	readtext=RHS; 

	UpdateStatementText();
	 width=UI.ASSGN_WDTH+returnpixelscount()*2;
	LeftCorner = Lcorner;
	branchno=0;
	pOutConn = NULL;	//No connectors yet

	Inlet.x = LeftCorner.x + width /2;
	Inlet.y = LeftCorner.y;

	Outlet.x = Inlet.x;
	Outlet.y = LeftCorner.y + UI.ASSGN_HI;	
}
Statement * readstat::ClpbrdHelper(void)
{
	readstat * u = new readstat(LeftCorner,readtext);
	return u;
}

void readstat::Edit(Output* pOut,Input * pIn)
{
	string tempReadText;
	//TODO: Ask the user in the status bar to enter the LHS and set the data member
	pOut->PrintMessage("Please enter the variable  u want to read data member");
	tempReadText=pIn->Getvariable(pOut);
	pOut->ClearStatusBar();		


	readstat *temp = new readstat(LeftCorner,readtext);


			// check if after the entered length is so large it does not fit in the drawing area
			if ( !(LeftCorner.y >= UI.ToolBarHeight && LeftCorner.y+UI.ASSGN_HI < UI.height - UI.StatusBarHeight && LeftCorner.x+temp->getwidth()/2 <= UI.DrawingAreaWidth&&LeftCorner.x-temp->getwidth()/2>0))
	      {
			pOut->PrintMessage("ERROR OUT of drawing area because statement is so long !!");
				delete temp;
				return;

	       }
	readtext = tempReadText;
	UpdateStatementText();
 width=UI.ASSGN_WDTH+returnpixelscount()*2;

}

		void readstat:: Save(ofstream &OutFile)
		{
	if(OutFile.is_open() == true )
		OutFile << "READ\t" << ID <<"\t"<<LeftCorner.x <<"\t"<< LeftCorner.y <<"\t"<<readtext<<"\t"<<endl;
		}
 void readstat:: Load(ifstream &InFile)
{
	if(InFile.is_open() == true )
		
	{
		InFile >> ID >> LeftCorner.x >> LeftCorner.y >> readtext  ;
	}
	Inlet.x = LeftCorner.x + width /2;
	Inlet.y = LeftCorner.y;

	Outlet.x = Inlet.x;
	Outlet.y = LeftCorner.y + UI.ASSGN_HI;	
	UpdateStatementText();
	width=UI.ASSGN_WDTH+returnpixelscount()*2;
}
void readstat::setreadtext(const string &L)
{
	readtext = L;
	UpdateStatementText();
}



void readstat::Draw(Output* pOut) const
{
	//Call Output::DrawAssign function to draw assignment statement 
	
	
	pOut->drawIOstat(LeftCorner,Text,Selected,width);


}
int readstat:: caniout()  const
{
	if(pOutConn==NULL)
	{
	return 1;

	}

	return 0;
	


}

 bool readstat:: is_p_here(Point p) 
	{
	
	 // it is insidie the big rectangle 
	  		if(p.x> LeftCorner.x-30 && p.y>LeftCorner.y  && p.y < LeftCorner.y+UI.ASSGN_HI && p.x<width+LeftCorner.x)
		     {
			
				 // here we need to eliminate the two traingles inside the parallelogram
				 Point c1,c2,c3;  // coordinates of first triangle
				 c1.x=LeftCorner.x; c1.y=LeftCorner.y;
				 c2.x=LeftCorner.x-30; c2.y=LeftCorner.y+UI.ASSGN_HI;
				 c3.x=c2.x; c3.y=c1.y;
				 double a1,a2,a3;   // check that the area of the three triangles made by any of the vertices to the point is equal to the area of triangle
				 double areat1= (c2.x-c1.x)* UI.ASSGN_HI /2;
				 a1=abs((p.x*(c2.y-c3.y) + c2.x*(c3.y-p.y)+ c3.x*(p.y-c2.y))/2); // coordinate gemortry  formula from mathopenref.com 
				 a2=abs((c1.x*(p.y-c3.y) + p.x*(c3.y-c1.y)+ c3.x*(c1.y-p.y))/2); // coordinate gemortry  formula from mathopenref.com 
				 a3=abs((c1.x*(c2.y-p.y) + c2.x*(p.y-c1.y)+ p.x*(c1.y-c2.y))/2); // coordinate gemortry  formula from mathopenref.com 
				  if(abs(areat1)==abs(a1+a2+a3))
				 {
					 return false;
				 }

				 
				 c1.x=LeftCorner.x+width; c1.y=LeftCorner.y;
				 c2.x=LeftCorner.x+width-30; c2.y=LeftCorner.y+UI.ASSGN_HI;
				 c3.x=c1.x; c3.y=c2.y;
				  areat1= (c3.x-c2.x)*UI.ASSGN_HI /2;
				 a1=abs((p.x*(c2.y-c3.y) + c2.x*(c3.y-p.y)+ c3.x*(p.y-c2.y))/2); // coordinate gemortry  formula from mathopenref.com 
				 a2=abs((c1.x*(p.y-c3.y) + p.x*(c3.y-c1.y)+ c3.x*(c1.y-p.y))/2); // coordinate gemortry  formula from mathopenref.com 
				 a3=abs((c1.x*(c2.y-p.y) + c2.x*(p.y-c1.y)+ p.x*(c1.y-c2.y))/2); // coordinate gemortry  formula from mathopenref.com

				  if(abs(areat1)==abs(a1+a2+a3))
				 {
					 return false;
				 }

				  return true;





	            }
			return false;
 }

//This function should be called when LHS or RHS changes
void readstat::UpdateStatementText()
{
	//Build the statement text: Left handside then equals then right handside
	ostringstream T;
	T<<"Read"<<"  "<<readtext;	
	Text = T.str();	 
}
int readstat ::getwidth() const
		{
			return width;


		}
bool readstat::playwithvararr(ApplicationManager *ptr,Var **x,int arrsize)
	{
		if(!ptr->isinarr(readtext))
		{
			Var m(readtext,0,true);
			ptr->addtovararr(&m);
			

		}
		return true;

	}
   	 Connector* readstat::runstat(ApplicationManager* ptr,int&c)	//run the statement and returnsthe pout connect for the next stat
	{
		Input* pin=ptr->GetInput();
		Output* pout=ptr->GetOutput();

		string x=pin->GetStringoutput(pout,c);
		if(!IsValue(x))
		{
					
			c=c+20;

			pout->PrintMessageoutput("Running error",c);
								c=c+20;

					pout->PrintMessageoutput("Press anywhere to continue",c);
								return NULL;

		}
		c=c+20;
		double k;
			 k=strtod(&x[0],NULL); // convert the string to double value for example "12.5" will be 12.5

		if(!ptr->isinarr(readtext))
		{
			
			 Var m(readtext,k,true);
			ptr->addtovararr(&m);
			

		}
		else
		{

			ptr->updatevarval(readtext,k);


		}

		return getpoutconnect(0);




	}

void readstat:: setoutconnector(Connector *c,int branch)
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
Statement * readstat::paste(Point dest)
{
	readstat* x = new readstat(dest,readtext);
	return x;
}

Connector* readstat:: getpoutconnect(int branch) const
{
	return pOutConn;



}
void readstat::removepout(Connector *C)
{
	pOutConn=NULL;
	


}

bool readstat:: isconnoutvalid() const
{
	if(pOutConn!=NULL)
	{

		return true;
	}
	return false;


}
void readstat:: setinconnector(Connector *c)
	{
		if(c->getDstStat()==this)
		{

			c->setEndPoint(Inlet);

		}
	


 }
readstat::~readstat()
{

}