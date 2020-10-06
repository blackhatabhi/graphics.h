/*************************************************************************/
/**********             	   ChanABrk4.cpp                 *************/
/*************************************************************************/
/****                                                                 ****/
/****             Computing method  and Init (intialisation)          ****/
/****                   for the class ChanAB                          ****/
/****                                                                 ****/
/*************************************************************************/



#include<iostream>
#include "ChanABrk4.h"
#include "1stOrderRk4.h"



void ChanAB::Init(const real dt)
{
if (Mexp){M = AlphaM( E0-rho)/( BetaM(E0-rho)+AlphaM(E0-rho) );}
if(Hexp){H = AlphaH( E0-rho)/( BetaH(E0-rho)+AlphaH(E0-rho) );}
}


/* *********** Methods for updating H and M after RK4 steps ********* */

void ChanAB::UpdateM( const real dt )
{
	if (Mexp) {
		real v=itsComp->GetV();
		real dv;
//allows Channels with stationary kinetic		
		if (variation){
		M = M + Mk1/6 + Mk2/3 + Mk3/3 + Mk4/6 ;}
		else{M=AlphaM(v-rhomod(v,dv,Max,Slope))/(AlphaM(v-rhomod(v,dv,Max,Slope))+BetaM(v-rhomod(v,dv,Max,Slope)));}	
	}
}

void ChanAB::UpdateH( const real dt )
{
	if (Hexp) {	
		H = H + Hk1/6 + Hk2/3 + Hk3/3 + Hk4/6 ;	
	}
}

/* **************  For the Runge Kutta intermediate steps  *********** */

// k1

void ChanAB::UpdateMk1( const real dt )
{
	if (Mexp) {
	
	
		  // compute M using first-order kinetics:
		  //	dM/dt = alpha*(1-M) - beta*M
		  real v = itsComp->GetV();
		  real dv=itsComp->dV;
		  if(variation){
		  Mk1 = FirstOrderRk4(M, AlphaM(v-rhomod(v,dv,Max,Slope)), BetaM(v-rhomod(v,dv,Max,Slope)), dt );	
          }
          else{Mk1=AlphaM(v-rhomod(v,dv,Max,Slope))/(AlphaM(v-rhomod(v,dv,Max,Slope))+BetaM(v-rhomod(v,dv,Max,Slope)))-M;} 		
		  
	}
}


void ChanAB::UpdateHk1( const real dt )
{
	if (Hexp) {
	
		  real v = itsComp->GetV();
		  real dv=itsComp->dV;
		  Hk1 = FirstOrderRk4(H, AlphaH(v-rhomod(v,dv,Max,Slope)), BetaH(v-rhomod(v,dv,Max,Slope)), dt);	

          
	}
}


// k2

void ChanAB::UpdateMk2( const real dt )
{
	if (Mexp) {
	
	
		  // compute M using first-order kinetics:
		  //	dM/dt = alpha*(1-M) - beta*M
		  
		  real u = itsComp->GetV()+ itsComp->Vk1/2;
		  real dv=itsComp->dV;
          if(variation){
		  Mk2 = FirstOrderRk4(M+Mk1/2, AlphaM(u-rhomod(u,dv,Max,Slope)), BetaM(u-rhomod(u,dv,Max,Slope)), dt );	
	      }
	      else{Mk2=AlphaM(u-rhomod(u,dv,Max,Slope))/(AlphaM(u-rhomod(u,dv,Max,Slope))+BetaM(u-rhomod(u,dv,Max,Slope)))-M;}
	}
}


void ChanAB::UpdateHk2( const real dt )
{
	if (Hexp) {
          real dv=itsComp->dV;
		  real u = itsComp->GetV() + itsComp->Vk1/2;
		  Hk2 = FirstOrderRk4(H+Hk1/2, AlphaH(u-rhomod(u,dv,Max,Slope)), BetaH(u-rhomod(u,dv,Max,Slope)), dt );	
		
	}
}

// k3

void ChanAB::UpdateMk3( const real dt )
{
	if (Mexp) {
	
	
		  // compute M using first-order kinetics:
		  //	dM/dt = alpha*(1-M) - beta*M
		  real u = itsComp->GetV()+ itsComp->Vk2/2;
		  real dv=itsComp->dV;
		  if(variation){
		  Mk3 = FirstOrderRk4(M+Mk2/2, AlphaM(u-rhomod(u,dv,Max,Slope)), BetaM(u-rhomod(u,dv,Max,Slope)), dt );	
	      }
          else{Mk3=AlphaM(u-rhomod(u,dv,Max,Slope))/(AlphaM(u-rhomod(u,dv,Max,Slope))+BetaM(u-rhomod(u,dv,Max,Slope)))-M;} 
	}
}


void ChanAB::UpdateHk3( const real dt )
{
	if (Hexp) {
	
		  real u = itsComp->GetV() + itsComp->Vk2/2;
		  real dv=itsComp->dV;
		  Hk3 = FirstOrderRk4(H+Hk2/2, AlphaH(u-rhomod(u,dv,Max,Slope)), BetaH(u-rhomod(u,dv,Max,Slope)), dt );	
	
	}
}


// k4

void ChanAB::UpdateMk4( const real dt )
{
	if (Mexp) {
	
		  real u = itsComp->GetV()+itsComp->Vk3;
		  real dv=itsComp->dV;
		  if (variation){
		  Mk4 = FirstOrderRk4(M+Mk3, AlphaM(u-rhomod(u,dv,Max,Slope)), BetaM(u-rhomod(u,dv,Max,Slope)), dt );	
	      }
	      else{Mk4=AlphaM(u-rhomod(u,dv,Max,Slope))/(AlphaM(u-rhomod(u,dv,Max,Slope))+BetaM(u-rhomod(u,dv,Max,Slope)))-M;}
	}
}


void ChanAB::UpdateHk4( const real dt )
{
	if (Hexp) {
	
		  real u = itsComp->GetV() + itsComp->Vk3;
		  real dv=itsComp->dV;
		  Hk4 = FirstOrderRk4(H+Hk3, AlphaH(u-rhomod(u,dv,Max,Slope)), BetaH(u-rhomod(u,dv,Max,Slope)), dt );	
	
	}
}
