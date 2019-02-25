// -------------------------------------------------------
// GhettoLED  -- by Dancorp (Fr) - Hardware Rev 1.2
// -------------------------------------------------------

#include <FastLED.h>
#include <EEPROM.h>
#include "Button.h"
// I-O  pins
# define LEFT_OUT_PIN 7         // Left channel data out pin to LEDs
# define RIGHT_OUT_PIN 6        // Right channel data out pin to LEDs
# define AUX1_OUT_PIN 5         // AUX1 channel data out pin to LEDs.
# define AUX2_OUT_PIN 4         // AUX2 channel data out pin to LEDs.
# define LEFT_IN_PIN A5         // Left aux in signal
# define RIGHT_IN_PIN A4        // Right aux in signal
# define RD_LED 10              // LED (a simple LED trigered by a NPN transistor)
# define BTN_PIN  3            // Push button on this pin

// LED Parameters (Warning : set up more than 120 led can cause unexcepted crashs)
# define N_PIXELS 30            // Number of pixels in LEFT/RIGHT string
# define N_PIXELS_AUX1 10       // Number of pixels in AUX1 string (VU Meters)
# define N_PIXELS_AUX2 9        // Number of pixels in AUX2 string (Cassette + tunner)
# define COLOR_ORDER GRB        // Try mixing up the letters (RGB, GBR, BRG, etc) for a whole new world of color combinations
# define BRIGHTNESS 200         // 0-255, higher number is brighter.
# define LED_TYPE WS2812B       // Probably WS2812B
# define N_PIXELS_HALF (N_PIXELS / 2)
# define TOP (N_PIXELS + 2)     // Allow dot to go slightly off scale

// Script Parameters
# define DC_OFFSET 0            // DC offset in aux signal - if unusure, leave 0
# define NOISE 25               // Noise/hum/interference in aux signal
# define SAMPLES 64             // Length of buffer for dynamic level adjustment
# define PEAK_FALL 10           // Rate of peak falling dot
# define DEBOUNCE_MS 20         // Number of ms to debounce the button 20 is default
# define LONG_PRESS 500         // Number of ms to hold the button to count as long press
# define PATTERN_TIME 20         // Seconds to show eaach pattern on auto
# define STANDBY_TIME 5         // Seconds to go to standby mode.
# define STANDBY_LVL  15         // Silence threshold for auto standby mgmt

uint8_t volCountLeft = 0; // Frame counter for storing past volume data
int volLeft[SAMPLES]; // Collection of prior volume samples
int lvlLeft = 1; // Current "dampened" audio level
int minLvlAvgLeft = 0; // For dynamic adjustment of graph low & high
int maxLvlAvgLeft = 512;

uint8_t volCountRight = 0; // Frame counter for storing past volume data
int volRight[SAMPLES]; // Collection of prior volume samples
int lvlRight = 10; // Current "dampened" audio level
int minLvlAvgRight = 0; // For dynamic adjustment of graph low & high
int maxLvlAvgRight = 512;
int Power = 1;
uint8_t Sleeptime = 0;
bool autoChangeVisuals = true;
bool RandomVisuals = false;

CRGB ledsLeft[N_PIXELS];
CRGB ledsRight[N_PIXELS];
CRGB ledsAux1[N_PIXELS_AUX1];
CRGB ledsAux2[N_PIXELS_AUX2];

uint8_t myhue = 0;
uint8_t myhue2 = 0;
void clearleds();
void vu4(bool is_centered, uint8_t channel);
void vu5(bool is_centered, uint8_t channel);
void vu6(bool is_centered, uint8_t channel);
void vu7(bool show_background);
void vu8();
void vu9();
void vu10();
void balls();
void fire();
void juggle();
void ripple(boolean show_background);
void sinelon();
void twinkle();
void rainbow(uint8_t rate, boolean Glitter, fract8 chanceOfGlitter);
void Brightdown ();
void plasma();



