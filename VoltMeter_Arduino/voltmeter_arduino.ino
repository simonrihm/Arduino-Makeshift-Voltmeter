// Initialize LCD screen
#include <LiquidCrystal.h>
LiquidCrystal LCD(7, 8, 9, 10, 11, 12);

// Set analog input pins
int sensorPin[4] = {
  A0,
  A1,
  A2,
  A3
};

// Raw data read by pins
int sensorRaw[4] = {
  0,
  0,
  0,
  0
};

// Converted voltage read from pins
float sensorValue[4] = {
  0,
  0,
  0,
  0
};

// Output string for LCD screen
char output[8] = {
  '0',
  ')',
  ' ',
  'X',
  '.',
  'X',
  'X',
  ' '
};

// Voltage values as output string for Serial Monitor
char valstr[4];

// Update interval in seconds
int updateTime = 1;

void setup() {
  // Initialize Serial Monitor at 9600 Baud
  Serial.begin(9600);

  // Initialize LCD screen and display start message
  LCD.begin(16,2);
  LCD.print("INIT MEASUREMENT");
  LCD.setCursor(0,1);
  LCD.print("UPDATE EVERY X S");
  LCD.setCursor(13,1);
  LCD.print(updateTime);

  // Wait 2 seconds before measurements start
  delay(2000);
}

void loop() {
  // Read input pins one after another
  for (int i = 0; i < 4; i++){
    // Read raw data and convert to Volt
    sensorRaw[i] = analogRead(sensorPin[i]);
    sensorValue[i] = sensorRaw[i] / 1023.0 * 5;

    // Print raw and converted data to Serial Monitor
    Serial.print(i+1);
    Serial.print(": ");
    Serial.print(sensorRaw[i]);
    Serial.print("/");
    Serial.print(sensorValue[i]);
    Serial.print(", ");
    
    // Set position on LCD screen and display voltage
    LCD.setCursor((i%2)*8,(i/2));
    dtostrf(sensorValue[i],4,2,valstr);
    output[0] = (i+1) + '0';
    for (int j = 0; j < 4; j++){
      output[3+j] = valstr[j];
    }
    LCD.print(output);
  }

  // End line on serial Monitor and wait for next measurement
  Serial.println("");
  delay(updateTime*1000);
}
