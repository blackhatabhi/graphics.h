/*************************************************************************/
/**********             	   AlphaSyn.cpp                  *************/
/*************************************************************************/
/****                                                                 ****/
/****    Functions Step (computing method) and Init (intialisation)   ****/
/****                   for the class Alphasyn                        ****/
/****                                                                 ****/
/*************************************************************************/

#include "AlphaSynS.h"
#include <math.h>
#include <iostream.h>


void AlphaSynS::Init(const real dt){ 
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
    Pr=Pr0;  
}



void AlphaSynS::Step( const real dt )
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
              	Pr=Pr0;
                return;
	}
 		      
// else computes the conductance over a time step : alpha function.
        
        PrInter=dt*(-(1/tau1+1/tau2)*Pr-1/tau1*Y);
        
        Y += dt*(1/tau2*Pr-1/tau2*SynEv*MaxG/gMax);
        Pr += PrInter;
        t += dt; 
         
        
 // if G has gotten ridiculously small, reset t
	if (t > pulseTime && Pr < 0.001E-19) {
	    Pr = Pr0;
		G = 0;
		Gk1=0;
		Gk2=0;
		Gk3=0;
		Gk4=0;
		t = 0;
		
	}           

}





