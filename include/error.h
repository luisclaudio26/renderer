#ifndef ERROR_H
#define ERROR_H

#include <iostream>
#include <cstdlib>
#include <string>

namespace Renderer
{
	inline void LogError(const std::string& s)
	{
		std::cout<<"ERROR: "<<s;
		abort();
	}
}

#endif