//  Button Stuff
uint8_t state = 0;
int buttonPushCounter = random(0, 17);
// int buttonPushCounter = 16;
Button modeBtn(BTN_PIN, DEBOUNCE_MS);

//Bool for Power Management

void setup() {
  delay(2000); // power-up safety delay
  digitalWrite(RD_LED, LOW);
  FastLED.addLeds < LED_TYPE, LEFT_OUT_PIN, COLOR_ORDER > (ledsLeft, N_PIXELS).setCorrection(TypicalLEDStrip);
  FastLED.addLeds < LED_TYPE, RIGHT_OUT_PIN, COLOR_ORDER > (ledsRight, N_PIXELS).setCorrection(TypicalLEDStrip);
  FastLED.addLeds < LED_TYPE, AUX1_OUT_PIN, COLOR_ORDER > (ledsAux1, N_PIXELS_AUX1).setCorrection(TypicalLEDStrip);
  FastLED.addLeds < LED_TYPE, AUX2_OUT_PIN, COLOR_ORDER > (ledsAux2, N_PIXELS_AUX2).setCorrection(TypicalLEDStrip);
  FastLED.setBrightness(BRIGHTNESS);
  Serial.begin(57600);
}


//----------------------
// Main Program aka loop
//----------------------

/* ---Power managment inforamtions---
 * Done using the Power variable
 * Power = 0 All Lights Off
 * Power = 1 AutoStandby Mode (Off) But Led is still up
 * Power = 2 AutoStandby Mode (On)
 * Power = 3 All Lights On whatever the volume level.
 */

void loop() {

  // Button State Managment
  modeBtn.read();
  switch (state) {

    case 0:
      if (modeBtn.wasReleased()) {
         
        if (Power == 0) {               //Short press can power up in standby mode
          Power = 2;
          Serial.println("--Power On Standby--");
          autoChangeVisuals = true;
          RandomVisuals = false;
          Serial.println("-Mode Auto-");
        }
        else if (Power > 1 && autoChangeVisuals) {       // leaving autochange without changing pattern
          autoChangeVisuals = false;
          RandomVisuals = true;
          Serial.println("-Mode Random-");
        }
        else if (Power > 1 && RandomVisuals) {
          RandomVisuals = false;
          Serial.println("-Mode Manual-");
        }
        else  {
          incrementButtonPushCounter();
        }
      }
      else if (modeBtn.pressedFor(LONG_PRESS))
        state = 1;
      break;

    case 1:
      if (modeBtn.wasReleased()) {
        state = 0;

        if (Power == 0) {
          Power = 3;
          Serial.println("--Power On Forced--");
          autoChangeVisuals = true;
          RandomVisuals =false;
        }
        else {
          Power = 0;
          Serial.println("--Power Off--");
        } // Long press always used to switch power (Auto / Off)

      }
      break;
  }









  // LIGHTS ON

  if (Power > 0 && Power < 3)
  {
    EVERY_N_SECONDS(1) {
      sleepmgnt(STANDBY_TIME);
    }
  }

  if (Power > 0) {
    digitalWrite(RD_LED, HIGH);
  }

  if (Power > 1) {



    FastLED.setBrightness(BRIGHTNESS);
    if (autoChangeVisuals) {
      EVERY_N_SECONDS(PATTERN_TIME) {
        incrementButtonPushCounter();
      }
      for (int dot = 0; dot < N_PIXELS_AUX2; dot++) {
        ledsAux2[dot] = CRGB::White; // Aux2 Color when Autochange
      }
    }

    else if (RandomVisuals) {
      EVERY_N_SECONDS(PATTERN_TIME) {
        buttonPushCounter = random(0, 16);
      }

      for (int dot = 0; dot < N_PIXELS_AUX2; dot++) {
        ledsAux2[dot] = CRGB::Orange; // Aux2 Color when Random
      }
    }
    else {
      for (int dot = 0; dot < N_PIXELS_AUX2; dot++) {
        ledsAux2[dot] = CRGB::Cyan; // Aux2 Color when Manual
      }
    }



    // AUX1 Effects Managment
    //if (buttonPushCounter % 2)  {  auxripple(true);} // noise mover effect on aux1 strip
    // else {auxripple(false);} // auxmeteorshower on aux1 strip

    for (int dotz = 0; dotz < N_PIXELS_AUX1; dotz++) {
      ledsAux1[dotz] = CRGB::Grey; // Aux Color
    }



    // Effects Switcher
    switch (buttonPushCounter) {
      case 0:
        vu10(); //rolling leds (like tape)
        break;

      case 1:
        vu5(true, 0);  // Vu Blue centered
        vu5(true, 1);
        break;

      case 2:
        juggle(); // Red meteors
        break;

      case 3:
        vu6(false, 0); //Vu Meter Rainbow
        vu6(false, 1);
        break;

      case 4:
        sinelon(); //kitt effect
        break;

      case 5:
        vu7(false); //Flashs
        break;

      case 6:
        twinkle(); // dots
        break;

      case 7:
        vu4(true, 0);  // Vu Green  centered
        vu4(true, 1);
        break;

      case 8:
        balls(); // bounding balls
        break;

      case 9:
        vu7(true); // Flash rings
        break;

      case 10:
        vu4(false, 0); // Vu Green not centered
        vu4(false, 1);
        break;

      case 11:
        rainbow(10, false, 80); //..rainbow !
        break;

      case 12:
        vu5(false, 0);  // Vu Violet not centered
        vu5(false, 1);
        break;

      case 13:
        vu9(); // rain / ocean wave
        break;

      case 14:
        vu8();// Three Mini VU
        break;

      case 15:
        ripple(true);  //Ripples (drops waves)
        break;

      case 16:
        fire(); //Fire
        break;

      case 17:
        plasma(); //Fire
        break;

    }
  }


  
  // LIGHTS OFF
  else {
    clearleds();
    digitalWrite(RD_LED, LOW); // Turn off the Radio LED

  }
}

