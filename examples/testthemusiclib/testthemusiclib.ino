#include <MelodyPlayer.h>

// Pin Assignments:
const int speaker = 8;

/**
 * Opening notes to Bach's Bwv565 Toccata in d minor.
 */
onenote bwvMelody[] = {
  {NOTE_A5, 4}, {NOTE_G5, 4}, {NOTE_A5, 4}, {0, 4},
  {NOTE_G5, 12}, {NOTE_F5, 12}, {NOTE_E5, 12}, {NOTE_D5, 12}, {NOTE_CS5, 4}, {NOTE_D5, 4}, {0, 2}
};

/**
 * G major scale.
 */
onenote gscale[] = {
  {NOTE_G2, 4}, {NOTE_A2, 4}, {NOTE_B2, 4}, {NOTE_C3, 4},
  {NOTE_D3, 4}, {NOTE_E3, 4}, {NOTE_FS3, 4}, {NOTE_G3, 4}, {0, 2}
};

MelodyPlayer bwv565(speaker, bwvMelody);
MelodyPlayer gmscale(speaker, gscale);

bool playingscale;

void setup() {
  bwv565.Play();
  playingscale = false;
}

void loop() {
  if (playingscale) {
    if (!gmscale.IsPlaying()) {
      bwv565.FromTheTop();
      bwv565.Play();
      playingscale = false;
    }
  } else {
    if (!bwv565.IsPlaying()) {
      gmscale.FromTheTop();
      gmscale.Play();    
      playingscale = true;
    }
  }
  bwv565.Update();
  gmscale.Update();
}

