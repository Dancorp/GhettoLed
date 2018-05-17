void auxsinelon() {

fadeToBlackBy(ledsAux1, N_PIXELS_AUX1, 20);//fading lenght
byte poss = beatsin8( 50, 0, N_PIXELS_AUX1-1 ); //speed
ledsAux1[poss] = CRGB::Red;
/*ledsAux1[pos] = CHSV( myhue, 255, 255);
EVERY_N_MILLISECONDS(40) {
myhue++;
}*/
 FastLED.show();

}
