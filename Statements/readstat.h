#pragma once
#include "Statement.h"
class readstat :
	public Statement
{
	string readtext;   //the thing u need to read
	double variablered;  // the variable input during runtime 
Connector *pOutConn;	//read statement Stat. has one Connector to next statement
	                        
	Point Inlet;	//A point where connections enters this statement 
	                //It's used as the (End) point of the (Input) connectors 
	Point Outlet;	//A point a connection leaves this statement
	                //It's used as the (Start) point of the (Output) connector

	Point LeftCorner;	//left corenr of the statement block.

	virtual void UpdateStatementText();
	
public:
	readstat(Point Lcorner, string r="");
	
	void setreadtext(const string &L);
			virtual bool is_p_here(Point p) ;
					virtual int getwidth() const;
virtual void setoutconnector(Connector *c,int branch);
						virtual void setinconnector(Connector *c);
					  virtual int caniout() const;
	virtual Statement * paste(Point dest)  ;   // a function that paste and make a new object of derived class
virtual bool isconnoutvalid() const;
   virtual Connector* getpoutconnect(int branch)const;
   virtual void removepout(Connector *C);
   virtual bool playwithvararr(ApplicationManager *ptr,Var **x,int arrsize);
   	virtual Connector* runstat(ApplicationManager* ptr,int&c);	//run the statement and returnsthe pout connect for the next stat
	virtual void Save(ofstream &OutFile);
						virtual void Load(ifstream &InFile);
								virtual void Edit(Output* pOut,Input * pIn) ;		//Edit the Statement parameter
	virtual Statement * ClpbrdHelper(void); // a function helps in the set of clipboard

	virtual void Draw(Output* pOut) const;
	virtual  ~readstat();
};
