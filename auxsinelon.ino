void auxsinelon() {

fadeToBlackBy(ledsAux1, N_PIXELS_AUX1, 10);
byte pos = beatsin8( 30, 0, N_PIXELS_AUX1-1 );
ledsAux1[pos] = CHSV( myhue, 255, 255);
EVERY_N_MILLISECONDS(40) {
myhue++;
}
 FastLED.show();

}
