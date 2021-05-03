#include "Output.h"
#include <cstring>

Output::Output()
{
	//Initialize user interface parameters
	UI.width = 1500;
	UI.height = 620;
	UI.wx = 15;
	UI.wy =15;

	UI.AppMode = DESIGN;	//Design Mode is the default mode

	UI.StatusBarHeight = 50;
	UI.ToolBarHeight = 50;
	UI.MenuItemWidth = 60;
	UI.DrawingAreaWidth = 0.75 * UI.width;

	UI.DrawColor = BLUE;
	UI.HighlightColor = RED;
	UI.MsgColor = RED;

	UI.ASSGN_WDTH = 150;
	UI.ASSGN_HI = 50;

	//Create the output window
	pWind = CreateWind(UI.width, UI.height, UI.wx, UI.wy);
	//Change the title
	pWind->ChangeTitle("MOS Programming Techniques Project");
	
	pWind->SetPen(RED,3);
	CreateDesignToolBar();
	CreateStatusBar();
	ClearDrawArea();
	ClearOutputBar();
}


Input* Output::CreateInput()
{
	Input* pIn = new Input(pWind);
	return pIn;
}

//======================================================================================//
//								Interface Functions										//
//======================================================================================//

window* Output::CreateWind(int wd, int h, int x, int y)
{
	return new window(wd, h, x, y);
}
//////////////////////////////////////////////////////////////////////////////////////////
void Output::CreateStatusBar()
{
	pWind->DrawLine(0, UI.height-UI.StatusBarHeight, UI.width, UI.height-UI.StatusBarHeight);
}
//////////////////////////////////////////////////////////////////////////////////////////
//TODO: Complete this function
void Output::CreateDesignToolBar() //Draws the Design Menu
{
	UI.AppMode = DESIGN;	//Design Mode
	
	//fill the tool bar 
		
	//You can draw the tool bar icons in any way you want.
	//Below is one possible way
	
	//First prepare List of images for each menu item
	//To control the order of these images in the menu, 
	//reoder them in Defs.h ==> enum DrawMenuItem
	string MenuItemImages[DSN_ITM_CNT];
	
	MenuItemImages[ITM_start]   ="images\\start.jpg";
		MenuItemImages[ITM_VALUE_ASSIGN] = "images\\value1.jpg";
	MenuItemImages[ITM_Variable_ASSIGN]=  "images\\variable.jpg";
	MenuItemImages[ITM_arthi]= "images\\operation.jpg";
	MenuItemImages[ITM_COND]	= "images\\ITM_COND.jpg";
	MenuItemImages[ITM_read] = "images\\ITM_read.jpg";
	MenuItemImages[ITM_write] = "images\\write.jpg";
	MenuItemImages[ITM_addconnector]= "images\\ITM_addconnector.jpg";
	MenuItemImages[ITM_end] = "images\\ITM_end.jpg";

	MenuItemImages[ITM_selectorunselect]= "images\\ITM_selectorunselect.jpg";
	MenuItemImages[ITM_edit]= "images\\ITM_edit.jpg";
	MenuItemImages[ITM_delete] = "images\\delete.jpg";
	MenuItemImages[ITM_redo] = "images\\ITM_redo.jpg";
	MenuItemImages[ITM_undo]= "images\\ITM_undo.jpg";
  MenuItemImages[ITM_copy] = "images\\copy.jpg";
	MenuItemImages[ITM_cut] = "images\\ITM_cut.jpg";
	MenuItemImages[ITM_paste] = "images\\ITM_paste.jpg";
	
	MenuItemImages[ITM_SWITCH_SIM_MODE]= "images\\ITM_SWITCH_SIM_MODE.jpg";

	MenuItemImages[ITM_save] = "images\\save1.jpg";
	MenuItemImages[ITM_load]= "images\\ITM_load.jpg";
	MenuItemImages[ITM_EXIT] = "images\\ITM_start.jpg";
	
	//TODO: Prepare images for each menu item and add it to the list


	//Draw menu item one image at a time
	for(int i=0; i<DSN_ITM_CNT; i++)
		pWind->DrawImage(MenuItemImages[i], i*UI.MenuItemWidth, 0, UI.MenuItemWidth, UI.ToolBarHeight);

	//Draw a line under the toolbar
	pWind->SetPen(RED, 2);
	pWind->DrawLine(0, UI.ToolBarHeight, UI.width, UI.ToolBarHeight);	

}

