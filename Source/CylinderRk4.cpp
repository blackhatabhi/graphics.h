//	Cylinder.cxx

#include "CylinderRk4.h"

// initialize the default values of electrical properties

real Cylinder::defRm = 0.33333;	// specific membrane resistance (ohm m^2)
real Cylinder::defCm = 0.01;	// specific membrane capacitance (farad/m^2)
real Cylinder::defRa = 0.3;		// specific axial resistance (ohm m)
real Cylinder::defE = -0.070;	// resting membrane potential (volt)

