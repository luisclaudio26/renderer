#ifndef _SHAPE_H_
#define _SHAPE_H_

#include <memory>
#include <string>
#include "../3rdparty/json.hpp"

class Shape
{
public:
	typedef std::unique_ptr<Shape> ptr;

	//--------------------------------
	//------ Introspection code ------
	//--------------------------------
	virtual std::string str() = 0;
};

#endif