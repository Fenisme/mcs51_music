#include <mcs51/8051.h>
#include "config.h"
#define VELOCITIES_TH 252
#define VELOCITIES_TL 24
#define SONG_METER 230
#define BREATHE_METER 23
struct _Freq
{
  unsigned short th:8;
  unsigned short tl:8;
};

typedef struct _Freq Freq;


struct _Song
{
  int freq:8;
  int length:8;
};

typedef struct _Song Song;
void song_timer (void) __interrupt 1;
void note_timer (void) __interrupt 3;
void song_init (void);
void song_play (void);
