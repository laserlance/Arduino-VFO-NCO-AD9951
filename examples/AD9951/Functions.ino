void serialEvent() {

     if(Serial.available() > 0) {

          parseSerial();

     }
}
void parseSerial(){

     String scmd;
     String sparam;
     String sreturn = "INVALID";
     boolean found = false;
     char buffer[17] = {'\0'}; // Receive up to 16 bytes
     int i = 0;

     Serial.readBytesUntil('\n', buffer, 16);

     for(i=0; i <= 2; i++){

          if(buffer[i] != '\0' && buffer[i] !=' '){
               scmd = scmd + buffer[i];
          }
          buffer[i] = '\0';
     }
     for(i=3; i <= 16; i++){

          if(buffer[i] != '\0' && buffer[i] !=' '){
               sparam = sparam + buffer[i];
          }
          buffer[i] = '\0';
     }
     if(debugcom){

          Serial.println("Command: " + scmd + "\t" + "Param: " + sparam);
     }

     if(scmd == "rfr"){ //read frequency register
       
        Serial.println((to_string(VFO.ftw[0]) + "\t" + to_string(VFO.ftw[1]) + "\t" + to_string(VFO.ftw[2]) + "\t" + to_string(VFO.ftw[3])));
         
         VFO.SendReg(ftw_reg, read_reg);
      
         sreturn = (to_string(VFO.ftw[0]) + "\t" + to_string(VFO.ftw[1]) + "\t" + to_string(VFO.ftw[2]) + "\t" + to_string(VFO.ftw[3]));
         
     }
     
     if(scmd == "rc1"){ //read configuration register 0
      
           Serial.println((to_string(VFO.cfr1[0]) + "\t" + to_string(VFO.cfr1[1]) + "\t" + to_string(VFO.cfr1[2]) + "\t" + to_string(VFO.cfr1[3])));
         
           VFO.SendReg(cfr1_reg, read_reg);
            
           sreturn = (to_string(VFO.cfr1[0]) + "\t" + to_string(VFO.cfr1[1]) + "\t" + to_string(VFO.cfr1[2]) + "\t" + to_string(VFO.cfr1[3]));    
     }
     
     if(scmd == "rc2"){ //read configuration register 2
      
           Serial.println((to_string(VFO.cfr2[0]) + "\t" + to_string(VFO.cfr2[1]) + "\t" + to_string(VFO.cfr2[2])));
         
           VFO.SendReg(cfr2_reg, read_reg);
            
           sreturn = (to_string(VFO.cfr2[0]) + "\t" + to_string(VFO.cfr2[1]) + "\t" + to_string(VFO.cfr2[2]));    
     }
     
     if(scmd == "raf"){ //read asf
      
           Serial.println((to_string(VFO.asf[0]) + "\t" + to_string(VFO.asf[1])));
         
           VFO.SendReg(asf_reg, read_reg);
            
           sreturn = (to_string(VFO.asf[0]) + "\t" + to_string(VFO.asf[1]));    
     }
     
     if(scmd == "rrr"){ //read arr
      
           Serial.println((to_string(VFO.arr)));
         
           VFO.SendReg(arr_reg, read_reg);
            
           sreturn = (to_string(VFO.arr));    
     }
     
     if(scmd == "rpo"){ //read pow 
      
           Serial.println((to_string(VFO.pow[0]) + "\t" + to_string(VFO.pow[1])));
         
           VFO.SendReg(pow_reg, read_reg);
            
           sreturn = (to_string(VFO.pow[0]) + "\t" + to_string(VFO.pow[1]));    
     }
     
     
     if(scmd == "sc1"){ //set configuration register 1
      
           Serial.println((to_string(VFO.cfr1[0]) + "\t" + to_string(VFO.cfr1[1]) + "\t" + to_string(VFO.cfr1[2]) + "\t" + to_string(VFO.cfr1[3])));
         
           VFO.SendReg(cfr1_reg, write_reg);
            
           sreturn = (to_string(VFO.cfr1[0]) + "\t" + to_string(VFO.cfr1[1]) + "\t" + to_string(VFO.cfr1[2]) + "\t" + to_string(VFO.cfr1[3]));    
     }
     
     if(scmd == "srr"){ //set arr
     
          Serial.println((to_string(VFO.arr)));
          
          VFO.ChangeARR(to_int(sparam));
          
          sreturn = (to_string(VFO.arr));
     
     }
     
      if(scmd == "saf"){ //set asf
     
          Serial.println((to_string(VFO.asf[0]) + "\t" + to_string(VFO.asf[1])));
          
          VFO.ChangeASF(to_int(sparam));
          
          sreturn = ((to_string(VFO.asf[0]) + "\t" + to_string(VFO.asf[1])));
     
     }
     
     if(scmd == "sok"){
      
       if(to_int(sparam) == 1){
       
          digitalWrite(osk, HIGH);
       
       }else{
        
          digitalWrite(osk, LOW);
       } 
       VFO.toggleIOSync();
	VFO.toggleIOUpdate();
       sreturn = "OK";
        
     }
     
     if(scmd == "sfr"){ //set frequency
      
           switch(to_int(sparam)){
                
               default:
               
                    sreturn = "Invalid Selection";               
               
               break;
            
               case 1:
                    
                    freq_24MHz();
                    sreturn = "ok";
                    
               break;
               
               case 2:
               
                    freq_27MHz();
                    sreturn = "ok";
                    
               break;
               
               case 3:
               
                    freq_41MHz();
                    sreturn = "ok";
                    
               break;
               
               case 4:
               
                    freq_80MHz();
                    sreturn = "ok";
                    
               break;
               
               case 5:
               
                    freq_100MHz();
                    sreturn = "ok";
                    
               break;
               
               case 6:
               
                    freq_120MHz();
                    sreturn = "ok";
                    
               break;

           }
              
     }
     
     if(scmd == "rst"){ //reset
          
          digitalWrite(oreset, HIGH);
          delayMicroseconds(50);
          digitalWrite(oreset, LOW);
          VFO.Config();
          VFO.toggleIOSync();
          VFO.toggleIOUpdate();
          sreturn = "ok";          
          
     }

     Serial.println(sreturn);     
     
}
String to_string(int val){
     char buf[24];
     char *intStr = itoa(val,buf,10);
     String str = String(intStr);
     return str;
}
String to_stringd(double val){
     char buf[24];
     char *intStr = itoa(val,buf,10);
     String str = String(intStr);
     return str;
}
String to_stringf(float val,unsigned int precision){

     char buf[24];
     dtostrf(val,2,precision,buf);
     return String(buf);

}

