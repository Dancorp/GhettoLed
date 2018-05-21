void ripple(boolean show_background) {

  const float RIPPLE_FADE_RATE = 0.80;
  const uint8_t MAX_STEPS = 16;
  static uint8_t rippleColor = 0;
  static uint8_t rippleCenter = 0;
  static int rippleStep = -1;

  // -- fill background --
  EVERY_N_MILLISECONDS(10) {
    myhue++;
  }
  if (show_background) {
    fill_solid(ledsLeft, N_PIXELS, CRGB::Blue);
  } else {
    fill_solid(ledsLeft, N_PIXELS, CRGB::Black);
  }

  EVERY_N_MILLISECONDS(50) {
    // -- do ripple --
    if (rippleStep == -1) {
      rippleCenter = random(N_PIXELS);
      rippleColor = myhue + 128;
      rippleStep = 0;
    }

    if (rippleStep == 0) {
      ledsLeft[rippleCenter] = CHSV(rippleColor, 255, 255);
      rippleStep++;
    } else {
      if (rippleStep < MAX_STEPS) {
        ledsLeft[wrap(rippleCenter + rippleStep)] = CHSV(rippleColor, 255, pow(RIPPLE_FADE_RATE, rippleStep) * 255);
        ledsLeft[wrap(rippleCenter - rippleStep)] = CHSV(rippleColor, 255, pow(RIPPLE_FADE_RATE, rippleStep) * 255);
        if (rippleStep > 3) {
          ledsLeft[wrap(rippleCenter + rippleStep - 3)] = CHSV(rippleColor, 255, pow(RIPPLE_FADE_RATE, rippleStep - 2) * 255);
          ledsLeft[wrap(rippleCenter - rippleStep + 3)] = CHSV(rippleColor, 255, pow(RIPPLE_FADE_RATE, rippleStep - 2) * 255);
        }
        rippleStep++;
      } else {
        rippleStep = -1;
      }
    }
  }

  // Copy left LED array into right LED array
  for (uint8_t i = 0; i < N_PIXELS; i++) {
    ledsRight[i] = ledsLeft[i];
  }

  FastLED.show();
  delay(50);
}

int wrap(int rippleStep) {
  if (rippleStep < 0) return N_PIXELS + rippleStep;
  if (rippleStep > N_PIXELS - 1) return rippleStep - N_PIXELS;
  return rippleStep;
}
