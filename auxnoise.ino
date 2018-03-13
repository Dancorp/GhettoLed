CRGBPalette16 currentPaletteNoise=LavaColors_p;
CRGBPalette16 targetPaletteNoise=OceanColors_p;
TBlendType    currentBlending;   
//static int16_t dist;                                          // A moving location for our noise generator.
uint16_t xscale = 30;                                         // Wouldn't recommend changing this on the fly, or the animation will be really blocky.
uint16_t yscale = 30;                                         // Wouldn't recommend changing this on the fly, or the animation will be really blocky.
uint8_t maxChanges = 24; 


void auxnoise() {

  EVERY_N_MILLISECONDS(20) {
    nblendPaletteTowardPalette(currentPaletteNoise, targetPaletteNoise, maxChanges);   // AWESOME palette blending capability.
    inoise8_mover();                                    // Update the LED array with noise at the new location
    fadeToBlackBy(ledsAux1, N_PIXELS_AUX1, 16);     
  }

  EVERY_N_SECONDS(5) {                                        // Change the target palette to a random one every 5 seconds.
    targetPaletteNoise = CRGBPalette16(CHSV(random8(), 255, random8(128,255)), CHSV(random8(), 255, random8(128,255)), CHSV(random8(), 192, random8(128,255)), CHSV(random8(), 255, random8(128,255)));
  }
 
  FastLED.show();
}

void inoise8_mover() {

  for (int i=0; i<20; i++) {
    uint8_t locn = inoise8(xscale, dist+yscale+i*200);  // Get a new pixel location from moving noise. locn rarely goes below 48 or above 192, so let's remove those ends.
    locn = constrain(locn,48,192);                      // Ensure that the occasional value outside those limits is not used.
    uint8_t pixlen = map(locn,48,192,0,N_PIXELS_AUX1-1);     // Map doesn't constrain, so we now map locn to the the length of the strand.
    ledsAux1[pixlen] = ColorFromPalette(currentPaletteNoise, pixlen, 255, LINEARBLEND);   // Use that value for both the location as well as the palette index colour for the pixel.
  }

  dist += beatsin8(10,1,4);      
}








