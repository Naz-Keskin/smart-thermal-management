// --- SMART THERMAL MANAGEMENT SYSTEM ---
// Features: ADC reading, Power Transistor Switching, Hysteresis Control

// 1. PIN DEFINITIONS
int sensorPin = A0; // Analog input for TMP36 Temperature Sensor
int motorPin = 9;   // Digital output to NPN Transistor Base (Motor Control)

void setup() {
  pinMode(motorPin, OUTPUT);
  Serial.begin(9600); // Initialize serial communication for monitoring
}

void loop() {
  // 2. ADC CONVERSION & TEMPERATURE CALCULATION
  int rawValue = analogRead(sensorPin); // Read 10-bit ADC value (0-1023)
  
  // Convert raw value to voltage (5V reference)
  float voltage = rawValue * (5.0 / 1023.0); 
  
  // Convert voltage to Celsius (TMP36 standard formula)
  float temperature = (voltage - 0.5) * 100; 

  // Print current state to Serial Monitor
  Serial.print("Current Temperature: ");
  Serial.print(temperature);
  Serial.println(" C");

  // 3. HYSTERESIS (DEADBAND) CONTROL ALGORITHM
  // Prevents rapid ON/OFF switching (chattering) to protect hardware from inrush currents.
  
  if (temperature > 31.0) {
    digitalWrite(motorPin, HIGH); // Trigger transistor, turn ON motor
  } 
  else if (temperature < 30.0) {
    digitalWrite(motorPin, LOW);  // Cut off base current, turn OFF motor
  }
  // If temperature is between 30.0 and 31.0, the system maintains its current state.

  delay(500); // 500ms sampling rate
}
