#ifndef _LIGHT_H_
#define _LIGHT_H_

#include <memory>
#include <string>

class Light
{
public:
	typedef std::unique_ptr<Light> ptr;

	//---------------------------
	//----- Debugging tools -----
	//---------------------------
	virtual std::string str() = 0;
};

#endif