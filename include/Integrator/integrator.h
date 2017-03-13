#ifndef _INTEGRATOR_H_
#define _INTEGRATOR_H_

#include <memory>

class Integrator
{
public:
	typedef std::unique_ptr<Integrator> ptr;
};

#endif