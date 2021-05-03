#include "Connector.h"
#include "Statements\Statement.h"
#include "Statements\condstat.h"
#include <fstream>
Connector::Connector(Statement* Src, Statement* Dst)	
//When a connector is created, it must have a source statement and a destination statement
//There are NO FREE connectors in the flowchart
{
	SrcStat = Src;
	DstStat = Dst;
	Selected=false;
	branch=0;
}

void Connector:: setbranch(int b)
{
	branch=b;


}
void Connector::setSrcStat(Statement *Src)
{	SrcStat = Src;	}

Statement* Connector::getSrcStat()
{	return SrcStat;	}

void Connector::setDstStat(Statement *Dst)
{	DstStat = Dst;	}

Statement* Connector::getDstStat()
{	return DstStat;	}


void Connector::setStartPoint(Point P)

{	Start = P;	}
void Connector::SetSelected(bool s)
{	Selected = s; }

bool Connector::IsSelected() const
{	return Selected; }

Point Connector::getStartPoint()
{	return Start;	}

void Connector::setEndPoint(Point P)
{	End = P;	}

Point Connector::getEndPoint()
{	return End;	}

bool Connector::pfinderhelper(int x, int y,int l,int d,Point c) const   // a function that returns true when point lies on a line
{
	
	double d1 = sqrt(pow((c.x-x),2)+pow(c.y-y,2));
	double d2 = sqrt(pow((c.x-l),2)+pow(c.y-d,2));
	double total = sqrt(pow((l-x),2)+pow(d-y,2));
	if (abs(d1+d2-total)<2) // leave tolerance with 2
		{
			
			
			return true; 
	}
	 return false;
	
}


