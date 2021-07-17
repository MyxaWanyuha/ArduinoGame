#include "Sound.h"

void SoundManager::PlayMelody( MelodyID id, bool cycle )
{
  if ( id == MelodyID::None ) return;

  const auto time = millis();

  if ( melodyPlaying != id )
  {
    melodyPlaying = id;
    melodyNote = 0;
    playNext = 0;
  }

  if ( ( melodyPlaying != MelodyID::None ) && ( time > playNext ) )
  {
    const uint16_t* melody = GetMelody( id );
    if ( melody[melodyNote] != melodyEnd )
    {
      if ( melody[melodyNote] )
        tone( pinSpeaker, melody[melodyNote], melody[melodyNote + 1] );
      else
        noTone( pinSpeaker );

      playNext = time + melody[melodyNote + 1] * 1.11;
      melodyNote += 2;
    }
    else if ( cycle )
    {
      melodyNote = 0;
      playNext = 0;
    }
  }
}

void SoundManager::Beep()
{
  tone( pinSpeaker, 147, BeepTimeout );
}

const uint16_t* SoundManager::GetMelody( MelodyID id )
{
  if ( MelodyID::Intro == id )
    return melodyIntro;
  if ( MelodyID::GameStart == id )
    return melodyGameStart;
  return melodyGameOver;
}
