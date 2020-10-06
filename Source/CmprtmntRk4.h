/**************************************************************************

	Cmprtmnt.h												JJS 8/26/95
	
		modified from CONICAL, the Computational Neuroscience Class Library
	
	A Compartment is an isopotential volume, to which other compartments
	may be attached through Links.  A Compartment may also have a number
	of Channels.  The current flow from these objects is balanced against
	the current flow through the Compartment membrane, to produce a new
	Compartment potential (voltage) in the Step method.

	Requires:
		VSource		-- base class
		VSink		-- base class
		Stepper		-- base class
		Link.h		-- header file for the Link class

**************************************************************************/

#ifndef COMPARTMENT_H
#define COMPARTMENT_H

#include "VSource.h"
#include "VSink.h"
#include "StepperRk4.h"
#include "Math.h"

// declare the Compartment class

class Compartment : public VSource, public VSink, public Stepper
{
  public:
	Compartment(void);                                
	
    virtual void Init( const real dt );     // update V[]
       			
	virtual void Step( const real dt );     // update V[]
	
	virtual void Stepk1(const real dt);     // update of the Runge Kutta k's     
	virtual void Stepk2(const real dt);
	virtual void Stepk3(const real dt);
	virtual void Stepk4(const real dt);

	
	virtual real GetV( void )				// get current voltage
	{ return V[itsMaster->GetCurIdx()]; }
	
	//Setter
	
	real GetgMax(real dt){
                            
           real dtau = tau1-tau2;
           return  (exp(- tau2 /dtau *log(tau1/tau2)) - exp(-tau1 /dtau *log(tau1/tau2)))*dt/dtau ; 
             
    }
	
    
// public variables (function parameters)
	
	real tau1, tau2, gMax;	// time constants and maximum of function alpha

	
	
/**** public variables: feel free to read or set these between steps! ****/
	
    real Gm;		// membrane conductance (siemens)
	real EGm;		// reversal potential times Gm (volt seimens, or amps)
	real Cm;		// negative of the membrane capacitance (farads)
    real P,P0;
    real EI;
    real X,GI, gMaxI, MaxGI; 

    real Vk1, Vk2, Vk3, Vk4;   //voltages at each step of the RK4 method
  
    protected:
   	

};

#endif
