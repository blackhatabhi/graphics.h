/**************************************************************************

	Input.h													JJS 24/03/2003
	
		addition to CONICAL, the Computational Neuroscience Class Library
	
	An Input is a Current source in Sink. Its conductance 
    is computed trough time from a pre-entered function. 
    It is an improvement of the step Injector adapted to olfactory inputs.

	Requires:
		Channel			-- base class
**************************************************************************/

#ifndef INPUT_H
#define INPUT_H

#include "ChannelRk4.h"
#include "NoiseSource.h"


class Input : public Channel
{
  public:

	Input( VSink *pTo, real pTau1, real pTau2, real pAmp )				// constructor
	: Channel( pTo, 0),Tau1(pTau1), Tau2(pTau2),Start(0.1) {SetAmp(pAmp);}
	
	virtual void Init(const real dt){
	t=0;
	Start=Start+0.001*Var();
    }
	
	virtual void Step(const real dt){                                   //stepper
        t+=dt;                 
        if(t<Start){G=0;Gk1=0;}
        else {
           G=Amplitude*(1-exp(-(t-Start)/Tau1));
           Gk0=Amplitude*dt*(1/Tau1*exp(-(t-Start)/Tau1));
           Gk1=G+Gk0;
           Gk2=Gk1; 
           Gk3=Gk2; 
           Gk4=Gk3;   
        }
        //if(t>2){t=0;}
    }  
     
    virtual void SetAmp(real pamp){Amplitude=pamp*GetgMax();
                                   t=0;  }
    real GetAmp(){return Amplitude/GetgMax();}                               
                                   
   	real GetgMax(){                   
        real dtau = Tau1-Tau2;
        return  1;   
    }
              
                                		
	virtual real GetEG( void ) const { return E*G; }   // inspectors
	
    virtual real GetEGk1(void) const { return E*Gk1; }   // inspectors Runge Kutta
	virtual real GetEGk2(void) const { return E*Gk2; }
	virtual real GetEGk3(void) const { return E*Gk3; }
	virtual real GetEGk4(void) const { return E*Gk4; }
	
	
	real Gk0;
	
  protected:
	real t;
	real Tau1, Tau2;
	real Amplitude;
	real Start;
};

#endif
