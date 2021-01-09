//Home made MIDI Controler, with Arduino UNO
//Béranger Quintana

//10 Control Change Buttons 
//6 Slide Potentiometers 

//2 MODES => 20 CC instructions and 12 Slides Pot actions 


// MIDI (cccc = canal):
 
// |================MESSAGE================|=======DATA1=======|========DATA2========|
// | 2500 cccc = note off => 128(10)       | 0xxx xxxx:  note  | 0xxx xxxx: velocity |
// | 2501 cccc = note on => 129(10)        | 0xxx xxxx:  note  | 0xxx xxxx: velocity |
// | 1110 cccc = pitch bend => 224(10)     | 0000 0000:  code  | 0xxx xxxx: speed    |
// | 1011 cccc = control change => 176(10) | 0xxx xxxx: number | 0xxx xxxx: value    |
// -----------------------------------------------------------------------------------

//Used PINS

// DIGITAL PINS

int D0 = 0;    
int D1 = 1;
int D2 = 2;
int D3 = 3;
int D4 = 4;
int D5 = 5;
int D6 = 6;
int D7 = 7;
int D8 = 8; 
int D9 = 9;
int D10 = 10;
int DLED1 = 11; //PROGRAMME 1
int DLED2 = 12; //PROGRAMME 2
int DLED3 = 13; //PROGRAMME 3

// ANALOG PINS

int An0 = 0;
float An0_Val = 0;
int An1 = 1;
int An1_Val = 0;
int An2 = 2;
int An2_Val = 0;
int An3 = 3;
int An3_Val = 0;
int An4 = 4;
int An4_Val = 0;
int An5 = 5;
int An5_Val = 0;
int mode = 0;

//***************************************************
//                       INIT
//***************************************************
void setup() 
{
  for (int i=0; i<11 ; i++)
  {
    pinMode(i,INPUT); //Initialization of all DigitalPins
  }
  for (int j=11; j<14 ; j++)
  {
    pinMode(j,OUTPUT);
  }
  Serial.begin(31250); //31250 FOR MIDI TRANSMITTING AND 9250 FOR SERIAL TESTS
  digitalWrite(DLED1,HIGH);
}

//***************************************************
//                   Main Program
//***************************************************

void loop()
{  
  MANAGE_MODE();
  MANAGE_DIGITALS();
  // MANAGE_ANALOGS();
  //Serial.print("\n\nMode actuel : ");
  //Serial.print(mode);
}


//FUNCTION : MIDI_TX : Send MIDI message to serial port.

void MIDI_TX(unsigned char MESSAGE, unsigned char DONNEE1, unsigned char DONNEE2) 
{
 Serial.write(MESSAGE); //envoi de l'octet de message sur le port série
 Serial.write(DONNEE1); //envoi de l'octet de donnée 1 sur le port série
 Serial.write(DONNEE2); //envoi de l'octet de donnée 2 sur le port série
}


//FUNCTION : MANAGE_DIGITALS : Manage behaviour of digital Rising edge
void MANAGE_DIGITALS()
{
  if (digitalRead(D0)== LOW)                                                                                               
  {
    MIDI_TX(176,0+10*mode,127);
    delay(250);  
  }
    
  else if (digitalRead(D1)== LOW)                                                                                               
  {
    MIDI_TX(176,1+10*mode,127);
    delay(250);  
  }
  else if (digitalRead(D2)== LOW)                                          
  {
    MIDI_TX(176,2+10*mode,127);
    delay(250);  
  }
  else if (digitalRead(D3)== LOW)                                                                                               
  {
    MIDI_TX(176,3+10*mode,127);
    delay(250);  
  }
  else if (digitalRead(D4)== LOW)                                                                                               
  {
    MIDI_TX(176,4+10*mode,127);
    delay(250);  
  }
  else if (digitalRead(D5)== LOW)                                                                                               
  {
    MIDI_TX(176,5+10*mode,127);
    delay(250);  
  }
  else if (digitalRead(D6)== LOW)                                                                                               
  {
    MIDI_TX(176,6+10*mode,127);
    delay(250);  
  }
  else if (digitalRead(D7)== LOW)                                                                                               
  {
    MIDI_TX(176,7+10*mode,127);
    delay(250);  
  }
  else if (digitalRead(D8)== LOW)                                                                                               
  {
    MIDI_TX(176,8+10*mode,127);
    delay(250);  
  }
  else if (digitalRead(D9)== LOW)                                                                                               
  {
    MIDI_TX(176,9+10*mode,127);
    delay(250);  
  }
}
void MANAGE_MODE()
{
  if (digitalRead(D10)==HIGH)
  {
    if (mode==0)
    {
      digitalWrite(DLED1,LOW);
      digitalWrite(DLED2,HIGH);
      delay(250);
    }
    if (mode==1)
    {
      digitalWrite(DLED2,LOW);
      digitalWrite(DLED3,HIGH);
      delay(250);
    }
    else if (mode==2)
    {
      digitalWrite(DLED3,LOW);
      digitalWrite(DLED1, HIGH);
      delay(250);
    }
    mode++;
    mode=mode%3;
  }
}
int temp0=0;
int temp1=0;
int temp2=0;
int temp3=0;
int temp4=0;
int temp5=0;

void MANAGE_ANALOGS()
{
  if (!(An0_Val-4<analogRead(An0)) || !(analogRead(An0)<An0_Val +4))
  {
    An0_Val=analogRead(An0); 
    temp0=int((An0_Val*127)/1023);
    MIDI_TX(176,30+6*mode,temp0);
  }
 /* if (!(An1_Val-4<analogRead(An1)) || !(analogRead(An1)<An1_Val +4))
  {
    An1_Val=analogRead(An1); 
    temp1=int((An1_Val*127)/1023);
    MIDI_TX(176,31+6*mode,temp1);
  }
  if (!(An2_Val-4<analogRead(An2)) || !(analogRead(An2)<An2_Val +4))
  {
    An2_Val=analogRead(An2); 
    temp2=int((An2_Val*127)/1023);
    MIDI_TX(176,32+6*mode,temp2);
  }
  if (!(An3_Val-4<analogRead(An3)) || !(analogRead(An3)<An3_Val +4))
  {
    An3_Val=analogRead(An3); 
    temp3=int((An3_Val*127)/1023);
    MIDI_TX(176,33+6*mode,temp3);
  }  
  if (!(An4_Val-4<analogRead(An4)) || !(analogRead(An4)<An4_Val +4))
  {
    An4_Val=analogRead(An4); 
    temp4=int((An4_Val*127)/1023);
    MIDI_TX(176,34+6*mode,temp4);
  } 
  if (!(An5_Val-4<analogRead(An5)) || !(analogRead(An5)<An5_Val +4))
  {
    An5_Val=analogRead(An5); 
    temp5=int((An5_Val*127)/1023);
    MIDI_TX(176,35+6*mode,temp5);
  } */
}
