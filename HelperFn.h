
#pragma once

// this file contains the functions that don't logically belong to any class
// and can be used by any class
// they are, in general, helper functions

#include <string>
using namespace std;

enum OpType
{
	VALUE_OP,
	VARIABLE_OP,
	INVALID_OP
};

bool IsValue (string input);
bool IsVariable (string input);
OpType ValueOrVariable (string input);
