/**************************************************************************

	VSource.h													JJS 8/29/95
	
		part of CONICAL, the Computational Neuroscience Class Library
	
	A VSource, or voltage source, is an object which can cause current to
	flow through a Current.  That is, a VSource has some potential (V), which
	may be read by other objects to adjust whatever (usually their own V).

	Requires:
		nothing
			
**************************************************************************/

#ifndef VSOURCE_H
#define VSOURCE_H

#ifndef real
#define real double
#endif

class VSource
{
  public:
	VSource( void ) { V[0] = V[1] = 0; }
	VSource( real pV ) { V[0] = V[1] = pV; }
	
    virtual void SetV( real pV ) { V[0] = V[1] = pV; }
	virtual real GetV( void ) { return V[0]; }
    real Vk1, Vk2, Vk3, Vk4;
    int Memory[200];
    real dV;
    
   protected:
	real V[2];         // membrane potential (volts); current and new values
	
	
};

#endif
