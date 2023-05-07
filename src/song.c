#include "song.h"
#include "music.h"

static int note;
static int song_index;
static int note_is_zero;
static unsigned int song_timer_count;
static unsigned int song_th1;
static unsigned int song_tl1;
static int song_timer_meter;
static Freq *song_freq_table;
static int song_timer_breathe;
static int song_length_now;
static Song *song_now;
static void song_set_note (void)
{
  if ((song_now + note)->freq)
    {
      song_th1 = (song_freq_table + (song_now + note)->freq)->th;
      song_tl1 = (song_freq_table + (song_now + note)->freq)->tl;
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
  if (note < song_length_now)
    note += 1;
  else
    {
      song_init ();
      return;
    }
  song_timer_count = (song_now + note)->length;
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
  song_index = 0;
  song_now = songs[song_index];
  song_timer_count = (song_now + note)->length;
  song_length_now = song_length[song_index];
  song_freq_table = freq_tables[song_index];
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
