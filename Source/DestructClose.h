/************************** Clear objects *********************************/ 

for(int m1=0; m1<NetSize; m1+=1){
   for(int k1=0; k1<NetSize; k1+=1){  
            delete input[m1][k1];
   } 
}

   // Clear Inhibition  
for(int m1=0; m1<NetSize; m1++){
    for(int k1=0; k1<NetSize; k1++){
        for(int m2=0; m2<NetSize; m2++){
           for(int k2=0; k2<NetSize; k2++){                                   
            delete SynS[m1][k1][m2][k2];
           }
        }
    }
}

    
  // Clear Exitation 
for(int m1=0; m1<NetSize; m1++){
    for(int k1=0; k1<NetSize; k1++){
        for(int m2=0; m2<NetSize; m2++){
           for(int k2=0; k2<NetSize; k2++){
          if(Je[m1][k1][m2][k2]>0.005){                                
            delete SynE[m1][k1][m2][k2];
          }  
       }
    }
  }
} 

/******************************* writes time after simulation **********************/

// time after simulation	
   time_t rawtime;
   struct tm * timeinfo;

   time ( &rawtime );
   timeinfo = localtime ( &rawtime );
   exfileP<<"Date and time after simulation are :"<< asctime (timeinfo);
   
//close file 
   exfileP.close();	
