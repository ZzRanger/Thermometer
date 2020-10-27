// Get inputs of T_Low, T_Mid, T_High, and corresponding resistances 
#include <math.h>

// Testing

// Calculator Port Set Up
int ThermistorPin = 0;
int Co_CalcPin = 3;
int Vo;
float R1 = 9910;
float R2;

// Button Set Up
int ButtonPin = 4;
float store_high;
int buttonState = 0;
  
int calculate(void){
  
  float T1 = 32;
  float T2 = 75;
  float T3 = 120;
  
  float R1 = 9500;
  float R2 = 2100;
  float R3 = 1000;

  float R = 3500;
  
  T1 = (T1 - 32) * (5 / 9) + 273.15;
  T2 = (T2 - 32) * 5 / 9 + 273.15;
  T3 = (T3 - 32) * 5 / 9 + 273.15;
 
  float L1 = log(R1);
  float L2 = log(R2);
  float L3 = log(R3);
  
  float Y1 = 1 / T1;
  float Y2 = 1 / T2;
  float Y3 = 1 / T3;
  
  float U2 = (Y2-Y1)/(L2-L1);
  float U3 = (Y3-Y1)/(L3-L1);
  
  float C = (U3 - U2)/(L3 - L2) * pow(L1 + L2 + L3, -1);
  float B = U2 - C * (L1*L1 + L1*L2 + L2*L2);
  float A = Y1 - (B+L1*L1*C)*L1;
  
  Serial.print(A);
  Serial.print(B);
  Serial.print(C);
  
  float tempK = 1 / (A + B * log(R) + C * pow(log(R), 3));
  
  float TC = tempK - 273.15;
  float TF = TC * 9 / 5 + 32;
  
  // Serial.print("Temperature is: %i Celsius and %i Fahrenheit", TC, TF);
  Serial.print(TC);
  Serial.print(TF);
  
}

int LED_check(){
  int LED_R = 8;
  int LED_G = 9;
  int LED_B = 10;
  pinMode(LED_R, OUTPUT);
  pinMode(LED_G, OUTPUT);
  pinMode(LED_B, OUTPUT);

  // Tests LEDs
  digitalWrite(LED_R, HIGH);
  delay(1000);
  digitalWrite(LED_R, LOW);
  delay(1000);
  Serial.print("Red");

  digitalWrite(LED_G, HIGH);
  delay(1000);
  digitalWrite(LED_G, LOW);
  delay(1000);
  Serial.print("Green");

  digitalWrite(LED_B, HIGH);
  delay(1000);
  digitalWrite(LED_B, LOW);
  delay(1000);
  Serial.print("Blue");
  
}
void setup(){
  pinMode(ButtonPin, OUTPUT);   
  pinMode(Co_CalcPin, INPUT);
  Serial.begin(9600);
  LED_check();
  }
  
void loop(){
  while (true) {
    // Resistance calculator
    Vo = analogRead(ThermistorPin);
    
    
    R2 = R1 * (1024.0 / (float)Vo - 1.0); // 1023.0 needs to be more accurate
    Serial.print("Resistance is: ");
    Serial.print(R2, 9);
    Serial.print("\n"); 

    Serial.println(Vo);
    
    delay(500);
    /*
    buttonState = digitalRead(ButtonPin);
    // Storing code
    if (buttonState == HIGH) {
      store_high = R2;
      Serial.print("Stored resistance is: ");
      Serial.print(store_high);
      Serial.print("\n");
    } 
    }*/
  }
}

    
    
    /*
    
    buttonState = digitalRead(ButtonPin);
    // Storing code
    if (buttonState == HIGH) {
      store_high = R2;
      Serial.print("Stored resistance is: ");
      Serial.print(store_high);
      Serial.print("\n");
    } 
  
    int calc_state = digitalRead(Co_CalcPin);
    if (Co_CalcPin == HIGH) {
      calculate();
      break;
    } */
    
    
    

  
  
  
