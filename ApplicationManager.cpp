#include "ApplicationManager.h"
#include "Actions\AddValueAssign.h"
#include "Actions\addvariableassign.h"
#include "Actions\addoperatorassign.h"
#include "Statements\condstat.h"
#include "GUI\Input.h"
#include "GUI\Output.h"
#include "Actions\addcondstat.h"
#include "Actions\addreadstat.h"
#include "Actions\addwritestat.h"
#include "Actions\addstart.h"
#include "Actions\addend.h"
#include "Statements\condstat.h"
#include "Statements\startstat.h"
#include "Statements\endstat.h"
#include "Statements\writestat.h"
#include "Statements\readstat.h"
#include "Statements\variableassign.h"
#include "Statements\operatorassign.h"
#include "Statements\ValueAssign.h"
#include "Actions\addconnector.h"
#include "Actions\selectaction.h"
#include "Actions\switchtosimmode.h"
#include "Actions\switchtodsnmode.h"
#include "Actions\deleter.h"
#include "Actions\copystatement.h"
#include "Actions\cutstatement.h"
#include "Actions\Paste.h"
#include "Actions\validiate.h"
#include "Actions\runaction.h"
#include "Actions\ActionSave.h"
#include "Actions\Edit.h"
#include<fstream>
#include "Actions\LoadAction.h"
//Constructor
ApplicationManager::ApplicationManager()
{
	//Create Input and output
	pOut = new Output;
	pIn = pOut->CreateInput();
	
	StatCount = 0;
	ConnCount = 0;
	pSelectedStat = NULL;	//no Statement is selected yet
	pClipboard = NULL;
	pselectedconnc=NULL;
	//Create an array of Statement pointers and set them to NULL		
	for(int i=0; i<MaxCount; i++)
	{
		StatList[i] = NULL;	
		ConnList[i] = NULL;
	}
	ischarvalid=false;
	isvalidvar=true;
	isvalidconn=true;
	vararrcount=0;
}


//==================================================================================//
//								Actions Related Functions							//
//==================================================================================//


ActionType ApplicationManager::GetUserAction() const
{
	//Ask the input to get the action from the user.
	return pIn->GetUserAction();		
}
////////////////////////////////////////////////////////////////////////////////////
//Creates an action and executes it
void ApplicationManager::ExecuteAction(ActionType ActType) 
{
	Action* pAct = NULL;
	
	//According to ActioType, create the corresponding action object
	switch (ActType)
	{
	case ADD_START:

		pAct=new addstart(this);
		break;

		case ADD_END:

		pAct=new addend(this);
		break;


		case ADD_VALUE_ASSIGN:
			pAct = new AddValueAssign(this);
			break;
			
		case ADD_VAR_ASSIGN:
			pAct=new addvariableassign(this);
				break;


		case ADD_OPER_ASSIGN:
			pAct=new addoperatorassign (this);
				break;

		case ADD_CONDITION:
			
			///create AddCondition Action here
			pAct=new addcondstat(this);
			break;

		case ADD_READ :
			
			pAct=new addreadstat(this);
			break;
			
			case ADD_WRITE :
			
				pAct=new addwritestat(this);
			break;

			case ADD_CONNECTOR:

				pAct= new addconnector(this);
				break;

		case SELECT:
			///create Select Action here
			pAct= new selectaction(this);
				break;
			
		case SWITCH_SIM_MODE:
			pAct= new switchtosimmode(this);

			break;


		case VALIDATE:
			pAct= new validiate(this);

			break;

		case SWITCH_DSN_MODE:
			pAct= new switchtodsnmode(this);

			break;
			case DEL:
			pAct = new deleter(this);
			
			break;		
		case COPY:
			pAct = new copystatement(this);
			
			break;	
		case CUT:
			pAct = new cutstatement(this);
			
			break;
		case PASTE:
			pAct = new Paste(this);

			break;

			case RUN:
				pAct = new runaction(this);

			break;

			case SAVE:
				pAct = new ActionSave(this);

			break;
			
		case EDIT_STAT:
				pAct = new Edit(this);

			break;
		case LOAD:
				pAct=new LoadAction(this);
				break;

		case EXIT:
			///create Exit Action here  // not specified in the document except cleanups no save and exit specified
			ClearForLoad();   // a function that clears everything same as loading a file 
			break;

		
		
		case STATUS:
			return;
	}
	
	//Execute the created action
	if(pAct != NULL)
	{
		pAct->Execute();//Execute
	

		delete pAct;	//Action is not needed any more ==> delete it
	}
}





