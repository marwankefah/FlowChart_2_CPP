#ifndef APPLICATION_MANAGER_H
#define APPLICATION_MANAGER_H

#include "DEFS.h"

#include "Statements\Statement.h"
class Input;
class Output;


//Main class that manages everything in the application.
class ApplicationManager
{
	enum { MaxCount = 200 };	//Max no of statements/connectors in a single flowchart

private:
	int StatCount;		//Actual number of statements
	int ConnCount;		//Actual number of connectors
	Statement* StatList[MaxCount];	//List of all statements (Array of pointers)
	Connector* ConnList[MaxCount];	//List of all connectors (Array of pointers)

	Statement *pSelectedStat; //a pointer to the last selected statement
	                          //you can set and get this pointer
	Connector * pselectedconnc;
	Statement *pClipboard;    //a pointer to the last copied/cut statement
	                          //you can set and get this pointer

	//Pointers to Input and Output classes
	Input *pIn;
	Output *pOut;
		bool isvalidconn;  // indicated that chart connector is valid made this because in validate must say the type of error
		bool isvalidvar;   // indicated that chart var flow is valid made this because in validate must say the type of error
		bool ischarvalid;  // true when total chart isvalid
		Var* vararr[1000]; // assume max memory for the variable is 1000 for our project
	int vararrcount;    // vararr must be here cause function play with variable bool must pass through all the statement which is here only
public:	
	ApplicationManager(); 
	~ApplicationManager();
	
	// == Actions Related Functions ==
	ActionType GetUserAction() const; //Reads the input command from the user 
	                                  //and returns the corresponding action type
	bool isinarr(string x) const;
	double getvarvalue(string x);
	void updatevarval(string x,double y);
	void ExecuteAction(ActionType) ;  //Creates an action and executes it
	void runflowchart();            // a function that runs the flow chart by passing on the array
	
	int getstartcount() const; // a function that returns the start stat count
	int getendcount() const;   // a function that return the end stat cound
		void condrecursion(Statement *C,int branch); // a function that passes left and passes right
		void addtovararr(Var *m);   // adds a variable to an array
		  		void  vararrdefault() ; // a function that sets all var arr to default which is empty NULL and set statlist all flag to false
						bool getisvalidvar() const;
						bool getisvalidconn() const;
						bool getisvalid();
	// == Statements/Connector Management Functions ==
	void AddStatement(Statement* pStat);    //Adds a new Statement to the Flowchart
	Statement *GetStatement(Point P) const;	//Searches for a statement where point P belongs
	                                        //TODO: Complete its implementation 
	                                        //      WITHOUT breaking class responsibilities
	void validit() ;   // checks that from start to end the number of conn is valid and var is initalized

	Statement * getstartstat() const ; // to get the start stat in the flowchart

	void AddConnector(Connector* pConn);    //Adds a new Connector to the Flowchart
	Connector *GetConnector(Point P) const;	//search for a Connector where point P belongs
	void DeleteConnector(Connector * deadConn);     // a function that deletes a connector and deallocate it
	void DeleteStatement(Statement * deadStat); // a function that deletes a statement and deallocate it

	// Note: you should use the following 4 functions 
	//       in order not to break class responsibilities (especially in copy, cut and paste)
	Statement *GetSelectedStatement() const;	 //Returns the selected Statement
	void SetSelectedStatement(Statement *pStat); //Set the Statement selected by the user
	Connector * getselectedconnector() const;
	void setselectedconnector(Connector *c);

	Statement *GetClipboard() const;	         //Returns the Clipboard
	void SetClipboard(Statement *pStat);         //Set the Clipboard

	void ApplicationManager::ClearForLoad(void);
	void Save(ofstream &OutFile);
	int Load(ifstream &myfile);
	void loadConn(int LDstatCount,ifstream &myfile);
	// == Interface Management Functions ==
	Input *GetInput() const;        //Return pointer to the input
	Output *GetOutput() const;      //Return pointer to the output
	void UpdateInterface() const;	//Redraws all the drawing window
	
};

#endif