//------------------------
// Button Counter Function
//------------------------
void incrementButtonPushCounter() {
  buttonPushCounter = ++buttonPushCounter % 18;
}


//-----------------------------
// Turn Off LED strips Function
//-----------------------------
void clearleds() { // Turn off all LEDs
  for (int dot = 0; dot < N_PIXELS; dot++) {
    ledsLeft[dot] = CRGB::Black;
    ledsRight[dot] = CRGB::Black;
  }
  for (int dot = 0; dot < N_PIXELS_AUX1; dot++) {
    ledsAux1[dot] = CRGB::Black;
  }
  for (int dot = 0; dot < N_PIXELS_AUX2; dot++) {
    ledsAux2[dot] = CRGB::Black;
  }
  FastLED.show();
}

//----------------------
// Auto Standby Function
//----------------------

void sleepmgnt(uint8_t time) {
  uint16_t avgsound;

  averageReadings(0);
  averageReadings(1);
  avgsound = (auxReading(0) + auxReading(1)) * 100 ;

  //Serial.print("Avg Volume ");
  //Serial.println(avgsound);

  if (Power == 2 && avgsound < STANDBY_LVL) {
    if (Sleeptime < time) {
      Serial.print("Timer ");
      Serial.println(Sleeptime);
      Sleeptime++;
    }
    else {
      Power = 1;
      Sleeptime = 0;
      Brightdown ();
    }
  }
  if (avgsound > STANDBY_LVL) {
    Sleeptime = 0;

  if (avgsound > STANDBY_LVL && Power == 1 ) {
    Power = 2;
      }
  }

}

