#ifndef OUPTUT_H
#define OUPTUT_H

#include "Input.h"

class Output	//The application manager should have a pointer to this class
{
private:	
	window* pWind;	//Pointer to the Graphics Window
public:
	Output();	

	window* CreateWind(int, int, int , int);
	Input* CreateInput(); //Creates a pointer to the Input object	

	void CreateStatusBar(); //Creates status bar

	//TODO: Complete the following 2 functions
	void CreateDesignToolBar();	//Tool bar of the design mode
	void CreateSimulationToolBar(); //Tool bar of the simulation mode

	void ClearStatusBar();	//Clears the status bar
	void ClearDrawArea();	//Clears the drawing area
	void ClearOutputBar(); //Clears the Output bar
	
	void PrintMessage(string msg);	//Prints a message on Status bar
	void DrawString(const int, const int, const string);  //Writes a string in the specified location
	void  drawlineonwind(Point x,Point y);

	// -- Statements Drawing Functions
	void DrawAssign(Point Left,string Text, bool Selected=false,int width=UI.ASSGN_WDTH, int height=UI.ASSGN_HI);
	void DrawConditionalstat(Point center, string Text, bool Selected ,int width=UI.ASSGN_WDTH, int height=UI.ASSGN_HI);
	void drawIOstat(Point Left ,string Text, bool Selected, int width=UI.ASSGN_WDTH, int height=UI.ASSGN_HI);
	void drawstart(Point Left, bool Selected, int width=UI.ASSGN_WDTH, int height=UI.ASSGN_HI,string text="START");
	void Drawconnector(Point start,Point end, bool Selected,int branch) const;
	void drawEND(Point Left, bool Selected, int width=UI.ASSGN_WDTH, int height=UI.ASSGN_HI,string text="END");
	void clearpartofoutput(int c);	//clear part of the output in order for input to work correctly

	void PrintMessageoutput(string msg,int c);	//Prints a message on output bar
	//TODO: Add similar functions for drawing all other statements.
	//		e.g. DrawCondtionalStat(......), DrawStart(......), DrawEnd(.......), ...etc
	//		Decide the parameters that should be passed to each of them
	
	//TODO: Add DrawConnector function

	~Output();
};

#endif