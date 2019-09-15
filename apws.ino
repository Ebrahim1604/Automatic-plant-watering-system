/*

 Connections:
 Sensor/actuator-------->Arduino
 1)moisture sensor------> A0
 2)photoresistor--------> A1
 3)Temp&humidity sensor--> A2
 4)relay for pump--------> 12

    LEd display-1  |        Arduino
   ________________________________
                   |
     D1/Common     |    2
        a1         |    4
        b1         |    4
        c1         |    5
        d1         |    7
        e1         |    8
        f1         |    9
        g1         |    10
        dp1        |    No connection

    LEd display-2  |        Arduino
   ________________________________
                   |
     D2/Common     |    3
        a2         |    14
        b2         |    15
        c2         |    16
        d2         |    17
        e2         |    22
        f2         |    24
        g2         |    26
        dp2        |    No connection

 */

#include "DHT.h"

int lightsensor = A1;
float light_thresh = 10.0; // this variable decides the threshold to classify a situation as day or night

const int moisturesensor = A0;  // Soil moisture sensor pin
float moisture_thresh = 50.0; // his variable decides the threshold to classify a situation as wet or dry

const int relay_for_pump = 12;

#define DHTPIN A2     // Digital pin connected to the DHT sensor
#define DHTTYPE DHT22 // Specifying the DHT type, i.e DHT22
DHT dht(DHTPIN, DHTTYPE);   // creating an object of DHT

const int D1 = 2;
const int a1 = 4;
const int b1 = 5;
const int c1 = 6;
const int d1 = 7;
const int e1 = 8;
const int f1 = 9;
const int g1 = 10;
//const int DP = 11;// dot is not used in this project

const int D2 = 3;
const int a2 = 14;
const int b2 = 15;
const int c2 = 16;
const int d2 = 17;
const int e2 = 22;
const int f2 = 24;
const int g2 = 26;


bool* sensor_values;
int* current_state_var;

void setup() {
  
 Serial.begin(9600);
 dht.begin();

 pinMode(D1, OUTPUT);
  pinMode(a1, OUTPUT);
  pinMode(b1, OUTPUT);
  pinMode(c1, OUTPUT);
  pinMode(d1, OUTPUT);
  pinMode(e1, OUTPUT);
  pinMode(f1, OUTPUT);
  pinMode(g1, OUTPUT);
 
  pinMode(D2, OUTPUT); 
  pinMode(a2, OUTPUT);
  pinMode(b2, OUTPUT);
  pinMode(c2, OUTPUT);
  pinMode(d2, OUTPUT);
  pinMode(e2, OUTPUT);
  pinMode(f2, OUTPUT);
  pinMode(g2, OUTPUT);

  pinMode(relay_for_pump, OUTPUT);
 
}

void loop() {
  
  sensor_values = sensor_check();
  current_state_var = statecheck(sensor_values);
  stateaction(current_state_var);

}


bool temp()
{
  float t = dht.readTemperature();
  if (t < 25.0){ return LOW; }
  else {return HIGH;}
}

bool humidity()
{
  float h = dht.readHumidity();
  if (h < 50.0){return LOW;}
  else{return HIGH;}  
}

bool light()
{
   int value; 
   float light_percentage;

   value = analogRead(lightsensor);
   light_percentage = (value*100.0)/1023.0;

  if (light_percentage < light_thresh){return LOW;}
  else{return HIGH;}
}

bool moisture()
{
  float moisture_percentage;
  int value;
  value = analogRead(moisturesensor);
  moisture_percentage = ( 100 - ( (value/1023.00) * 100 ) );

  if (moisture_percentage < moisture_thresh){return LOW;}
  else{return HIGH;}

}

bool* sensor_check(){

   static bool values[4];
   values[0] = temp();
   values[1] = humidity();
   values[2] = light();
   values[3] = moisture();

   return values;
    
}


int* Array(int a, int b,int c){
  
    static int var[3];
    var[0] = a;
    var[1] = b;
    var[2] = c;
    return var;
}

