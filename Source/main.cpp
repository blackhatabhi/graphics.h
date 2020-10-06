
#include <iostream.h>       // for output
#include<fstream.h>         // for file output
#include "sstream.h"        // for string output
#include <string>


#include "CmprtmntRk4.h"    // for cylindrical compartment		    
#include "CurrentRk4.h"

#include "Chanlist.h"       // my library of ion channels  
#include "param.h"          // file for all parameters 

#include "Injector.h"		// for current injection
#include "Input.h"   
#include "Noise.h"          // Cell noise generator
#include "NoiseSource.h"    // Header file for all kind of noise variable

#include <math.h> 
#include<stdlib.h>
#include<time.h>          

#ifdef macintosh
#include <console.h>		// for ccommand() function
#endif



// Reading files
const int read = 0;

//Cells
Compartment cell[NetSize][NetSize];
Input *input[NetSize][NetSize];       // Their inputs

// Connectivity

AlphaSynS *SynS[NetSize][NetSize][NetSize][NetSize];     
real Ji[NetSize][NetSize][NetSize][NetSize];              //synaptic strength (Inhibitory)
    

AlphaSyn *SynE[NetSize][NetSize][NetSize][NetSize];        
real Je[NetSize][NetSize][NetSize][NetSize];              //synaptic strength (Exitatory)

 
// Output files

const int M1=0;                                           //Index of the cells that are recorded
const int K1=0; 
const int M2=0;
const int K2=1;

real LFP1[Nstep];                                         //LFP traces
real LFP2[Nstep];
real LFP3[Nstep];
real LFP4[Nstep];
real LFP5[Nstep];
int counterLFP3[NetSize][NetSize];

real Raster[NetSize*NetSize][1000];                        // raster of spikes
int gRaster[Nstep];                                       // global raster
int SynRaster[Nstep];
int Rcount[Ncell]; 
real tableV[3][Nstep];                                    //For ouputs  
real Vmem[NetSize][NetSize];                             
int count = 0;                                            //Counter for outputs

const char DELIM = '\t';		                          //field delimiter for output

char a[30]="réseau";                                      //Generic name of the output files
char b[100]="réseau.txt";                                 //Char variable for output files

real variable[11];
#include "LFPfiltDecl.h"

/********************* Method for creating mitral cells *********************/
 

void MakeMitral(Compartment *mitral){
    
             
	mitral->SetV( EREST );		// start at rest
    mitral->Gm=Area/RM;
    mitral->Cm=Area*CM;
    mitral->EGm=ELEAK*Area/RM;
    mitral->MaxGI=gSingI*Area;
    mitral->P0=P0;
    mitral->tau1=taurise;
    mitral->tau2=taudecay;
    mitral->EI=Ein;
    
    ChanStd *NaChan = new ChanStd( mitral, gNa*(1+Var()*DeltaG)*Area);
    //SetUpNaBhalaChannelTres( *NaChan,Slop );
	SetUpNaBhalaChannel( *NaChan );
    
    ChanTM  *KfstChan = new ChanTM( mitral, gK*(1+Var()*DeltaG)*Area );
	SetUpKfastChannel( *KfstChan );
    
    ChanTM *NaPChan = new ChanTM( mitral, gNaP*(1+Var()*DeltaG)*Area );
    SetUpNaPWangXJChannel( *NaPChan );
     
    ChanTM *Ks1Chan = new ChanTM( mitral, gKs*(1+Var()*DeltaG)*Area );
    SetUpKs1WangXJChannel( *Ks1Chan );
     
    ChanTM *AChan = new ChanTM( mitral, gA*(1+Var()*DeltaG)*Area );
    SetUpAWangChannel( *AChan );
   
    Noise *noise = new Noise( mitral );
    noise->SetAmplitude(0.008*Area); 
    
}

void SetMitral(Compartment *mitral){
    
             
	mitral->SetV( EREST );		// start at rest
    mitral->Gm=Area/RM;
    mitral->Cm=Area*CM;
    mitral->EGm=ELEAK*Area/RM;
    mitral->MaxGI=gSingI*Area;
    mitral->P0=P0;
    mitral->tau1=taurise;
    mitral->tau2=taudecay;
    mitral->EI=Ein;
 }

/**************************************************************************/
/*************************     Main Program     ***************************/
/**************************************************************************/


