#ifndef STATEMENT_H
#define STATEMENT_H
#include "..\defs.h"
#include "..\Connector.h"
//class Output;
class ApplicationManager; //forward class declaration

#include "..\GUI\Output.h"
#include "../Var.h"
#include "../ApplicationManager.h"
//Base class for all Statements
class Statement
{	 
	
	static int begid;  // cannot be exported anywhere else only here
protected:	

	int ID;			//Each Statement has an ID --> must be unique
	int branchno;   // each statement has a branch no 1 for yes 2 for no and 0 for anything else
	string Text;	//Statement text (e.g.  "X = 5" OR "salary > 3000" and so on)
	bool Selected;	//true if the statement is selected on the folwchart
	bool passedflag; // helps in validation
	virtual void UpdateStatementText() = 0;	//is called when any part of the stat. is edited	
	int width;    // width of the stat modified with the text
	/// Add more parameters if needed.
public:
	Statement();
	void SetSelected(bool s);
	bool IsSelected() const;
	virtual bool is_p_here(Point p) =0; // a function that returns true when p(x,y) is here
	int  getbranch() const ;
	virtual void Draw(Output* pOut) const  = 0 ;	//Draw the statement
	int returnpixelscount() const ; // a function that returns the pixels of a text
	virtual int getwidth()const=0 ; // return the width of stat
	virtual void setoutconnector(Connector* c,int branch)=0;   // a function that sets the connector out in case of cond we will check it 
	virtual void setinconnector(Connector *c)=0; // to set the connector with the inlet of a stat
	virtual int  caniout() const=0;   // a function that returns 0 when there is no place to get a connector out and 1 if there is a place to add in any stat if cond 1 if place for yes 2 if place for no and 3 if both are empty
		virtual Statement * paste(Point dest) = 0 ;   // a function that paste and make a new object of derived class
		void setpassedflag(bool x);   // set that u passed on this statement
		bool getpassedflag();   // i passed over it
		virtual void removepout(Connector *C)=0 ; //a function that removes the pout from the stat while deleteing
		virtual bool playwithvararr(ApplicationManager * pmanager ,Var **x,int arrsize)=0 ;  // ptr to application can not be violation cause no other way to add to var statement except like this // a function that plays with the array of variables of the flow chart for valid check
	        int getid();
			void setid(int a);

	virtual void Save(ofstream &OutFile) = 0;	//Save the Statement parameters to a file
	virtual void Load(ifstream &Infile) = 0;	//Load the Statement parameters from a file
	virtual Statement * ClpbrdHelper(void)=0; // a function helps in the set of clipboard

		virtual void Edit(Output* pOut,Input * pIn)=0 ;		//Edit the Statement parameter

	virtual Connector* runstat(ApplicationManager* ptr,int& c)=0;	//run the statement and returnsthe pout connect for the next stat c is the point to shift down

	//[BONUS] virtual void GenerateCode(ofstream &OutFile) = 0;	//write the statement code to a file
		virtual bool isconnoutvalid() const=0; //checks that the pout connect != NULL in case of end it return true when it is NULL ENd pout connect is always null
		virtual Connector* getpoutconnect(int branch) const=0; //depend on the branch
	///TODO: Add more functions if needed

};

#endif