#include <LiquidCrystal.h>
LiquidCrystal LCD(7, 8, 9, 10, 11, 12);

int sensorPin[4] = {
  A0,
  A1,
  A2,
  A3
};

int sensorRaw[4] = {
  0,
  0,
  0,
  0
};

float sensorValue[4] = {
  0,
  0,
  0,
  0
};

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
char valstr[4];

void setup() {
  Serial.begin(9600);
  
  LCD.begin(16,2);
  LCD.print("INIT MEASUREMENT");
  LCD.setCursor(0,1);
  LCD.print("UPDATE EVERY 1 S");

  delay(2000);
}

void loop() {
  
  for (int i = 0; i < 4; i++){
    sensorRaw[i] = analogRead(sensorPin[i]);
    sensorValue[i] = sensorRaw[i] / 1023.0 * 5;
    Serial.print(i+1);
    Serial.print(": ");
    Serial.print(sensorRaw[i]);
    Serial.print("/");
    Serial.print(sensorValue[i]);
    Serial.print(", ");
    
    LCD.setCursor((i%2)*8,(i/2));
    dtostrf(sensorValue[i],4,2,valstr);
    output[0] = (i+1) + '0';
    for (int j = 0; j < 4; j++){
      output[3+j] = valstr[j];
    }
    LCD.print(output);
  }

  Serial.println("");
  delay(1000);
}
