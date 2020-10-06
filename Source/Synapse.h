/**************************************************************************

	Synapse.h												   JJS 10/01/95
	
		part of CONICAL, the Computational Neuroscience Class Library
	
	A synapse is a channel whose conductance in  Vsink depends on spiking 
    events from VSource.  

	This class also defines a Vthresh variable, which may be used (by
	derived classes) as the threshold voltage for neurotransmitter release,
	and pulseTime, which defines the duration of a transmitter pulse.  The
	exact use and meaning of these variables may vary.

	Requires:
		Channel			-- base class
		
**************************************************************************/

#ifndef SYNAPSE_H
#define SYNAPSE_H

#include "ChannelRk4.h"

class Synapse : public Channel
{
  public:

	Synapse( VSink *pTo, VSource *pComp, real pMaxG=0 )		// constructor
	: Channel( pTo, pComp, pMaxG ), t(0), Vthresh(0), pulseTime(1) {}
	
	virtual void Step( const real dt ){ NULL;}		// Null method

	// public variables
	
	
	real Vthresh;		// presynaptic V threshold for transmitter release
	real pulseTime;		// duration of a transmitter pulse

  protected:

	real t;				// time since itsComp->GetV() > Vthresh
};

#endif