int to_int(String sval){

     char buf[10]; 
     sval.toCharArray(buf,10);
     int val = atoi(buf); 
     return val;

}
float to_float(char *cval){

     float temp = atof(cval);
     return temp; 

}
float to_float(String sval){

     char buf[] = {
          '\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0'                 };
     sval.toCharArray(buf,16);
     float temp = atof(buf);  
     return temp;
}

boolean invertLogic(boolean value){

     if(value){

          return false;

     }
     else{

          return true;
     }
}

void freq_24MHz(){
 
      //24MHz
     VFO.ftw[0] = 0xF6;
     VFO.ftw[1] = 0x28;
     VFO.ftw[2] = 0x5C;
     VFO.ftw[3] = 0x0F;
     VFO.SendReg(ftw_reg, write_reg); //This means that you'd like to send the Frequency register to the AD9951 and you want to write to the register
     VFO.toggleIOSync();
     VFO.toggleIOUpdate();     
     
}

void freq_27MHz(){
     
     //27MHz
     VFO.ftw[0] = 0x14;
     VFO.ftw[1] = 0xAE;
     VFO.ftw[2] = 0x47;
     VFO.ftw[3] = 0x11;
     VFO.SendReg(ftw_reg, write_reg); //This means that you'd like to send the Frequency register to the AD9951 and you want to write to the register
     VFO.toggleIOSync();
     VFO.toggleIOUpdate();     
}

void freq_41MHz(){
     
      //41MHz
     VFO.ftw[0] = 0xA4;
     VFO.ftw[1] = 0x70;
     VFO.ftw[2] = 0x3D;
     VFO.ftw[3] = 0x1A;
     VFO.SendReg(ftw_reg, write_reg); //This means that you'd like to send the Frequency register to the AD9951 and you want to write to the register
     VFO.toggleIOSync();
     VFO.toggleIOUpdate();      
}

void freq_80MHz(){
 
      //80MHz
     VFO.ftw[0] = 0x33;
     VFO.ftw[1] = 0x33;
     VFO.ftw[2] = 0x33;
     VFO.ftw[3] = 0x33;
     VFO.SendReg(ftw_reg, write_reg); //This means that you'd like to send the Frequency register to the AD9951 and you want to write to the register
     VFO.toggleIOSync();
     VFO.toggleIOUpdate();    
}

void freq_100MHz(){
 
      //100MHz
     VFO.ftw[0] = 0x00;
     VFO.ftw[1] = 0x00;
     VFO.ftw[2] = 0x00;
     VFO.ftw[3] = 0x40;
     VFO.SendReg(ftw_reg, write_reg); //This means that you'd like to send the Frequency register to the AD9951 and you want to write to the register
     VFO.toggleIOSync();
     VFO.toggleIOUpdate();    
}

void freq_120MHz(){
 
      //80MHz
     VFO.ftw[0] = 0xCD;
     VFO.ftw[1] = 0xCC;
     VFO.ftw[2] = 0xCC;
     VFO.ftw[3] = 0x4C;
     VFO.SendReg(ftw_reg, write_reg); //This means that you'd like to send the Frequency register to the AD9951 and you want to write to the register
     VFO.toggleIOSync();
     VFO.toggleIOUpdate();    
}



