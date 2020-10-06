/**************** Channel general Set Up : ChannelStd or TM  ****************/
#ifndef CHANLIST_H
#define CHANLIST_H

#include "ChanStdRk4.h"		    // for Hodgkin-Huxley channels
#include "ChanTM.h"  
#include "AlphaSyn.h"
#include "AlphaSynI.h" 
#include "AlphaSynS.h"  
   
const real ENA = 0.045;			// sodium equilibrium potential 
const real EK = -0.070;			// potassium equilibrium potential 
const real ECA = 0.09;			// calcium equilibrium potential 
const real Eex =0;              // exitation equilibrium potential
const real Ein =-0.07;          // exitation equilibrium potential



const real sig = -0.006;        // Tuning of spikes (XJ Wang) 
const real phi = 200/7;         // Temperature coeff (XJ Wang)




/****************************** Wang XJ 1993 ********************************/

void SetUpNaWangXJChannel( ChanStd &pChan )
{
	// set the equilibrium potential
	pChan.SetE( ENA );

	// set up "M" (activation) gating variable
	pChan.Mexp = 3;
	pChan.variation =0;    // 0 for use of the steady state only. Complete dynamic 1.
	pChan.SetFunc( kStdAlphaM, kLinForm, -phi*0.1E6, -10E-3, -0.030+sig, 0 );
	pChan.SetFunc( kStdBetaM, kExpForm, phi*4.0E3, -18.0E-3, -0.055+sig, 0 );
	
	// set up "H" (inactivation) gating variable
	pChan.Hexp = 1;
	pChan.SetFunc( kStdAlphaH, kExpForm, phi*70.0, -20.0E-3, -0.044+sig, 0 );
	pChan.SetFunc( kStdBetaH, kSigForm, phi*1.0E3, -10.0E-3, -0.014+sig, 0 );
}

void SetUpKWangXJChannel( ChanStd &pChan )
{
	// set the equilibrium potential
	pChan.SetE( EK );

	// set up "M" (activation) gating variable
	pChan.Mexp = 4;
	pChan.SetFunc( kStdAlphaM, kLinForm, -phi*10.0E3, -10.0E-3, -0.034+sig, 0 );
	pChan.SetFunc( kStdBetaM, kExpForm, phi*125.0, -80.0E-3, -0.044+sig, 0 );
	
	// set up "H" (inactivation) gating variable
	pChan.Hexp = 0;

}


void SetUpNaPWangXJChannel( ChanTM &pChan )
{
	// set the equilibrium potential
	pChan.SetE( ENA );

	// set up "M" (activation) gating variable
	pChan.Mexp = 1;
	pChan.variation= 0;
	pChan.SetFunc( kStdInfM, kSigForm, 1, -0.005, -0.051 , 0 );
	
	pChan.Hexp=0;
	
}

void SetUpKs1WangXJChannel( ChanTM &pChan )
{
	// set the equilibrium potential
	pChan.SetE( EK );

	// set up "M" (activation) gating variable
	pChan.Mexp = 1;
	pChan.SetFunc( kStdTauM, kCstForm, 0.010 , 0 , 0 , 0 );
	pChan.SetFunc( kStdInfM, kSigForm, 1 , -0.0065, -0.034 , 0 );
	
	// set up "H" (inactivation) gating variable
	pChan.Hexp = 1;
	pChan.SetFunc( kStdTauH, kSioForm, 0.220 , -0.00685 , -0.0716, 0.200 );
	pChan.SetFunc( kStdInfH, kSigForm, 1 , 0.0066, -0.065 , 0 );
		
}

void SetUpKs2WangXJChannel( ChanTM &pChan )
{
	// set the equilibrium potential
	pChan.SetE( EK );

	// set up "M" (activation) gating variable
	pChan.Mexp = 1;
	pChan.SetFunc( kStdTauM, kCstForm, 0.010 , 0 , 0 , 0 );
	pChan.SetFunc( kStdInfM, kSigForm, 1 , -0.0065, -0.034 , 0 );
	
	// set up "H" (inactivation) gating variable
	pChan.Hexp = 1;
	pChan.SetFunc( kStdTauH, kSioForm, 1.2 , -0.004 , -0.0636, 0.200 );
	pChan.SetFunc( kStdInfH, kSigForm, 1 , 0.0066, -0.065, 0 );	
		
}

/****************************** Bhala Bower 1993 ***************************/


void SetUpNaBhalaChannel( ChanStd &pChan )
{
    pChan.UndoThreshold();
	// set the equilibrium potential
	pChan.SetE( ENA );
    pChan.Setrho(-8E-3); 
   	pChan.variation =1;    // 0 for use of the steady state only. Complete dynamic 1.
	// set up "M" (activation) gating variable
	pChan.Mexp = 3;
	pChan.SetFunc( kStdAlphaM, kLinForm, -320E3, -0.004, -0.042, 0 );
	pChan.SetFunc( kStdBetaM, kLinForm, 280E3, 5E-3, -0.015, 0 );
	
	// set up "H" (inactivation) gating variable
	pChan.Hexp = 1;
	pChan.SetFunc( kStdAlphaH, kExpForm, 128, -18E-3, -0.038, 0 );
	pChan.SetFunc( kStdBetaH, kSigForm, 4E3, -5E-3, -0.015, 0 );
}

