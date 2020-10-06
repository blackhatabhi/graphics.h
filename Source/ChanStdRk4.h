/**************************************************************************

	ChanStd.h													JJS 9/08/95
	
		part of CONICAL, the Computational Neuroscience Class Library
	
	Objects of the ChanStd class are active channels whose gating
	variables (M and H) are updated by one of three standard equation
	forms.  All three formulas use the same parameters (A, B, and V0)
	but these have very different meanings from form to form.  The
	equations used are defined in StdForms.h.
	
	Requires:
		ChanAB			-- base class
		StdForms.h		-- standard formula definitions
		
**************************************************************************/

#ifndef CHANSTD_H
#define CHANSTD_H

#include "ChanABrk4.h"
#include "StdForms.h"

// one channel needs four equations, denoted by:
enum StdEqnType {
	kStdAlphaM,
	kStdBetaM,
	kStdAlphaH,
	kStdBetaH,
kQtyStdEqnTypes };

// each equation has three parameters, denoted by:
enum {
	kStdParamA,
	kStdParamB,
	kStdParamV0,
	kStdParamC,
kQtyStdParams };

class ChanStd : public ChanAB
{
  public:

	// constructors
	ChanStd( Compartment *pTo, real pMaxG=0.1, real pMexp=1, real pHexp=1 )
	: ChanAB( pTo, pMaxG, pMexp, pHexp ) {}
	ChanStd( VSink *pTo, VSource *pComp, real pMaxG=0.1, real pMexp=1, real pHexp=1 )
	: ChanAB( pTo, pComp, pMaxG, pMexp, pHexp ) {}
	
	// function defining method (a setter)
	virtual void SetFunc( StdEqnType pType, StdForm pForm, real pA, real pB, real pV0, real pC )
	{	itsForm[pType] = pForm;
		itsParam[pType][kStdParamA] = pA;
		itsParam[pType][kStdParamB] = pB;
		itsParam[pType][kStdParamV0]= pV0;
		itsParam[pType][kStdParamC]= pC;
		
	}
		
	// channel activation/inactivation functions
	virtual real AlphaM( const real V ) const
	{	return StdFormula( itsForm[kStdAlphaM], V,
			itsParam[kStdAlphaM][kStdParamA], 
			itsParam[kStdAlphaM][kStdParamB],
			itsParam[kStdAlphaM][kStdParamV0],
            itsParam[kStdAlphaM][kStdParamC] ); }
		
	virtual real BetaM( const real V) const
	{	return StdFormula( itsForm[kStdBetaM], V,
			itsParam[kStdBetaM][kStdParamA], 
			itsParam[kStdBetaM][kStdParamB],
			itsParam[kStdBetaM][kStdParamV0],
            itsParam[kStdBetaM][kStdParamC] ); }

	virtual real AlphaH( const real V ) const
	{	return StdFormula( itsForm[kStdAlphaH], V,
			itsParam[kStdAlphaH][kStdParamA], 
			itsParam[kStdAlphaH][kStdParamB],
			itsParam[kStdAlphaH][kStdParamV0],
            itsParam[kStdAlphaH][kStdParamC] ); }

	virtual real BetaH( const real V ) const
	{	return StdFormula( itsForm[kStdBetaH], V,
			itsParam[kStdBetaH][kStdParamA], 
			itsParam[kStdBetaH][kStdParamB],
			itsParam[kStdBetaH][kStdParamV0],
            itsParam[kStdBetaH][kStdParamC] ); }

	// public variables which define the functions:
	
	StdForm	itsForm[kQtyStdEqnTypes];	// format (kExpForm, kSigForm, kLinForm)
	real	itsParam[kQtyStdEqnTypes][kQtyStdParams];
};

#endif