Statement * ApplicationManager:: getstartstat() const  // to get the start stat in the flowchart but first we check the count of start
{

	startstat* c=NULL;
	if(getstartcount()!=1)
	{
		return NULL;

	}
		for(int i=0;i<StatCount;i++)
		{
			
			
			c=dynamic_cast<startstat*>(StatList[i]);
			if(c)
			{
				return StatList[i];

			}


		}
		return c;



}
bool ApplicationManager:: isinarr(string x) const
{
	for(int i=0;i<vararrcount;i++)
	{

		if(vararr[i]->getname()==x)
		{

			return true;

		}

	}
		return false;


}
	void ApplicationManager::runflowchart()           // a function that runs the flow chart by passing on the array
	{
		if(!ischarvalid)
		{
			return ;

		}

		Statement* temp=getstartstat();
		Connector *tempconn;
		int c=0;
		while(temp!=NULL)
		{

		tempconn=temp->runstat(this,c);
		if(tempconn==NULL)
		{
			GetOutput()->PrintMessage(" Running finished check the output area and press anykey to cont");
        GetInput()->waitforkeypressed();
		GetOutput()->ClearOutputBar();
		GetOutput()->ClearStatusBar();
			return;
		}

		temp=tempconn->getDstStat();
		}



		




	}



void ApplicationManager::Save(ofstream &OutFile)
{
	OutFile << StatCount<<"\t"<<endl;
	for (int i = 0;i < StatCount ; i++)
	{
		StatList[i]->Save(OutFile);
	}
	OutFile << ConnCount<<"\t"<<endl;
	for (int i = 0;i < ConnCount ; i++)
	{
		ConnList[i]->save(OutFile);
	}
}
int ApplicationManager::Load(ifstream &myfile)
{
	Point p;
	p.x=0;
	p.y=0;
	int x ;
	myfile>>x;
	
	for (int i = 0;i < x;i++)
	{
		string y;
		myfile>>y;
		if (y == "start")
		{
			startstat * u=new startstat(p);
			u->Load(myfile);
			AddStatement(u);
		}
		else if(y == "end")
		{
			endstat * u=new endstat(p);
			u->Load(myfile);
			AddStatement(u);
		}
		else if(y =="COND")
		{
			Statement * u=new condstat(p);
		u->Load(myfile);

		AddStatement(u);
		}
		else if(y == "VAL")
		{
		ValueAssign * u=new ValueAssign(p,"",0.0);
		u->Load(myfile);
		AddStatement(u);
		}
		else if(y=="VAR")
		{
			variableassign * u=new variableassign(p,"","");
		u->Load(myfile);
		AddStatement(u);
		}
		else if(y=="WRITE")
		{
		writestat * u=new writestat(p,"");
		u->Load(myfile);
		AddStatement(u);
		}
		else if (y=="READ")
		{
			readstat * u=new readstat(p,"");
			u->Load(myfile);
			AddStatement(u);
		}
		else if (y=="OP_ASSIGN")
		{
			operatorassign * u=new operatorassign(p,"","","","");
			u->Load(myfile);
			AddStatement(u);
		}
		else
		pOut->PrintMessage("Eh el hzardh matgeebo file 3edel");
	}
	return x;
}

