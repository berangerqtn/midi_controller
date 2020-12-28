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
  Serial.begin(57600); //57250 FOR MIDI TRANSMITTING AND 9250 FOR SERIAL TESTS
  digitalWrite(DLED1,HIGH);
}

//***************************************************
//                   Main Program
//***************************************************

void loop()
{  
  MANAGE_MODE();
  MANAGE_DIGITALS();
  MANAGE_ANALOGS();
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
    Serial.print("\nPIN 0 Activé!\n");
    Serial.print(mode);
    MIDI_TX(176,60+10*mode,127);
    delay(250);  
  }
    
  else if (digitalRead(D1)== LOW)                                                                                               
  {
    Serial.print("\nPIN 1 Activé!\n");
    MIDI_TX(176,61+10*mode,127);
    delay(250);  
  }
  else if (digitalRead(D2)== LOW)                                          
  {
    Serial.print("\nPIN 2 Activé!\n");
    MIDI_TX(176,62+10*mode,127);
    delay(250);  
  }
  else if (digitalRead(D3)== LOW)                                                                                               
  {
    Serial.print("\nPIN 3 Activé!\n");
    MIDI_TX(176,63+10*mode,127);
    delay(250);  
  }
  else if (digitalRead(D4)== LOW)                                                                                               
  {
    Serial.print("\nPIN 4 Activé!\n");
    MIDI_TX(176,64+10*mode,127);
    delay(250);  
  }
  else if (digitalRead(D5)== LOW)                                                                                               
  {
    Serial.print("\nPIN 5 Activé!\n");
    MIDI_TX(176,65+10*mode,127);
    delay(250);  
  }
  else if (digitalRead(D6)== LOW)                                                                                               
  {
    Serial.print("\nPIN 6 Activé!\n");
    MIDI_TX(176,66+10*mode,127);
    delay(250);  
  }
  else if (digitalRead(D7)== LOW)                                                                                               
  {
    Serial.print("\nPIN 7 Activé!\n");
    MIDI_TX(176,67+10*mode,127);
    delay(250);  
  }
  else if (digitalRead(D8)== LOW)                                                                                               
  {
    Serial.print("\nPIN 8 Activé!\n");
    MIDI_TX(176,68+10*mode,127);
    delay(250);  
  }
  else if (digitalRead(D9)== LOW)                                                                                               
  {
    Serial.print("\nPIN 9 Activé!\n");
    MIDI_TX(176,69+10*mode,127);
    delay(250);  
  }
}
void MANAGE_MODE()
{
  if (digitalRead(D10)==HIGH)
  {
    Serial.print("\nPIN10 activé, Changement de programme");
    if (mode==0)
    {
      Serial.print("\nOn passe au mode 2 ");
      digitalWrite(DLED1,LOW);
      digitalWrite(DLED2,HIGH);
      delay(250);
    }
    if (mode==1)
    {
      Serial.print("\nOn passe au mode 3 ");
      digitalWrite(DLED2,LOW);
      digitalWrite(DLED3,HIGH);
      delay(250);
    }
    else if (mode==2)
    {
      Serial.print("\nOn passe au mode 1 ");
      digitalWrite(DLED3,LOW);
      digitalWrite(DLED1, HIGH);
      delay(250);
    }
    mode++;
    mode=mode%3;
  }
}
int temp =0;
void MANAGE_ANALOGS()
{
  //Serial.print(analogRead(An0));
  //Serial.print("\n");
  if (!(An0_Val-4<analogRead(An0)) || !(analogRead(An0)<An0_Val +4))
  {
    An0_Val=analogRead(An0); 
    temp=int((An0_Val*127)/1023);
    MIDI_TX(176,41+6*mode,temp);
        
    Serial.print("\nChangement de Valeur : ");
    Serial.print(An0_Val);
    Serial.print("   |||   "); 
    Serial.print(temp);    
  }
}
