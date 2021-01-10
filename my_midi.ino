//----------------------------------------------------
//     Home made MIDI Controler, with Arduino UNO
//Béranger Quintana

//8 Control Change Buttons 
//6 Slide Potentiometers 

//3 MODES => 24 CC instructions and 18 Slides Pot actions 


// MIDI (cccc = canal):
 
// |================MESSAGE================|=======DATA1=======|========DATA2========|
// | 2500 cccc = note off => 128(10)       | 0xxx xxxx:  note  | 0xxx xxxx: velocity |
// | 2501 cccc = note on => 129(10)        | 0xxx xxxx:  note  | 0xxx xxxx: velocity |
// | 1110 cccc = pitch bend => 224(10)     | 0000 0000:  code  | 0xxx xxxx: speed    |
// | 1011 cccc = control change => 176(10) | 0xxx xxxx: number | 0xxx xxxx: value    |
// -----------------------------------------------------------------------------------


//IMPORTANT : DO NOT START YOUR CC COMMUNICATION ON CC0 BECAUSE THE TX PIN FROM THE ARDUINO WILL INTERFERE


// DIGITAL PINS

int D0 = 0; // WE CANNOT USE THE DIGITAL PIN 0 FOR THIS PROJECT BECAUSE WE ARE USING SERIAL COMMUNICATION (e.g. Serial Begin)  
int D1 = 1; // WE CANNOT USE THE DIGITAL PIN 1 FOR THIS PROJECT BECAUSE WE ARE USING SERIAL COMMUNICATION (e.g. Serial Begin)
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
  Serial.begin(31250); //31250 FOR MIDI TRANSMITTING AND 9600 FOR SERIAL TESTS
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
}


//FUNCTION : MIDI_TX : Send MIDI message to serial port.

void MIDI_TX(unsigned char MESSAGE, unsigned char DONNEE1, unsigned char DONNEE2) 
{
 Serial.write(MESSAGE); 
 Serial.write(DONNEE1); 
 Serial.write(DONNEE2); 
}

