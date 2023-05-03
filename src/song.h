#include <mcs51/8051.h>
#include "config.h"
#define VELOCITIES_TH 252
#define VELOCITIES_TL 102
#define SONG_METER 312
struct _Freq
{
  unsigned short th:8;
  unsigned short tl:8;
};

typedef struct _Freq Freq;


struct _Song
{
  int freq:4;
  int length:4;
};

typedef struct _Song Song;
void song_timer (void) __interrupt 1;
void note_timer (void) __interrupt 3;
void play_song (void);