/**************************************************************************

	ChanTAU.h													JJS 9/06/95
	
	addition to CONICAL, the Computational Neuroscience Class Library
	
	A ChanTAU is a ChanHH in which the change in the gating variables
	(i.e., UpdateM and UpdateH) are defined in terms of stationary functions and 
    time constants (InfM, TauM, AlphaH, and BetaH) that may be found in the 
    StdForms.h libary of kinetic types.  
	
	Like ChanHH itself, ChanTAU can be instantiated, but doesn't do much,
	because AlphaM etc. do nothing.  Subclasses should override these
	four functions to provide full functionality.
	
	Requires:
		ChanHH			-- base class
		
**************************************************************************/

#ifndef CHANTAU_H
#define CHANTAU_H

#include "ChanHHrk4.h"

class ChanTAU : public ChanHH
{
  public:
  
	// constructors
	ChanTAU( Compartment *pTo, real pMaxG=0.1, real pMexp=1, real pHexp=1, int pVar=1 )
	: ChanHH( pTo, pMaxG, pMexp, pHexp ), variation(pVar), rho(0), E0(-0.0665) {}
	
	ChanTAU( VSink *pTo, VSource *pComp, real pMaxG=0.1, real pMexp=1, real pHexp=1, int pVar=1 )
	: ChanHH( pTo, pComp, pMaxG, pMexp, pHexp ), variation(pVar), rho(0),E0(-0.0665) {}
	
	virtual void Init(const real dt);                        //Initialise
	
	virtual void UpdateM( const real dt );		// update M (calls AlphaM, BetaM)
	virtual void UpdateH( const real dt );		// update H (calls AlphaH, BetaH)

    // for Runge-Kutta 4
    virtual void UpdateMk1( const real dt );
    virtual void UpdateHk1( const real dt );
    virtual void UpdateMk2( const real dt );
    virtual void UpdateHk2( const real dt );
    virtual void UpdateMk3( const real dt );
    virtual void UpdateHk3( const real dt );
    virtual void UpdateMk4( const real dt );
    virtual void UpdateHk4( const real dt );
    
    
	// channel activation/inactivation functions: override these
	virtual real TauM( const real V ) const	{ return 1; }
	virtual real InfM( const real V)  const { return 1; }
	virtual real TauH( const real V ) const	{ return 1; }
	virtual real InfH( const real V ) const	{ return 1; }
	
	int variation;
	real rho;     // tuning
	real E0;
	
	virtual void Setrho(real prho){rho=prho;}
};

#endif