void Output:: drawlineonwind(Point x,Point y)  
{

	pWind->DrawLine(x.x, x.y, y.x, y.y);	


}
//////////////////////////////////////////////////////////////////////////////////////////
//TODO: Complete this function
void Output::CreateSimulationToolBar() //Draws the Simulation Menu
{
	UI.AppMode = SIMULATION;	//Simulation Mode
	
		string MenuItemImages[SIM_ITM_CNT];
	MenuItemImages[	ITM_VALIDATE]=	"images\\ITM_VALIDATE.jpg";//Validate
	MenuItemImages[ITM_RUN]  = "images\\ITM_RUN.jpg"; //Run
	MenuItemImages[ITM_debug]   ="images\\ITM_debug.jpg";
	MenuItemImages[ITM_generatecode]="images\\ITM_generatecode.jpg";

	//TODO:Add more items names here
	   MenuItemImages[ITM_SWITCH_DSN_MODE]=	"images\\ITM_SWITCH_DSN_MODE.jpg";//Switch to Design mode
	   //Draw menu item one image at a time
	for(int i=0; i<SIM_ITM_CNT; i++)
	{
		pWind->DrawImage(MenuItemImages[i], i*UI.MenuItemWidth, 0, UI.MenuItemWidth, UI.ToolBarHeight);
    }

	pWind->DrawImage("images\\ITM_start.jpg", SIM_ITM_CNT*UI.MenuItemWidth, 0, UI.MenuItemWidth, UI.ToolBarHeight);  // drawing the exit part

	//Draw a line under the toolbar
	pWind->SetPen(RED, 2);
	pWind->DrawLine(0, UI.ToolBarHeight, UI.width, UI.ToolBarHeight);
		
	
	pWind->SetPen(WHITE, 2);
	pWind->SetBrush(WHITE); // clearing the design menu except the exit
	pWind->DrawRectangle((SIM_ITM_CNT+1)*UI.MenuItemWidth,0,UI.width,UI.ToolBarHeight); // SIm cnt +1 because the exit part is added
	///TODO: add code to create the simulation tool bar
}
//////////////////////////////////////////////////////////////////////////////////////////
void Output::ClearStatusBar()
{
	//Clear Status bar by drawing a filled white rectangle
	pWind->SetPen(RED, 2);
	pWind->SetBrush(WHITE);
	pWind->DrawRectangle(0, UI.height - UI.StatusBarHeight, UI.width, UI.height);
}
//////////////////////////////////////////////////////////////////////////////////////////
void Output::ClearDrawArea()
{
	pWind->SetPen(RED, 2);
	pWind->SetBrush(WHITE);
	pWind->DrawRectangle(0, UI.ToolBarHeight, UI.DrawingAreaWidth, UI.height - UI.StatusBarHeight);
}
//////////////////////////////////////////////////////////////////////////////////////////
void Output::ClearOutputBar()
{
	//Create output bar by drawing a filled rectangle
	pWind->SetPen(RED, 2);
	pWind->SetBrush(BLACK);
	pWind->DrawRectangle(UI.DrawingAreaWidth, UI.ToolBarHeight, UI.width, UI.height - UI.StatusBarHeight);
}
//////////////////////////////////////////////////////////////////////////////////////////
void Output::PrintMessage(string msg)	//Prints a message on status bar
{
	ClearStatusBar();	//First clear the status bar
	
	pWind->SetPen(UI.MsgColor, 50);
	pWind->SetFont(20, BOLD , BY_NAME, "Arial");   
	pWind->DrawString(10, UI.height - (int) (UI.StatusBarHeight/1.5), msg);
}

