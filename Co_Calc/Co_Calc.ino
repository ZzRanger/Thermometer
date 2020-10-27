#include <math.h>

// Calculator Port Set Up
int ThermistorPin = 0;
int Co_CalcPin = 3;
int Vo;
float R1 = 430;
float R2;

int calculate(void){
  
  float T1 = 0.0000000000000000000;
  float T2 = 21.0000000000000000;
  float T3 = 100.0000000000000000000;

  float R1 = 30990.71;
  float R2 = 12507.94;
  float R3 = 834.05;  
  
  T1 = (T1 - 32) * (5 / 9) + 273.15;
  T2 = (T2 - 32) * 5 / 9 + 273.15;
  T3 = (T3 - 32) * 5 / 9 + 273.15;

  double Y1, Y2, Y3;
  Y1 = pow(T1, -1);
  Y2 = pow(T2, -1);
  Y3 = pow(T3, -1);
   
  float L1 = log(R1);
  float L2 = log(R2);
  float L3 = log(R3);

  float U2 = (Y2-Y1)/(L2-L1);
  float U3 = (Y3-Y1)/(L3-L1);

  
  
  float C = (U3 - U2)/(L3 - L2) * pow(L1 + L2 + L3, -1);
  float B = U2 - C * (L1*L1 + L1*L2 + L2*L2);
  float A = Y1 - (B+L1*L1*C)*L1;

  Serial.print("Ka = ");
  Serial.print(A, 20);
  Serial.print("\n");

  Serial.print("Kb = ");
  Serial.print(B, 20);
  Serial.print("\n");
  
  Serial.print("Kc = ");
  Serial.print(C, 20);
  Serial.print("\n");
  /*
  float tempK = 1 / (A + B * log(R) + C * pow(log(R), 3));
  
  float TC = tempK - 273.15;
  float TF = TC * 9 / 5 + 32;
  
  // Serial.print("Temperature is: %i Celsius and %i Fahrenheit", TC, TF);
  Serial.print(TC);
  Serial.print(TF); */
  
}

void setup() {
  Serial.begin(9600);
  
}

void loop() {
  calculate();
  delay(10000);
}
