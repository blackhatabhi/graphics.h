/**************************************************************************

	ChannelRk4.h													JJS 8/29/95
	
		derived from CONICAL, the Computational Neuroscience Class Library
	
	A Channel is a type of Current whose voltage V is fixed, but whose
	conductance G varies with time.  A Channel implements an active
	channel; for a passive channel, you can simply use a Current.

	Note that since a Channel needs a voltage to activate the channel,
	it must be either attached to a Compartment, or separately attached
	to a VSink and a VSource (see constructors below).  The former is
	appropriate for a membrane channel; the latter would be appropriate
	for (say) a synapse, whose conductance depends on presynaptic
	voltage, but whose current affects the postsynaptic compartment.

	Requires:
		Current			-- base class
		Stepper			-- base class
		Compartment		-- source of V for channel activation
		
**************************************************************************/

#ifndef CHANNEL_H
#define CHANNEL_H

#include "CurrentRk4.h"
#include "StepperRk4.h"
#include "CmprtmntRk4.h"

class Channel : public Current, virtual public Stepper
{
  public:
  
	Channel( Compartment *pTo, real pMaxG=0.1 )					// constructor
	: Current( pTo ), itsComp( pTo ), MaxG( pMaxG ) {}

	Channel( VSink *pTo, VSource *pComp, real pMaxG=0.1 )		// constructor
	: Current( pTo ), itsComp( pComp ), MaxG( pMaxG ) {}
	
	virtual void Step( const real dt )		// update G
	{ G = 0; }				// (default behavior is passive -- override here)
    
    virtual void Stepk1( const real dt )		// update Gk1
	{ Gk1 = 0; }	
    virtual void Stepk2( const real dt )		// update Gk2
	{ Gk2 = 0; }	
    virtual void Stepk3( const real dt )		// update Gk3
	{ Gk3 = 0; }	
	virtual void Stepk4( const real dt )		// update Gk4
	{ Gk4 = 0; }
    virtual void Init() {}	
	// public variables:
	
	real MaxG;					// maximum conductance
	
  protected:

	VSource *itsComp;			// compartment whose V affects our G
	
};

#endif
