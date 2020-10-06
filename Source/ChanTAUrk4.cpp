/*************************************************************************/
/**********             	   ChanTAUrk4.cpp                *************/
/*************************************************************************/
/****                                                                 ****/
/****             Computing method  and Init (intialisation)          ****/
/****                   for the class ChanTAU                         ****/
/****                                                                 ****/
/*************************************************************************/


#include<iostream>
#include "ChanTAU.h"
#include "1stOrderTMRk4.h"


/* **********  Stationary values for the starting voltage  ********* */


void ChanTAU::Init(const real dt)
{
if (Mexp){M=InfM( E0-rho );}
if (Hexp){H=InfH( E0-rho );}
}

/* **********     Computation of H and M after RK4 steps   ********* */

void ChanTAU::UpdateM( const real dt )
{
	if (Mexp) {
//----> Runge Kutta			
       if(variation){		
		    M = M + Mk1/6 + Mk2/3 + Mk3/3 + Mk4/6 ;		
       }
		
// For persitant currents		
       else{ 
            M=InfM( itsComp->GetV() -rho); 
       }
		
	}
}

void ChanTAU::UpdateH( const real dt )
{
//----> Runge Kutta	
	if (Hexp) {					
		H = H + Hk1/6 + Hk2/3 + Hk3/3 + Hk4/6 ;		
	}
}




/* ************** For the Runge Kutta intermediate steps *********** */

// ******************** k1

void ChanTAU::UpdateMk1( const real dt )
{
	if (Mexp) {
          real v = itsComp->GetV();
		  if(variation){
		  Mk1 = FirstOrderTMRk4(M, TauM(v-rho), InfM(v-rho), dt );	
		  }
          else{ Mk1=InfM(v-rho)-M; 
          }	  
	}
}


void ChanTAU::UpdateHk1( const real dt )
{
	if (Hexp) {

		  real v = itsComp->GetV();
		  Hk1 = FirstOrderTMRk4(H, TauH(v-rho), InfH(v-rho), dt); 
	}
}


// ******************** k2

void ChanTAU::UpdateMk2( const real dt )
{
	if (Mexp) {
          real u = itsComp->GetV()+ itsComp->Vk1/2;
	      if(variation){
		  Mk2 = FirstOrderTMRk4(M+Mk1/2, TauM(u-rho), InfM(u-rho), dt );	
		  }
		  else{ Mk2=InfM(u-rho)-M; 
          }
	}
}


void ChanTAU::UpdateHk2( const real dt )
{
	if (Hexp) {
	
		  real u = itsComp->GetV() + itsComp->Vk1/2;
		  Hk2 = FirstOrderTMRk4(H+Hk1/2, TauH(u-rho), InfH(u-rho), dt );	
		
	}
}

// ******************** k3

void ChanTAU::UpdateMk3( const real dt )
{
	if (Mexp) {
          real u = itsComp->GetV()+ itsComp->Vk2/2;
	      if(variation){
		  Mk3 = FirstOrderTMRk4(M+Mk2/2, TauM(u-rho), InfM(u-rho), dt );	
          }
          else{ Mk3=InfM(u-rho)-M; 
          }
          		
	}
}


void ChanTAU::UpdateHk3( const real dt )
{
	if (Hexp) {
		  real u = itsComp->GetV() + itsComp->Vk2/2;
		  Hk3 = FirstOrderTMRk4(H+Hk2/2, TauH(u-rho), InfH(u-rho), dt );	
		
	}
}


//********************* k4

void ChanTAU::UpdateMk4( const real dt )
{
	if (Mexp) {
          real u = itsComp->GetV()+itsComp->Vk3;
          if(variation){	
		  Mk4 = FirstOrderTMRk4(M+Mk3, TauM(u-rho), InfM(u-rho), dt );	
	      }
	      else{ Mk4=InfM(u-rho)-M; 
          }
	}
}



void ChanTAU::UpdateHk4( const real dt )
{
	if (Hexp) {
	
		  real u = itsComp->GetV() + itsComp->Vk3;
		  Hk4 = FirstOrderTMRk4(H+Hk3, TauH(u-rho), InfH(u-rho), dt );	
		
	}
}
