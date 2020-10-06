/***********************  A file for all parameters  ************************/
// Opens file ...Prop.txt

    stringstream s3;
    s3<<"ProP"<<a<<".txt";
	s3>>b;
	ofstream exfileP(b);
// writes parameters
   exfileP<<"Size of network->"<<NetSize<<endl<<"Conductance variations->"<<DeltaG<<endl;
   exfileP<<"gInput->"<<gInput<<endl<<"DeltaGI->"<<DeltaGI<<endl;	
   exfileP<<"SgI->"<<SgI<<endl<<"gI->"<<gI<<endl<<"Li->"<<Li<<"LatI->"<<LatI<<endl;
   exfileP<<"SgE->"<<SgE<<endl<<"gE->"<<gE<<endl<<"Le->"<<Le<<"LatE->"<<LatE<<endl; 
   exfileP<<"TaudI->"<<TaudI<<"TaurI->"<<TaurI<<"TaudE->"<<TaudE<<"TaurE->"<<TaurE<<endl<<endl;
   exfileP<<"MITRAL CELLS PROPERTIES"<<endl;
   exfileP<<"gNa->"<<gNa<<" gK->"<<gK<<" gKs->"<<gKs<<" gNaP->"<<gNaP<<" gA->"<<gA<<endl;
   exfileP<<"CM->"<<CM<<" RM->"<<gK<<" ELEAK->"<<ELEAK<<endl<<endl;

// and writes starting time
   time_t rawtime2;
   struct tm * timeinfo2;

   time ( &rawtime2 );
   timeinfo2 = localtime ( &rawtime2 );
   exfileP<<"Starting date and time are:"<< asctime (timeinfo2)<<endl;   



/****************** writes the table of inputs on a file   **************************/
     
   stringstream s6;
   s6<<"Inp"<<a<<".txt";
   s6>>b;
       
   ofstream inpexfile(b);
   
 for(int m1=0; m1<NetSize; m1++){
    for(int k1=0; k1<NetSize; k1++){
       
           inpexfile<<input[m1][k1]->GetAmp()/Area<<DELIM;
           }
           inpexfile<<endl;
        }
  
	inpexfile.close();   
	
	
/*************************** writes the tables of connections on files   *************/
// Inhibition     
   stringstream s1;
   s1<<"SynI"<<a<<".txt";
   s1>>b;
       
   ofstream synexfile(b);
   
 for(int m1=0; m1<NetSize; m1++){
    for(int k1=0; k1<NetSize; k1++){
        for(int m2=0; m2<NetSize; m2++){
           for(int k2=0; k2<NetSize; k2++){
           synexfile<<Ji[m1][k1][m2][k2]<<DELIM;
           }
           synexfile<<endl;
        }
        synexfile<<"Cell-"<<m1<<"-"<<k1<<endl;  
    }
    
 }
	synexfile.close();
	
/* Exitation
   stringstream s2;	
   s2<<"SynE"<<a<<".txt";
   s2>>b;
       
   ofstream syn2exfile(b);
   
      
 for(int m1=0; m1<NetSize; m1++){
    for(int k1=0; k1<NetSize; k1++){
        for(int m2=0; m2<NetSize; m2++){
           for(int k2=0; k2<NetSize; k2++){
           syn2exfile<<Je[m1][k1][m2][k2]<<DELIM;
           }
           syn2exfile<<endl;
        }
        syn2exfile<<"Cell-"<<m1<<"-"<<k1<<<<endl;  
    }
    
 }
	syn2exfile.close();
*/		
