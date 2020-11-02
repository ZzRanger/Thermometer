#define aref_voltage 4.096 

int ADCPin = 0; //using A1 input for this sketch
int ADCReading;

float count = 0;

int calculate(void){

  /* In Celsius */
  
  float T1 = 1.82;
  float T2 = 43.91;
  float T3 = 76.56;
  
  float R1 = 33017.949218750;
  float R2 = 4671.255371093;
  float R3 = 1422.147705078;
  
  T1 = T1 + 273.15;
  T2 = T2 + 273.15;
  T3 = T3 + 273.15;
  
  float L1 = log(R1);
  float L2 = log(R2);
  float L3 = log(R3);
  
  float Y1 = 1.0 / T1;
  float Y2 = 1.0 / T2;
  float Y3 = 1.0 / T3;
  
  float U2 = (Y2-Y1)/(L2-L1);
  float U3 = (Y3-Y1)/(L3-L1);
  
  float C = (U3 - U2)/(L3 - L2) * pow(L1 + L2 + L3, -1);
  float B = U2 - C * (L1*L1 + L1*L2 + L2*L2);
  float A = Y1 - (B+L1*L1*C)*L1;

  Serial.print("A: ");
  Serial.println(A, 15);
  Serial.print("B: ");
  Serial.println(B, 15);
  Serial.print("C: ");
  Serial.println(C, 15);
}

void setup(){

  Serial.begin(9600);

  analogReference(EXTERNAL);

}

void loop(){

  // /* Comment out if calculating coefficients
  
  ADCReading = analogRead(ADCPin);  
 
  Serial.print("ADC reading = ");
  Serial.print(ADCReading);     // the raw analog reading
 
  // converting that reading to voltage, which is based off the reference voltage
  float voltage = ADCReading * aref_voltage;
  voltage /= 1024.0; 

  float test = 1024.0 - ADCReading;
 
  // print out the voltage
  Serial.print(" - ");
  Serial.print(voltage); 
  Serial.println(" volts");

  float R2 = 9780 * (1024.0 / ADCReading - 1.0); // 1023.0 needs to be more accurate
  Serial.print("Resistance is: ");
  Serial.print(R2, 9);
  Serial.print("\n"); 

  Serial.println(count);
  count++;

  // */
  
  calculate();

  delay(1000);

}