int* statecheck(bool* sensor_value){

  if(sensor_value[0]==LOW && sensor_value[1]==LOW && sensor_value[2]==LOW && sensor_value[3]==LOW){
           return Array(1,15000,1000);
    }
 else if(sensor_value[0]==LOW && sensor_value[1]==LOW &&sensor_value[2]==LOW && sensor_value[3]==HIGH){
           return Array(2,30000,3000);
    }
 else if(sensor_value[0]==LOW && sensor_value[1]==LOW && sensor_value[2]==HIGH && sensor_value[3]==LOW){
           return Array(3,15000,3000);
    }
 else if(sensor_value[0]==LOW && sensor_value[1]==LOW && sensor_value[2]==HIGH && sensor_value[3]==HIGH){
           return Array(4,30000,5000);
    }
 else if(sensor_value[0]==LOW && sensor_value[1]==HIGH && sensor_value[2]==LOW && sensor_value[3]==LOW){
           return Array(5,20000,3000);
    }
 else if(sensor_value[0]==LOW && sensor_value[1]==HIGH && sensor_value[2]==LOW && sensor_value[3]==HIGH){
           return Array(6,0,0);
    }
 else if(sensor_value[0]==LOW && sensor_value[1]==HIGH && sensor_value[2]==HIGH && sensor_value[3]==LOW){
           return Array(7,20000,5000);
    }
 else if(sensor_value[0]==LOW && sensor_value[1]==HIGH && sensor_value[2]==HIGH && sensor_value[3]==HIGH){
           return Array(8,30000,1000);
    }
 else if(sensor_value[0]==HIGH && sensor_value[1]==LOW && sensor_value[2]==LOW && sensor_value[3]==LOW){
           return Array(9,10000,3000);
    }
 else if(sensor_value[0]==HIGH && sensor_value[1]==LOW && sensor_value[2]==LOW && sensor_value[3]==HIGH){
           return Array(10,25000,5000);
    }
 else if(sensor_value[0]==HIGH && sensor_value[1]==LOW && sensor_value[2]==HIGH && sensor_value[3]==LOW){
           return Array(11,10000,5000);
    }
 else if(sensor_value[0]==HIGH && sensor_value[1]==LOW && sensor_value[2]==HIGH && sensor_value[3]==HIGH){
           return Array(12,20000,1000);
    }
 else if(sensor_value[0]==HIGH && sensor_value[1]==HIGH && sensor_value[2]==LOW && sensor_value[3]==LOW){
           return Array(13,15000,5000);
    }
 else if(sensor_value[0]==HIGH && sensor_value[1]==HIGH && sensor_value[2]==LOW && sensor_value[3]==HIGH){
           return Array(14,25000,1000);
    }
 else if(sensor_value[0]==HIGH && sensor_value[1]==HIGH && sensor_value[2]==HIGH && sensor_value[3]==LOW){
           return Array(15,10000,1000);
    }
 else if(sensor_value[0]==HIGH && sensor_value[1]==HIGH && sensor_value[2]==HIGH && sensor_value[3]==HIGH){
           return Array(16,25000,3000);
    }
}


void number1(int d)             //Number 1
{
  if (d == 1)
 {
  digitalWrite(a1, HIGH);
  digitalWrite(b1, LOW);
  digitalWrite(c1, LOW);
  digitalWrite(d1, HIGH);
  digitalWrite(e1, HIGH);
  digitalWrite(f1, HIGH);
  digitalWrite(g1, HIGH);
  }   
 else
 {
  digitalWrite(a2, HIGH);
  digitalWrite(b2, LOW);
  digitalWrite(c2, LOW);
  digitalWrite(d2, HIGH);
  digitalWrite(e2, HIGH);
  digitalWrite(f2, HIGH);
  digitalWrite(g2, HIGH);
 }
}

void number2(int d)             //Number 2
{ 
  if (d == 1)
 {
  digitalWrite(a1, LOW);
  digitalWrite(b1, LOW);
  digitalWrite(c1, HIGH);
  digitalWrite(d1, LOW);
  digitalWrite(e1, LOW);
  digitalWrite(f1, HIGH);
  digitalWrite(g1, LOW);
  }   
 else
 {
  digitalWrite(a2, LOW);
  digitalWrite(b2, LOW);
  digitalWrite(c2, HIGH);
  digitalWrite(d2, LOW);
  digitalWrite(e2, LOW);
  digitalWrite(f2, HIGH);
  digitalWrite(g2, LOW);
 }
}

