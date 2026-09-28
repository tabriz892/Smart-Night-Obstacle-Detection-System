#include <Wire.h>
#include <Adafruit_LiquidCrystal.h>

Adafruit_LiquidCrystal lcd(0);

const int TRIG_PIN = 8;
const int ECHO_PIN = 9;
const int PIR_PIN = 10;

const int BUZZER_PIN = 11;

const int RED_LED = 7;
const int GREEN_LED = 6;
const int YELLOW_LED = 5;

long duration;
float distance;

void setup()
{
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  pinMode(PIR_PIN, INPUT);

  pinMode(BUZZER_PIN, OUTPUT);

  pinMode(RED_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);
  pinMode(YELLOW_LED, OUTPUT);

  lcd.begin(16, 2);
  lcd.setBacklight(1);

  lcd.setCursor(0, 0);
  lcd.print("SMART NIGHT");

  lcd.setCursor(0, 1);
  lcd.print("DETECTION");

  delay(2000);
  lcd.clear();
}

void loop()
{
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);

  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);

  digitalWrite(TRIG_PIN, LOW);

  duration = pulseIn(ECHO_PIN, HIGH, 30000);

  if (duration > 0)
  {
    distance = duration * 0.0343 / 2;
  }
  else
  {
    distance = 999;
  }

  int movement = digitalRead(PIR_PIN);

  lcd.clear();

  if (movement == HIGH)
  {
    digitalWrite(RED_LED, HIGH);
    digitalWrite(YELLOW_LED, LOW);
    digitalWrite(GREEN_LED, LOW);

    tone(BUZZER_PIN, 3000);

    lcd.setCursor(0, 0);
    lcd.print("DIST:");
    lcd.print(distance, 1);
    lcd.print("cm");

    lcd.setCursor(0, 1);
    lcd.print("MOVEMENT DETECT");
  }

  else if (distance > 0 && distance < 30)
  {
    digitalWrite(RED_LED, HIGH);
    digitalWrite(YELLOW_LED, LOW);
    digitalWrite(GREEN_LED, LOW);

    tone(BUZZER_PIN, 3000);

    lcd.setCursor(0, 0);
    lcd.print("DIST:");
    lcd.print(distance, 1);
    lcd.print("cm");

    lcd.setCursor(0, 1);
    lcd.print("OBJECT TOO CLOSE");
  }

  else if (distance >= 30 && distance <= 150)
  {
    digitalWrite(RED_LED, LOW);
    digitalWrite(YELLOW_LED, HIGH);
    digitalWrite(GREEN_LED, LOW);

    tone(BUZZER_PIN, 2000);

    lcd.setCursor(0, 0);
    lcd.print("DIST:");
    lcd.print(distance, 1);
    lcd.print("cm");

    lcd.setCursor(0, 1);
    lcd.print("OBJECT DETECTED");
  }

  else
  {
    digitalWrite(RED_LED, LOW);
    digitalWrite(YELLOW_LED, LOW);
    digitalWrite(GREEN_LED, HIGH);

    noTone(BUZZER_PIN);

    lcd.setCursor(0, 0);
    lcd.print("DIST:");

    if (distance < 999)
    {
      lcd.print(distance, 1);
      lcd.print("cm");
    }
    else
    {
      lcd.print("NO OBJECT");
    }

    lcd.setCursor(0, 1);
    lcd.print("ROAD CLEAR");
  }

  delay(300);
}