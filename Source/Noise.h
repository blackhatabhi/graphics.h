/**************************************************************************

	Noise.h													JJS 24/03/2003
	
		addition to CONICAL, the Computational Neuroscience Class Library
	
	A Noise is a Current source in Sink.  Its value 
    is aleatory with Mean = 0 and Variance = 0.1 nA.
	
	This is implemented by keeping G equal to 0, but letting EG return
	E (as if G=1) -- a bit of a double standard.  Additional methods
	SetI and GetI are implemented to allow this class to be used in
	a more technically correct manner.


	Requires:
		Channel			-- base class
		NoiseI          -- gaussian white noise generator
**************************************************************************/

#ifndef NOISE_H
#define NOISE_H

#include "ChannelRk4.h"
#include "NoiseSource.h"



class Noise : public Channel
{
  public:

	Noise( Compartment *pTo )				// constructor
	: Channel( pTo, 0), Amplitude(0.1E-9){}
	
	virtual void Step(const real dt){E=NoiseI(Amplitude);}   //stepper
			
	virtual real GetEG( void ) const { return E; }   // inspectors
	
    virtual real GetEGk1(void) const { return E; }   // inspectors Runge Kutta
	virtual real GetEGk2(void) const { return E; }
	virtual real GetEGk3(void) const { return E; }
	virtual real GetEGk4(void) const { return E; }
	
	virtual void SetAmplitude(real pAmp) { Amplitude = pAmp; } // Amplitude setter
	
  protected:
	real Amplitude;
};

#endif
