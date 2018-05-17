/*
 * Looks like fire! Both channels are seperate and random
 */

void auxfire() {
  const uint8_t AUXCOOLING = 55;
  const uint8_t AUXSPARKING = 50;
  
  // Array of temperature readings at each simulation cell
  static byte auxheat[N_PIXELS_AUX1];
 
  // Step 1.  Cool down every cell a little
  for (int m = 0; m < N_PIXELS_AUX1; m++) {
    auxheat[m] = qsub8(auxheat[m], random8(0, ((AUXCOOLING * 10) / N_PIXELS_AUX1) + 2));
  }

  // Step 2.  Heat from each cell drifts 'up' and diffuses a little
  for (int n = N_PIXELS_AUX1 - 1; n >= 2; n--) {
    auxheat[n] = (auxheat[n - 1] + auxheat[n - 2] + auxheat[n - 2]) / 3;
  }

  // Step 3.  Randomly ignite new 'sparks' of heat near the bottom
  if (random8() < AUXSPARKING) {
    int p = random8(7);
    auxheat[p] = qadd8(auxheat[p], random8(160, 255));
  }

  // Step 4.  Map from heat cells to LED colors
  for (int q = 0; q < N_PIXELS_AUX1; q++) {
    // Scale the heat value from 0-255 down to 0-240
    // for best results with color palettes.
    byte auxcolorindex = scale8(auxheat[q], 240);
    CRGB auxcolor = ColorFromPalette(CRGBPalette16(CRGB::Black, CRGB::Red, CRGB::Yellow, CRGB::White), auxcolorindex);
    int auxpixelnumber = q;
    ledsAux1[auxpixelnumber] = auxcolor;
  }

  FastLED.show();
}
