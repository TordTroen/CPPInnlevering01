#pragma once

/* JUST A FRIENDLY CLASS TO PROPERLY PRINT MESSAGES FOR DEBUGGING WITH LINE NUMBERS */

#include <string>
#include <iostream>

class PError
{
public:
	PError(std::string error);
	PError() : PError{ "" } {}
};