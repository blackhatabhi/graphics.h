/**************************************************************************

	AlphaSyn.h													JJS 9/13/95
	
		part of CONICAL, the Computational Neuroscience Class Library
	
	This file implements a classic "alpha function" synapse.  When the
	voltage in the presynaptic compartment (i.e., the VSource) exceeds
	a threshold Vthresh, the alpha function is initiated.  A fixed
	conductance change ensues, following a double exponential specified
	by tau1 and tau2.  The function cannot be started again until
	refractTime has passed.

	Requires:
		Synapse			-- base class
		
**************************************************************************/

#ifndef ALPHASYN_H
#define ALPHASYN_H
#include<math.h>
#include "Synapse.h"

class AlphaSyn : public Synapse
{
  public:
     
	AlphaSyn( VSink *pTo, VSource *pComp, real pMaxG=0, real pLat=0 )		// constructor
	: Synapse( pTo, pComp, pMaxG ), tau1(0), tau2(0), Lat(pLat), SynEv(0) {}
	
	virtual void Step( const real dt );		// update G
    virtual void Init(const real dt);
    
    
//Setter
	
	real GetgMax(real dt){
                            
           real dtau = tau1-tau2;
           return  (exp(- tau2 /dtau *log(tau1/tau2)) - exp(-tau1 /dtau *log(tau1/tau2)))*dt/dtau ; 
             
    }
	
    
// public variables (function parameters)
	
	real tau1, tau2, gMax;	// time constants and maximum of function alpha
    real Lat;
    int Nmem;
    real Gk0;
    real X;
    int SynEv;
};

#endif
