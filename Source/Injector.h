/**************************************************************************

	Injector.h													JJS 9/11/95
	
		part of CONICAL, the Computational Neuroscience Class Library
	
	An Injector is an ideal Current source, that is, one which provides
	a constant current regardless of the potential of the voltage sink
	to which it is attached.  Such a current source has an infinite
	internal resistance, i.e. zero conductance, and an infinite source
	potential, so that the current (E-V)G = EG-VG = EG for finite V.
	
	This is implemented by keeping G equal to 0, but letting EG return
	E (as if G=1) -- a bit of a double standard.  Additional methods
	SetI and GetI are implemented to allow this class to be used in
	a more technically correct manner.

	Requires:
		Current			-- base class
		
**************************************************************************/

#ifndef INJECTOR_H
#define INJECTOR_H

#include "CurrentRk4.h"

class Injector : public Current
{
  public:

	Injector( VSink *pTo, real pI=0 )				// constructor
	: Current( pTo, 0, pI ) {}
	
	virtual void SetI( real pI ) { E = pI; }		// setter
	
	virtual real GetI( void ) const { return E; }			// inspectors
	virtual real GetEG( void ) const { return E; }
	
    virtual real GetEGk1(void) const { return E; }      // inspectors Runge Kutta
	virtual real GetEGk2(void) const { return E; }
	virtual real GetEGk3(void) const { return E; }

};

#endif
