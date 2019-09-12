/*
 Pin-out of arduino with the LED display is as follows. Refer the attached image to see the LED display's pinout
   LEd display    |        Arduino
   ________________________________
                  |
       D1         |    6
       D2         |    7
        a         |    8
        b         |    9
        c         |    10
        d         |    11
        e         |    14
        f         |    15
        g         |    16
  dp,D3,D4        |    No connection
 
 
 */ 



//the pins of 4-digit 7-segment display attached to arduino board digital pins 2 - 13 respectively
const int a = 6;
const int b = 7;
const int c = 8;
const int d = 9;
const int e = 10;
const int f = 11;
const int g = 14;
//const int DP = 11;// dot is not used in this project
const int D1 = 15;
const int D2 = 16;

int i =0;

void setup()
{
  Serial.begin(9600);//initialize serial communications at 9600 bps
//set all the pins of the LED display as output
  pinMode(a, OUTPUT);
  pinMode(b, OUTPUT);
  pinMode(c, OUTPUT);
  pinMode(d, OUTPUT);
  pinMode(e, OUTPUT);
  pinMode(f, OUTPUT);
  pinMode(g, OUTPUT);
  pinMode(D1, OUTPUT);
  pinMode(D2, OUTPUT); 
  
  
}

void loop()
{
  digitalWrite(D1, HIGH);
  i++;
  pickNumber(i);
  delay(1000);
  clearLEDs();
  
  if (i == 16)
  {
    i = 0;
  }

  
}

void number1()             //Number 1
{
  digitalWrite(a, HIGH);
  digitalWrite(b, LOW);
  digitalWrite(c, LOW);
  digitalWrite(d, HIGH);
  digitalWrite(e, HIGH);
  digitalWrite(f, HIGH);
  digitalWrite(g, HIGH);
}

void number2()             //Number 2
{
  digitalWrite(a, LOW);
  digitalWrite(b, LOW);
  digitalWrite(c, HIGH);
  digitalWrite(d, LOW);
  digitalWrite(e, LOW);
  digitalWrite(f, HIGH);
  digitalWrite(g, LOW);
}

void number3()            //Number 3
{
  digitalWrite(a, LOW);
  digitalWrite(b, LOW);
  digitalWrite(c, LOW);
  digitalWrite(d, LOW);
  digitalWrite(e, HIGH);
  digitalWrite(f, HIGH);
  digitalWrite(g, LOW);
}

void number4()             //Number 4
{
  digitalWrite(a, HIGH);
  digitalWrite(b, LOW);
  digitalWrite(c, LOW);
  digitalWrite(d, HIGH);
  digitalWrite(e, HIGH);
  digitalWrite(f, LOW);
  digitalWrite(g, LOW);
}

void number5()             //Number 5
{
  digitalWrite(a, LOW);
  digitalWrite(b, HIGH);
  digitalWrite(c, LOW);
  digitalWrite(d, LOW);
  digitalWrite(e, HIGH);
  digitalWrite(f, LOW);
  digitalWrite(g, LOW);
}

void number6()             //Number 6
{
  digitalWrite(a, LOW);
  digitalWrite(b, HIGH);
  digitalWrite(c, LOW);
  digitalWrite(d, LOW);
  digitalWrite(e, LOW);
  digitalWrite(f, LOW);
  digitalWrite(g, LOW);
}

void number7()            //Number 7
{
  digitalWrite(a, LOW);
  digitalWrite(b, LOW);
  digitalWrite(c, LOW);
  digitalWrite(d, HIGH);
  digitalWrite(e, HIGH);
  digitalWrite(f, HIGH);
  digitalWrite(g, HIGH);
}

void number8()            //Number 8
{
  digitalWrite(a, LOW);
  digitalWrite(b, LOW);
  digitalWrite(c, LOW);
  digitalWrite(d, LOW);
  digitalWrite(e, LOW);
  digitalWrite(f, LOW);
  digitalWrite(g, LOW);
}

void number9()             //Number 9
{
  digitalWrite(a, LOW);
  digitalWrite(b, LOW);
  digitalWrite(c, LOW);
  digitalWrite(d, LOW);
  digitalWrite(e, HIGH);
  digitalWrite(f, LOW);
  digitalWrite(g, LOW);
}

void number0()             //Number 0
{
  digitalWrite(a, LOW);
  digitalWrite(b, LOW);
  digitalWrite(c, LOW);
  digitalWrite(d, LOW);
  digitalWrite(e, LOW);
  digitalWrite(f, LOW);
  digitalWrite(g, HIGH);
}

void pickNumber(int x) {
  switch (x) {
    case 1: number1(); 
            break;
    case 2: number2(); 
            break;
    case 3: number3(); 
            break;
    case 4: number4(); 
            break;
    case 5: number5(); 
            break;
    case 6: number6(); 
            break;
    case 7: number7(); 
            break;
    case 8: number8(); 
            break;
    case 9: number9(); 
            break;
    case 10: number1();
             delay(50);
             digitalWrite(D1,LOW);
             digitalWrite(D2, HIGH);
             number0();
             delay(50);
             digitalWrite(D2, LOW);
             break;
    case 11: number1();
             delay(50);
             digitalWrite(D1,LOW);
             digitalWrite(D2, HIGH);
             number1();
             delay(50);
             digitalWrite(D2, LOW);
             break;
    case 12: number1();
             delay(50);
             digitalWrite(D1,LOW);
             digitalWrite(D2, HIGH);
             number2();
             delay(50);
             digitalWrite(D2, LOW);
             break;
    case 13: number1();
             delay(50);
             digitalWrite(D1,LOW);
             digitalWrite(D2, HIGH);
             number3();
             delay(50);
             digitalWrite(D2, LOW);
             break;
    case 14: number1();
             delay(50);
             digitalWrite(D1,LOW);
             digitalWrite(D2, HIGH);
             number4();
             delay(50);
             digitalWrite(D2, LOW);
             break;
    case 15: number1();
             delay(50);
             digitalWrite(D1,LOW);
             digitalWrite(D2, HIGH);
             number5();
             delay(50);
             digitalWrite(D2, LOW);
             break;
    case 16: number1();
             delay(50);
             digitalWrite(D1,LOW);
             digitalWrite(D2, HIGH);
             number6();
             delay(50);
             digitalWrite(D2, LOW);
             break;
    default: number0(); 
             break;
  }
}
//*************************************************************
void clearLEDs()
{
  digitalWrite(a, HIGH);
  digitalWrite(b, HIGH);
  digitalWrite(c, HIGH);
  digitalWrite(d, HIGH);
  digitalWrite(e, HIGH);
  digitalWrite(f, HIGH);
  digitalWrite(g, HIGH);
}

