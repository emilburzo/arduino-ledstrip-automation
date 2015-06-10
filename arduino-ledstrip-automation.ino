#include <LowPower.h>
#include <IRremote.h>

#define ON 1
#define OFF 0

#define LEVEL_DARK  800
#define LEVEL_LIGHT 600

//#define DEBUG

IRsend irsend;

unsigned long codeValue; // The code value if not raw
int codeLen; // The length of the code

int sensorPin = A5; // select the input pin for the photoresistor
int light = 0; // variable to store the value coming from the photoresistor
int light_state = OFF; // light state

void setup()
{
#if defined(DEBUG)
  Serial.begin(9600);
#endif
}

void lightsOn() {
#if defined(DEBUG)
  Serial.println("lights on");
#endif

  codeValue = 16236607;
  codeLen = 32;
  irsend.sendNEC(codeValue, codeLen);

  light_state = ON;
}

void lightsOff() {
#if defined(DEBUG)
  Serial.println("lights off");
#endif

  codeValue = 16203967;
  codeLen = 32;
  irsend.sendNEC(codeValue, codeLen);

  light_state = OFF;
}

void loop() {
  light = analogRead(sensorPin);

#if defined(DEBUG)
  Serial.println(light);
#endif

  // if the light level exceeds the threshold and the lights are off
  // turn them on
  if (light > LEVEL_DARK && light_state == OFF) {
    lightsOn();
  }

  if (light <= LEVEL_LIGHT && light_state == ON) {
    lightsOff();
  }

#if defined(DEBUG)
  delay(1000);
#else
  LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF);
#endif
}