main( int argc, char **argv )
{
/************************* Initiates random numbers *********************/
    
    srand(time(NULL));

/*** give Mac Symantec C++ users a chance to redirect input & output  ***/
	#ifdef macintosh
		ccommand( &argv );
	#endif

/************* Create the cells; add their channels and their current injection ***************/   
for(int m1=0; m1<NetSize; m1+=1){      
     for(int k1=0; k1<NetSize; k1+=1){  
         MakeMitral(&cell[m1][k1]); 
     }
}    


/********************************  Preparing Results output file  ***********************/
 	stringstream ss;
	ss<<"Results"<<".txt";
	ss>>b;
    ofstream Results(b);    
    
    Results<<"fLFP"<<DELIM<<"LFPOscIndex"<<DELIM;
    Results<<"index1"<<DELIM<<"1/sqrt(N)"<<DELIM<<"phase"<<DELIM<<"N"<<DELIM;     
    Results<<"mPsth"<<DELIM<<"index2"<<DELIM;
    Results<<"vLFP1"<<DELIM<<"vLFP2"<<DELIM;
    Results<<"F0"<<DELIM<<"index3"<<DELIM;
    Results<<"tau"<<DELIM<<"Minn1"<<DELIM;
    Results<<"F"<<DELIM<<"tau"<<DELIM<<"Minn2"<<DELIM;         
    Results<<"F"<<DELIM<<"tau"<<DELIM<<"Minn3"<<endl;                     
                                                	
/********************************  Preparing Simulations and running...  ***********************/

variable[0]=0;
variable[1]=.1;
variable[2]=.5;
variable[3]=1;
variable[4]=2;
variable[5]=4;
variable[6]=6;
variable[7]=8;



for(int f=0;f<8; f++){ 
for(int o=0; o<10;o++){

gI=0.03;
gSingI=0.007*variable[f];
SgI=gI*10;
gE=0;

for(int m1=0; m1<NetSize; m1+=1){      
     for(int k1=0; k1<NetSize; k1+=1){  
         SetMitral(&cell[m1][k1]); 
     }
}  

/*********************** defining simulation name  *************************/
stringstream s0;
   s0<<"Res"<<"I"<<100*gI<<"SI"<<100*gSingI;
   s0>>a;
   
/***********************  Builds the Network   ************************/
#include "Construction.h" 
/***********************  A file for all parameters  ************************/  
#include "PropOut.h"

	
   
   
   
   /*********************************************************************/	
   /*****             Runs the simulation for all cells             *****/
   /*****                                                           *****/
   /*********************************************************************/


    
             
// Initializes : this is question of life and death. Many of the steppers  
// do not work without initialization
          for(int m1=0; m1<NetSize; m1+=1){
              for(int k1=0; k1<NetSize; k1++){        
                  counterLFP3[m1][k1]=500;
              }
          }
      
          gStepmaster.doStepinit(DT);  
          count=0;
          
          for(int k1=0; k1<TMAX/DT; k1++){
               LFP1[k1]=0;
               LFP2[k1]=0;
               LFP3[k1]=0;
               gRaster[k1]=0;
               SynRaster[k1]=0;
   	      }
   	      
   	      for(int k1=0; k1<NetSize*NetSize;k1++){
               Rcount[k1]=0;
               for(int m=0; m<100; m++){
                   Raster[k1][m]=0;              
               }  	      
   	      }
   	      
//Computes each time step DT record every DT. 
//This is the core of the simulation !!!

	for (real T=0; T<TMAX; T += DT) {
	
		  gStepmaster.doStepk1(DT);
          gStepmaster.doStepk2(DT);
          gStepmaster.doStepk3(DT);
          gStepmaster.doStepk4(DT);
          gStepmaster.StepAll(DT);          
      
        tableV[0][count]= 1000*cell[M1][K1].GetV();
        tableV[1][count]= 1000*cell[M2][K2].GetV();
 
        
  //Analysis in the step
             
        
        for(int m1=0; m1<NetSize; m1++){           // Summate all potentials for the LFP
           for(int k1=0; k1<NetSize; k1++){
             LFP1[count]+=10*(cell[m1][k1].GetV()+0.07);
             counterLFP3[m1][k1]++;
                      
             if(cell[m1][k1].GetV()>-0.054 && Vmem[m1][k1]<-0.054){
               counterLFP3[m1][k1]=0;   
             }
             
             if(counterLFP3[m1][k1]<500){      // for 20ms
               LFP3[count]+=10*0.014;  
             }
             else{       
               LFP3[count]+=10*(cell[m1][k1].GetV()+0.07);   
             } 
                
             
             if(cell[m1][k1].Memory[0]>0){
                Raster[k1+NetSize*m1][Rcount[k1+NetSize*m1]]=count*DT;
                gRaster[count]++;
                Rcount[k1+NetSize*m1]++;
             }
             
             Vmem[m1][k1]=cell[m1][k1].GetV();
                   
                                        
           }
        }
        count+=1;
    }
    
        
/******************   Writes all recorded traces in a  file    ****************/
    stringstream s4;	
    s4<<a<<".txt";	
	s4>>b;
	ofstream exfile(b);
	
#include "LFPfilter.h"
	
	for(int j=0; j<TMAX/DT; j+=1){
	    exfile << tableV[0][j] << DELIM
        <<tableV[1][j]<<DELIM
        <<LFP2[j]<<DELIM
        <<LFP1[j]<<DELIM
        <<gRaster[j]<<DELIM
        <<LFPpic1[j]//LFP3[j]
        <<endl;
	}
	
	exfile.close();
	
	
	stringstream s5;
	s5<<"Rast"<<a<<".txt";
	s5>>b;
	
	ofstream exfileR(b);
	
	
	for(int j=0; j<Ncell; j+=1){
	    for(int k=0; k<Rcount[j]; k++){
	       exfileR<<Raster[j][k]<<DELIM;
	    }
        exfileR<<endl;
	}
	
	exfileR.close();

    count=0;
    for(int k1=0; k1<Ncell;k1++){
               Rcount[k1]=0;
               for(int m=0; m<100; m++){
                   Raster[k1][m]=0;              
               }  	      
   	      }
   	      
   
   
/************************** Clear objects *********************************/ 

#include "DestructClose.h"

	
}//o
}//f


Results.close();

return 1;
}


