/**
 * This is a simple Arduino music player that plays an arbitrary-length melody without
 * using the tone() call with the third argument (duration), which blocks all other
 * processing while playing.
 *
 * Provide it a pin and an array of onenote structs to play.
 */

#include "MelodyPlayer.h"

/**
 * Class Constructor.
 * pin: Which pin has the speaker attached.
 * playmelody: Reference to the array of notes to play.
 */
//template <size_t noteCount>
//MelodyPlayer::MelodyPlayer(int speakerPin, onenote (&playmelody)[noteCount]) {
//  melody = playmelody;
//  songlength = sizeof(playmelody) / sizeof(onenote);
//  pin = speakerPin;
//  note = 0;
//  prevMillis = 0;
//  currDuration = 0;
//  quiet = true;
//}

void MelodyPlayer::Play() {
  quiet = false;
  prevMillis = millis();
  // Note duration is one second divided by the note type.
  // A quarter note = 1000 / 4, eighth note = 1000/8, etc.
  currDuration = 1000 / melody[note].duration;
  // A pitch of 0 is a rest. Don't call tone.
  if (melody[note].pitch != 0) {
    tone(pin, melody[note].pitch);
  }
}

/**
 * Is this playing notes?
 */
bool MelodyPlayer::IsPlaying() {
  return !quiet;
}

/**
 * Pause playing. If Play() is called next, it will resume playback
 * where stopped. To reset to the beginning of the song, call the
 * FromTheTop() method.
 */
void MelodyPlayer::Pause() {
  noTone(pin);
  quiet = true;
}

/**
 * Reset playback to the beginning of the song.
 */
void MelodyPlayer::FromTheTop() {
  note = 0;
  prevMillis = 0;
  currDuration = 0;
  quiet = true;
}

/**
 * Call this periodically from loop() while you want the notes to play.
 */
void MelodyPlayer::Update() {
  // If not currently playing, exit method ASAP.
  if (quiet) {
    return;
  }

  int currMillis = millis();
  // Is it time to play the next note?
  if ((currMillis - prevMillis) >= currDuration) {
    // Stop playing the last note.
    noTone(pin);
    note++;

    // Might be the end of the song.
    if (note >= songlength) {
      // Yes, it's the end. Reset for next time.
      quiet = true;
      note = 0;
      prevMillis = 0;
      currDuration = 0;
    } else {
      // No, play the next note.
      prevMillis = currMillis;
      // Note duration is one second divided by the note type.
      // A quarter note = 1000 / 4, eighth note = 1000/8, etc.
      currDuration = 1000 / melody[note].duration;
      // A pitch of 0 is a rest. Don't call tone.
      if (melody[note].pitch != 0) {
        tone(pin, melody[note].pitch);
      }
    }
  }
}
