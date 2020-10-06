/**************************************************************************

	Stepper.h													JJS 8/29/95
	
		part of CONICAL, the Computational Neuroscience Class Library
	
	A Stepper is any object which needs to be updated at each tick of the
	clock; that is, it needs to receive a regular Step(dt) call.
	
	Requires:
		nothing

**************************************************************************/

#ifndef STEPPER_H
#define STEPPER_H

#ifndef real
#define real double
#endif

#include "StepmstrRk4.h"

// global variable, instantiated in Stepmstr.cxx:
extern Stepmaster gStepmaster;

class Stepper
{
	friend class Stepmaster;
	
  public:

	Stepper( )								// constructor
	 : itsMaster(0)	{ gStepmaster.Attach( *this ); }

	~Stepper( )								// destructor
		{ if (itsMaster) itsMaster->Remove( *this ); }
		
	virtual void Step( const real dt )		// update whatever
		{  /* null method */  }
    virtual void Stepk1( const real dt )		// update whatever dedicated to step 1 of the Rk4
		{  /* null method */  }
    virtual void Stepk2( const real dt )		// update whatever dedicated to step 2
		{  /* null method */  }
    virtual void Stepk3( const real dt )		// update whatever dedicated to step 3
		{  /* null method */  }
    virtual void Stepk4( const real dt )		// update whatever dedicated to step 4
		{  /* null method */  }
    
    virtual void Init(const real dt){}	                // initialize

  protected:
	Stepmaster *itsMaster;			// Stepmaster to which it's attached
};

#endif