void number3(int d)            //Number 3
{
  if (d == 1)
 {
  digitalWrite(a1, LOW);
  digitalWrite(b1, LOW);
  digitalWrite(c1, LOW);
  digitalWrite(d1, LOW);
  digitalWrite(e1, HIGH);
  digitalWrite(f1, HIGH);
  digitalWrite(g1, LOW);
  }   
 else
 {
  digitalWrite(a2, LOW);
  digitalWrite(b2, LOW);
  digitalWrite(c2, LOW);
  digitalWrite(d2, LOW);
  digitalWrite(e2, HIGH);
  digitalWrite(f2, HIGH);
  digitalWrite(g2, LOW);
 }
}

void number4(int d)             //Number 4
{
  if (d == 1)
 {
  digitalWrite(a1, HIGH);
  digitalWrite(b1, LOW);
  digitalWrite(c1, LOW);
  digitalWrite(d1, HIGH);
  digitalWrite(e1, HIGH);
  digitalWrite(f1, LOW);
  digitalWrite(g1, LOW);
  }   
 else
 {
  digitalWrite(a2, HIGH);
  digitalWrite(b2, LOW);
  digitalWrite(c2, LOW);
  digitalWrite(d2, HIGH);
  digitalWrite(e2, HIGH);
  digitalWrite(f2, LOW);
  digitalWrite(g2, LOW);
 }
}

void number5(int d)             //Number 5
{
  if (d == 1)
 {
  digitalWrite(a1, LOW);
  digitalWrite(b1, HIGH);
  digitalWrite(c1, LOW);
  digitalWrite(d1, LOW);
  digitalWrite(e1, HIGH);
  digitalWrite(f1, LOW);
  digitalWrite(g1, LOW);
  }   
 else
 {
  digitalWrite(a2, LOW);
  digitalWrite(b2, HIGH);
  digitalWrite(c2, LOW);
  digitalWrite(d2, LOW);
  digitalWrite(e2, HIGH);
  digitalWrite(f2, LOW);
  digitalWrite(g2, LOW);
 }
}

void number6(int d)             //Number 6
{
  if (d == 1)
 {
  digitalWrite(a1, LOW);
  digitalWrite(b1, HIGH);
  digitalWrite(c1, LOW);
  digitalWrite(d1, LOW);
  digitalWrite(e1, LOW);
  digitalWrite(f1, LOW);
  digitalWrite(g1, LOW);
  }   
 else
 {
  digitalWrite(a2, LOW);
  digitalWrite(b2, HIGH);
  digitalWrite(c2, LOW);
  digitalWrite(d2, LOW);
  digitalWrite(e2, LOW);
  digitalWrite(f2, LOW);
  digitalWrite(g2, LOW);
 }
}

void number7(int d)            //Number 7
{
  if (d == 1)
 {
  digitalWrite(a1, LOW);
  digitalWrite(b1, LOW);
  digitalWrite(c1, LOW);
  digitalWrite(d1, HIGH);
  digitalWrite(e1, HIGH);
  digitalWrite(f1, HIGH);
  digitalWrite(g1, HIGH);
  }   
 else
 {
  digitalWrite(a2, LOW);
  digitalWrite(b2, LOW);
  digitalWrite(c2, LOW);
  digitalWrite(d2, HIGH);
  digitalWrite(e2, HIGH);
  digitalWrite(f2, HIGH);
  digitalWrite(g2, HIGH);
 }
}

void number8(int d)            //Number 8
{
  if (d == 1)
 {
  digitalWrite(a1, LOW);
  digitalWrite(b1, LOW);
  digitalWrite(c1, LOW);
  digitalWrite(d1, LOW);
  digitalWrite(e1, LOW);
  digitalWrite(f1, LOW);
  digitalWrite(g1, LOW);
  }   
 else
 {
  digitalWrite(a2, LOW);
  digitalWrite(b2, LOW);
  digitalWrite(c2, LOW);
  digitalWrite(d2, LOW);
  digitalWrite(e2, LOW);
  digitalWrite(f2, LOW);
  digitalWrite(g2, LOW);
  }   
}


void number9(int d)             //Number 9
{
  if (d == 1)
 {
  digitalWrite(a1, LOW);
  digitalWrite(b1, LOW);
  digitalWrite(c1, LOW);
  digitalWrite(d1, LOW);
  digitalWrite(e1, HIGH);
  digitalWrite(f1, LOW);
  digitalWrite(g1, LOW);
  }   
 else
 {
  digitalWrite(a2, LOW);
  digitalWrite(b2, LOW);
  digitalWrite(c2, LOW);
  digitalWrite(d2, LOW);
  digitalWrite(e2, HIGH);
  digitalWrite(f2, LOW);
  digitalWrite(g2, LOW); 
 }
}