void ApplicationManager::loadConn(int LDstatCount,ifstream &myfile)
{
int LDconnCount;	
myfile.ignore(LDstatCount+1,'\n');
myfile>>LDconnCount;
for (int i = 0;i < LDconnCount;i++)
{
	int srcID,dstID,branch;
	Connector * u = new Connector(NULL,NULL);
	myfile>>srcID;
	myfile>>dstID;
	myfile>>branch;
	for (int j = 0 ;j < LDstatCount;j++)
	{
		if(StatList[j]->getid() == srcID)
		{
			u->setSrcStat(StatList[j]);
			StatList[j]->setoutconnector(u,branch);

		}
		if(StatList[j]->getid() == dstID)
		{
			u->setDstStat(StatList[j]);
			StatList[j]->setinconnector(u);

		}
		u->setbranch(branch);
	}
	AddConnector(u);


}
}

void ApplicationManager::ClearForLoad(void)
{
	int x=StatCount;
	int y=ConnCount;
	for(int i=0;i<vararrcount;i++)
	{
		if(vararr[i]!=NULL)
		{
		delete vararr[i];
		vararr[i]=NULL;
		vararrcount--;
		}
	}

	for(int i=0; i<x; i++)
	{
		if(StatList[i]!=NULL)
		{
		delete StatList[i];
		StatList[i]=NULL;
		StatCount--;
		}
		
	}
	for(int i=0; i<y; i++)
	{
		if(ConnList[i]!=NULL)
		{
		delete ConnList[i];
		ConnList[i]=NULL;
		ConnCount--;
		}
	}
}

/* void ApplicationManager::loadConn(int LDstatCount,ifstream&myfile)
{
	






myfile.ignore((1000(LDstatCount)+1), '\n');
myfile>>LDconnCount;
for (int i = 0;i > LDconnCount;i++)
{
	int srcID,dstID,branch;
	Connector * u = new Connector(NULL,NULL);
	myfile>>srcID;
	myfile>>dstID;
	myfile>>branch;
	for (int j = 0 ;j > LDstatCount)
	{
		if(StatList[j]->getID == srcID)
		{
			u->setsrcstat(StatList[j]);
		}
		if(StatList[j]->getID == dstID)
		{
			u->setdststat(StatList[j]);
		}
		u->branch = branch;
		//addconnector(u);
	}

}

*/



