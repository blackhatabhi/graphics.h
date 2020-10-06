/**************************************************************************

	FirstOrderRk4.h												JJS 9/06/95
	
		modified from CONICAL, the Computational Neuroscience Class Library
	
	This header file does not declare a class, but rather, a general-
	purpose function for integrating first-order kinetic equations of 
	the form:
				dy/dt = alpha*(1-y) - beta*y
	
	This is equivalent to the kinetic reaction a <---> b, where y is the
	value of a (or b), 1-y is the value of the other, the forward reaction
	rate is alpha, and the backward rate is beta.  To use, write
	
				newy = FirstOrder( y, alpha, beta, dt )

	Requires:
		math library		-- ANSI math functions, defined in <math.h>
		
**************************************************************************/

#ifndef FIRSTORDER_H
#define FIRSTORDER_H

#include <math.h>

#ifndef real
#define real double
#endif

inline real FirstOrderRk4( real y, real alpha, real beta, real dt )
{
	real ratesum = alpha + beta;
	
	//Exp Euler 
    //return y + (alpha/ratesum - y) * (1 - exp(-ratesum*dt) );
    
    //Runge Kutta
    return  (alpha - ratesum*y)*dt;
}

#endif
