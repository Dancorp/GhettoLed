void meteorRain(byte meteorSize, byte meteorTrailDecay, boolean meteorRandomDecay, int SpeedDelay) {  

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
        ledsAux1[i-j] = CHSV(myhue2, 255, 255);
     // ledsAux1[i-j] = CRGB::Red;
     
        EVERY_N_MILLISECONDS(120) {
        myhue2++;
        }
        
       } 
    }
   
   FastLED.show();
   delay(SpeedDelay);
  }
}