int ApplicationManager:: getstartcount() const // a function that returns the start stat count
{
     	startstat* c=NULL;
		int count=0;
		for(int i=0;i<StatCount;i++)
		{
			
			
			c=dynamic_cast<startstat*>(StatList[i]);
			if(c)
			{

				  count++;


			}


		}

		return count;
}
	int ApplicationManager:: getendcount() const // a function that return the end stat count
	{
		endstat* c=NULL;
		int count=0;
		for(int i=0;i<StatCount;i++)
		{
			
			
			c=dynamic_cast<endstat*>(StatList[i]);
			if(c)
			{

				  count++;


			}


		}

		return count;

	}
	void ApplicationManager:: addtovararr(Var *m)
	{
		vararr[vararrcount]=new Var(m->getname(),m->getvalue(),m->getinitalized());
		vararrcount++;
	}
	bool ApplicationManager::getisvalidvar() const
	{
		return isvalidvar;


	}
		bool ApplicationManager:: getisvalidconn() const
						{
							return isvalidconn;

						}
			double ApplicationManager ::getvarvalue(string x) // we make sure that this function is used with something in the array
			{
				for(int i=0;i<vararrcount;i++)
				{
					if(vararr[i]->getname()==x)
					{

						return vararr[i]->getvalue();

					}


				}
				

			}

				void ApplicationManager::updatevarval(string x,double y)
				{
	
					for(int i=0;i<vararrcount;i++)

		      {
					if(vararr[i]->getname()==x)
					{
						vararr[i]->setvalue(y);
						return;
					}
				}



					return;
				}

	void ApplicationManager:: condrecursion(Statement *C,int branch) // a function that passes left and passes right
	{


	     Statement* temp;
		if(C->getpoutconnect(branch)==NULL )  //end is reached
		{

			return;

		}
				temp=C->getpoutconnect(branch)->getDstStat();
			bool	y=temp->playwithvararr(this,vararr,vararrcount);  // returns true when var flow correct each statement

				if(!y)

				{
					isvalidvar=false;
					return ;
				}


				
			
		condstat *anotherrec=dynamic_cast<condstat*>(temp);
		if(anotherrec&&temp->getpassedflag()==false)
			{
				temp->setpassedflag(true);
				condrecursion(temp,1);
				condrecursion(temp,2);

			}
		else if(!anotherrec && temp->getpassedflag()==false)
		{

			branch=0;

		}

      if( temp->getpassedflag()==true)  //a loop is detected we must return we passed here before
		{

			return;

		}
		temp->setpassedflag(true);

		
		
	

		
	

		


		condrecursion(temp,branch);

	}

	void ApplicationManager:: validit()   // sets each bool which is the type error but connectors is the priotity 
		{
        if(getstartcount()!=1|| getendcount()!=1)
	     {
			 isvalidconn=false;
	           	return ;

         }

			for(int i=0;i<StatCount;i++)
			{
				if(StatList[i]->isconnoutvalid()==false)  //thenumberofconnectors out of a statement if is there only one stat without pout connect return false
				{
						isvalidconn=false;
			return ;
				}
			}


			Statement *temp =getstartstat();
			bool x=false;
			x=temp->playwithvararr(this,vararr,vararrcount);  // returns true cause it is a start




			temp->getpoutconnect(0)->getSrcStat()->setpassedflag(true);
			while(getstartstat()->getpoutconnect(0)!=NULL)   // do not enter if only start statement in the sheet
			{
							
				
				temp=temp->getpoutconnect(0)->getDstStat();
				x=temp->playwithvararr(this,vararr,vararrcount);  // returns true cause it is a start
				
				if(!x)

				{
					isvalidvar=false;
					return ;
				}


				condstat *conditional=dynamic_cast<condstat*>(temp);
				endstat *lastend=dynamic_cast<endstat*>(temp);
				
				if(lastend)
				{
		          	temp->setpassedflag(true);
					break;


				}
				
					if(conditional)
					{
					
						temp->setpassedflag(true);

						condrecursion(conditional,1);
						condrecursion(conditional,2);
						break;

					}
					else
					{

						temp->setpassedflag(true);

					}
		

			}




			for(int i=0;i<StatCount;i++)
	{
		if(!(StatList[i]->getpassedflag()))
		{

			isvalidconn=false;
			return ;

		}

	}

			isvalidconn=true;
			isvalidvar=true;
			ischarvalid=true;
			return ;




		}

		bool ApplicationManager::getisvalid() 
		{
	
			if(isvalidconn &&isvalidvar)
			{
			return true;
			}
			return false;
		}
		
		void ApplicationManager:: vararrdefault()  // a function that sets all var arr  and stat conn passed flag to falseto default which is empty NULL
		{
			for(int i=0;i<vararrcount;i++)
	           {
		  if(vararr[i]!=NULL)
		{
		vararr[i]=NULL;
		}
	              }


			for(int i=0;i<StatCount;i++)
			{

				StatList[i]->setpassedflag(false);

			}


			vararrcount=0;
		}


//==================================================================================//
//						Statements Management Functions								//
//==================================================================================//


//Add a statement to the list of statements
void ApplicationManager::AddStatement(Statement *pStat)
{
	if(StatCount < MaxCount)
		StatList[StatCount++] = pStat;
	
}
void ApplicationManager::AddConnector(Connector *pStat)
{
	if(ConnCount < MaxCount)
		ConnList[ConnCount++] = pStat;
	
}

//Deleters
void ApplicationManager::DeleteConnector(Connector * deadConn)
{
	for (int i= 0;i < ConnCount ;i++)
	{
		if (deadConn == ConnList[i])
		{			


			ConnList[i] = ConnList[ConnCount-1];
			deadConn->getSrcStat()->removepout(deadConn);   // to remove the pout from src to  eliminate error that might occur
				deadConn=NULL;
			ConnList[ConnCount-1]=NULL; 
			
			ConnCount--;

		}

	}
}

