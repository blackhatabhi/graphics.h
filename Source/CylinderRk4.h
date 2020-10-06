/**************************************************************************

	Cylinder.h													JJS 8/29/95
	
		part of CONICAL, the Computational Neuroscience Class Library
	
	A Cylinder is a Compartment which has a, well, cylindrical shape.  This
	assumption allows you to specify the compartment's properties in terms
	of its dimensions, its specific membrane resistance and capacitance,
	and specific axial (cytoplasmic) resistance.  The absolute capacitance
	and conductance figures needed by the Compartment will be automatically
	derived.
	
	Membrane values here are the *specific* values, independent of cell
	dimensions.  Thus the cell dimensions can be changed without changing
	membrane properties.
	
	Cylinder is an entirely inline class -- all its code is contained
	within this header file.  Cylinder.cxx contains only the initializers
	for the class variables (defRm, defCm, defRa, and defE).

	Requires:
		Compartment		-- base class

**************************************************************************/

#ifndef CYLINDER_H
#define CYLINDER_H

#include "CmprtmntRk4.h"

#ifndef Pi
#define Pi 3.141592653589793
#endif

class Cylinder : public Compartment
{
  public:

	// static (class) variables defining default values for electrical properties:
	static real defRm;	// specific membrane resistance (ohm m^2)
	static real defCm;	// specific membrane capacitance (farad/m^2)
	static real defRa;	// specific axial resistance (ohm m)
	static real defE;	// resting membrane potential (volt)
  
  	Cylinder( void )							// default constructor
  	: itsRadius(0.000001), itsLength(0.000001),
  	  itsRm(defRm), itsCm(defCm), itsRa(defRa), itsE(defE) {}

  	Cylinder( real pRadius, real pLength )		// constructor (given dimensions)
  	: itsRadius(pRadius), itsLength(pLength),
  	  itsRm(defRm), itsCm(defCm), itsRa(defRa), itsE(defE) {}
  	
  	// inspectors (used because we can't have you changing values willy-nilly):
	
	
	
	virtual real GetRadius() { return itsRadius; }
	virtual real GetLength() { return itsLength; }
	virtual real GetArea() { return Pi * 2*itsRadius * itsLength; }
	virtual real GetRm() { return itsRm; }
	virtual real GetCm() { return itsCm; }
	virtual real GetRa() { return itsRa; }
	virtual real GetE() { return itsE; }
	
	// setters (American, not Irish):
	
	void SetRadius( real pRadius ) { itsRadius = pRadius; Derive(); }
	void SetLength( real pLength ) { itsLength = pLength; Derive(); }
	void SetRm( real pRm ) { itsRm = pRm; Derive(); }
	void SetCm( real pCm ) { itsCm = pCm; Derive(); }
	void SetRa( real pRa ) { itsRa = pRa; Derive(); }
	void SetE( real pE ) { itsE = pE; Derive(); }

  protected:
  
	virtual void Derive( void )
	{ 
		Gm = GetArea() / itsRm;
		EGm = itsE * Gm;
		negC = -( GetArea() * itsCm);
		Gi = Pi * itsRadius*itsRadius / (itsLength * itsRa );
	}
	
	// member variables
	
	real itsRadius, itsLength, itsRm, itsCm, itsRa, itsE;
};

#endif