void SetUpNaBhalaChannelTres( ChanStd &pChan, real pSlope )
{
    pChan.DoThreshold();
	// set the equilibrium potential
	pChan.SetE( ENA );
    pChan.Setrho(-8E-3);
    pChan.SetSlope(pSlope); 
	// set up "M" (activation) gating variable
	pChan.Mexp = 3;
	pChan.SetFunc( kStdAlphaM, kLinForm, -320E3, -0.004, -0.042, 0 );
	pChan.SetFunc( kStdBetaM, kLinForm, 280E3, 5E-3, -0.015, 0 );
	
	// set up "H" (inactivation) gating variable
	pChan.Hexp = 1;
	pChan.SetFunc( kStdAlphaH, kExpForm, 128, -18E-3, -0.038, 0 );
	pChan.SetFunc( kStdBetaH, kSigForm, 4E3, -5E-3, -0.015, 0 );
}
	
void SetUpKfastChannel( ChanTM &pChan )
{
	// set the equilibrium potential
	pChan.SetE( EK );
	pChan.Setrho(-8E-3);

	// set up "M" (activation) gating variable
	pChan.Mexp = 2;
	pChan.SetFunc( kStdTauM, kKftForm, 0 , 0 , 0 , 0 );
	pChan.SetFunc( kStdInfM, kSigForm, 1 , -0.01046, -0.01324 , 0 );
	
	// set up "H" (inactivation) gating variable
	pChan.Hexp = 1;
	pChan.SetFunc( kStdTauH, kCstForm, 0.05 , 0 , 0 , 0 );
	pChan.SetFunc( kStdInfH, kSioForm, 0.866 , -0.014, -0.006525 , 0.134 );
	
		
}
void SetUpCaBhalaChannel( ChanStd &pChan )
{
	// set the equilibrium potential
	pChan.SetE( ECA );

	// set up "M" (activation) gating variable
	pChan.Mexp = 3;
	pChan.SetFunc( kStdAlphaM, kSigForm, 7500, -7E-3, 0.013, 0 );
	pChan.SetFunc( kStdBetaM, kSigForm, 1650, 4E-3, 0.014, 0 );
	
	// set up "H" (inactivation) gating variable
    pChan.Hexp = 1;
	pChan.SetFunc( kStdAlphaH, kSigForm, 6.8, 12E-3, -0.030, 0 );
	pChan.SetFunc( kStdBetaH, kSigForm, 60, -11E-3, 0, 0 );
	
}

void SetUpKCaBhalaChannel( ChanStd &pChan )
{
	// set the equilibrium potential
	pChan.SetE( EK );

	// set up "M" (activation) gating variable
	pChan.Mexp = 1;
	pChan.SetFunc( kStdAlphaM, kExpForm, 5*0.015, 27E-3, 0.065, 0 );
	pChan.SetFunc( kStdBetaM, kCstForm, 50, 0, 0, 0 );
	
	// set up "H" (inactivation) gating variable
    pChan.Hexp = 0;
	
}




void SetUpKslowChannel( ChanTM &pChan )
{
	// set the equilibrium potential
	pChan.SetE( EK );

	// set up "M" (activation) gating variable
	pChan.Mexp = 2;
	pChan.SetFunc( kStdTauM, kKslForm, 0 , 0 , 0 , 0 );
	pChan.SetFunc( kStdInfM, kSigForm, 1 , -0.01046, -0.01324, 0);
	
	// set up "H" (inactivation) gating variable
	pChan.Hexp = 1;
	pChan.SetFunc( kStdTauH, kCstForm, 0.2 , 0 , 0 , 0 );
	pChan.SetFunc( kStdInfH, kSioForm, 0.866 , -0.014, -0.006525 , 0.134 );
	
		
}

void SetUpABhalaChannel( ChanTM &pChan )
{
	// set the equilibrium potential
	pChan.SetE( EK );

	// set up "M" (activation) gating variable
	pChan.Mexp = 1;
	pChan.SetFunc( kStdTauM, kCstForm, 1E-3, 0, 0, 0 );
	pChan.SetFunc( kStdInfM, kSigForm, 1, -30.0E-3, -0.042, 0 );  //13
	
	// set up "H" (inactivation) gating variable
	pChan.Hexp = 1;
	pChan.SetFunc( kStdTauH, kCstForm, 50E-3, 0, 0, 0 );
	pChan.SetFunc( kStdInfH, kSigForm, 1, 40.0E-3, -0.110, 0 );  //18
}

