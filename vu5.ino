/*
 * Old-skool green and red from bottom or middle N_PIXELS
 */

void vu5(bool is_centered, uint8_t channel) {

  CRGB* leds;
  uint8_t i = 0;
  uint8_t *peak;      // Pointer variable declaration
  uint16_t height = auxReading(channel);

  if(channel == 0) {
    leds = ledsLeft;    // Store address of peakLeft in peak, then use *peak to
    peak = &peakLeft;   // access the value of that address
  }
  else {
    leds = ledsRight;
    peak = &peakRight;
  }

  if (height > *peak)
    *peak = height; // Keep 'peak' dot at top

  if(is_centered) {
    // Color pixels based on old school green / red
    for (uint8_t i = 0; i < N_PIXELS_HALF; i++) {
      if (i >= height) {
        // Pixels greater than peak, no light
        //leds[N_PIXELS_HALF - i - 1] = CRGB::Black;
        //leds[N_PIXELS_HALF + i] = CRGB::Black;
            leds[N_PIXELS - i - 1] = CRGB::Black;
            leds[i] = CRGB::Black;
      } else {
        if (i > N_PIXELS_HALF - (N_PIXELS_HALF / 3)){
          //leds[N_PIXELS_HALF - i - 1] = CRGB::Red;
          //leds[N_PIXELS_HALF + i] = CRGB::Red;
            leds[N_PIXELS - i - 1] = CRGB::Yellow;
            leds[i] = CRGB::Yellow;
        }
        else {
          //leds[N_PIXELS_HALF - i - 1] = CRGB::Blue;
          //leds[N_PIXELS_HALF + i] = CRGB::Blue;
            leds[N_PIXELS - i - 1] = CRGB(255, 0, 255);
            leds[i] = CRGB(51, 153, 255);
        }
      }
    }
  
    // Draw peak dot
    if (*peak > 0 && *peak <= N_PIXELS_HALF - 1) {
      if (*peak > N_PIXELS_HALF - (N_PIXELS_HALF / 3)){
        //leds[N_PIXELS_HALF - *peak - 1] = CRGB::Red;
        //leds[N_PIXELS_HALF + *peak] = CRGB::Red;
        leds[N_PIXELS - *peak - 1] = CRGB::White;
        leds[*peak] = CRGB::White;
      } else {
        //leds[N_PIXELS_HALF - *peak - 1] = CRGB::Green;
        //leds[N_PIXELS_HALF + *peak] = CRGB::Green;
        leds[N_PIXELS - *peak - 1] = CRGB::Yellow;
        leds[*peak] = CRGB::Yellow;
      }
    }
    
  } else {
    // Color pixels based on old school green/red vu
    for (uint8_t i = 0; i < N_PIXELS; i++) {
      if (i >= height) leds[i] = CRGB::Black;
      else if (i > N_PIXELS - (N_PIXELS / 3)) leds[i] = CRGB::Yellow;
      else leds[i] = CRGB::Yellow;
    }
  
    // Draw peak dot
    if (*peak > 0 && *peak <= N_PIXELS - 1)
      if (*peak > N_PIXELS - (N_PIXELS / 3)) leds[*peak] = CRGB::Yellow;
      else leds[*peak] = CRGB::Yellow;
  }
  
  dropPeak(channel);

  averageReadings(channel);

  FastLED.show();
}