void Output::clearpartofoutput(int c)	//clear part of the output in order for input to work correctly
{
	
	pWind->SetPen(BLACK, 50);
	pWind->SetFont(20, BOLD , BY_NAME, "Arial");   
	pWind->DrawRectangle(UI.DrawingAreaWidth+5,UI.ToolBarHeight+c,UI.width  ,UI.ToolBarHeight+c+15);
}


void Output::PrintMessageoutput(string msg,int c)	//Prints a message on output bar
{
	pWind->SetPen(WHITE, 50);
	pWind->SetFont(20, BOLD , BY_NAME, "Arial");   
	pWind->DrawString(UI.DrawingAreaWidth+5,UI.ToolBarHeight+c,msg);
}
//////////////////////////////////////////////////////////////////////////////////////////
void Output::DrawString(const int iX, const int iY, const string Text)
{
	pWind->SetPen(BLACK, 2);
	pWind->DrawString(iX, iY, Text);
}
//////////////////////////////////////////////////////////////////////////////////////////

//======================================================================================//
//								Statements Drawing Functions								//
//======================================================================================//

//Draw assignment statement and write the "Text" on it
	void Output:: DrawAssign(Point Left,string Text, bool Selected,int width, int height)
{
	

	if(Selected)	//if stat is selected, it should be highlighted
		pWind->SetPen(UI.HighlightColor,3);	//use highlighting color
	else
		pWind->SetPen(UI.DrawColor,3);	//use normal color

	//Draw the statement block rectangle
	pWind->DrawRectangle(Left.x, Left.y, Left.x + width, Left.y + height);
		
	//Write statement text
	pWind->SetPen(BLACK, 2);
	pWind->DrawString(Left.x+width/5-Text.length(), Left.y + height/4, Text);
}
	void Output:: DrawConditionalstat(Point Left, string Text, bool Selected ,int width, int height)
{

	if(Selected)	//if stat is selected, it should be highlighted
		pWind->SetPen(UI.HighlightColor,3);	//use highlighting color
	else
		pWind->SetPen(UI.DrawColor,3);	//use normal color
	
	int x[4];
	x[0]=Left.x;
	x[1]=Left.x+width/2;
	x[2]=Left.x;
	x[3]=Left.x-width/2;
	int H[4];
	H[0]=Left.y;
	H[1]=Left.y+height/2;
	H[2]=Left.y+height;
	H[3]=Left.y+height/2;
	//Draw the statement block rectangle
	pWind->DrawPolygon(x, H,4 );
		
	//Write statement text
	pWind->SetPen(BLACK, 2);

	pWind->DrawString(Left.x-Text.length()*5-width/40, Left.y + (height+12)/4, Text);
}
	void Output:: drawIOstat(Point Left ,string Text, bool Selected, int width, int height)
{
	if(Selected)	//if stat is selected, it should be highlighted
		pWind->SetPen(UI.HighlightColor,3);	//use highlighting color
	else
		pWind->SetPen(UI.DrawColor,3);	//use normal color
	



	int x[4];
	x[1]=Left.x;
	x[0]=Left.x+width;	
	x[3]=Left.x+width-30;
	x[2]=Left.x-30;

	int y[4];
	y[0]=Left.y;
	y[1]=Left.y;
	y[2]=Left.y+height;
	y[3]=Left.y+height;
	//Draw the statement block rectangle
	pWind->DrawPolygon(x, y,4 );
	
	//Write statement text
	pWind->SetPen(BLACK, 2);
	
	pWind->DrawString(Left.x+width/5-Text.length(), Left.y + height/4, Text);
}


