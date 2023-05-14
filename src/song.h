#ifndef __SONG_H__
#define __SONG_H__
#include <mcs51/8051.h>
#include "config.h"
struct _Freq
{
  unsigned short th:8;
  unsigned short tl:8;
};

typedef struct _Freq Freq;


struct _Song
{
  unsigned int freq:4;
  unsigned int length:4;
};

typedef struct _Song Song;
void song_timer (void) __interrupt 1;
void note_timer (void) __interrupt 3;
void song_init ();
void song_play (void);
void song_pause (void);
void song_next (void);
void song_switch (void);
void song_replay (void);
int song_get_index (void);
int song_get_status (void);
#endif