void number0(int d)             //Number 0
{
  if (d == 1)
 {
  digitalWrite(a1, LOW);
  digitalWrite(b1, LOW);
  digitalWrite(c1, LOW);
  digitalWrite(d1, LOW);
  digitalWrite(e1, LOW);
  digitalWrite(f1, LOW);
  digitalWrite(g1, HIGH);
  }   
 else
 {
  digitalWrite(a2, LOW);
  digitalWrite(b2, LOW);
  digitalWrite(c2, LOW);
  digitalWrite(d2, LOW);
  digitalWrite(e2, LOW);
  digitalWrite(f2, LOW);
  digitalWrite(g2, HIGH);
 }
}


void Display_on(int state)
{
  switch (state) {
    
    case 1: digitalWrite(D1, HIGH);
            number1(1);
            break;
            
            
    case 2: digitalWrite(D1, HIGH);
            number2(1);
            break;
    
    case 3: digitalWrite(D1, HIGH);
            number3(1);
            break;
    
    case 4: digitalWrite(D1, HIGH);
            number4(1);
            break;
    
    case 5: digitalWrite(D1, HIGH);
            number5(1);
            break;
    
    case 6: digitalWrite(D1, HIGH);
            number6(1);
            break;
    
    case 7: digitalWrite(D1, HIGH);
            number7(1);
            break;
    
    case 8: digitalWrite(D1, HIGH);
            number8(1);
            break;
    
    case 9: digitalWrite(D1, HIGH);
            number9(1);
            break;
    
    case 10: digitalWrite(D1, HIGH);
             number1(1);
             digitalWrite(D2, HIGH);
             number0(2);
             break;
    
    case 11: digitalWrite(D1, HIGH);
             number1(1);
             digitalWrite(D2, HIGH);
             number1(2);
             break;
    
    case 12: digitalWrite(D1, HIGH);
             number1(1);
             digitalWrite(D2, HIGH);
             number2(2);
             break;
    
    case 13: digitalWrite(D1, HIGH);
             number1(1);
             digitalWrite(D2, HIGH);
             number3(2);
             break;
    
    case 14: digitalWrite(D1, HIGH);
             number1(1);
             digitalWrite(D2, HIGH);
             number4(2);
             break;
    
    case 15: digitalWrite(D1, HIGH);
             number1(1);
             digitalWrite(D2, HIGH);
             number5(2);
             break;
    
    case 16: digitalWrite(D1, HIGH);
             number1(1);
             digitalWrite(D2, HIGH);
             number6(2);
             break;
    
    default: digitalWrite(D1, HIGH);
             number0(1);
             digitalWrite(D2, HIGH);
             number0(2);
             break;
  }
}

void Display_off()
{
  digitalWrite(D1, LOW);
  digitalWrite(D2, LOW);
  
  digitalWrite(a1, HIGH);
  digitalWrite(b1, HIGH);
  digitalWrite(c1, HIGH);
  digitalWrite(d1, HIGH);
  digitalWrite(e1, HIGH);
  digitalWrite(f1, HIGH);
  digitalWrite(g1, HIGH);
  
  digitalWrite(a2, HIGH);
  digitalWrite(b2, HIGH);
  digitalWrite(c2, HIGH);
  digitalWrite(d2, HIGH);
  digitalWrite(e2, HIGH);
  digitalWrite(f2, HIGH);
  digitalWrite(g2, HIGH);

  }

void stateaction(int* val){

    Serial.print("State = ");
    Serial.print(val[0]);
    Display_on(val[0]);
    
    Serial.print(", ");
    Serial.print("Waiting time = ");
    Serial.print(val[1]/1000);
    Serial.print("secs");
    delay(val[1]);
    
    Serial.print(", ");
    Serial.print("Watering time = ");
    Serial.print(val[2]/1000);
    Serial.println("secs");
    digitalWrite(relay_for_pump, HIGH);
    delay(val[2]);
    digitalWrite(relay_for_pump, LOW);
    
    Display_off();
  }