void ApplicationManager::DeleteStatement(Statement * deadStat)
{
	for (int i= 0;i < StatCount ;i++)
	{
		if (deadStat == StatList[i])
		{	
			int x=ConnCount;
			int j=0;
			while(j<ConnCount)
			{
				if(ConnList[j]!=NULL)  // not empty list
				{
					

				if ((ConnList[j]->getDstStat() == deadStat) || (ConnList[j]->getSrcStat() == deadStat))
				{

					DeleteConnector(ConnList[j]);

		             x=ConnCount;
			        j=0;
	             }
				else
				{

                            j++;
				}
			     
				}


			}

			deadStat=NULL;
			
			StatList[i] = StatList[StatCount-1];
			StatList[StatCount-1]=NULL; 

			
			
			StatCount--;


		}

	}
}


////////////////////////////////////////////////////////////////////////////////////
Statement *ApplicationManager::GetStatement(Point P) const
{
	//If this point P(x,y) belongs to a statement return a pointer to it.
	//otherwise, return NULL
	for(int i=0;i<StatCount;i++)
	{
		if(StatList[i]->is_p_here(P))
		{

			return StatList[i];

		}

	}
	return NULL;
}
	Connector *ApplicationManager::GetConnector(Point P) const
{
	//If this point P(x,y) belongs to a connector return a pointer to it.
	//otherwise, return NULL
	for(int i=0;i<ConnCount;i++)
	{
		if(ConnList[i]->is_p_here(P))
		{

			return ConnList[i];

		}

	}

	///Add your code here to search for a statement given a point P(x,y)	
	///WITHOUT breaking class responsibilities

	return NULL;
}
////////////////////////////////////////////////////////////////////////////////////
//Returns the selected statement
Statement *ApplicationManager::GetSelectedStatement() const
{	return pSelectedStat;	}

////////////////////////////////////////////////////////////////////////////////////
//Set the statement selected by the user
void ApplicationManager::SetSelectedStatement(Statement *pStat)
{	pSelectedStat = pStat;	}
////////////////////////////////////////////////////////////////////////////////////
//Returns the selected connector
Connector *ApplicationManager::getselectedconnector() const
{	return pselectedconnc;	}

////////////////////////////////////////////////////////////////////////////////////
//Set the connector selected by the user
void ApplicationManager::setselectedconnector(Connector *pStat)
{	pselectedconnc = pStat;	}
////////////////////////////////////////////////////////////////////////////////////
//Returns the Clipboard
Statement *ApplicationManager::GetClipboard() const
{	return pClipboard;	}

////////////////////////////////////////////////////////////////////////////////////
//Set the Clipboard
void ApplicationManager::SetClipboard(Statement *pStat)

{	
	pClipboard=pStat;

}


//==================================================================================//
//							Interface Management Functions							//
//==================================================================================//





//Draw all figures on the user interface
void ApplicationManager::UpdateInterface() const
{
	
	pOut->ClearDrawArea();
	//Draw all statements
	for(int i=0; i<StatCount; i++)
		StatList[i]->Draw(pOut);
	
	//Draw all connections
	for(int i=0; i<ConnCount; i++)
		ConnList[i]->Draw(pOut);

	Sleep(500);
	pOut->ClearStatusBar();
	pOut->ClearOutputBar();

}
////////////////////////////////////////////////////////////////////////////////////
//Return a pointer to the input
Input *ApplicationManager::GetInput() const
{	return pIn; }
//Return a pointer to the output
Output *ApplicationManager::GetOutput() const
{	return pOut; }
////////////////////////////////////////////////////////////////////////////////////


//Destructor
ApplicationManager::~ApplicationManager()
{
	
	for(int i=0;i<vararrcount;i++)
	{
		if(vararr[i]!=NULL)
		{
		delete vararr[i];
		vararr[i]=NULL;
		}
	}

	for(int i=0; i<StatCount; i++)
		delete StatList[i];
	for(int i=0; i<StatCount; i++)
		delete ConnList[i];
	delete pIn;
	delete pOut;
	
	
}
