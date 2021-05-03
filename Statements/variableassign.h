#ifndef variable_assign_H
#define variable_assign_H

#include "Statement.h"

//variable Assignment statement class
//The value assignment statement assigns a variable to a variable
class variableassign : public Statement
{
private:
	string LHS;	//Left Handside of the assignment (name of a variable)
	string RHS;	//Right Handside (variable)
	
	Connector *pOutConn;	//Variable Assignment Stat. has one Connector to next statement
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
	variableassign(Point Lcorner, string LeftHS="", string RightHS="");
	void setLHS(const string &L);
	void setRHS(string R);
		virtual bool is_p_here(Point p) ;
		virtual int getwidth() const;
		virtual void Save(ofstream &OutFile);
						virtual void Load(ifstream &InFile);
virtual void setoutconnector(Connector *c,int branch);
						virtual void setinconnector(Connector *c);
						  virtual int caniout() const;
	virtual Statement * paste(Point dest)  ;   // a function that paste and make a new object of derived class
virtual bool isconnoutvalid() const;
   virtual Connector* getpoutconnect(int branch) const;
   virtual void removepout(Connector *C);
   virtual bool playwithvararr(ApplicationManager *ptr,Var **x,int arrsize);
   	virtual Connector* runstat(ApplicationManager* ptr,int &c);	//run the statement and returnsthe pout connect for the next stat
			virtual void Edit(Output* pOut,Input * pIn) ;		//Edit the Statement parameter
				virtual Statement * ClpbrdHelper(void); // a function helps in the set of clipboard

	virtual void Draw(Output* pOut) const;
	virtual ~variableassign();
};

#endif