#include "Statement.h"

int Statement::begid=0;
Statement::Statement()
{ 

	
	//TODO: set the ID with a unique value
	begid++;
	setid(begid);
	Text = "";

	Selected = false;
	passedflag=false;
}
int Statement:: getid(){

return ID;

}
void Statement:: setid(int a){

ID=a;

}
void Statement::setpassedflag(bool x)
{
	passedflag=x;
}
bool Statement:: getpassedflag()
		{
return passedflag;

		}
	int  Statement::  getbranch() const 
	{
		return branchno;

	}


int Statement:: returnpixelscount() const
{
	int c=Text.length();
	for(int i=0; i<Text.length();i++)
	{
		if(Text[i]=='m' || Text[i]=='M'|| Text[i]=='n'|| Text[i]=='N'|| Text[i]=='L'|| Text[i]=='W'|| Text[i]=='w')
		{
			c=c+6;

		}
		else if(Text[i]=='i'||Text[i]=='l')  
		{
			c=c++;
		}
		else
		{
			c=c+4;

		}



	}

	return c;
}

void Statement::SetSelected(bool s)
{	Selected = s; }



bool Statement::IsSelected() const
{	return Selected; }