//TODO: Add similar functions for drawing all other statements.
//		e.g. DrawCondtionalStat(......), DrawStart(......), DrawEnd(.......), ...etc
//		Decide the parameters that should be passed to each of them
	void Output:: drawstart(Point Left, bool Selected, int width, int height,string Text)
{
	if(Selected)	//if stat is selected, it should be highlighted
		pWind->SetPen(UI.HighlightColor,3);	//use highlighting color
	else
		pWind->SetPen(UI.DrawColor,3);	//use normal color

	//Draw the statement block rectangle
	pWind->DrawEllipse(Left.x-width/2, Left.y-height/2, Left.x + width/2, Left.y + height/2);
		
	//Write statement text
	pWind->SetPen(BLACK, 2);
	pWind->DrawString(Left.x-width/6, Left.y-height/6, Text);

}
	void Output:: drawEND(Point Left, bool Selected, int width, int height,string text)  //left = center
{

	if(Selected)	//if stat is selected, it should be highlighted
		pWind->SetPen(UI.HighlightColor,3);	//use highlighting color
	else
		pWind->SetPen(UI.DrawColor,3);	//use normal color

	//Draw the statement block rectangle
	pWind->DrawEllipse(Left.x-width/2, Left.y-height/2, Left.x + width/2, Left.y + height/2);
		
	//Write statement text
	pWind->SetPen(BLACK, 2);
	pWind->DrawString(Left.x-width/6, Left.y-height/6, text);
	
}
	
//TODO: Add DrawConnector function

