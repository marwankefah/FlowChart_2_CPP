#include "Var.h"


Var::Var()
{
	setname("-1");
	setinialized(false);
	setvalue("no");

}

Var:: Var(string x,double l,bool y)    // as we said before you can not enter char cause in page 3 it is specified rather than this 
{

	setname(x);
	setinialized(y);
    value=l;

}

void Var::setname(string n)
{
	x=n;
	

}
	void Var::setinialized(bool x)
	{

		isinitialized=x;
	}
	void Var::setvalue(string x)   // the value i ask the respond was after many times and for this in project description it is indicated in page 3 that read x read value user so we can not make a string or char from a variable only value double
	{
			value=strtod(&x[0],NULL); // convert the string to double value for example "12.5" will be 12.5


	}
	void Var:: setvalue(double x)
	{
		value=x;

	}
	double Var::getvalue()const 
	{
		return value;

	}
		bool Var::getinitalized() const
		{
			return isinitialized;

		}
	string Var::getname() const
	{


		return x;
	}

Var::~Var(void)
{
}
