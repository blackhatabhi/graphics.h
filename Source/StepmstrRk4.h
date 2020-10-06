/**************************************************************************

	Stepmaster.h												JJS 2/21/96
	
		part of CONICAL, the Computational Neuroscience Class Library
	

	Any Stepper object must be attached to a Stepmaster.  This serves
	two purposes: (1) it keeps track of which memory index (0 or 1) is
	the current one, via its GetCurIdx() method; (2) it can call the
	Step() method of all its attached Steppers, via StepAll(dt).
	
	When a Stepmaster object is killed, all the attached Steppers are
	destroyed as well.  If a Stepper is destroyed, the Stepmaster is
	automatically notified but remains intact.  A Stepper can only be
	removed by attaching it to another Stepmaster.
	
	For ease of use in normal situations, a global gStepmaster is
	automatically defined.  By default, any Steppers created attach
	to gStepmaster.

**************************************************************************/

#ifndef STEPMASTER_H
#define STEPMASTER_H

#ifndef real
#define real double
#endif

class Stepper;

// declare a linked list node for keeping track of Steppers
class StepperNode
{
  friend class Stepmaster;
  private:
	StepperNode( StepperNode *pPrev, Stepper& pIt, StepperNode *pNext=0 )
	{ itsStepper = &pIt; if (pPrev) pPrev->itsNext = this; itsNext = pNext; }  
	Stepper	*itsStepper;
	StepperNode	*itsNext;
};

class Stepmaster
{
	friend class Stepper;
	
  public:
	Stepmaster( );						// constructor
	~Stepmaster( );						// destructor

	// simulation-building methods
	void Attach( Stepper& );			// add a Stepper to our list

	// simulation-running methods
	void StepAll( const real dt );		// update all attached Steppers
	
    void doStepk1(const real dt);         //update k1 in all attached steppers 
	void doStepk2(const real dt);         //update k2 in all attached steppers
	void doStepk3(const real dt);         //update k3 in all attached steppers
	void doStepk4(const real dt);         //update k4 in all attached steppers
	
	void doStepinit(const real dt);       //initialise what need to be...
	
	int GetCurIdx( ) { return itsCurIdx; }

	
  protected:
	void Remove( Stepper& );			// remove a Stepper (dying or defecting)

	// protected variables:
	StepperNode *itsListHead, *itsListTail;	
	int			itsCurIdx;
};

#endif
