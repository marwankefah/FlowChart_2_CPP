#include "writestat.h"
#include <sstream>
#include<fstream>

using namespace std;

writestat::writestat(Point Lcorner, string RHS)
{
	
	writetext=RHS; 

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
Statement * writestat::ClpbrdHelper(void)
 {
	 writestat * u = new writestat(LeftCorner,writetext);
	 return u;
 }

void writestat:: Save(ofstream &OutFile)
		{
	if(OutFile.is_open() == true )
		OutFile << "WRITE\t" << ID <<"\t"<<LeftCorner.x <<"\t"<< LeftCorner.y <<"\t"<<writetext<<"\t"<<endl;
		}
 void writestat:: Load(ifstream &InFile)
{
	string temp;
	string temp2="/0";

	if(InFile.is_open() == true )
		
	{
		
		InFile >> ID >> LeftCorner.x >> LeftCorner.y ;
		InFile>>temp;
		if(temp[0]=='"')
		{	
			while(temp2[temp2.length()-1]!='"')
			{
			InFile>>temp2;
			temp=temp+" "+temp2;

			}
		
		}	

		writetext=temp;

	}
	Inlet.x = LeftCorner.x + width /2;
	Inlet.y = LeftCorner.y;

	Outlet.x = Inlet.x;
	Outlet.y = LeftCorner.y + UI.ASSGN_HI;	
	UpdateStatementText();
	width=UI.ASSGN_WDTH+returnpixelscount()*2;
}
  void writestat::Edit(Output* pOut,Input * pIn)
 {
	 string tempWriteText;
	 //TODO: Ask the user in the status bar to enter the LHS and set the data member
	pOut->PrintMessage("Please enter the variable or string "   "  u want to write data member");

	tempWriteText=pIn->GetString(pOut);
	if(!IsVariable(tempWriteText))
	{
		while(tempWriteText[0]!='"' || tempWriteText[tempWriteText.length()-1]!='"' || tempWriteText.length()==1)    // one case if he entered only one " 
	{

	pOut->PrintMessage("ERROR !! Please enter a valid variable or string between "   "  u want to write");
		tempWriteText=pIn->GetString(pOut);
		if(IsVariable(tempWriteText))
		{
			break;

		}

	}
	}
		pOut->ClearStatusBar();	


	
	writestat *temp = new writestat(LeftCorner,tempWriteText);


			// check if after the entered length is so large it does not fit in the drawing area
			if ( !(LeftCorner.y >= UI.ToolBarHeight && LeftCorner.y+UI.ASSGN_HI < UI.height - UI.StatusBarHeight && LeftCorner.x+temp->getwidth()/2 <= UI.DrawingAreaWidth&&LeftCorner.x-temp->getwidth()/2>0))
	      {
			pOut->PrintMessage("ERROR OUT of drawing area because statement is so long !!");
			delete temp;
				return;

	       }
			writetext = tempWriteText;
			delete temp;
			UpdateStatementText();
			width=UI.ASSGN_WDTH+returnpixelscount()*2;

 }

void writestat::setwritetext(const string &L)
{
	writetext = L;
	UpdateStatementText();
}



void writestat::Draw(Output* pOut) const
{
	//Call Output::DrawAssign function to draw assignment statement 
	
	
	pOut->drawIOstat(LeftCorner,Text,Selected,width);


}
int writestat:: caniout()  const
{
	if(pOutConn==NULL)
	{
	return 1;

	}

	return 0;
	


}

 bool writestat:: is_p_here(Point p) 
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
				 double areat1= (c2.x-c1.x)*UI.ASSGN_HI /2;
				 a1=abs((p.x*(c2.y-c3.y) + c2.x*(c3.y-p.y)+ c3.x*(p.y-c2.y))/2); // coordinate gemortry  formula from mathopenref.com 
				 a2=abs((c1.x*(p.y-c3.y) + p.x*(c3.y-c1.y)+ c3.x*(c1.y-p.y))/2); // coordinate gemortry  formula from mathopenref.com 
				 a3=abs((c1.x*(c2.y-p.y) + c2.x*(p.y-c1.y)+ p.x*(c1.y-c2.y))/2); // coordinate gemortry  formula from mathopenref.com 
				  if(abs(areat1)==abs(a1+a2+a3))
				 {
					 return false;
				 }

				 /// eliminate the second traiangle
				c1.x=LeftCorner.x+width; c1.y=LeftCorner.y;
				 c2.x=LeftCorner.x+width-30; c2.y=LeftCorner.y+UI.ASSGN_HI;
				 c3.x=c1.x; c3.y=c2.y;

				 areat1= (c3.x-c2.x)*UI.ASSGN_HI /2;
				 a1=abs((p.x*(c2.y-c3.y) + c2.x*(c3.y-p.y)+ c3.x*(p.y-c2.y))/2); // coordinate gemortry  formula from mathopenref.com 
				 a2=abs((p.x*(c1.y-c3.y) + c1.x*(c3.y-p.y)+ c3.x*(p.y-c1.y))/2); // coordinate gemortry  formula from mathopenref.com 
				 a3=abs((p.x*(c2.y-c1.y) + c2.x*(c1.y-p.y)+ c1.x*(p.y-c2.y))/2); // coordinate gemortry  formula from mathopenref.com 
				  if(abs(areat1)==abs(a1+a2+a3))
				 {
					 return false;
				 }

				  return true;





	            }
			return false;
 }

//This function should be called when LHS or RHS changes
void writestat::UpdateStatementText()
{
	//Build the statement text: Left handside then equals then right handside
	ostringstream T;
	T<<"write"<<"  "<<writetext;	
	Text = T.str();	 
}
void writestat:: setoutconnector(Connector *c,int branch)
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
bool writestat:: isconnoutvalid() const
{
	if(pOutConn!=NULL)
	{

		return true;
	}
	return false;


}
bool writestat::playwithvararr(ApplicationManager *ptr,Var **x,int arrsize)
	{

		if(writetext[0]=='"')
		{
			return true;

		}

		if(!ptr->isinarr(writetext))
		{
				Output*pout=ptr->GetOutput();				
				Sleep(1000);

				string text="Write  STATEMENT HAS A PROBLEM  VARIABLE  "+writetext+" is Not initalized";
					pout->PrintMessage(text);
						Sleep(2000);
			return false;


		}


		return true;

	}
 void writestat::removepout(Connector *C)
{
	pOutConn=NULL;
	


}

Connector* writestat:: getpoutconnect(int branch) const
{
	return pOutConn;



}

   	 Connector* writestat::runstat(ApplicationManager* ptr,int &c)	//run the statement and returnsthe pout connect for the next stat
	{
		   Output* pout=ptr->GetOutput();
		   			   string x;

		   if(writetext[0]=='"')
		   {
			   x=writetext;
			   x[writetext.length()-1]=' ';
			   x[0]=' ';

			   pout->PrintMessageoutput(x,c);		

		   }
		   else
		   {
			   string x;
			   double l;
			   l=ptr->getvarvalue(writetext);
			  x=to_string(l);
			   		pout->PrintMessageoutput(x,c);		

		   }

		c=c+20;

		return getpoutconnect(0);



	}

 Statement * writestat::paste(Point dest)
{
	writestat * x = new writestat(dest,writetext);
	return x;
}
void writestat:: setinconnector(Connector *c)
	{
		if(c->getDstStat()==this)
		{

			c->setEndPoint(Inlet);

		}
	


 }
 int writestat ::getwidth() const
		{
			return width;


		}
writestat::~writestat()
{

}