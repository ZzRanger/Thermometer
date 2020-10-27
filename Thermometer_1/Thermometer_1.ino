int ThermistorPin = 0;

int Vo = analogRead(ThermistorPin);

float R1 = 49900;
float logR2, R2, T, TC, TF;
// float c1 = 1.009249522e-03, c2 = 2.378405444e-04, c3 = 2.019202697e-07;
// float c1 = 1.067051714e-03, c2 = 2.316792140e-04, c3 = 1.790672996e-07;
// float c1 = 1.067051714e-03, c2 = 2.316792140e-04, c3 = 1.800672996e-07;
// float c1 = 1.151997008e-03, c2 = 2.366295820e-04, c3 = 0.09287821506e-07;
// float c1 = 1.028906071e-03, c2 =  2.544670825e-04, c3 = -0.3941545247e-07;
float c1 = 1.401417907e-03, c2 = 1.977943553e-04, c3 = 1.599867495e-07; // SUPER GOOD
// float c1 = 1.565196774e-03, c2 = 1.677219221e-04, c3 = 2.938130160e-07;
// float c1 = 1.843893726e-03, c2 = 1.165486806e-04, c3 = 5.215406424e-07;
int LED_R = 8;
int LED_G = 9;
int LED_B = 10;

void setup() {
  pinMode(LED_R, OUTPUT);
  pinMode(LED_G, OUTPUT);
  pinMode(LED_B, OUTPUT);
  
  Serial.begin(9600);
}

int LED(void) {
  
  if (TC >= 25 && TC <= 45.99) {
    digitalWrite(LED_R, LOW);
    digitalWrite(LED_G, HIGH);
    digitalWrite(LED_B, LOW);
  }

  else if (TC > 46 && TC <= 55.99) {
    digitalWrite(LED_R, HIGH);
    digitalWrite(LED_G, LOW);
    digitalWrite(LED_B, LOW);
  }

  else if (TC > 56 && TC <= 75) {
    digitalWrite(LED_R, LOW);
    digitalWrite(LED_G, LOW);
    digitalWrite(LED_B, HIGH);
  }

  else {
    digitalWrite(LED_R, LOW);
    digitalWrite(LED_G, LOW);
    digitalWrite(LED_B, LOW);
  }
}

void loop() {

  Vo = analogRead(ThermistorPin);
  R2 = R1 * (1023.0000000000 / (float)Vo - 1.00000000); // 857
  logR2 = log(R2);
  T = (1.0 / (c1 + c2*logR2 + c3*logR2*logR2*logR2));
  TC = T - 273.15;
  TF = (TC * 9.0)/ 5.0 + 32.0; 

  float Volt = (5 * R1) / (R1 + R2);

  Serial.print("Temperature: "); 
  Serial.print(TC, 10);
  Serial.println(" C ");  
  Serial.print("Voltage: ");
  Serial.print(Volt, 10);
  Serial.println(" V ");

  // Function for LED
  LED();

  delay(1000);
} 
