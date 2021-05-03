
#include "HelperFn.h"

bool IsValue (string input)
{
		if(input.length()==0) // string is empty rare
	{
return false;
	}
	// checks if the input string is a double value
	// return true if it's double value, false otherwise
		int dotcounter=0; // count the dots in a string if more than one then it is invalid

	int i=0; // counter to make the one with negative value valid
	if(input[0]=='-'&&input.length()!=1) // does not contain only 1 
	{
		i++;
	}

	for(i;i<input.length();i++)
	{
		if(input[i]=='.')
		{
			if(dotcounter==0 &&input.length()>1) // check that it is the first dot 
			{
			dotcounter++;
			}
			else
			{
				return false; // return false when overloaded dots
			}
		}
		else if(!isdigit(input[i]))
		{
			return false;

		}

	}
	// Double values can be: 12.5, -12.5, -23, -23. , -23.0 …etc.

	//TODO: complete this function

	return true;
}

bool IsVariable (string input)
{
	// checks if the input string is a variable name
	// return true if it can be a variable name, false otherwise
	if(input.length()==0)   // string is empty rare
	{
return false;
	}
	if(IsValue(input))
	{
		return false;
	}

	
	// Variable names must start with an alphabetic letter (small or capital) or an underscore (_). 
	if(!isalpha(input[0]) && input[0]!='_')
	{
		return false;

	}
	for (int i=1;i<input.length();i++) // pass from the second letter 
	{
		if(!isdigit(input[i]) && input[i]!='_' && !isalpha(input[i]))
		{
			return false;

		}


	}

	// After the first initial letter, variable names can contain letters, numbers and underscores.  
	// No spaces or special characters, however, are allowed.

	//TODO: complete this function

	return true;
}

OpType ValueOrVariable (string input)
{
	// checks if the input string is a double value or a variable name
	// chand returns enum "OpType" (the enum is declared in the .h)

	//TODO: complete this function
	if(IsValue(input))
	{

		return VALUE_OP;
	}
	if(IsVariable(input))
	{

		return VARIABLE_OP;
	}

	return INVALID_OP;
}
