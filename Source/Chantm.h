/**************************************************************************

	ChanStd.h													JJS 9/08/95
	
		part of CONICAL, the Computational Neuroscience Class Library
	
	Objects of the ChanStd class are active channels whose gating
	variables (M and H) are updated by one of three standard equation
	forms.  All three formulas use the same parameters (A, B, and V0)
	but these have very different meanings from form to form.  The
	equations used are defined in StdForms.h.
	
	Requires:
		ChanTAU			-- base class
		StdForms.h		-- standard formula definitions
		
**************************************************************************/

#ifndef CHANTM_H
#define CHANTM_H

#include "ChanTAU.h"
#include "StdForms.h"

// one channel needs four equations, denoted by:
enum StdEqType {
	kStdTauM,
	kStdInfM,
	kStdTauH,
	kStdInfH,
kQtyStdEqTypes };

// each equation has three parameters, denoted by:
enum {
	kStdParaA,
	kStdParaB,
	kStdParaV0,
	kStdParaC,
kQtyStdParas };

class ChanTM : public ChanTAU
{
  public:

	// constructors
	ChanTM( Compartment *pTo, real pMaxG=0.1, real pMexp=1, real pHexp=1 )
	: ChanTAU( pTo, pMaxG, pMexp, pHexp ) {}
	ChanTM( VSink *pTo, VSource *pComp, real pMaxG=0.1, real pMexp=1, real pHexp=1 )
	: ChanTAU( pTo, pComp, pMaxG, pMexp, pHexp ) {}
	
	// function defining method (a setter)
	virtual void SetFunc( StdEqType pType, StdForm pForm, real pA, real pB, real pV0, real pC )
	{	itsForm[pType] = pForm;
		itsParam[pType][kStdParaA] = pA;
		itsParam[pType][kStdParaB] = pB;
		itsParam[pType][kStdParaV0]= pV0;
		itsParam[pType][kStdParaC]= pC;
	}
		
	// channel activation/inactivation functions
	virtual real TauM( const real V ) const
	{	return StdFormula( itsForm[kStdTauM], V,
			itsParam[kStdTauM][kStdParaA], 
			itsParam[kStdTauM][kStdParaB],
			itsParam[kStdTauM][kStdParaV0],
            itsParam[kStdTauM][kStdParaC] ); }
		
	virtual real InfM( const real V) const
	{	return StdFormula( itsForm[kStdInfM], V,
			itsParam[kStdInfM][kStdParaA], 
			itsParam[kStdInfM][kStdParaB],
			itsParam[kStdInfM][kStdParaV0],
            itsParam[kStdInfM][kStdParaC] ); }

	virtual real TauH( const real V ) const
	{	return StdFormula( itsForm[kStdTauH], V,
			itsParam[kStdTauH][kStdParaA], 
			itsParam[kStdTauH][kStdParaB],
			itsParam[kStdTauH][kStdParaV0],
            itsParam[kStdTauH][kStdParaC] ); }

	virtual real InfH( const real V ) const
	{	return StdFormula( itsForm[kStdInfH], V,
			itsParam[kStdInfH][kStdParaA], 
			itsParam[kStdInfH][kStdParaB],
			itsParam[kStdInfH][kStdParaV0],
            itsParam[kStdInfH][kStdParaC] ); }

	// public variables which define the functions:

	StdForm	itsForm[kQtyStdEqTypes];	// format (kExpForm, kSigForm, kLinForm)
	real	itsParam[kQtyStdEqTypes][kQtyStdParas];
	
};

#endif

