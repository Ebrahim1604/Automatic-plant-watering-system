const int t = 2;
const int h = 3;
const int l = 4;
const int m = 5;

int* sensor_values;
int* current_state_var;

void setup() {
  Serial.begin(9600);
  
  pinMode(A0,OUTPUT);
  pinMode(A1,OUTPUT);
  pinMode(A2,OUTPUT);
  pinMode(A3,OUTPUT);

  pinMode(t,INPUT_PULLUP);
  pinMode(h,INPUT_PULLUP);
  pinMode(l,INPUT_PULLUP);
  pinMode(m,INPUT_PULLUP);

  digitalWrite(A0,LOW);
  digitalWrite(A1,LOW);
  digitalWrite(A2,LOW);
  digitalWrite(A3,LOW);
}

void loop() {
  
  sensor_values = sensor_check();
  current_state_var = statecheck(sensor_values);
  Print(current_state_var);
  delay(50);

}

int* sensor_check(){

   static int values[4];
   values[0] = !digitalRead(t);
   values[1] = !digitalRead(h);
   values[2] = !digitalRead(l);
   values[3] = !digitalRead(m);

   return values;
    
}

int statecheck(int* sensor_value){

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

void Print(int* val){

    Serial.print("State = ");
    Serial.print(val[0]);
    Serial.print(", ");
    Serial.print("Waiting time = ");
    Serial.print(val[1]);
    Serial.print(", ");
    Serial.print("Watering time = ");
    Serial.println(val[2]);
  }

int* Array(int a, int b,int c){
  
    static int var[3];
    var[0] = a;
    var[1] = b;
    var[2] = c;
    return var;
  }
