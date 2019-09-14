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

//the pins of 4-digit 7-segment display attached to arduino board digital pins 2 - 13 respectively
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
const int a2 = 11;
const int b2 = 12;
const int c2 = 13;
const int d2 = A0;
const int e2 = A1;
const int f2 = A2;
const int g2 = A3;


void setup()
{
  Serial.begin(9600);//initialize serial communications at 9600 bps
//set all the pins of the LED display as output
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
  
  
}

void loop()
{
  for (int i=1; i<=16; i++)
  {
    Display_on(i);
    delay(1000);
    Display_off();
   
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

void Display_on(int state) {
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
//*************************************************************
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
