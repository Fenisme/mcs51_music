#include "song.h"
static Freq freq_table[] =
{
  {0, 0},
  {250, 54},
  {250, 216},
  {251, 104},
  {251, 170},
  {252, 35},
  {252, 192},
  {248, 70},
};

static Song test_song[] =
{
  {1, 2},
  {2, 2},
  {3, 2},
  {1, 2},
  {1, 2},
  {2, 2},
  {3, 2},
  {1, 2},
  {3, 2},
  {4, 2},
  {5, 4},
  {3, 2},
  {4, 2},
  {5, 4},
  {5, 1},
  {6, 1},
  {5, 1},
  {4, 1},
  {3, 2},
  {1, 2},
  {5, 1},
  {6, 1},
  {5, 1},
  {4, 1},
  {3, 2},
  {1, 2},
  {3, 2},
  {7, 2},
  {1, 4},
  {3, 2},
  {7, 2},
  {1, 4},
};
static unsigned int song_timer_count;
static int note;
static unsigned int song_th1;
static unsigned int song_tl1;
static int song_timer_meter;
static void song_set_note (void)
{
  if (test_song[note].freq)
    {
      song_th1 = freq_table[test_song[note].freq].th;
      song_tl1 = freq_table[test_song[note].freq].tl;
      TR1 = 1;
    }
  else
    TR1 = 0;
}

static void song_next_note (void)
{
  TR1 = 0;
  if (note < sizeof(test_song))
    note += 1;
  else
    note = 0;
  song_timer_count = test_song[note].length;
  song_set_note ();
  TR1 = 1;
}

void song_timer (void) __interrupt 1
{
  song_timer_meter -= 1;
  if (song_timer_meter == 0) 
    {
      song_timer_count -= 1;
      song_timer_meter = SONG_METER;
      P2_1 = !P2_1;
    }
  if (song_timer_count <= 0)
    song_next_note ();
  TH0 = VELOCITIES_TH;
  TL0 = VELOCITIES_TL;
}

void note_timer (void) __interrupt 3
{
  TH1 = song_th1;
  TL1 = song_tl1;
  BUZZ = !BUZZ;
}

void play_song (void)
{
  TMOD = 0x11;
  note = 0;
  song_timer_count = test_song[note].length;
  TH0 = VELOCITIES_TH;
  TL0 = VELOCITIES_TL;
  song_timer_meter = SONG_METER;
  ET0 = 1;
  song_set_note ();
  ET1 = 1;
  TR0 = 1;
  TR1 = 1;
  EA = 1;
}
