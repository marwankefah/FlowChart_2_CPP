#include "endstat.h"
#include <sstream>
#include<fstream>

using namespace std;

endstat::endstat(Point center)
{
	


	centerpoint = center;
	
		width=UI.ASSGN_WDTH;
		pOutconnect = NULL;	//No connectors yet

	Outlet.y = centerpoint.y+UI.ASSGN_HI/2;
	Outlet.x= centerpoint.x;	
	inlet.y = centerpoint.y-UI.ASSGN_HI/2;
	inlet.x= centerpoint.x ;		
}
Statement * endstat::ClpbrdHelper(void)
{
	endstat * u = new endstat(centerpoint);
	return u;
}

	void endstat::Edit(Output* pOut,Input * pIn)
	 {
		 pOut->PrintMessage("End statement cannot be edited !");
	 }


void  endstat::Save(ofstream &OutFile)
{
	if(OutFile.is_open() == true )
		OutFile << "end\t" << ID <<"\t"<< centerpoint.x <<"\t"<< centerpoint.y <<"\t"<<endl;

}
void endstat:: Load(ifstream &InFile)
{
	if(InFile.is_open() == true )
		
	{
		InFile >> ID >> centerpoint.x >> centerpoint.y  ;
	}
	Outlet.y = centerpoint.y+UI.ASSGN_HI/2;
	Outlet.x= centerpoint.x;	
	inlet.y = centerpoint.y-UI.ASSGN_HI/2;
	inlet.x= centerpoint.x ;	
}
bool endstat:: isconnoutvalid() const  //
{
	return true;


}

void endstat::Draw(Output* pOut) const
{
	//Call Output::DrawAssign function to draw assignment statement 	
	pOut->drawEND(centerpoint,Selected);


}
bool endstat::playwithvararr(ApplicationManager *ptr,Var **x,int arrsize)
	{

		return true;



	}
void endstat::removepout(Connector *C)
{
	pOutconnect=NULL;
	


}
Connector* endstat::runstat(ApplicationManager* ptr,int &c)	//run the statement and returnsthe pout connect for the next stat
	{

		 
		Output* pout=ptr->GetOutput();
		pout->PrintMessageoutput("Press any key to continue",c);		
		c=c+20;

		return getpoutconnect(0);

	}

int endstat ::getwidth() const
		{
			return width;


		}
 /*bool validateastat()//Execute the statement in the simulation mode  // return true when it is valida always return true because we validate this already in design mode
			{
				return true;


			}
			*/
void endstat:: setoutconnector(Connector *c,int branch) // contains no out connector
	{
		return ; /// no out connector

    }
Statement * endstat::paste(Point dest)
{
endstat * x =  new endstat(dest);
	return x;
}
void endstat:: setinconnector(Connector *c)
	{
		if(c->getDstStat()==this)
		{

			c->setEndPoint(inlet);

		}
	


 }

Connector* endstat:: getpoutconnect(int branch) const  // always=NULL
{
	return pOutconnect;



}
void endstat::UpdateStatementText()
	{

		Text="end";
		return;


	}

 int endstat:: caniout()  const
{
	

	return 0;
	


}

bool endstat:: is_p_here(Point p) 
{

	double minoraxis,majoraxis;
	minoraxis=UI.ASSGN_HI/2;
	majoraxis=UI.ASSGN_WDTH/2;
	double x=pow(p.x-centerpoint.x,2)/pow(majoraxis,2) + pow(p.y-centerpoint.y,2)/pow(minoraxis,2);
	if(x<1.0)
	{
		return true;


	}
	return false;





	
}

endstat::~endstat()
{

}