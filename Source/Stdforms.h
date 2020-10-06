/**************************************************************************

	StdForms.h													JJS 9/08/95
	
		part of CONICAL, the Computational Neuroscience Class Library
	
	This file does not define a class; rather, it defines some standard
	formulas which are frequently used to describe channel gating, etc.
	It also defines some constants and a front-end function for accessing
	compatible functions through a single call (StdFormula) if the format
	is only known at runtime.
	
	Requires:
		math			-- ANSI math functions (defined in <math.h>)
		
**************************************************************************/

#ifndef STDFORMS_H
#define STDFORMS_H

#ifndef real
#define real double
#endif

#include <math.h>

enum StdForm {
	kExpForm,
	kSigForm,
	kSioForm,
	kLinForm,
	kCstForm,
	kKftForm,
	kKslForm,
	kWangForm,
	kAmForm,
	kAh1Form,
	kAh2Form,
kQtyForms };

inline real ExpForm(real v, real A, real B, real V0)
{
	return A * exp((v-V0)/B);
}

inline real SigForm(real v, real A, real B, real V0)
{
	return A / (exp((v-V0)/B) + 1);
}

inline real LinForm(real v, real A, real B, real V0)
{
	return (v==V0 ? A : A * (v-V0) / (exp((v-V0)/B)  - 1) );
}

inline real CstForm( real A)
{
	return A ;
}

inline real SioForm(real v, real A, real B, real V0, real C)
{
	return C + A / (exp((v-V0)/B) + 1);
}

inline real WangForm(real v, real A, real B, real V0, real C)
{
	return A *exp(C*(v-V0)/B)/ (exp((v-V0)/B) + 1);
}

inline real KftForm(real v)
{
	if(v<-0.043) return 0.95889E-3 + 0.209E-3 * exp( v/0.03938 ) ;
	if(v>=-0.043 && v<-0.025) return 2.6597E-3 + 0.5108E-3* exp(-2*pow((v+34.559E-3)/14.031E-3 ,2));
	if(v>=-0.025 && v<0.032)  return 0.117E-3 + 3.2E-3/(exp((v+0.00309)/0.01361)+1);
    if(v>=0.032) return 0.34E-3;
}

inline real AmForm(real v)
{
    return 1E-3*(1/( exp((v+0.0358)/0.0197)+exp(-(v+0.0797)/0.0127) ) + 0.37); 
}

inline real Ah1Form(real v)
{
    if(v<-0.063) return 1E-3/( exp((v+0.046)/0.0197)+exp(-(v+0.238)/0.0375) ) ;
    if(v>=-0.063) return 19E-3; 
}

inline real Ah2Form(real v)
{
    if(v<-0.073) return 1E-3/( exp((v+0.046)/0.0197)+exp(-(v+0.238)/0.0375) ) ;
    if(v>=-0.073) return 60E-3; 
}

inline real StdFormula( StdForm pForm, real V, real A, real B, real V0, real C )
{
	switch (pForm) {
		case kExpForm: return ExpForm( V, A, B, V0 );
		case kSigForm: return SigForm( V, A, B, V0 );
		case kSioForm: return SioForm( V, A, B, V0, C);
		case kLinForm: return LinForm( V, A, B, V0 );
		case kCstForm: return CstForm( A );
		case kWangForm: return WangForm(V, A, B, V0, C);
        case kKftForm: return KftForm( V );
		case kKslForm: return 4*KftForm( V );
		case kAmForm: return AmForm(V);
		case kAh1Form: return Ah1Form(V);
		case kAh2Form: return Ah2Form(V);
	}
	return 0;
}

#endif
