//***********************************************************************//
//*********************** Builds the network ****************************//
//***********************************************************************//



/******************** Creates input distribution ************************/

if(read==0){
     for(int m1=0; m1<NetSize; m1+=1){
       for(int k1=0; k1<NetSize; k1++){  
          input[m1][k1]= new Input(&cell[m1][k1],InpR,InpD,gInput*(1+Var()*DeltaGI)*Area);
          input[m1][k1]->SetE(0);              // reversal potential for glutamatergic input synapses
          cell[m1][k1].SetV(EREST);	           // Start at rest
       }
    }

}

else
{
     int Idx;
     Idx=0;
     real data[Ncell];           // file contains an undermined number of integer values
     ifstream fin;     // declare stream variable name

     fin.open("InpResIdI7E0.txt",ios::in);    // open file
     assert (!fin.fail( ));     
     fin >> data[Idx];        // get first number from the file (priming the input statement)
                              // You must attempt to read info prior to an eof( ) test.
     while (!fin.eof( ))      //if not at end of file, continue reading numbers
     {
          Idx++;
          fin >> data[Idx];         //get next number from file
     } 
     fin.close( );       //close file 
     //assert(!fin.fail( ));
     
    for(int m1=0; m1<NetSize; m1+=1){
       for(int k1=0; k1<NetSize; k1++){  
        input[m1][k1]= new Input(&cell[m1][k1],InpR,InpD,data[k1+10*m1]*Area);
        input[m1][k1]->SetE(0);            // reversal potential for glutamatergic input synapses
        cell[m1][k1].SetV(EREST);	       // Start at rest
       }
    }
    
   
     
}

  

/********************  Defines synaptic strength ************************/

// Creates synaptic strengths

if(read==0){
  // for lateral inhibition

   for(int k1=0; k1<NetSize; k1++){
      for(int k2=0; k2<NetSize; k2++){
          for(int m1=0; m1<NetSize; m1++){
             for(int m2=0; m2<NetSize; m2++){
               Ji[m1][k1][m2][k2]=2*gI*exp(-pow((k1-k2)/Li,2)-pow((m1-m2)/Li,2))*rand()/32767;
             }
          }
      }
   } 
 // then for self inhibition

   for(int k1=0; k1<NetSize; k1++){
      for(int m1=0; m1<NetSize; m1++){  
         Ji[m1][k1][m1][k1]=SgI*(1+0.5*Var());
      }   
   }
} 
else{
      int Idx2, Idx1;
      char marker[10];
     Idx2=0;
     Idx1=0;
     
     ifstream fin;     // declare stream variable name

     fin.open("SynIResIdI7E0.txt",ios::in);    // open file
     assert (!fin.fail( ));     
      
for(int m1=0; m1<NetSize; m1++){
    for(int k1=0; k1<NetSize; k1++){
        for(int m2=0; m2<NetSize; m2++){
           for(int k2=0; k2<NetSize; k2++){                   
            fin >> Ji[m1][k1][m2][k2];         //get next number from file
           }   
        }
            fin>>marker;         
    }
}
     fin.close( );       //close file 
     //assert(!fin.fail( ));    
}





  // for lateral exitation 
  for(int k1=0; k1<NetSize; k1++){
    for(int k2=0; k2<NetSize; k2++){
        for(int m1=0; m1<NetSize; m1++){
           for(int m2=0; m2<NetSize; m2++){
             Je[m1][k1][m2][k2]=2*gE*(1+Var()*0.2);
           }
        }
    }
  }
  // then for self exitation

  for(int k1=0; k1<NetSize; k1++){
    for(int m1=0; m1<NetSize; m1++){  
       Je[m1][k1][m1][k1]=SgE*(1+0.5*Var());
    }   
  } 

     



 
/*********************  Creates links between cells  *******************/
/*********** !!!!! Maximal latency 500 time steps **********************/    
  
 // Inhibition  
 for(int m1=0; m1<NetSize; m1++){
    for(int k1=0; k1<NetSize; k1++){
       for(int m2=0; m2<NetSize; m2++){
          for(int k2=0; k2<NetSize; k2++){
            SynS[m1][k1][m2][k2] = new AlphaSynS(&cell[m1][k1], &cell[m2][k2], Ji[m1][k1][m2][k2], LatI,0);
            if(m1==m2 && k1==k2){
              SetUpSynS( *SynS[m1][k1][m2][k2], STaudI, STaurI, Threshold);// sink / source / Gmax / Fmax / tau1 / tau2 / Fsat / Mean
            }
            else{
              SetUpSynS( *SynS[m1][k1][m2][k2], TaudI, TaurI, Threshold);// sink / source / Gmax / Fmax / tau1 / tau2 / Fsat / Mean
            }     
          }
        }                                                  
     }
  }
                        //   !!!!!  Whatever is added here : check in Destruct&Close.h that it is later removed
                               
        
 // Exitation 
 for(int m1=0; m1<NetSize; m1++){
    for(int k1=0; k1<NetSize; k1++){
       for(int m2=0; m2<NetSize; m2++){
          for(int k2=0; k2<NetSize; k2++){
             if(Je[m1][k1][m2][k2]>0.005){                                
                SynE[m1][k1][m2][k2] = new AlphaSyn(&cell[m1][k1], &cell[m2][k2], Je[m1][k1][m2][k2]*Area, LatE*(1+0.5*Var()) ); 
                SetUpSynE( *SynE[m1][k1][m2][k2], TaudE, TaurE, Threshold);
             }          
          }
       }
    }
 }