/* slope check */
bool Connector:: is_p_here(Point c) const   // if the distance betweeen the start and the point added to the distance between the point and the end is equal to the distance from start to end not valid in equilateral so we need to gain aslo the slope
	{


		bool x=false,y=false,z=false,l=false,a1=false,a2=false,ex=false;
		Point first=Start;   // temporary 
		Point end=End;       // temporary
		

		
	if(first.y<end.y)
	{
	if(branch==1)
	{

		x=pfinderhelper(first.x,first.y,first.x-20,first.y,c);
	y=	pfinderhelper(first.x-20,first.y,first.x-20,first.y+UI.ASSGN_HI/2,c);

		
		z=pfinderhelper(first.x-20,first.y+UI.ASSGN_HI/2,end.x,first.y+UI.ASSGN_HI/2,c);
	  l=	pfinderhelper(end.x,first.y+UI.ASSGN_HI/2,end.x,end.y,c);

	  a1=pfinderhelper(end.x,end.y,end.x-7,end.y-7,c); //arrow down
      a2=pfinderhelper(end.x,end.y,end.x+7,end.y-7,c);   // arrow down
	


	}
	if(branch==2)
	{
		
		x=pfinderhelper(first.x,first.y,first.x+20,first.y,c);
		y=pfinderhelper(first.x+20,first.y,first.x+20,first.y+UI.ASSGN_HI/2,c);

		
		l=pfinderhelper(first.x+20,first.y+UI.ASSGN_HI/2,end.x,first.y+UI.ASSGN_HI/2,c);
		z=pfinderhelper(end.x,first.y+UI.ASSGN_HI/2,end.x,end.y,c);

	a1=pfinderhelper(end.x,end.y,end.x-7,end.y-7,c); //arrow down
   a2=pfinderhelper(end.x,end.y,end.x+7,end.y-7,c);   // arrow down
	


	}

	if(branch==0)
	{
			
			x=pfinderhelper(first.x,first.y,first.x,first.y+15,c);
	y=pfinderhelper(first.x,first.y+15,end.x,first.y+15,c);
	l=	pfinderhelper(end.x,first.y+15,end.x,end.y,c);

	a1=pfinderhelper(end.x,end.y,end.x-7,end.y-7,c); //arrow down
    a2=pfinderhelper(end.x,end.y,end.x+7,end.y-7,c);   // arrow down
	


	}


	}



	if(first.y>=end.y)
	{



		if(branch==1)
	{


		if(first.x>=end.x)
		{
			
			x=pfinderhelper(first.x,first.y,end.x-UI.ASSGN_WDTH,first.y,c);       // make long  space for myself left 
			first.x=end.x-UI.ASSGN_WDTH;

		}
		else
		{
				
			x=pfinderhelper(first.x,first.y,first.x-UI.ASSGN_WDTH,first.y,c);       // make  space for myself left
			first.x=first.x-UI.ASSGN_WDTH;
		}

	
	
			y=pfinderhelper(first.x,first.y,first.x,end.y-15,c);
		l=	pfinderhelper(first.x,end.y-15,end.x,end.y-15,c);
		z=	pfinderhelper(end.x,end.y-15,end.x,end.y,c);
		

  a1= pfinderhelper(end.x,end.y,end.x-7,end.y-7,c); //arrow down
  a2= pfinderhelper(end.x,end.y,end.x+7,end.y-7,c);   // arrow down
	


		}

	if(branch==2)
	{
		
		if(first.x<=end.x)
		{
			
			x=pfinderhelper(first.x,first.y,end.x+UI.ASSGN_WDTH,first.y,c);       // make long space for myself right
			first.x=end.x+UI.ASSGN_WDTH;

		}
		else
		{
				
			x=pfinderhelper(first.x,first.y,first.x+UI.ASSGN_WDTH,first.y,c);       // make  space for myself right
			first.x=first.x+UI.ASSGN_WDTH;
		}




		
	
	
		y=pfinderhelper(first.x,first.y,first.x,end.y-15,c);
			z=pfinderhelper(first.x,end.y-15,end.x,end.y-15,c);
			l=pfinderhelper(end.x,end.y-15,end.x,end.y,c);
		

   a1=pfinderhelper(end.x,end.y,end.x-7,end.y-7,c); //arrow down
   a2=pfinderhelper(end.x,end.y,end.x+7,end.y-7,c);   // arrow down
	


		


	}

	if(branch==0)
	{
		
		
		
		
		x=pfinderhelper(first.x,first.y,first.x,first.y+15,c);   // make space for myslef down
		first.y=first.y+15;
		
		
		if(first.x>=end.x)
		{
			
			y=pfinderhelper(first.x,first.y,first.x+UI.ASSGN_WDTH,first.y,c);       // make  space for myself right
			l=pfinderhelper(first.x+UI.ASSGN_WDTH,first.y,first.x+UI.ASSGN_WDTH,end.y-UI.ASSGN_HI,c);   // make space for myslef up

			first.x=first.x+UI.ASSGN_WDTH;
			first.y=end.y-UI.ASSGN_HI;
		}
		else 
		{
				
			
		   y= pfinderhelper(first.x,first.y,first.x-UI.ASSGN_WDTH,first.y,c);       // make  space for myself right
			l=pfinderhelper(first.x-UI.ASSGN_WDTH,first.y,first.x-UI.ASSGN_WDTH,end.y-UI.ASSGN_HI,c);   // make space for myslef up

			first.x=first.x-UI.ASSGN_WDTH;
			first.y=end.y-UI.ASSGN_HI;
		
		}

	z=pfinderhelper(first.x,first.y,end.x,first.y,c);
			a1=pfinderhelper(end.x,first.y,end.x,end.y,c);
		

         	 a2=pfinderhelper(end.x,end.y,end.x-7,end.y-7,c); //arrow down
ex=  pfinderhelper(end.x,end.y,end.x+7,end.y-7,c);   // arrow down
	






	}
	}





	if(x||z||l||y||a1||a2||ex)
	{
		return true;
	}

	return false;
		
	
	}
	void Connector:: save(ofstream &OutFile){

	if(OutFile.is_open() == true ){
		OutFile << getSrcStat()->getid() <<"\t"<< getDstStat()->getid() <<"\t"<< branch<<"\t"<<endl;
	
	
	}

}

void Connector::Draw(Output* pOut) const
{
	///TODO: Call Output to draw a connector from SrcStat to DstStat on the output window
	
	pOut->Drawconnector(Start,End,Selected,branch);
}

