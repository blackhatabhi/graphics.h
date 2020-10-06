/**************************************************************************

	NoiseI.h												JJS 9/06/95
	
		addition to CONICAL, the Computational Neuroscience Class Library.
		Fonction that generate a white gaussian noise centered around zero with
        standard    
	
	
	Requires:
		math library		-- ANSI math functions, defined in <math.h>
		
**************************************************************************/

#ifndef NOISESOURCE_H
#define NOISESOURCE_H

#include <math.h>
#include<stdlib.h>
#include<time.h>
#ifndef real
#define real double
#endif


// Homogeneous distribution -1 to 1
inline real Var(){return 2*double(rand())/32767-1;}

// Gaussian distribution
inline real NoiseI(real max)
{
	double a1,a2,X,V1,V2, S;
    

do{
    a1=rand();
    V1=2*a1/32767-1;
    a2=rand();
    V2=2*a2/32767-1;
    S= V1*V1 + V2*V2;
}while(S>=1);
   

    
    X= sqrt(-2*log(S) / S) * V1; //bruit blanc normalisé 
    
    return max*X;
}

inline int fact(int i){
   int res=1;
   if(i=0){ return 1;}
   else{ 
     for(int k=2; k<i+1; k++){res=res*k;}
     return res;
   } 
}

inline int NoisePoiss(real m){
   real x;
   real Part=0;
   int r=0;

   x=rand()/32767;
   do{
      Part+=exp(-m)*(pow(m,r)/fact(r));
      r++;
   }while(Part<x);
   
   return r-1;

}

#endif
