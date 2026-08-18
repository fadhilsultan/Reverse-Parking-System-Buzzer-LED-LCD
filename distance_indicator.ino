#include <Adafruit_NeoPixel.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

const int trigPin = 9;
const int echoPin = 10;
const int redLED = 5;     // close 
const int yellowLED = 6;  // mid 
const int greenLED = 7;   // far 
const int buzzerPin = 8;

// NeoPixel setup
#define NEOPIN 4
#define NUMPIXELS 4
Adafruit_NeoPixel strip(NUMPIXELS, NEOPIN, NEO_GRB + NEO_KHZ800);

// LCD setup PCF8574 I2C backpack, address 0x20 in Tinkercad
LiquidCrystal_I2C lcd(0x20, 16, 2);

// Distance (cm)
const int closeDist = 100;  // red LED + police flash
const int midDist   = 170;  // yellow LED: up to 170 cm
const int farDist    = 300; // green LED: up to 300 cm, beyond this = nothing detected

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(redLED, OUTPUT);
  pinMode(yellowLED, OUTPUT);
  pinMode(greenLED, OUTPUT);
  pinMode(buzzerPin, OUTPUT);

  strip.begin();
  strip.show(); // start with all pixels off
  strip.setBrightness(80);

  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Reverse Parking");
  delay(1000);
  lcd.clear();

  Serial.begin(9600);
}

long getDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  long duration = pulseIn(echoPin, HIGH);
  long distance = duration * 0.034 / 2;
  return distance;
}

void setStripColor(uint8_t r, uint8_t g, uint8_t b) {
  for (int i = 0; i < NUMPIXELS; i++) {
    strip.setPixelColor(i, strip.Color(r, g, b));
  }
  strip.show();
}

void updateLCD(long distance, String status) {
  lcd.setCursor(0, 0);
  lcd.print("Dist: ");
  lcd.print(distance);
  lcd.print(" cm   ");
  lcd.setCursor(0, 1);
  lcd.print(status);
  lcd.print("        ");
}

void policeFlash(long distance) {
  updateLCD(distance, "!! TOO CLOSE !!");

  // Flash 1: red LED + red strip
  digitalWrite(redLED, HIGH);
  digitalWrite(yellowLED, LOW);
  digitalWrite(greenLED, LOW);
  setStripColor(255, 0, 0);
  tone(buzzerPin, 1500);
  delay(100);
  noTone(buzzerPin);
  digitalWrite(redLED, LOW);
  setStripColor(0, 0, 0);
  delay(60);

  // Flash 2: yellow LED + blue strip (classic police contrast)
  digitalWrite(yellowLED, HIGH);
  setStripColor(0, 0, 255);
  tone(buzzerPin, 1650);
  delay(100);
  noTone(buzzerPin);
  digitalWrite(yellowLED, LOW);
  setStripColor(0, 0, 0);
  delay(60);

  // Flash 3: green LED + red strip again
  digitalWrite(greenLED, HIGH);
  setStripColor(255, 0, 0);
  tone(buzzerPin, 1800);
  delay(100);
  noTone(buzzerPin);
  digitalWrite(greenLED, LOW);
  setStripColor(0, 0, 0);
  delay(60);
}

void loop() {
  long distance = getDistance();
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  if (distance > 0 && distance <= closeDist) {
    // CLOSE: police-style flash + LCD alert
    policeFlash(distance);

  } else {
    // Not close - make sure flashing stops and LEDs reset
    digitalWrite(redLED, LOW);
    digitalWrite(yellowLED, LOW);
    digitalWrite(greenLED, LOW);
    noTone(buzzerPin);

    if (distance <= midDist) {
      // MID: yellow LED + yellow strip + moderate beep
      digitalWrite(yellowLED, HIGH);
      setStripColor(255, 150, 0);
      updateLCD(distance, "Caution: Medium");
      tone(buzzerPin, 1200);
      delay(120);
      noTone(buzzerPin);
      delay(200);

    } else if (distance <= farDist) {
      // FAR: green LED + green strip + slow, low beep
      digitalWrite(greenLED, HIGH);
      setStripColor(0, 255, 0);
      updateLCD(distance, "Safe: Far away");
      tone(buzzerPin, 700);
      delay(100);
      noTone(buzzerPin);
      delay(500);

    } else {
      // Out of range - strip off
      setStripColor(0, 0, 0);
      updateLCD(distance, "No object found");
    }
  }
}
