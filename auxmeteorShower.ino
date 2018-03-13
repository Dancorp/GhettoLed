/*
From: Peter Routon
Date: December 2014
This is my adaptation and simplification (i.e., reduced options) of meteorShower, Jon Burroughs' adaptation
of some funkboxing code from Thomas Eldridge.
*/


uint8_t hue = 32;
byte idex = 255;
byte meteorLength = 29;

void auxmeteorShower(){
  // slide all the pixels down one in the array
  memmove8( &ledsAux1[1], &ledsAux1[0], (N_PIXELS_AUX1 - 1) * 3 );

  // increment the meteor display frame
  idex++;
  // make sure we don't drift into space
  if ( idex > meteorLength ) {
    idex = 0;
    // cycle through hues in each successive meteor tail
    hue += 32;  
  }

  // this switch controls the actual meteor animation, i.e., what gets placed in the
  // first position and then subsequently gets moved down the strip by the memmove above
  switch ( idex ) {
  case 0:
    ledsAux1[0] = CRGB(200,200,200); 
    break;
  case 1:
    ledsAux1[0] = CHSV((hue - 20), 255, 210); 
    break;
  case 2:
    ledsAux1[0] = CHSV((hue - 22), 255, 180); 
    break;
  case 3:
    ledsAux1[0] = CHSV((hue - 23), 255, 150); 
    break;
  case 4:
    ledsAux1[0] = CHSV((hue - 24), 255, 110); 
    break;
  case 5:
    ledsAux1[0] = CHSV((hue - 25), 255, 90); 
    break;
  case 6:
    ledsAux1[0] = CHSV((hue - 26), 160, 60); 
    break;
  case 7:
    ledsAux1[0] = CHSV((hue - 27), 140, 40); 
    break;
  case 8:
    ledsAux1[0] = CHSV((hue - 28), 120, 20); 
    break;
  case 9:
    ledsAux1[0] = CHSV((hue - 29), 100, 20); 
    break;
  default:
    ledsAux1[0] = CRGB::Black; 
  }

  // show the blinky
  FastLED.show();  
  // control the animation speed/frame rate
  delay(30);
}
