#ifndef SOUND_H
#define SOUND_H
#include <Arduino.h>

enum class MelodyID : uint8_t
{
  None = 0,
  Intro,
  GameStart,
  GameOver,
};

const uint16_t melodyEnd = 4096;
const uint16_t melodyIntro[] = { 440,90,0,90,440,90,0,90,220,90,220,90,220,90,0,900,440,90,0,90,440,90,0,90,220,90,220,90,220,90,0,900,440,90,0,90,440,90,0,90,220,90,220,90,220,90,0,900,293,90,0,90,293,90,0,90,146,90,146,90,146,90,0,900,melodyEnd };
const uint16_t melodyGameStart[] = { 659,98,783,98,987,98,783,98,622,98,739,98,987,98,739,98,523,98,659,98,783,98,659,98,493,98,622,98,739,98,987,98,987,293,melodyEnd };
const uint16_t melodyGameOver[] = { 369, 75, 349, 75, 311, 75, 277, 75, 261, 75, 233, 75, 220, 450, 220, 225, melodyEnd };

class SoundManager
{
public:
  void PlayMelody( MelodyID id, bool cycle = false );
  void Beep();
private:
  const uint16_t* GetMelody( MelodyID id );

  MelodyID melodyPlaying = MelodyID::None;
  uint8_t melodyNote = 0;
  uint64_t playNext = 0;

  const uint8_t pinSpeaker = 8;
  const uint8_t BeepTimeout = 50;
};

#endif // SOUND_H