/****************************** Wang, McKenzie 1996 ***************************/

void SetUpAWangChannel( ChanTM &pChan )
{   // Without the indicated shift (SenseLab ModelDB)
	// set the equilibrium potential
	pChan.SetE( EK );
    
	// set up "M" (activation) gating variable
	pChan.Mexp = 1;
	pChan.SetFunc( kStdTauM, kWangForm, 25E-3, 10E-3, -0.045, 0.75 );
	pChan.SetFunc( kStdInfM, kSigForm, 1, -14.0E-3, 0.0076, 0 );
	
	// set up "H" (inactivation) gating variable
	pChan.Hexp = 1;
	pChan.SetFunc( kStdTauH, kWangForm, 55.5E-3, 5E-3, -0.070, 0.99 );
	pChan.SetFunc( kStdInfH, kSigForm, 1, 6.0E-3, -0.0474, 0 );
}

void SetUpKdWangChannel( ChanTM &pChan )
{   // Without the indicated shift (SenseLab ModelDB)
	// set the equilibrium potential
	pChan.SetE( EK );

	// set up "M" (activation) gating variable
	pChan.Mexp = 1;
	pChan.SetFunc( kStdTauM, kWangForm, 285E-3, 18E-3, -0.050, 0.5 );
	pChan.SetFunc( kStdInfM, kSigForm, 1, -10.0E-3, 0.021, 0 );
	
	// set up H
	
	pChan.Hexp=0;
	
}


/*************************** Huguenard, McCormick 1992 ***********************/


void SetUpA1Channel( ChanTM &pChan )
{   
	pChan.SetE( EK );

	// set up "M" (activation) gating variable
	pChan.Mexp = 4;
	pChan.SetFunc( kStdTauM, kAmForm, 0, 0, 0, 0 );
	pChan.SetFunc( kStdInfM, kSigForm, 1, -8.5E-3, -0.060, 0 );
	
	// set up "H" (inactivation) gating variable
	pChan.Hexp = 1;
	pChan.SetFunc( kStdTauH, kAh1Form, 0, 0, 0, 0);
	pChan.SetFunc( kStdInfH, kSigForm, 1, 6.0E-3, -0.078, 0 );
}

void SetUpA2Channel( ChanTM &pChan )
{
	pChan.SetE( EK );

	// set up "M" (activation) gating variable
	pChan.Mexp = 4;
	pChan.SetFunc( kStdTauM, kAmForm, 0, 0, 0, 0 );
	pChan.SetFunc( kStdInfM, kSigForm, 1, -20E-3, -0.036, 0 );
	
	// set up "H" (inactivation) gating variable
	pChan.Hexp = 1;
	pChan.SetFunc( kStdTauH, kAh2Form, 0, 0, 0, 0);
	pChan.SetFunc( kStdInfH, kSigForm, 1, 6.0E-3, -0.078, 0 );
}



/*********************** Synapses general set up  ***********************/

// Be careful with rise and decay times : check that if they are equal
// you've put this case in AlphaSyn Step method (default : removed)  


void SetUpSynE( AlphaSyn &pSyn,real pTaud, real pTauR, real Tresh  )
{
    pSyn.Vthresh = Tresh;
    pSyn.pulseTime = 0.005;
    pSyn.tau1 = pTauR;      
    pSyn.tau2 = pTaud;
    pSyn.SetE(Eex);

}

void SetUpSynI( AlphaSyn &pSyn, real pTaud, real pTauR, real Tresh )
{
    pSyn.Vthresh = Tresh;
    pSyn.pulseTime = 0.005;
    pSyn.tau1 = pTauR;      
    pSyn.tau2 = pTaud;
    pSyn.SetE(Ein);
 
}

void SetUpSynS( AlphaSynS &pSyn, real pTaud, real pTauR, real Tresh )
{
    pSyn.Vthresh = Tresh;
    pSyn.pulseTime = 0.005;
    pSyn.tau1 = pTauR;      
    pSyn.tau2 = pTaud;
    pSyn.SetE(Ein);
 
}


void SetUpSynI2( AlphaSynI &pSyn, real pTauD, real pTauR, real Tresh )
{
    pSyn.Vthresh = Tresh;
    pSyn.tau1 = pTauR;      
    pSyn.tau2 = pTauD;
    pSyn.SetE(Ein);

}
/*************************** Synaptic noise **********************************/
/*
void SetExitatoryNoise(SynNoise &pSyn){
  pSyn.SetE(Eex);
  pSyn.SetTaus(0.0005,0.010);
  pSyn.SetMean(0.2);
}

void SetInhibitoryNoise(SynNoise &pSyn){
  pSyn.SetE(Ein);
  pSyn.SetTaus(0.0005,0.007);
  pSyn.SetMean(0.2);
}
*/
#endif
