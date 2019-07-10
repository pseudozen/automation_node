/*
 Automation Node
 Simple LED controller example

 This example uses the "Automation Node Rev 1" board to run a simple,
 5-channel LED-strip controller.

 Assumptions: 
 
 - Feather ESP32 installed on the given headers (IC6)
 - external 12V supply, with enough capacity for the LED strips hooked up
 - a 5V regulator for the ESP32 (Rev 1 board only has vias for external 5V regulator)
 
 */

 const int LED1 = 14;
 const int LED2 = 32;
 const int LED3 = 15;
 const int LED4 = 33;
 const int LED5 = 27;
 

// create PWM channels for ESP32
#define LEDC_CHANNEL_1     0
#define LEDC_CHANNEL_2     1
#define LEDC_CHANNEL_3     2
#define LEDC_CHANNEL_4     3
#define LEDC_CHANNEL_5     4

// use 13 bit precission for LEDC timer
#define LEDC_TIMER_13_BIT  13

// use 5000 Hz as a LEDC base frequency
#define LEDC_BASE_FREQ     5000

int brightness = 0;    // how bright the LED is
int fadeAmount = 5;    // how many points to fade the LED by

// Arduino like analogWrite
// value has to be between 0 and valueMax
void ledcAnalogWrite(uint8_t channel, uint32_t value, uint32_t valueMax = 255) {
  // calculate duty, 8191 from 2 ^ 13 - 1
  uint32_t duty = (8191 / valueMax) * min(value, valueMax);

  // write duty to LEDC
  ledcWrite(channel, duty);
}

void setup() {
  // Setup timers and attach timer to the led pins
  ledcSetup(LEDC_CHANNEL_1, LEDC_BASE_FREQ, LEDC_TIMER_13_BIT);
  ledcAttachPin(LED1, LEDC_CHANNEL_1);
}

void loop() {
  // set the brightness on LEDC channel 0
  ledcAnalogWrite(LEDC_CHANNEL_1, brightness);

  // change the brightness for next time through the loop:
  brightness = brightness + fadeAmount;

  // reverse the direction of the fading at the ends of the fade:
  if (brightness <= 0 || brightness >= 255) {
    fadeAmount = -fadeAmount;
  }
  // wait for 30 milliseconds to see the dimming effect
  delay(30);
}
