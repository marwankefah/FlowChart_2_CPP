#pragma once
#include "Statement.h"
class condstat: public Statement
{
    string LHS;	//Left Handside of the cond (vale or variable)
	string cond; // the cond in the middle
	string RHS;	//Right Handside (Value or variable)
	
	Connector *pOutConn[2];	//Value Assignment Stat. has one Connector to next statement
	                        //Each statement type in flowchart has a predefined number of (output) connectors
	                        //For example, conditional statement always has 2 output connectors

	                        //Note: We don't need to keep track with input connectors
	                        //      Whenever we want to iterate on all statements of the flowchart
	                        //      we will begin with start statement then its output connector
	                        //      then the connector's destination statement and so on (follow the connectors)

	Point Inlet;	//A point where connections enters this statement 
	                //It's used as the (End) point of the (Input) connectors
	Point Outlet1;	//A point a connection leaves this statement
	Point Outlet2;          //It's used as the (Start) point of the (Output) connector

	Point topcenter;	//top  center  of the cond block.

	virtual void UpdateStatementText();
	
public:
	condstat(Point center, string LeftHS="", string mid="", string RightHS="");
	
	void setLHS(const string &L);   // why is this const &
	void setcond(string mid);
	void setRHS(string R);
virtual bool is_p_here(Point p) ;
	virtual void Draw(Output* pOut) const;
			virtual int getwidth() const;
			virtual void setoutconnector(Connector *c,int branch);
						virtual void setinconnector(Connector *c);
						virtual int  caniout() const;    
	virtual Statement * paste(Point dest)  ;   // a function that paste and make a new object of derived class
virtual bool isconnoutvalid() const;
virtual Connector* getpoutconnect(int branch)const ;
virtual void removepout(Connector *C);
   virtual bool playwithvararr(ApplicationManager *ptr,Var **x,int arrsize);
	virtual Connector* runstat(ApplicationManager* ptr,int &c);	//run the statement and returnsthe pout connect for the next stat
	// make operator overloading for run if there is time
	virtual void Save(ofstream &OutFile);
		virtual void Load(ifstream &InFile);	
		virtual void Edit(Output* pOut,Input * pIn) ;		//Edit the Statement parameter
			virtual Statement * ClpbrdHelper(void); // a function helps in the set of clipboard

	virtual ~condstat();

};

