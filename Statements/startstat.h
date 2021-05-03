#pragma once
#include "Statement.h"
class startstat :
	public Statement
{
Connector *pOutConn;	//read statement Stat. has one Connector to next statement
	                        
	Point Outlet;	//A point a connection leaves this statement
	                //It's used as the (Start) point of the (Output) connector
	Point inlet;   // no inlet here but in case of validation ask instructor
	Point centerpoint;	//left corenr of the statement block.
		virtual void UpdateStatementText(); // we do not need cause in drawing i got this

	
public:
	startstat(Point center);
	virtual bool startstat:: is_p_here(Point p) ;
	 virtual int getwidth() const;
		virtual void setoutconnector(Connector *c,int branch);
						virtual void setinconnector(Connector *c);
						  virtual int caniout() const;
	virtual Statement * paste(Point dest)  ;   // a function that paste and make a new object of derived class
		//	virtual bool validateastat();	//Execute the statement in the simulation mode
	virtual bool isconnoutvalid() const;
   virtual Connector* getpoutconnect(int branch)const;

		virtual void removepout(Connector *C);
		   virtual bool playwithvararr(ApplicationManager *ptr,Var **x,int arrsize);
	virtual Connector* runstat(ApplicationManager* ptr,int &c);	//run the statement and returnsthe pout connect for the next stat
	virtual void Save(ofstream &OutFile);
						virtual void Load(ifstream &InFile);
								virtual void Edit(Output* pOut,Input * pIn) ;		//Edit the Statement parameter
	virtual Statement * ClpbrdHelper(void); // a function helps in the set of clipboard

	virtual void Draw(Output* pOut) const;
	virtual  ~startstat();
};

