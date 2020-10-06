const real tbin=0.002;
const real lcorre=0.1;
const real TSTOP=TMAX-0.1;

real Start=0.2;
real DA=0.02;
int Nmax=int(0.01/DT);
int Nmin=int(0.03/DT);

int K,L,Spcount;
int LFPpic1[Nstep];
int tpic[50000];
real Ph;
real Sp, Scos, Ssin, index1, phase, index2, vPsth, mPsth, mLFP1, vLFP1, mLFP2, vLFP2;

int bin=int(tbin/DT);
real Psth[int(TMAX/tbin)];

real autoc[int(lcorre/tbin)];
real autocL[int(lcorre/DT)];
real fitvect[100];
real Maxx, Minn, F0, F1, tau1, F, tau;

real fit(real t[], real tau, real f, int size){
    real s=0; 
    for (int i=0; i<size; i++){
        s+=pow(t[i]-exp(-i*0.002/tau)*cos(2*3.141592653589793238462*f*i*0.002),2);    
    }
    return s;
}   
