#include <Wire.h>//Include the Wire library to talk I2C

 

//This is the I2C Address of the MCP4725, by default (A0 pulled to GND).

//Please note that this breakout is for the MCP4725A0.

#define MCP4725_ADDR 0x60  

//For devices with A0 pulled HIGH, use 0x61

 

int lookup = 0; //varaible for navigating through the tables

 

int signal3[41]={

0,1147,1188,1229,1270,1311,1352,1393,1434,1475,1516,1556,

1597,1638,1679,1720,1761,1802,1843,1884,1925,1966,2007,2048,

2089,2130,2171,2212,2253,2294,2335,2376,2417,2458,2499,2540,

2580,2621,2662,2703,2744

};

 

void setup()

{

  Serial.begin(9600);   //Sets the baud for serial data transmission

 

  Wire.begin();

 

 

  pinMode(A2, OUTPUT);// Set A2 and A3 as Outputs to make them our GND and Vcc,

  pinMode(A3, OUTPUT);//which will power the MCP4725

 
  digitalWrite(A2, LOW);//Set A2 as GND

  digitalWrite(A3, HIGH);//Set A3 as Vcc

}

//---------------------------------------------------

void loop()

{ 

    // Send data only when you receive data:
      
    char letter = Serial.read();
    if(Serial.available()>0 && letter == 't'){ 

    lookup=32;  //max output

    Serial.print(lookup);          //Print Value inside data in Serial monitor   
    }     

    else if(Serial.available()>0 && letter == 'f'){ 

    lookup=0;  //min output

    Serial.print(lookup);          //Print Value inside data in Serial monitor 
    }
    

    delay(100);

    Wire.beginTransmission(MCP4725_ADDR);

    Wire.write(64);                     // cmd to update the DAC

    Wire.write(signal3[lookup] >> 4);        // the 8 most significant bits...

    Wire.write((signal3[lookup] & 15) << 4); // the 4 least significant bits...   

    Wire.endTransmission();

    //break;

      //}       

    }