//////////////////////////////////////////////////////////////////////////////////////////
void Output::Drawconnector(Point first,Point end, bool Selected,int branch) const
{
	
	if(Selected)	//if stat is selected, it should be highlighted
		{
			pWind->SetPen(UI.HighlightColor,3);	//use highlighting color
	     }
     	else
		{
	
	pWind->SetPen(UI.DrawColor,3);	//use normal color
	}


	if(first.y<end.y)
	{
	if(branch==1)
	{
		
		pWind->DrawLine(first.x,first.y,first.x-20,first.y);
			pWind->DrawString(first.x-30,first.y-20,"YES");

		pWind->DrawLine(first.x-20,first.y,first.x-20,first.y+UI.ASSGN_HI/2);

		
		pWind->DrawLine(first.x-20,first.y+UI.ASSGN_HI/2,end.x,first.y+UI.ASSGN_HI/2);
		pWind->DrawLine(end.x,first.y+UI.ASSGN_HI/2,end.x,end.y);

	pWind->DrawLine(end.x,end.y,end.x-7,end.y-7); //arrow down
pWind->DrawLine(end.x,end.y,end.x+7,end.y-7);   // arrow down
	


	}
	if(branch==2)
	{
		
		pWind->DrawLine(first.x,first.y,first.x+20,first.y);
					pWind->DrawString(first.x+30,first.y-20,"NO");

		pWind->DrawLine(first.x+20,first.y,first.x+20,first.y+UI.ASSGN_HI/2);

		
		pWind->DrawLine(first.x+20,first.y+UI.ASSGN_HI/2,end.x,first.y+UI.ASSGN_HI/2);
		pWind->DrawLine(end.x,first.y+UI.ASSGN_HI/2,end.x,end.y);

	pWind->DrawLine(end.x,end.y,end.x-7,end.y-7); //arrow down
   pWind->DrawLine(end.x,end.y,end.x+7,end.y-7);   // arrow down
	


	}

	if(branch==0)
	{
			
			pWind->DrawLine(first.x,first.y,first.x,first.y+15);
	pWind->DrawLine(first.x,first.y+15,end.x,first.y+15);
		pWind->DrawLine(end.x,first.y+15,end.x,end.y);

	pWind->DrawLine(end.x,end.y,end.x-7,end.y-7); //arrow down
pWind->DrawLine(end.x,end.y,end.x+7,end.y-7);   // arrow down
	


	}


	}



	if(first.y>=end.y)
	{



		if(branch==1)
	{


		if(first.x>=end.x)
		{
			
			pWind->DrawLine(first.x,first.y,end.x-UI.ASSGN_WDTH,first.y);// make long  space for myself left 
			pWind->DrawString(first.x-30,first.y-20,"YES");
			first.x=end.x-UI.ASSGN_WDTH;

		}
		else
		{
				
			pWind->DrawLine(first.x,first.y,first.x-UI.ASSGN_WDTH,first.y);       // make  space for myself left
			pWind->DrawString(first.x-30,first.y-20,"YES");

			first.x=first.x-UI.ASSGN_WDTH;
		}

	
	
			pWind->DrawLine(first.x,first.y,first.x,end.y-15);
			pWind->DrawLine(first.x,end.y-15,end.x,end.y-15);
			pWind->DrawLine(end.x,end.y-15,end.x,end.y);
		

   pWind->DrawLine(end.x,end.y,end.x-7,end.y-7); //arrow down
   pWind->DrawLine(end.x,end.y,end.x+7,end.y-7);   // arrow down
	


		}

	if(branch==2)
	{
		
		if(first.x<=end.x)
		{
			
			pWind->DrawLine(first.x,first.y,end.x+UI.ASSGN_WDTH,first.y);       // make long space for myself right
			pWind->DrawString(first.x+30,first.y-20,"NO");

			first.x=end.x+UI.ASSGN_WDTH;

		}
		else
		{

			pWind->DrawLine(first.x,first.y,first.x+UI.ASSGN_WDTH,first.y);       // make  space for myself right
						pWind->DrawString(first.x+30,first.y-20,"NO");

						first.x=first.x+UI.ASSGN_WDTH;
		}




		
	
	
			pWind->DrawLine(first.x,first.y,first.x,end.y-15);
			pWind->DrawLine(first.x,end.y-15,end.x,end.y-15);
			pWind->DrawLine(end.x,end.y-15,end.x,end.y);
		

   pWind->DrawLine(end.x,end.y,end.x-7,end.y-7); //arrow down
   pWind->DrawLine(end.x,end.y,end.x+7,end.y-7);   // arrow down
	


		


	}

	if(branch==0)
	{
		
		
		
		
		pWind->DrawLine(first.x,first.y,first.x,first.y+15);   // make space for myslef down
		first.y=first.y+15;
		
		
		if(first.x>=end.x)
		{
			
			pWind->DrawLine(first.x,first.y,first.x+UI.ASSGN_WDTH,first.y);       // make  space for myself right
			pWind->DrawLine(first.x+UI.ASSGN_WDTH,first.y,first.x+UI.ASSGN_WDTH,end.y-UI.ASSGN_HI);   // make space for myslef up

			first.x=first.x+UI.ASSGN_WDTH;
			first.y=end.y-UI.ASSGN_HI;
		}
		else 
		{
				
			
		    pWind->DrawLine(first.x,first.y,first.x-UI.ASSGN_WDTH,first.y);       // make  space for myself right
			pWind->DrawLine(first.x-UI.ASSGN_WDTH,first.y,first.x-UI.ASSGN_WDTH,end.y-UI.ASSGN_HI);   // make space for myslef up

			first.x=first.x-UI.ASSGN_WDTH;
			first.y=end.y-UI.ASSGN_HI;
		
		}

		pWind->DrawLine(first.x,first.y,end.x,first.y);
			pWind->DrawLine(end.x,first.y,end.x,end.y);
		

         	 pWind->DrawLine(end.x,end.y,end.x-7,end.y-7); //arrow down
   pWind->DrawLine(end.x,end.y,end.x+7,end.y-7);   // arrow down
	






	}

	/*

            pWind->DrawLine(end.x, end.y, end.x +7, end.y -7); // arrow left
	        pWind->DrawLine(end.x, end.y, end.x+7 , end.y+7);   // arrow left

			pWind->DrawLine(end.x, end.y, end.x -7, end.y -7); // arrow right
	        pWind->DrawLine(end.x, end.y, end.x-7 , end.y+7);   // arrow right

*/

		

	} // end of connector up





		if(Selected)	//if stat is selected, it should be highlighted
	{
		pWind->SetPen(UI.HighlightColor,2);	//use highlighting color
	}
	else
	{
		pWind->SetPen(UI.DrawColor,2);	//use normal color
	}
	pWind->SetPen(UI.DrawColor) ; // set it again to default
	
}

Output::~Output()
{
	delete pWind;
}
