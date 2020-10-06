
/*************************************************************************/
/**********             	   AlphaSyn.cpp                  *************/
/*************************************************************************/
/****                                                                 ****/
/****    Functions Step (computing method) and Init (intialisation)   ****/
/****                   for the class Alphasyn                        ****/
/****                                                                 ****/
/*************************************************************************/

#include "AlphaSynI.h"
#include <math.h>
#include <iostream.h>


void AlphaSynI::Init(const real dt){ 
    G=0;
    X=0;
    Y=0;
    t=0;
    Gk0=0;
    Gk1=0;
   	Gk2=0;
   	Gk3=0;
   	Gk4=0;
   	SynEv=0;
   	Fmax=GetFmax(dt);
   	gMax=GetgMax(dt);
   	sat=0;
   	decision=1;
   	interval=0;
}



void AlphaSynI::Step( const real dt )
{      
       SynEv=0;
       SpkEv=0;
       
       if(decision){
                 if(Freq<Mn) Mean=Mn;
                 else Mean=1/Freq; 
                 
                 do{interval=Mean+NoiseI(Mean);}
                 while(interval<0.005);  
                 decision=0;
       }   
	   
       if(T >=interval && T<interval +dt){
                 decision=1;
                 SynEv=1;
                 t=0;
                 T=0; 
       }
       
       //Computation of the actual conductance
                 Gk0=dt*(-(1/tau1+1/tau2)*G-1/tau1*X);
                 Gk1=G+Gk0;
                 Gk2=Gk1;
                 Gk3=Gk1;
                 Gk4=Gk1;
        
                 X += dt*(1/tau2*G-1/tau2*SynEv*MaxG/gMax);
                 G += Gk1;
                 t +=dt; 
                 T +=dt;
	
	       // if G has gotten ridiculously small, reset t
	       if (t > pulseTime && G < 0.001E-9) {
		         G = 0;
		         X=0;
		         Gk1=0;
		         Gk2=0;
		         Gk3=0;
	   	         Gk4=0;
                 t = 0;
           } 
           
       //Compute the mean of intervals given the spikes detected in Vsources     
       if (itsComp->Memory[0]){
           if(!sat){
                 SpkEv=1;          
           }
       } 
       
       Gk0=dt*(-(1/T1+1/T2)*Freq-1/T1*Y);
       Y += dt*(1/T2*Freq-1/T2*SpkEv*Freqmax/Fmax);
       Freq += Gk0;
      
       if(1/Freq<=1/Freqmax && 1/(Freq-Gk1)>1/Freqmax) {decision=1; T=0;}
       
       if (Freq>Fsat) sat=1;
       
       if (Freq+Mn< 2*Mn && sat==1) {
		         Freq = 0;
		         Y=0;
		         sat=0;    
       } 
}





