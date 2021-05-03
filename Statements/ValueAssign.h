#ifndef VALUE_ASSIGN_H
#define VALUE_ASSIGN_H

#include "Statement.h"
#include "../Actions/validiate.h"
//Value Assignment statement class
//The value assignment statement assigns a value to a variable
class ValueAssign : public Statement
{
private:
	string LHS;	//Left Handside of the assignment (name of a variable)
	double RHS;	//Right Handside (Value)
	
	Connector *pOutConn;	//Value Assignment Stat. has one Connector to next statement
	                        //Each statement type in flowchart has a predefined number of (output) connectors
	                        //For example, conditional statement always has 2 output connectors

	                        //Note: We don't need to keep track with input connectors
	                        //      Whenever we want to iterate on all statements of the flowchart
	                        //      we will begin with start statement then its output connector
	                        //      then the connector's destination statement and so on (follow the connectors)

	Point Inlet;	//A point where connections enters this statement 
	                //It's used as the (End) point of the (Input) connectors
	Point Outlet;	//A point a connection leaves this statement
	                //It's used as the (Start) point of the (Output) connector

	Point LeftCorner;	//left corenr of the statement block.

	virtual void UpdateStatementText();
	
public:
	ValueAssign(Point Lcorner, string LeftHS="", double RightHS=0);
	void setLHS(const string &L);
	void setRHS(double R);
		virtual bool is_p_here(Point p) ;
		virtual void setoutconnector(Connector *c,int branch);
						virtual void setinconnector(Connector *c);
						  virtual int caniout() const;
						  	virtual Statement * ClpbrdHelper(void); // a function helps in the set of clipboard

	virtual Statement * paste(Point dest)  ;   // a function that paste and make a new object of derived class
virtual bool isconnoutvalid() const;
   virtual Connector* getpoutconnect(int branch) const ;
   virtual void removepout(Connector *C);
   virtual bool playwithvararr(ApplicationManager *ptr,Var **x,int arrsize);
		virtual int getwidth() const;
	virtual void Draw(Output* pOut) const;
		virtual Connector* runstat(ApplicationManager* ptr,int &C);	//run the statement and returnsthe pout connect for the next stat
		virtual void Save(ofstream &OutFile);
						virtual void Load(ifstream &InFile);
								virtual void Edit(Output* pOut,Input * pIn) ;		//Edit the Statement parameter

	virtual ~ValueAssign();

};

#endif