//----------------------
// Line In Read Function
//----------------------
uint16_t auxReading(uint8_t channel) {

  int n = 0;
  uint16_t height = 0;

  if (channel == 0) {
    int n = analogRead(LEFT_IN_PIN); // Raw reading from left line in
    n = abs(n - 512 - DC_OFFSET); // Center on zero
    n = (n <= NOISE) ? 0 : (n - NOISE); // Remove noise/hum
    lvlLeft = ((lvlLeft * 7) + n) >> 3; // "Dampened" reading (else looks twitchy)
    volLeft[volCountLeft] = n; // Save sample for dynamic leveling
    volCountLeft = ++volCountLeft % SAMPLES;
    // Calculate bar height based on dynamic min/max levels (fixed point):
    height = TOP * (lvlLeft - minLvlAvgLeft) / (long)(maxLvlAvgLeft - minLvlAvgLeft);
  }

  else {
    int n = analogRead(RIGHT_IN_PIN); // Raw reading from mic
    n = abs(n - 512 - DC_OFFSET); // Center on zero
    n = (n <= NOISE) ? 0 : (n - NOISE); // Remove noise/hum
    lvlRight = ((lvlRight * 7) + n) >> 3; // "Dampened" reading (else looks twitchy)
    volRight[volCountRight] = n; // Save sample for dynamic leveling
    volCountRight = ++volCountRight % SAMPLES;
    // Calculate bar height based on dynamic min/max levels (fixed point):
    height = TOP * (lvlRight - minLvlAvgRight) / (long)(maxLvlAvgRight - minLvlAvgRight);
  }

  // Calculate bar height based on dynamic min/max levels (fixed point):
  height = constrain(height, 0, TOP);

  return height;
}

//--------------------
// Peak Drop  function
//--------------------
uint8_t peakLeft, peakRight;
void dropPeak(uint8_t channel) {

  static uint8_t dotCountLeft, dotCountRight;

  if (channel == 0) {
    if (++dotCountLeft >= PEAK_FALL) { //fall rate
      if (peakLeft > 0) peakLeft--;
      dotCountLeft = 0;
    }
  } else {
    if (++dotCountRight >= PEAK_FALL) { //fall rate
      if (peakRight > 0) peakRight--;
      dotCountRight = 0;
    }
  }
}

//-------------------------------------------
// Function for averaging the sample readings
//-------------------------------------------
void averageReadings(uint8_t channel) {

  uint16_t minLvl, maxLvl;

  // minLvl and maxLvl indicate the volume range over prior frames, used
  // for vertically scaling the output graph (so it looks interesting
  // regardless of volume level).  If they're too close together though
  // (e.g. at very low volume levels) the graph becomes super coarse
  // and 'jumpy'...so keep some minimum distance between them (this
  // also lets the graph go to zero when no sound is playing):
  if (channel == 0) {
    minLvl = maxLvl = volLeft[0];
    for (int i = 1; i < SAMPLES; i++) {
      if (volLeft[i] < minLvl) minLvl = volLeft[i];
      else if (volLeft[i] > maxLvl) maxLvl = volLeft[i];
    }
    if ((maxLvl - minLvl) < TOP) maxLvl = minLvl + TOP;

    minLvlAvgLeft = (minLvlAvgLeft * 63 + minLvl) >> 6; // Dampen min/max levels
    maxLvlAvgLeft = (maxLvlAvgLeft * 63 + maxLvl) >> 6; // (fake rolling average)
  }

  else {
    minLvl = maxLvl = volRight[0];
    for (int i = 1; i < SAMPLES; i++) {
      if (volRight[i] < minLvl) minLvl = volRight[i];
      else if (volRight[i] > maxLvl) maxLvl = volRight[i];
    }
    if ((maxLvl - minLvl) < TOP) maxLvl = minLvl + TOP;
    minLvlAvgRight = (minLvlAvgLeft * 63 + minLvl) >> 6; // Dampen min/max levels
    maxLvlAvgRight = (maxLvlAvgLeft * 63 + maxLvl) >> 6; // (fake rolling average)
  }

}

void  Brightdown ()
{
int bi = BRIGHTNESS;
while (bi > 0) {
  FastLED.setBrightness(bi);
  FastLED.show();
  bi--;
}
}

