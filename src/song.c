#include "song.h"
const static Freq freq_table[] =
{
  {0, 0},
  {253, 180},
  {253, 69},
  {253, 108},
  {252, 239},
  {253, 244},
  {254, 119},
  {254, 71},
  {254, 162},
  {254, 182},
  {254, 218},
  {254, 250},
  {255, 35},
  {255, 59},
};

const static Song test_song[] =
{
  {1, 2},{2, 2},{3, 2},{4, 2},{1, 2},{2, 2},{3, 2},{4, 2},{1, 2}, /* 1 */ 
  {2, 2},{3, 2},{4, 2},{1, 2},{2, 2},{3, 2},{4, 2},{1, 2}, /* 2 */ 
  {2, 2},{3, 2},{4, 2},{1, 2},{2, 2},{3, 2},{4, 2},{1, 2}, /* 3 */ 
  {2, 2},{3, 2},{4, 2},{1, 2},{2, 2},{3, 2},{4, 2},{1, 2}, /* 4 */ 
  {2, 2},{3, 2},{4, 2},{1, 2},{2, 2},{3, 2},{4, 2},{5, 8}, /* 5 */ 
  {0, 5},{3, 1},{1, 1},{3, 1},{5, 8}, /* 6 */ 
  {0, 3},{3, 1},{1, 1},{3, 1},{1, 1},{5, 1},{4, 3}, /* 7 */ 
  {3, 1},{4, 3},{3, 1},{4, 3},{3, 1},{1, 2},{3, 2},{2, 8}, /* 8 */ 
  {0, 8},{4, 1}, /* 9 */ 
  {3, 1},{6, 3},{6, 1},{6, 1},{7, 1},{6, 2},{6, 1},{7, 1},{6, 1},{7, 1},{6, 1},{7, 1},{5, 1}, /* 10 */ 
  {5, 7},{0, 6},{4, 1},{3, 1},{6, 3}, /* 11 */ 
  {6, 1},{6, 1},{7, 1},{6, 1},{7, 1},{8, 3},{8, 1},{8, 1},{6, 1},{8, 3}, /* 12 */ 
  {6, 2},{5, 9},{0, 1},{5, 1},{7, 1},{5, 1},{1, 3}, /* 13 */ 
  {5, 1},{1, 3},{5, 1},{1, 3},{5, 1},{7, 1},{5, 1},{7, 1},{5, 1},{1, 3}, /* 14 */ 
  {5, 1},{1, 3},{5, 1},{1, 4},{0, 2},{3, 1},{1, 1},{5, 2}, /* 15 */ 
  {4, 2},{3, 2},{5, 2},{1, 3},{5, 1},{1, 1},{3, 1},{3, 2},{4, 8}, /* 16 */ 
  {0, 6},{6, 1},{8, 1},{9, 1}, /* 17 */ 
  {10, 1},{8, 1},{9, 1},{9, 2},{9, 1},{8, 1},{9, 1},{10, 1},{8, 1},{9, 1},{9, 2},{9, 1},{10, 1},{11, 1}, /* 18 */ 
  {10, 1},{11, 1},{10, 1},{11, 2},{11, 1},{10, 1},{11, 2},{12, 2},{11, 2},{6, 1},{8, 1},{9, 1}, /* 19 */ 
  {10, 1},{8, 1},{9, 1},{9, 2},{9, 1},{8, 1},{9, 1},{10, 1},{8, 1},{9, 1},{9, 2},{9, 1},{10, 1},{11, 1}, /* 20 */ 
  {10, 1},{11, 1},{10, 1},{11, 2},{11, 1},{10, 1},{11, 2},{12, 2},{11, 2},{12, 2},{11, 3}, /* 21 */ 
  {12, 1},{11, 3},{12, 1},{11, 1},{12, 1},{13, 1},{11, 1},{12, 2},{12, 2},{11, 3}, /* 22 */ 
  {12, 1},{11, 3},{12, 1},{11, 1},{12, 1},{13, 1},{11, 1},{12, 2},{12, 1},{12, 1},{11, 1}, /* 23 */ 
  {10, 1},{10, 2},{10, 2},{9, 1},{11, 2},{10, 1},{10, 2},{10, 2},{9, 1},{9, 1},{6, 8}, /* 24 */ 
  {0, 6},{12, 1},{12, 1},{11, 1}, /* 25 */ 
  {10, 1},{10, 2},{10, 2},{9, 1},{11, 2},{10, 2},{10, 2},{9, 1},{9, 1},{6, 8}, /* 26 */ 
  {0, 8},
};

static int note;
static int note_is_zero;
static unsigned int song_timer_count;
static unsigned int song_th1;
static unsigned int song_tl1;
static int song_timer_meter;
static int song_timer_breathe;
static void song_set_note (void)
{
  if (test_song[note].freq)
    {
      song_th1 = freq_table[test_song[note].freq].th;
      song_tl1 = freq_table[test_song[note].freq].tl;
      note_is_zero = 0;
    }
  else
    note_is_zero = 1;
    buzz_stop ();
}

static void song_next_note (void)
{
  buzz_stop ();
  song_timer_breathe = BREATHE_METER;
  if (note < sizeof(test_song))
    note += 1;
  else
    {
      song_init ();
      return;
    }
  song_timer_count = test_song[note].length;
  song_set_note ();
}

void song_timer (void) __interrupt 1
{
  if (song_timer_breathe)
    song_timer_breathe -= 1;
  else if (!note_is_zero)
    buzz_resume ();
  song_timer_meter -= 1;
  if (song_timer_meter == 0) 
    {
      song_timer_count -= 1;
      song_timer_meter = SONG_METER;
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
  buzz_switch ();
}

void song_init (void)
{
  TMOD = 0x11;
  note = 0;
  song_timer_count = test_song[note].length;
  TH0 = VELOCITIES_TH;
  TL0 = VELOCITIES_TL;
  song_timer_meter = SONG_METER;
  ET0 = 1;
  ET1 = 1;
  song_set_note ();
  EA = 0;
  TR0 = 0;
  TR1 = 0;
  buzz_stop ();
}

void song_play (void)
{
  TR0 = 1;
  TR1 = 1;
  EA = 1;
}
