// mqtt_simulator_arduino.ino
// Arduino UNO sketch to read LDR (A0) and LM35 (A1)
// Sends serial lines like: LDR:520,TEMP:27.5

const int LDR_PIN = A0;
const int TEMP_PIN = A1; // LM35

void setup() {
  Serial.begin(9600);
  delay(500);
}

void loop() {
  int ldrValue = analogRead(LDR_PIN); // 0 - 1023
  int tempRaw = analogRead(TEMP_PIN);
  // LM35: 10mV per degree C, ADC ref 5V => tempC = (tempRaw * 5.0 / 1023.0) / 0.01
  float voltage = tempRaw * (5.0 / 1023.0);
  float temperatureC = (voltage) / 0.01; // LM35

  Serial.print("LDR:");
  Serial.print(ldrValue);
  Serial.print(",TEMP:");
  Serial.print(temperatureC, 1);
  Serial.println();
  delay(2000);
}
