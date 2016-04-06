#include "PError.h"

PError::PError(std::string error) 
{
	std::cout << "There was a problem with " << error << " on line " << __LINE__ << std::endl;
}

PError::PError(std::string error, const char * sdlError) {
	std::cout << "There was a problem with " << error << " and " << sdlError << " on line " << __LINE__ << std::endl;
}

