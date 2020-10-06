/*************************************************************************/
/**********             	   CmpprtmntRk4.cpp              *************/
/*************************************************************************/
/****                                                                 ****/
/****             Computing method  and Init (intialisation)          ****/
/****                   for the class Compartment                     ****/
/****                                                                 ****/
/*************************************************************************/





#include<iostream.h>
#include "CmprtmntRk4.h"
#include "CurrentRk4.h"
#include <math.h>
#include "NoiseSource.h"

/* ***************** Integrate stoch. synaptic events ********************* */
real GetX(real GI, real X, real P, real tau1, real tau2, real gMax, real MaxG, real dt){
    real Ev=0;
    if((1+Var())/2<P-floor(P)){
        Ev=1+floor(P);
    }
    X += dt*(1/tau2*GI-1/tau2*Ev*MaxG/gMax);
    return X;
}

real GetGI(real GI, real X, real tau1, real tau2, real dt){
    GI+=dt*(-(1/tau1+1/tau2)*GI-1/tau1*X);
    return GI;
}


/* ***************************   Constructor   ************************** */
Compartment::Compartment( void )
{
	// set variables to default values
	// LATER: get these from some preferences thing somewhere
	Gm  = 1;
	EGm = Gm * -0.070;
	Cm = 1;
	V[0] = V[1] = 0;
	X=0;
	GI=0;
   
}

/* ****************************  Initiation  *************************** */

void Compartment::Init( const real dt )
{
	//Sets the queue to resting potential : -70 mV
    for(int m=0; m<200; m++){Memory[m]=0;}
    dV=0;
    gMaxI=GetgMax(dt);
    X=0;
	GI=0;	
	
}


/* ****************************  General step  *************************** */

void Compartment::Step( const real dt )
{
	// This is the routine which actually calculates the new value of V.
	// Runge Kutta last step
	
	
	
	
    int curIdx = itsMaster->GetCurIdx();
	V[!curIdx] = V[curIdx] + Vk1/6 + Vk2/3 + Vk3/3 + Vk4/6; 
	dV=Vk1/6 + Vk2/3 + Vk3/3 + Vk4/6;
	
	
	for(int m=200-2; m>=0; m-- ){Memory[m+1]=Memory[m];}
	
    if (V[!curIdx]>-0.03 && V[curIdx]<=-0.03) {Memory[0]=1;}
	else {Memory[0]=0;}
	
	
}


/* ***************** Runge Kutta step function definition **************** */



                   /************ Step 1  **************/

void Compartment::Stepk1( const real dt )
{
    real Ak1 = EGm, Bk1 = Gm;
    
    for (CurrentNode *ln = itsCurrentList; ln; ln = ln->itsNext) {
		// note: this is a lot of dereferencing... can this be streamlined more?
		Ak1 += ln->itsCurrent->GetEG();
		Bk1 += ln->itsCurrent->G;
		
    }
    
    Ak1 += EI*GI;
    Bk1 += GI;
    
   int curIdx = itsMaster->GetCurIdx();
	Vk1 = -1/Cm *( V[curIdx]*Bk1 - Ak1)*dt;       
}

                   /************ Step 2  **************/

void Compartment::Stepk2( const real dt )
{
    
    real Ak2 = EGm, Bk2 = Gm;
    P=P0;
    for (CurrentNode *ln = itsCurrentList; ln; ln = ln->itsNext) {
		Ak2 += ln->itsCurrent->GetEGk1();
		Bk2 += ln->itsCurrent->Gk1;
		P+= ln->itsCurrent->GetPr();
    }
    
    GI=GetGI(GI,X, tau1, tau2, dt);
    X=GetX(GI,X,P, tau1, tau2, gMaxI, MaxGI,dt);
    Ak2 += EI*GI;
    Bk2 += GI;
    int curIdx = itsMaster->GetCurIdx();
    Vk2 = -1/Cm *((V[curIdx]+Vk1/2)*Bk2 - Ak2)*dt; 
}

                   /************ Step 3  **************/

void Compartment::Stepk3( const real dt )
{
    real Ak3 = EGm, Bk3 = Gm;
    for (CurrentNode *ln = itsCurrentList; ln; ln = ln->itsNext) {
		
		Ak3 += ln->itsCurrent->GetEGk2();
		Bk3 += ln->itsCurrent->Gk2;
    }
    Ak3 += EI*GI;
    Bk3 += GI;
     int curIdx = itsMaster->GetCurIdx();
     Vk3 = -1/Cm * ((V[curIdx]+Vk2/2)*Bk3 - Ak3)*dt;    
}

                   /************ Step 4  **************/

void Compartment::Stepk4( const real dt )
{
     real Ak4 = EGm, Bk4 = Gm;
    for (CurrentNode *ln = itsCurrentList; ln; ln = ln->itsNext) {
		
		Ak4 += ln->itsCurrent->GetEGk3();
		Bk4 += ln->itsCurrent->Gk3;
    }
    Ak4 += EI*GI;
    Bk4 += GI;
     int curIdx = itsMaster->GetCurIdx();    
     Vk4 = -1/Cm * ((V[curIdx]+Vk3)*Bk4 - Ak4)*dt;   
}
