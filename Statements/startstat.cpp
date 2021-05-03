#include "startstat.h"
#include <sstream>
#include<fstream>

using namespace std;

startstat::startstat(Point center)
{
	

	width=UI.ASSGN_WDTH;
	centerpoint = center;
	branchno=0;
	pOutConn = NULL;	//No connectors yet

	Outlet.y = centerpoint.y+UI.ASSGN_HI/2;
	Outlet.x= centerpoint.x;	
	inlet.y = centerpoint.y-UI.ASSGN_HI/2;
	inlet.x= centerpoint.x ;	
}
Statement * startstat::ClpbrdHelper(void)
{
	startstat * u = new startstat(centerpoint);
	return u;
}
 void startstat::Edit(Output* pOut,Input * pIn)
	 {
		 pOut->PrintMessage("Start statement cannot be edited !");
	 }
void startstat:: Save(ofstream &OutFile)
{
	if(OutFile.is_open() == true )
		OutFile << "start\t" << ID <<"\t"<< centerpoint.x <<"\t"<< centerpoint.y <<"\t"<<endl;

}


 void startstat:: Load(ifstream &InFile)
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

int startstat ::getwidth() const
		{
			return width;


		}
Connector* startstat:: getpoutconnect(int branch) const
{
	return pOutConn;



}

bool startstat:: isconnoutvalid() const
{
	if(pOutConn!=NULL)
	{

		return true;
	}
	return false;


}
void startstat:: setoutconnector(Connector *c,int branch) // contains  out connector
	{
		if(branch==0&& pOutConn==NULL&&c->getSrcStat()==this)
		{

			c->setStartPoint(Outlet);
						pOutConn=c;

		}

    }
/*	 bool validateastat()//Execute the statement in the simulation mode  // return true when it is valida always return true because we validate this already in design mode
			{
				return true;


			}*/

Statement * startstat::paste(Point dest)
{
	startstat * x = new startstat(dest);
	return x;
}
void startstat::removepout(Connector *C)
{
	pOutConn=NULL;
	


}
  Connector* startstat::runstat(ApplicationManager* ptr,int &c)	//run the statement and returnsthe pout connect for the next stat
	{
		return getpoutconnect(0);


	}


void startstat:: setinconnector(Connector *c)  // start has no in connector but in case of validate simulation as mentioned
	{
		if(c->getDstStat()==this)
		{

			c->setEndPoint(inlet);

		}
	


 }
int startstat:: caniout()  const
{
	if(pOutConn==NULL)
	{
	return 1;

	}

	return 0;
	


}

bool startstat:: is_p_here(Point p) 
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

	 void startstat::UpdateStatementText()
	{
		Text="start";
		return;


	}


void startstat::Draw(Output* pOut) const
{
	//Call Output::DrawAssign function to draw assignment statement 	
	pOut->drawstart(centerpoint,Selected);


}
bool startstat::playwithvararr(ApplicationManager *ptr,Var **x,int arrsize)
	{

		return true;


	}



startstat::~startstat()
{

}