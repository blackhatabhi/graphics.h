#ifndef PARAM_H
#define PARAM_H


/************** Defines some global paramaters -- all in SI units *************/

//Simulation

const real TMAX = 1;            //simulation time (sec)
const real DT   = 40E-6;	    //simulation time step (sec)
const int Nstep = 1+int(TMAX/DT); //number of steps

// Cells properties  
const real RM = 10;		        // specific membrane resistance (ohm m^2)
const real CM = 0.01;			// specific membrane capacitance (farad/m^2)
const real EREST = -0.0665;	    // resting membrane potential (volts)
const real ELEAK = -0.0665;	    // "leak" potential (volts)
const real Area=3E-10;          // m^2 

real gA=100;                    //Conductance KA  (Siemens/ m^2)
real gNa=500;                   //Conductance Sodium 
real gK=900;                    //Conductance delayed rectifier
real gKs=310;                   //Conductance conductance potassium slow 
real gNaP=1.1;                  //Conductance sodium persistant 
real DeltaG=0.5;                  //Max variation in conductances (%) 
real Slop=0.0001;

// Input properties
real gInput=30;                 //Tuft synaptic conductance (Siemens / m^2)
const real DeltaGI=0;         //Variation of in amplitudes    (%)
real InpR =0.03;                //Input decay and rise  
real InpD =0.3;             

// Mitral cells
const int NetSize=10;            // Size of the square network in number of cell
const int Ncell=NetSize*NetSize; // Number of cells

//Synapses propeties
real Threshold=-0.03;            // Voltage for triggering synapse

//Inhibition properties
real Ratio=0;                   // ratio of type 1 and 2 inhibition
// single Event;
real P0=0.0005;
real gSingI=0.2;
real taudecay=0.01;
real taurise=0.0002;
//Type1
real gI=0.02;                      //mean conductance (S/m^2) for lateral 
real SgI=0.2;                    //and self Inhibition
real Li=5;                //typical length for inhibitory arborization (nbr of cells)
real TaudI=0.05;                // decay time of Inhibition 
real TaurI=0.0002;               // rise time
real LatI=0.0005;                // Latency
real STaudI=0.1;                // decay time of Inhibition 
real STaurI=0.0002;               // rise time
real SLatI=0.0005;                // Latency
//Type2
real TaudI2=0.01;                // decay time of Inhibition 
real TaurI2=0.003;               // rise time
real Fmax=40;
real Fsat=100;
real MeanRate=1/2;
real tfd=0.1;
real tfr=0.015;

//Excitation properties
real gE=0;                      //mean conductance (S/m^2) for lateral  
real SgE=0;                     //and self Exitation 
const real Le=4;                //typical length for exitarory arborization (nbr of cells)
real TaudE=0.008;               // decay time of Excitation 
real TaurE=0.0005;               // rise time
real LatE=0.0014;                // Latency




#endif
