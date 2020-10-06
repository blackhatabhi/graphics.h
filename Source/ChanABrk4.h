/**************************************************************************

	ChanAB.h													JJS 9/06/95
	
		part of CONICAL, the Computational Neuroscience Class Library
	
	A ChanAB is a ChanHH in which the change in the gating variables
	(i.e., UpdateM and UpdateH) are defined in terms of Alpha and Beta
	functions (AlphaM, BetaM, AlphaH, and BetaH).  See ChanInfTau for
	an alternative to this format.
	
	Like ChanHH itself, ChanAB can be instantiated, but doesn't do much,
	because AlphaM etc. do nothing.  Subclasses should override these
	four functions to provide full functionality.
	
	Requires:
		ChanHH			-- base class
		
**************************************************************************/

#ifndef CHANABRK4_H
#define CHANABRK4_H

#include "ChanHHrk4.h"
#include "math.h"

class ChanAB : public ChanHH
{
  public:
  
	// constructors
	ChanAB( Compartment *pTo, real pMaxG=0.1, real pMexp=1, real pHexp=1 )
	: ChanHH( pTo, pMaxG, pMexp, pHexp ), variation(1),rho(0),E0(-0.0665),Tres(0) {}
	
	ChanAB( VSink *pTo, VSource *pComp, real pMaxG=0.1, real pMexp=1, real pHexp=1 )
	: ChanHH( pTo, pComp, pMaxG, pMexp, pHexp ), variation(1),rho(0),E0(-0.0665),Tres(0) {}
	
	virtual void Init(const real dt);                        // Initialize
	
	virtual void UpdateM( const real dt );		// update M (calls AlphaM, BetaM)
	virtual void UpdateH( const real dt );		// update H (calls AlphaH, BetaH)

    virtual void UpdateMk1( const real dt );
    virtual void UpdateHk1( const real dt );
    virtual void UpdateMk2( const real dt );
    virtual void UpdateHk2( const real dt );
    virtual void UpdateMk3( const real dt );
    virtual void UpdateHk3( const real dt );
    virtual void UpdateMk4( const real dt );
    virtual void UpdateHk4( const real dt );
  
    //Treshold modulation function
    real rhomod(real V, real dV, real max, real slope){real x=dV/slope;
                                              if (dV>0 && Tres){return rho*(1+x*exp(-x/5+1-log(5/2.7)));}
                                              else {return rho;}      
                                          } 
    
	// channel activation/inactivation functions: override these
	virtual real AlphaM( const real V ) const	{ return 1; }
	virtual real BetaM( const real V) const		{ return 1; }
	virtual real AlphaH( const real V ) const	{ return 1; }
	virtual real BetaH( const real V ) const	{ return 1; }
	
	int variation;
	real rho;       // Tuning
	real E0;
	real Max, Slope;
	int Tres;
	
	virtual void Setrho(real prho){rho=prho;}
	virtual void SetSlope(real pslo){Slope=pslo;}
	virtual void DoThreshold(){Tres=1;}
	virtual void UndoThreshold(){Tres=0;}
};

#endif
