
/*************************************************************************/
/**********             	   AlphaSyn.cpp                  *************/
/*************************************************************************/
/****                                                                 ****/
/****    Functions Step (computing method) and Init (intialisation)   ****/
/****                   for the class Alphasyn                        ****/
/****                                                                 ****/
/*************************************************************************/

#include "AlphaSyn.h"
#include <math.h>
#include <iostream.h>


void AlphaSyn::Init(const real dt){ 
    G=0;
    X=0;
    t=0;
    Gk1=0;
   	Gk2=0;
   	Gk3=0;
   	Gk4=0;
   	SynEv=0;
    Nmem = int(floor(Lat/dt));
    gMax=GetgMax(dt);  
}



void AlphaSyn::Step( const real dt )
{   
// reset the spike detection variable 
	SynEv=0; 
	
// check the presynaptic voltage
// but ONLY if we're not already releasing (in the pulse time window)
    if(t == 0 || t > pulseTime) {
		if (itsComp->Memory[Nmem]>0){ SynEv=1; t=dt;}
    }
	
// if we're not spiking -- i.e., t == 0 -- then return
	if (t==0){ 
                G=0;
              	Gk1=0;
              	Gk2=0;
              	Gk3=0;
              	Gk4=0;
              	SynEv=0;
                return;
	}
 		      
// else computes the conductance over a time step : alpha function.
        Gk0=dt*(-(1/tau1+1/tau2)*G-1/tau1*X);
        Gk1=G+Gk0;
        Gk2=Gk1;
        Gk3=Gk1;
        Gk4=Gk1;
        
        X += dt*(1/tau2*G-1/tau2*SynEv*MaxG/gMax);
        G += Gk0;
        t += dt; 
         
        
 // if G has gotten ridiculously small, reset t
	if (t > pulseTime && G < 0.001E-9) {
		G = 0;
		Gk1=0;
		Gk2=0;
		Gk3=0;
		Gk4=0;
		t = 0;
		
	}           

}





