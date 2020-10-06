
// filter the sommation with spikes
	   LFP4[0]=0;
	for(int j=0; j<TMAX/DT-1; j+=1){
       LFP4[j+1]=(1-62.8*DT)*LFP4[j]+62.8*DT*LFP1[j];
	}
	

	   LFP2[int(TMAX/DT)-1]=0;
	for(int j=int(TMAX/DT)-1; j>0; j--){
       LFP2[j-1]=(1-62.8*DT)*LFP2[j]+62.8*DT*LFP4[j];
	}
	
       LFP4[0]=0;
	for(int j=0; j<TMAX/DT-1; j+=1){
       LFP4[j+1]=(1-628*DT)*LFP4[j]-628*DT*(LFP1[j]-LFP2[j]);
	}
	
	   LFP2[int(TMAX/DT)-1]=0;
	for(int j=int(TMAX/DT)-1; j>0; j--){
       LFP2[j-1]=(1-628*DT)*LFP2[j]+628*DT*LFP4[j];
	}
	
	
// filter the sommation without spikes
	   LFP4[0]=0;
	for(int j=0; j<TMAX/DT-1; j+=1){
       LFP4[j+1]=(1-62.8*DT)*LFP4[j]+62.8*DT*LFP3[j];
	}
	

	   LFP5[int(TMAX/DT)-1]=0;
	for(int j=int(TMAX/DT)-1; j>0; j--){
       LFP5[j-1]=(1-62.8*DT)*LFP5[j]+62.8*DT*LFP4[j];
	}
	
		   LFP4[0]=0;
	for(int j=0; j<TMAX/DT-1; j+=1){
       LFP4[j+1]=(1-628*DT)*LFP4[j]-628*DT*(LFP3[j]-LFP5[j]);
	}
	
	   LFP3[int(TMAX/DT)-1]=0;
	for(int j=int(TMAX/DT)-1; j>0; j--){
       LFP3[j-1]=(1-628*DT)*LFP3[j]+628*DT*LFP4[j];
	}




//Detect maxs of LFP
for(int j=0; j<TMAX/DT; j+=1){LFPpic1[j]=0;}
for(int j=0; j<50000; j+=1){tpic[j]=0;}

L=0;
for(int j=0; j<TMAX/DT; j+=1){
       if(LFP2[j]>DA){
            if(LFP2[j]>=LFP2[j-1] && LFP2[j]>=LFP2[j+1]){
                        K=0;
                        for(int n=-Nmax;n<Nmax; n++){ 
                             if(LFP2[j]<LFP2[j+n]){K=1;}                   
                        }
                        if(K==0){LFPpic1[j]=1; tpic[L]=j; L++;}
                        else{LFPpic1[j]=0;}
            }
            
       }
       else{LFPpic1[j]=0;}
}


//mean and variance of LFPs
mLFP1=0;
for (int i=int(Start/DT); i<TSTOP/DT;i++){   
    mLFP1+=LFP2[i]*DT/(TSTOP-Start);   
}

vLFP1=0;
for (int i=int(Start/DT); i<TSTOP/DT;i++){   
    vLFP1+=pow(LFP2[i]-mLFP1,2)*DT/(TSTOP-Start);   
}

mLFP2=0;
for (int i=int(Start/DT); i<TSTOP/DT;i++){   
    mLFP2+=LFP3[i]*DT/(TSTOP-Start);   
}

vLFP2=0;
for (int i=int(Start/DT); i<TSTOP/DT;i++){   
    vLFP2+=pow(LFP3[i]-mLFP2,2)*DT/(TSTOP-Start);   
}




//autocorrelogramme of the LFP

for (int j=0;j<int(lcorre/DT);j++){  
    autocL[j]=0;   
}


for (int j=0;j<int(lcorre/DT);j++){
    for (int i=int(Start/DT); i<TSTOP/DT-j;i++){   
        autocL[j]+=(LFP2[i]-mLFP1)*(LFP2[i+j]-mLFP1)*DT/((TSTOP-Start)-j*DT)/vLFP1;   
    }
}

Maxx=0;
F0=0;

//init
for (int j=int(0.01/DT);j<int(0.05/DT);j++){    
    if(autocL[j]>=autocL[j+1] && autocL[j]>=autocL[j-1]){
        if(Maxx<autocL[j]){Maxx=autocL[j]; F0=1/(DT*j);}
    }    
}

Results<<F0<<DELIM<<Maxx<<DELIM;



//Compute the phase of spikes and synchronization index 1

Spcount=0;
Scos=0; Ssin=0;

