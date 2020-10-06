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

#ifndef ALPHASYNI_H
#define ALPHASYNI_H
#include<math.h>
#include "Synapse.h"
#include "NoiseSource.h"

class AlphaSynI : public Synapse
{
  public:
     
	AlphaSynI( VSink *pTo, VSource *pComp, real pMaxG=0, real pF=50 ,real pT1=0.05,real pT2=0.100, real pFst=100, real pMean=0.5)		// constructor
	: Synapse( pTo, pComp, pMaxG ), tau1(0), tau2(0), SynEv(0),T(0), Mn(pMean), T1(pT1), T2(pT2),Fsat(pFst),Freqmax(pF) {}
	
	virtual void Step( const real dt );		// update G
    virtual void Init(const real dt);
    
    
//Setter
	
	real GetgMax(real dt){
                            
           real dtau = tau1-tau2;
           return  (exp(- tau2 /dtau *log(tau1/tau2)) - exp(-tau1 /dtau *log(tau1/tau2)))*dt/dtau ; 
             
    }
	
	real GetFmax(real dt){                        
           real dtau = T1-T2;
           return  (exp(- T2 /dtau *log(T1/T2)) - exp(-T1 /dtau *log(T1/T2)))*dt/dtau;           
    }
    
// public variables (function parameters)
	
	real tau1, tau2, gMax, Mn;	// time constants and maximum of function alpha ; mean rate of IPSPs at rest
    real X,Y;
    int SynEv, SpkEv, sat;
    real interval;
    real Gk0;
    int decision;
	int calcul;
    real Mean,Freq,Freqmax,Fmax,T1,T2, Fsat;
    
 protected:
 
    real T;
 
};

#endif
