/**************************************************************************

	FirstOrderTMRk4.h												JJS 9/06/95
	
		addition from CONICAL, the Computational Neuroscience Class Library
	
	This header file does not declare a class, but rather, a general-
	purpose function for integrating first-order kinetic equations of 
	the form:
				dy/dt = ( inf - y)/tau
	

	Requires:
		math library		-- ANSI math functions, defined in <math.h>
		
**************************************************************************/

#ifndef FIRSTORDERTMRK4_H
#define FIRSTORDERTMRK4_H

#include <math.h>

#ifndef real
#define real double
#endif

inline real FirstOrderTMRk4( real y, real tau, real inf, real dt )
{
    //Runge Kutta
    return  (inf - y)*dt/tau;
}

#endif
