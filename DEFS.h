#ifndef DEFS_H
#define DEFS_H

//This file contains some global constants and definitions to be used in the project.

enum  MODE	//Modes of operation
{
	DESIGN,
	SIMULATION
};

// TODO: Add any action type here
enum ActionType // The actions supported
{
	ADD_START, //Add start statement
	ADD_END,   //Add end statement
	ADD_VALUE_ASSIGN, //Add value assignment statement
	ADD_VAR_ASSIGN,	  //Add variable assignment statement
	ADD_OPER_ASSIGN,  //Add operator assignment statement
	ADD_CONDITION,    //Add a conditional statement (for if and while-loop statements)
	ADD_READ,  //Add read statement
	ADD_WRITE, //Addd write statemetn

	ADD_CONNECTOR, //Add a connector between two statements
	
	SELECT,		//Select a statement, a connector
	EDIT_STAT,	//Edit a statement

	DEL,   //Delete a figure
	COPY,  //Copy a figure
	CUT,   //Cut a figure
	PASTE, //Paste a figure
    redo,      // for phase 2 
    undo,
	SAVE,		//Save the whole graph to a file
	LOAD,		//Load a graph from a file

	SWITCH_SIM_MODE,	//Switch to simulatiom mode

	EXIT,		//Exit the application


	//TODO: ADD THE ACTIONS OF SIMULATION MODE
	VALIDATE,  // check if the chart is valid or not
	RUN,      // excuting the flow chart by displaying the final output
	Debug,    // debug step by step in simulation
	Generatecode,   // generate code only if it is valid in phase 2
   SWITCH_DSN_MODE,	//Switch to Design mode
   	SIM_TOOL,	   //A click on an empty place in the sim tool bar


   DRAWING_AREA,  //A click on the drawing area
	OUTPUT_AREA,   //A click on the output area
	DSN_TOOL,	   //A click on an empty place in the design tool bar
	STATUS 		   //A click on the status bar
};

// TODO: you should add more items
enum DesignMenuItem //The items of the design menu --> THE ORDER MATTERS
{
	//Note: Items are ordered here as they appear in menu
	//If you change the menu items order, change the order here too
		//Note: Items are ordered here as they appear in menu
	//If you change the menu items order, change the order here too
	ITM_start,    // start  oval shape	
    ITM_VALUE_ASSIGN,//pressend also when entering a varibale
	ITM_Variable_ASSIGN,//pressend also when entering a varibale
	ITM_arthi,   // action arthimatic (for every action there is an item as specified in the document)
	ITM_COND,		//conditional statement
    ITM_read,    // read and write statement 
	ITM_write,
	ITM_addconnector,  // add connector
	ITM_end, // end oval shape

	ITM_selectorunselect,  // select or unselect statement
	ITM_edit,  // edit a statement
	ITM_delete,	
	ITM_undo,   // to delete the last change happened

	ITM_redo,  // phase 2 bonus redoing the previous when undo is pressed once
    ITM_copy,     
	ITM_cut,
	ITM_paste,
	
	ITM_SWITCH_SIM_MODE,	//Switch to simulatiom mode

	ITM_save,
	ITM_load,
	ITM_EXIT,		//Exit

	
	
	
	
	DSN_ITM_CNT		//no. of design menu items ==> This should be the last line in this enum
};

// TODO: you should add more items if needed
enum SimMenuItem //The items of the simulation menu
{
	//Note: Items are ordered here as they appear in menu
	ITM_VALIDATE,	//Validate
	ITM_RUN,	    //Run
	ITM_debug,   
	ITM_generatecode,
	//TODO:Add more items names here
	   ITM_SWITCH_DSN_MODE,	//Switch to Design mode

	SIM_ITM_CNT		//no. of simulation menu items ==> This should be the last line in this enum
	
};




#ifndef NULL
#define NULL 0
#endif

#endif