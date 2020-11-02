#define aref_voltage 4.096 

int ADCPin = 0; //using A1 input for this sketch
int ADCReading;

float count = 0;

// Thermometer Code
int LED_R = 8;
int LED_G = 9;
int LED_B = 10;

float logR2, R2, T, TC; // Define variables
float A = 1.155586923e-03, B = 2.295800759e-04, C = 0.9719571354e-07; // Define coefficents (used in equation converting voltage to temperature)

int LED(void) {

  if (TC <= 12) {
    digitalWrite(LED_R, HIGH);
    digitalWrite(LED_G, LOW);
    digitalWrite(LED_B, LOW);
    delay(1000);
  }

  if (TC >= 12.1 && TC <= 18) {
    digitalWrite(LED_R, LOW);
    digitalWrite(LED_G, HIGH);
    digitalWrite(LED_B, LOW);
    delay(1000);
  }

  if (TC >= 18.1 && TC <= 35) {
    digitalWrite(LED_R, HIGH);
    digitalWrite(LED_G, LOW);
    digitalWrite(LED_B, HIGH);
    delay(1000);
  }

  if (TC >= 35.1 && TC <= 42) {
    digitalWrite(LED_R, HIGH);
    digitalWrite(LED_G, HIGH);
    digitalWrite(LED_B, LOW);
    delay(1000);
  }

  if (TC >= 42.1 && TC <= 51) {
    digitalWrite(LED_R, LOW);
    digitalWrite(LED_G, LOW);
    digitalWrite(LED_B, HIGH);
    delay(1000);
  }

  if (TC >= 51.1 && TC <= 66) {
    digitalWrite(LED_R, LOW);
    digitalWrite(LED_G, HIGH);
    digitalWrite(LED_B, HIGH);
    delay(1000);
  }

  if (TC >= 66.1) {
    digitalWrite(LED_R, HIGH);
    digitalWrite(LED_G, HIGH);
    digitalWrite(LED_B, HIGH);
    delay(1000);
  }
  
  if (TC >= 35 && TC <= 45.99) {
    digitalWrite(LED_R, HIGH);
    digitalWrite(LED_G, HIGH);
    digitalWrite(LED_B, LOW);
    delay(1000);
  }

  else if (TC > 46 && TC <= 55.99) {
    digitalWrite(LED_R, HIGH);
    digitalWrite(LED_G, LOW);
    digitalWrite(LED_B, LOW);
    delay(1000);
  }

  else if (TC > 56 && TC <= 75) {
    digitalWrite(LED_R, LOW);
    digitalWrite(LED_G, LOW);
    digitalWrite(LED_B, HIGH);
    delay(1000);
  }

  else {
    digitalWrite(LED_R, LOW);
    digitalWrite(LED_G, LOW);
    digitalWrite(LED_B, LOW);
    delay(1000);
  }

  
}


void setup(){

  pinMode(LED_R, OUTPUT);
  pinMode(LED_G, OUTPUT);
  pinMode(LED_B, OUTPUT);

  Serial.begin(9600);

  analogReference(EXTERNAL);

}

void loop(){

  ADCReading = analogRead(ADCPin);  
 
  // Serial.print("ADC reading = ");
  // Serial.print(ADCReading);     // the raw analog reading
 
  // converting that reading to voltage, which is based off the reference voltage

  float test = 1024.0 - ADCReading;

  float voltage = test * aref_voltage;
  voltage /= 1024.0; 
 
  // print out the voltage
  /* 
  
  Serial.print(" - ");
  Serial.print(voltage); Serial.println(" volts");

  */


  /* Conversion of voltage to temperature */
  
  float R2 = 9780 * (1024.0 / ADCReading - 1.0); // Converts voltage to resistance

  /* Note: 1024.0 is equivalent to 4.096 and ADCReading is equivalent to sensor reading (equivalent to 4.096 / voltage)
   * We wanted to reduce the number of calculations in the program to ensure the greatest possible accuracy */
    
  logR2 = log(R2); // logR2 = ln(R2) 
  T = (1.0 / (A + B*logR2 + C*logR2*logR2*logR2)); // Tempearture in Kelvin
  TC = T - 273.15; // Temperature in Celsius

/*
  Serial.print("Resistance is: ");
  Serial.print(R2, 9);
  Serial.print("\n"); 

  Serial.println(count);
  count++;
*/

  Serial.print("Temperature: "); 
  Serial.print(TC, 1);
  Serial.println(" C ");  
  Serial.print("Voltage: ");
  Serial.print(voltage, 2);
  Serial.println(" V ");

  // Function for LED
  LED();

  // delay(1000);

}
