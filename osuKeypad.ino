#include <CapacitiveSensor.h>
#include <HID-Project.h>

/**
 * Thresholds and delays depend on your setup. Adjust using serial debug.
 * Below are some values I use with a 100Kohm resistor. Higher resistance gives bigger values.
 */
#define PRESS_DELAY 3
#define RELEASE_DELAY 3
#define PRESS_THRESHOLD 5
#define RELEASE_THRESHOLD 2

CapacitiveSensor key1_sensor = CapacitiveSensor(A0, A1);
bool key1_pressed = false;
int key1_pressDelay = PRESS_DELAY;
int key1_releaseDelay = RELEASE_DELAY;
CapacitiveSensor key2_sensor = CapacitiveSensor(A2, A3);
bool key2_pressed = false;
int key2_pressDelay = PRESS_DELAY;
int key2_releaseDelay = RELEASE_DELAY;
long sample = 0;

void setup() {
  //Serial.begin(115200);
  pinMode(LED_BUILTIN_TX,INPUT);
  pinMode(LED_BUILTIN_RX,INPUT);
  key1_sensor.set_CS_Timeout_Millis(10);
  key2_sensor.set_CS_Timeout_Millis(10);
  BootKeyboard.begin();
}

void loop() {
  sample = key1_sensor.capacitiveSensorRaw(1);
  //Serial.println(sample);
  if (sample > PRESS_THRESHOLD) {
    if (!key1_pressed) {
      if (key1_pressDelay == 0) {
        key1_pressed = true;
        BootKeyboard.press(KEY_QUOTE);
      } else {
        key1_pressDelay--;
      }
    }
    key1_releaseDelay = RELEASE_DELAY;
  } else if (sample < RELEASE_THRESHOLD) {
    if (key1_pressed) {
      if (key1_releaseDelay == 0) {
        key1_pressed = false;
        BootKeyboard.release(KEY_QUOTE);
      } else {
        key1_releaseDelay--;
      }
    }
    key1_pressDelay = PRESS_DELAY;
  }

  sample = key2_sensor.capacitiveSensorRaw(1);
  //Serial.println(sample);
  if (sample > PRESS_THRESHOLD) {
    if (!key2_pressed) {
      if (key2_pressDelay == 0) {
        key2_pressed = true;
        BootKeyboard.press(KEY_SEMICOLON);
      } else {
        key2_pressDelay--;
      }
    }
    key2_releaseDelay = RELEASE_DELAY;
  } else if (sample < RELEASE_THRESHOLD) {
    if (key2_pressed) {
      if (key2_releaseDelay == 0) {
        key2_pressed = false;
        BootKeyboard.release(KEY_SEMICOLON);
      } else {
        key2_releaseDelay--;
      }
    }
    key2_pressDelay = PRESS_DELAY;
  }
}