for(int i=1;i<L;i++){
    if(tpic[i]-tpic[i-1]<Nmin && tpic[i-1]>int(Start/DT)){
        for(int j=tpic[i-1];j<tpic[i];j++){
            if(gRaster[j]==1){
                        Ph=2*3.141592653589793238462*(j-tpic[i-1])/(tpic[i]-tpic[i-1]);
                        Scos+=cos(Ph); Ssin+=sin(Ph); 
                        Spcount++;
            }    
        } 
    }
}


Scos=Scos/Spcount;
Ssin=Ssin/Spcount;
index1=sqrt(pow(Ssin,2)+pow(Scos,2));
if(Scos>=0){phase=180/3.141592653589793238462*atan(Ssin/Scos);}
else{phase=180+180/3.141592653589793238462*atan(Ssin/Scos);}

Sp=Spcount;
Results<<index1<<DELIM<<1/sqrt(Sp)<<DELIM<<phase<<DELIM<<Spcount<<DELIM;




//Number of spike per bin and second synchronisation index
for (int i=0; i<TMAX/tbin;i++){   
    Psth[i]=0;   
}

for (int i=0; i<TMAX/tbin;i++){
    for(int j=0;j<bin;j++){
        Psth[i]+=gRaster[i*bin+j];
    }    
}

mPsth=0;
for (int i=int(Start/tbin); i<TMAX/tbin;i++){   
    mPsth+=Psth[i]*tbin/(TMAX-Start);   
}


index2=0;
for (int i=int(Start/tbin); i<TMAX/tbin;i++){   
    index2+=pow(Psth[i],2)*tbin/((TMAX-Start)*pow(mPsth,2));  
}

Results<<mPsth<<DELIM<<index2<<DELIM;
Results<<sqrt(vLFP1)<<DELIM<<sqrt(vLFP2)<<DELIM;



//autocorrelogramme of the psth

for (int j=0;j<int(lcorre/tbin);j++){  
    autoc[j]=0;   
}
for (int j=0;j<int(lcorre/tbin);j++){
    for (int i=int(Start/tbin); i<TMAX/tbin-j;i++){   
        autoc[j]+=(Psth[i]-mPsth)*(Psth[i+j]-mPsth)*tbin/((TMAX-Start)-j*tbin);   
    }
}

vPsth=0;
for (int i=int(Start/tbin); i<TMAX/tbin;i++){   
    vPsth+=pow(Psth[i]-mPsth,2)*tbin/(TMAX-Start);
}
 

for (int j=0;j<int(lcorre/tbin);j++){  
    autoc[j]=autoc[j]/vPsth;   
}

//fitting

Maxx=0;
F0=0;
//init
for (int j=int(0.01/tbin);j<int(0.05/tbin);j++){    
    if(autoc[j]>=autoc[j+1] && autoc[j]>=autoc[j-1]){
        if(Maxx<autoc[j]){Maxx=autoc[j]; F0=1/(tbin*j);}
    }    
}

F=F0;
Results<<F0<<DELIM<<Maxx<<DELIM;

for(int h=0;h<100;h++){
    fitvect[h]=fit(autoc,h*0.001,F,50);
}

Minn=100000;
for (int j=0;j<100;j++){    
        if(Minn>fitvect[j]){Minn=fitvect[j]; tau=j*0.001;}      
}
Results<<tau<<DELIM<<Minn<<DELIM;

//loops

for(int i=0; i<5;i++){

for(real h=-50;h<50;h++){
    fitvect[int(50+h)]=fit(autoc,tau,F*(1+h/100),50);
}

Minn=100000;
F1=F;
for (real j=-50;j<50;j++){    
    if(Minn>fitvect[int(50+j)]){Minn=fitvect[int(50+j)]; F=F1*(1+j/100);}   
}

for(real h=-50;h<50;h++){
    fitvect[int(50+h)]=fit(autoc,0.001*(50+h),F,50);
}

Minn=100000;
tau1=tau;
for (real j=-50;j<50;j++){    
        if(Minn>fitvect[int(50+j)]){Minn=fitvect[int(50+j)]; tau=(50+j)*0.001;}  
}

}  //i

Results<<F<<DELIM<<tau<<DELIM<<Minn<<DELIM;



Minn=100000;
real fitre;
for(int j=0;j<100;j++){
for(int h=0;h<100;h++){
    fitre=fit(autoc,h*0.001,j*1,50);
    if(Minn>fitre){Minn=fitre; F=j*1; tau=h*0.001;}
}
}

Results<<F<<DELIM<<tau<<DELIM<<Minn<<endl;

stringstream Ss;
	Ss<<"Corre"<<a<<".txt";
	Ss>>b;
    ofstream cor(b);
    
    for(int i=0; i<lcorre/DT;i++){
        cor<<autocL[i]<</*DELIM<<exp(-i*0.002/tau)*cos(2*3.141592653589793238462*F*i*0.002)<<*/endl;
    }
    cor.close();

