/**************************************************************************

	ChanHHrk4.h													JJS 9/06/95
	
		derived from CONICAL, the Computational Neuroscience Class Library
	
	ChanHH implements a Hodgkin-Huxley form active ion channel.  The
	channel conductance G is equal to M^Mexp * H^Hexp, where M and H
	are functions of voltage and time, and Mexp and Hexp are constants
	(integer by convention, but any value is allowed here).

	This is not an abstract base class; you can instantiate it, but it
	doesn't do much.  The UpdateM and UpdateH methods do nothing, which
	means that the gating variables (M and H) stay wherever you set them.
	Subclasses should override these two functions.

	Requires:
		Channel			-- base class
		math			-- ANSI math functions (defined in <math.h>)
		
**************************************************************************/

#ifndef CHANHH_H
#define CHANHH_H

#include "ChannelRk4.h"

class ChanHH : public Channel
{
  public:

	// constructors
	ChanHH( Compartment *pTo, real pMaxG=0.1, real pMexp=1, real pHexp=1 )
	: Channel( pTo, pMaxG ), M(0), H(0), Mexp(pMexp), Hexp(pHexp) {}

	ChanHH( VSink *pTo, VSource *pComp, real pMaxG=0.1, real pMexp=1, real pHexp=1 )
	: Channel( pTo, pComp, pMaxG ), M(0), H(0), Mexp(pMexp), Hexp(pHexp) {}

	// update methods
	
	virtual void Step( const real dt );			// updates G,
												// calls UpdateM and UpdateH	
    
    
    virtual void Stepk1( const real dt );	    // Runge Kutta step functions
    virtual void Stepk2( const real dt );	    // will update Mk's and Hk's
    virtual void Stepk3( const real dt );	
    virtual void Stepk4( const real dt );	
    
    
	virtual void UpdateM( const real dt ) {}	// update M (override this)
	virtual void UpdateH( const real dt ) {}	// update H (override this)
    
    virtual void UpdateMk1(const real dt) {}  //update for the Runge Kutta loop
    virtual void UpdateHk1(const real dt) {}  //update for the Runge Kutta loop
    virtual void UpdateMk2(const real dt) {}  //update for the Runge Kutta loop
    virtual void UpdateHk2(const real dt) {}  //update for the Runge Kutta loop
	virtual void UpdateMk3(const real dt) {}  //update for the Runge Kutta loop
    virtual void UpdateHk3(const real dt) {}  //update for the Runge Kutta loop	
    virtual void UpdateMk4(const real dt) {}  //update for the Runge Kutta loop
    virtual void UpdateHk4(const real dt) {}  //update for the Runge Kutta loop
    
 
 
 
 // public variables:
	
	real M, H;                   // gating variables, updated at each general step 
 	real Mk1, Mk2, Mk3, Mk4;	 // gating variables for rk4			
	real Hk1, Hk2, Hk3, Hk4;
    real Mexp, Hexp;			// exponents in current function

};	

#endif

