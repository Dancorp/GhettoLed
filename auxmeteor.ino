void meteorRain(byte red, byte green, byte blue, byte meteorSize, byte meteorTrailDecay, boolean meteorRandomDecay, int SpeedDelay) {  

for(int i = 0; i < N_PIXELS_AUX1; i++ ) {
  ledsAux1[i] = CRGB::Black;
  }
FastLED.show();
  for(int i = 0; i < N_PIXELS_AUX1+N_PIXELS_AUX1; i++) {
    
    
    // fade brightness all LEDs one step
    for(int j=0; j<N_PIXELS_AUX1; j++) {
      if( (!meteorRandomDecay) || (random(10)>5) ) {
         ledsAux1[j].fadeToBlackBy( meteorTrailDecay );
      }
    }
    
    // draw meteor
    for(int j = 0; j < meteorSize; j++) {
      if( ( i-j <N_PIXELS_AUX1) && (i-j>=0) ) {
        ledsAux1[i-j] = CRGB(red, green, blue);
       } 
    }
   
   FastLED.show();
   delay(SpeedDelay);
  }
}


