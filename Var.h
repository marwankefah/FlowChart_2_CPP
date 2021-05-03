#pragma once
#include <iostream>
using namespace std;
class Var
{
	string x;   // include the variable name
	bool isinitialized; // true when the value is initialized
	double value; // contains the value of the string as written in the description all variables contains values as seen in read it is said read variable "value" from the user

public:
	
Var();
Var(string x,double l,bool y);

	void setname(string name);
	void setinialized(bool x);
	void setvalue(string x);
		void setvalue(double x);

	double getvalue()const ;
		bool getinitalized() const;
	string getname() const;
	~Var(void);
};

