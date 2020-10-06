/**************************************************************************

	CurrentRk4.h													JJS 8/26/95
	
		modified from CONICAL, the Computational Neuroscience Class Library
	
	A Current is any object which attaches to a VSink and which provides
	a source of current for that VSink.

	Requires:
		VSink.h			-- header file for the VSink class
		
**************************************************************************/

#ifndef CURRENT_H
#define CURRENT_H

#include "VSink.h"

#ifndef real
#define real double
#endif

class Current
{
  public:
  
	Current( VSink *pTo, real pG=0, real pE=0, real pGk1=0, real pGk2=0, real pGk3=0, real pGk4=0 )				// constructor
	: itsTo(pTo), G(pG), E(pE), Gk1(pGk1), Gk2(pGk2), Gk3(pGk3), Gk4(pGk4), Pr(0) { pTo->AddCurrent(this); }
	
	virtual ~Current( void ) { itsTo->RemoveCurrent(this); }	// destructor
	
	virtual void SetE( real pE ) { E = pE; }			// setter
	
	virtual real GetE(void) const { return E; }			// inspectors
	virtual real GetEG(void) const { return G*E; }
	
			
	virtual real GetEGk1(void) const { return Gk1*E; }      // inspectors Runge Kutta
	virtual real GetEGk2(void) const { return Gk2*E; }
	virtual real GetEGk3(void) const { return Gk3*E; }
	virtual real GetPr(void) const { return Pr; }
	
	
	virtual VSink *GetTo(void) const { return itsTo; }

	// public variables:
	
	real G;
	real Gk1, Gk2, Gk3, Gk4;
	real Pr;
	
  protected:	
	VSink *itsTo;
	real E;
};

#endif
	
