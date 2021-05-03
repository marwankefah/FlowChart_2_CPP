
#include "Input.h"
#include "Output.h"
#include <cstring>

Input::Input(window* pW)
{
	pWind = pW; //point to the passed window
}

void Input::GetPointClicked(Point &P) const
{
	pWind->WaitMouseClick(P.x, P.y);	//Wait for mouse click
}
void Input::waitforkeypressed() 
{
	char key;
			pWind->WaitKeyPress(key);
			return;

}

string Input::GetString(Output *pO) const 
{
	string Label;
	char Key;
	while(1)
	{
		pWind->WaitKeyPress(Key);
		if(Key == 27 )	//ESCAPE key is pressed
			return "";	//returns nothing as user has cancelled label
		if(Key == 13 )	//ENTER key is pressed
			return Label;
		if((Key == 8) && (Label.size() >= 1))	//BackSpace is pressed
			Label.resize(Label.size() -1 );			
		else
			Label += Key;
		if (pO)
			pO->PrintMessage(Label);
	}
}

string Input::GetStringoutput(Output *pO,int c) const  // get a string from outputarea
{
	string Label;
	char Key;
	while(1)
	{
		pWind->WaitKeyPress(Key);
		if(Key == 27 )	//ESCAPE key is pressed
			return "";	//returns nothing as user has cancelled label
		if(Key == 13 )	//ENTER key is pressed
			return Label;
		if((Key == 8) && (Label.size() >= 1))	//BackSpace is pressed
			Label.resize(Label.size() -1 );			
		else
			Label += Key;
		if (pO)
		{
			pO->clearpartofoutput(c);
			pO->PrintMessageoutput(Label,c);
		}
	}
}

double Input::GetValue(Output* pO) const	// Reads a double value from the user 
{
	///TODO: add code to read a double value from the user and assign it to D
	string c; 

	double D = 0;
		
	//This function should make any needed validations on the entered text 
	// to make sure it is a double value (e.g. 12.5, -12.5, -23, -23., -23.0 …etc.).

	pO->PrintMessage("Please enter a value:");
	c=GetString(pO);   // read the first double value
	while(!IsValue(c))// check it is not a value to enter again
	{
		pO->PrintMessage("ERROR!! Enter a valid double");

		c=GetString(pO); // read a double value again
	}

	D=strtod(&c[0],NULL); // convert the string to double value for example "12.5" will be 12.5

	
	return D;
}

string Input::Getvariable(Output* pO) const	// Reads a  variable from the user 
{
	string c="\0";  // initalization f the string

		
	//This function should make any needed validations on the entered text 
	pO->PrintMessage("Please enter a variable:");
	   c=GetString(pO); // read from the user 
	  while(!IsVariable(c))  // check if it is not a variable to enter again
	{
		pO->PrintMessage("ERROR!! Enter a valid variable");

		c=GetString(pO); // enter again to check
	}


	
	return  c;  // return the variable as a string
}

string Input::Getarithoperator(Output* pO) const	// Reads an arthimatic operation from the user 
{
	string c="\0"; // initializaing of the string

		
	//This function should make any needed validations on the entered text 
	pO->PrintMessage("Please enter an arthi operation:");
	   c=GetString(pO);  // get the string from the user
	  

	   while(c!="/" && c!="+" &&c!="-" &&c!="*") // if it is not any of the operation accepted  (breaks when an operation is entered)
	 {
		pO->PrintMessage("ERROR!! Enter a valid arthi operation");  // asks the user to enter again for check

		c=GetString(pO);
	 

	 }


	
	return  c;   // operation is sent as a string "*" and can be compared in the next phase as "*"=="*" string compared by string input by user no need for enum
}

string Input::GetCompOperator(Output* pO) const  // read comparison operator from the user
{
	string c="\0"; // initializaion of the sent string

	pO->PrintMessage("Please enter an comp operator:");
	   c=GetString(pO); // get the string from user
	  

	   while(c!=">" && c!="<" &&c!=">=" &&c!="<=" &&c!="==" && c!="!=") // if it is not equal to any valid operator
	 {
		pO->PrintMessage("ERROR!! Enter a valid comp opertator");

		c=GetString(pO); // get another string from the user to check
	
	 }
	   

	return c;  // return the string of the operator as a string why do not we return it as enum??


}

ActionType Input::GetUserAction() const
{	
	//This function reads the position where the user clicks to determine the desired action

	int x,y;
	pWind->WaitMouseClick(x, y);	//Get the coordinates of the user click

	if(UI.AppMode == DESIGN )	//application is in design mode
	{
		//[1] If user clicks on the Toolbar
		if ( y >= 0 && y < UI.ToolBarHeight)
		{	
			//Check whick Menu item was clicked
			//This assumes that menu items are lined up horizontally
			int ClickedItem = (x / UI.MenuItemWidth);
			//Divide x coord of the point clicked by the menu item width (int division)
			//if division result is 0 ==> first item is clicked, if 1 ==> 2nd item and so on
			switch (ClickedItem)
			{

			case ITM_start:  return ADD_START;  // start  oval shape	
			case ITM_VALUE_ASSIGN: return ADD_VALUE_ASSIGN;//pressend also when entering a varibale
			case	ITM_Variable_ASSIGN:  return ADD_VAR_ASSIGN; //pressend also when entering a varibale
			case ITM_arthi:  return ADD_OPER_ASSIGN; // action arthimatic (for every action there is an item as specified in the document)
			case ITM_COND:	return ADD_CONDITION;//conditional statement
			case ITM_read:    return ADD_READ;// read and write statement 
			case ITM_write: return ADD_WRITE;
			case ITM_addconnector: return ADD_CONNECTOR; // add connector
			case ITM_end:  return ADD_END; // end oval shape

			case	ITM_selectorunselect: return SELECT; // select or unselect statement
			case ITM_edit:  return EDIT_STAT;// edit a statement
			case ITM_delete: return DEL;
			case ITM_redo: return redo;// phase 2 bonus redoing the previous when undo is pressed once
			case ITM_undo: return undo; // to delete the last change happened
			case  ITM_copy:   return COPY;
			case ITM_cut:  return CUT;
			case 	ITM_paste: return PASTE;
	
			case ITM_SWITCH_SIM_MODE:	return SWITCH_SIM_MODE;//Switch to simulatiom mode

			case ITM_save: return SAVE;
			case ITM_load:return LOAD;
			case ITM_EXIT:return EXIT; //Exit



			default: return DSN_TOOL;
			}
		}
	
		//[2] User clicks on the drawing area
		if ( y >= UI.ToolBarHeight && y < UI.height - UI.StatusBarHeight)
		{
			if (x <= UI.DrawingAreaWidth)
				return DRAWING_AREA;	
			else
				return OUTPUT_AREA;
		}
		
		//[3] User clicks on the status bar
		return STATUS;
	}
	else	//Application is in Simulation mode
	{
					int ClickedItem = (x / UI.MenuItemWidth);

					switch(ClickedItem)
					{
		case ITM_VALIDATE:	return VALIDATE;//Validate
		case ITM_RUN:	return RUN;    //Run
		case ITM_debug:   return Debug;
		case ITM_generatecode: return Generatecode;
		case ITM_SWITCH_DSN_MODE: return SWITCH_DSN_MODE; //Switch to Design mode	
		case 5: return EXIT;

		default : return SIM_TOOL;
					}
	}

}


Input::~Input()
{
}
