#pragma once
#include "Statement.h"
class endstat :
	public Statement
{	
	
	
	Connector *pOutconnect; //  here the pout connect is always equal NULL
	Point Outlet;    /// contains no outler or pout connect
	Point inlet;	//A point a connection leaves this statement
	                //It's used as the (end) point of the (Output) connector

	Point centerpoint;	//left corenr of the statement block.

	virtual void UpdateStatementText(); // we do not need cause in drawing i got this
public:
	endstat(Point center);
	virtual bool is_p_here(Point p) ;
 			virtual int getwidth() const;
  virtual void setoutconnector(Connector *c,int branch);
  virtual void setinconnector(Connector *c);
  virtual int caniout() const;
	virtual void Draw(Output* pOut) const;
		virtual Statement * paste(Point dest)  ;   // a function that paste and make a new object of derived class
 //virtual bool validateastat();//Execute the statement in the simulation mode  // return true when it is valida always return true because we validate this already in design mode
		virtual bool isconnoutvalid() const;  // return true always
virtual Connector* getpoutconnect(int branch)const;
virtual void removepout(Connector *C);
   virtual bool playwithvararr(ApplicationManager *ptr,Var **x,int arrsize);
   	virtual Connector* runstat(ApplicationManager* ptr,int &c);	//run the statement and returnsthe pout connect for the next stat

	virtual void Save(ofstream &OutFile);
						virtual void Load(ifstream &InFile);
								virtual void Edit(Output* pOut,Input * pIn) ;		//Edit the Statement parameter
	virtual Statement * ClpbrdHelper(void); // a function helps in the set of clipboard

	virtual  ~endstat();
};

