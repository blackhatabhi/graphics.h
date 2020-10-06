/*************************************************************************/
/**********             	   ChanHHrk4.cpp                 *************/
/*************************************************************************/
/****                                                                 ****/
/****             Computing method  and Init (intialisation)          ****/
/****                   for the class ChanHH                          ****/
/****                                                                 ****/
/*************************************************************************/


#include "ChanHHrk4.h"
#include <math.h>


void ChanHH::Step( const real dt )
{
	// First, update the gating variables.
	// Then conductance G can be computed directly.

	if (Mexp) UpdateM( dt );
	if (Hexp) UpdateH( dt );
	
	// Note: for efficiency, we could restrict the exponents to
	// integers, do a "case" here, and multiply them out the long way...
	
	G = MaxG * pow(M,Mexp) * pow(H,Hexp);
}


void ChanHH::Stepk1( const real dt )
{
	// First, update the gating variables.
	// Then conductance G can be computed directly.

	if (Mexp) UpdateMk1( dt );
	if (Hexp) UpdateHk1( dt );
	
	
	Gk1 = MaxG * pow(M+Mk1/2,Mexp) * pow(H+Hk1/2,Hexp);
}

void ChanHH::Stepk2( const real dt )
{
	// First, update the gating variables.
	// Then conductance G can be computed directly.

	if (Mexp) UpdateMk2( dt );
	if (Hexp) UpdateHk2( dt );
	
	
	Gk2 = MaxG * pow(M+Mk2/2,Mexp) * pow(H+Hk2/2,Hexp);
}

void ChanHH::Stepk3( const real dt )
{
	// First, update the gating variables.
	// Then conductance G can be computed directly.

	if (Mexp) UpdateMk3( dt );
	if (Hexp) UpdateHk3( dt );
	
	
	Gk3 = MaxG * pow(M+Mk3,Mexp) * pow(H+Hk3,Hexp);
}

void ChanHH::Stepk4( const real dt )
{
	// First, update the gating variables.
	// Then conductance G can be computed directly.

	if (Mexp) UpdateMk4( dt );
	if (Hexp) UpdateHk4( dt );
	
	
	Gk4 = MaxG * pow(M+Mk4,Mexp) * pow(H+Hk4,Hexp);
}