//FUNCTION : MANAGE_DIGITALS : Manage behaviour of digital Low edge
void MANAGE_DIGITALS()
{
 
  if (digitalRead(D2)== LOW)                                          
  {
    MIDI_TX(176,70+8*mode,127);
    delay(250);  
  }
  else if (digitalRead(D3)== LOW)                                                                                               
  {
    MIDI_TX(176,71+8*mode,127);
    delay(250);  
  }
  else if (digitalRead(D4)== LOW)                                                                                               
  {
    MIDI_TX(176,72+8*mode,127);
    delay(250);  
  }
  else if (digitalRead(D5)== LOW)                                                                                               
  {
    MIDI_TX(176,73+8*mode,127);
    delay(250);  
  }
  else if (digitalRead(D6)== LOW)                                                                                               
  {
    MIDI_TX(176,74+8*mode,127);
    delay(250);  
  }
  else if (digitalRead(D7)== LOW)                                                                                               
  {
    MIDI_TX(176,75+8*mode,127);
    delay(250);  
  }
  else if (digitalRead(D8)== LOW)                                                                                               
  {
    MIDI_TX(176,76+8*mode,127);
    delay(250);  
  }
  else if (digitalRead(D9)== LOW)                                                                                               
  {
    MIDI_TX(176,77+8*mode,127);
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
int switch0=0;
int temp1=0;
int switch1=0;
int temp2=0;
int switch2=0;
int temp3=0;
int switch3=0;
int temp4=0;
int switch4=0;
int temp5=0;
int switch5=0;

void MANAGE_ANALOGS()
{
  //ANALOG0
  if (!(An0_Val-6*7<analogRead(An0)) || !(analogRead(An0)<An0_Val +6*7) && (switch0==0))
  {
    switch0=1;
    An0_Val=analogRead(An0); 
    temp0=int((An0_Val*127)/1023);
    MIDI_TX(176,100+6*mode,temp0);
  }
  else if (!(An0_Val-6*7<analogRead(An0)) || !(analogRead(An0)<An0_Val +6*7) && (switch0==1))
  {
    if ((!(An0_Val-8<analogRead(An0)) || !(analogRead(An0)<An0_Val+8)))
    {
        switch0=0;
    }
    else
    {
        An0_Val=analogRead(An0); 
        temp0=int((An0_Val*127)/1023);
        MIDI_TX(176,100+6*mode,temp0);
    }
  }
  /*
  //ANALOG1
  if ((!(An1_Val-6*7<analogRead(An1)) || !(analogRead(An1)<An1_Val +6*7)) && (switch1==0))
  {
    switch1=1;
    An1_Val=analogRead(An1); 
    temp1=int((An1_Val*127)/1023);
    MIDI_TX(176,101+6*mode,temp1);
  }
  else if ((!(An1_Val-6*7<analogRead(An1)) || !(analogRead(An1)<An1_Val +6*7)) && (switch1==1))
  {
    if ((!(An1_Val-8<analogRead(An1)) || !(analogRead(An1)<An1_Val+8)))
    {
        switch1=0;
    }
    else
    {
        An1_Val=analogRead(An1); 
        temp1=int((An1_Val*127)/1023);
        MIDI_TX(176,101+6*mode,temp1);
    }
  }

  //ANALOG2
  if ((!(An2_Val-6*7<analogRead(An2)) || !(analogRead(An2)<An2_Val +6*7)) && (switch2==0))
  {
    switch2=1;
    An2_Val=analogRead(An2); 
    temp2=int((An2_Val*127)/1023);
    MIDI_TX(176,102+6*mode,temp2);
  }
  else if ((!(An2_Val-6*7<analogRead(An2)) || !(analogRead(An2)<An2_Val +6*7)) && (switch2==1))
  {
    if ((!(An2_Val-8<analogRead(An2)) || !(analogRead(An2)<An2_Val+8)))
    {
        switch2=0;
    }
    else
    {
        An2_Val=analogRead(An2); 
        temp2=int((An2_Val*127)/1023);
        MIDI_TX(176,102+6*mode,temp2);
    }
  }

  //ANALOG3
  if ((!(An3_Val-6*7<analogRead(An3)) || !(analogRead(An3)<An3_Val +6*7)) && (switch3==0))
  {
    switch3=1;
    An3_Val=analogRead(An3); 
    temp3=int((An3_Val*127)/1023);
    MIDI_TX(176,103+6*mode,temp3);
  }
  else if ((!(An3_Val-6*7<analogRead(An3)) || !(analogRead(An3)<An3_Val +6*7)) && (switch3==1))
  {
    if ((!(An3_Val-8<analogRead(An3)) || !(analogRead(An3)<An3_Val+8)))
    {
        switch3=0;
    }
    else
    {
        An3_Val=analogRead(An3); 
        temp3=int((An3_Val*127)/1023);
        MIDI_TX(176,103+6*mode,temp3);
    }
  }

  //ANALOG4
  if ((!(An4_Val-6*7<analogRead(An4)) || !(analogRead(An4)<An4_Val +6*7)) && (switch4==0))
  {
    switch4=1;
    An4_Val=analogRead(An4); 
    temp4=int((An4_Val*127)/1023);
    MIDI_TX(176,104+6*mode,temp4);
  }
  else if ((!(An4_Val-6*7<analogRead(An4)) || !(analogRead(An4)<An4_Val +6*7)) && (switch4==1))
  {
    if ((!(An4_Val-8<analogRead(An4)) || !(analogRead(An4)<An4_Val+8)))
    {
        switch4=0;
    }
    else
    {
        An4_Val=analogRead(An4); 
        temp4=int((An4_Val*127)/1023);
        MIDI_TX(176,104+6*mode,temp4);
    }
  }

  //ANALOG5
  if ((!(An5_Val-6*7<analogRead(An5)) || !(analogRead(An5)<An5_Val +6*7)) && (switch5==0))
  {
    switch5=1;
    An5_Val=analogRead(An5); 
    temp5=int((An5_Val*127)/1023);
    MIDI_TX(176,105+6*mode,temp5);
  }
  else if ((!(An5_Val-6*7<analogRead(An5)) || !(analogRead(An5)<An5_Val +6*7)) && (switch5==1))
  {
    if ((!(An5_Val-8<analogRead(An5)) || !(analogRead(An5)<An5_Val+8)))
    {
        switch5=0;
    }
    else
    {
        An5_Val=analogRead(An5); 
        temp5=int((An5_Val*127)/1023);
        MIDI_TX(176,105+6*mode,temp5);
    }
  }*/
}
