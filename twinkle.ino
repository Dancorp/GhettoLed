void twinkle() {
  if (random(25) == 1) {
    uint16_t i = random(N_PIXELS);
    ledsLeft[i] = CRGB(random(256), random(256), random(256));
  }

  if (random(25) == 1) {
    uint16_t i = random(N_PIXELS);
    ledsRight[i] = CRGB(random(256), random(256), random(256));
  }

  fadeToBlackBy(ledsLeft, N_PIXELS, FADE_RATE);
  fadeToBlackBy(ledsRight, N_PIXELS, FADE_RATE);
  
  FastLED.show();
  delay(10);
}
