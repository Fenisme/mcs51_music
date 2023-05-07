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
static int song_buzz_status;
static int song_timer_breathe;
static int song_length_now;
static int song_status;
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
  if (note < song_length[song_index])
    note += 1;
  else
    {
      song_next ();
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

static void song_setup (void)
{
  note = 0;
  song_now = songs[song_index];
  song_timer_count = (song_now + note)->length;
  song_length_now = song_length[song_index];
  song_freq_table = freq_tables[song_index];
  song_timer_meter = SONG_METER;
}

void song_pause (void)
{
  TR0 = 0;
  TR1 = 0;
  buzz_stop();
  song_status = 0;
}

void song_next (void)
{
  if (song_index < 2)
    song_index += 1;
  else
    song_index = 0;
  song_setup ();
}

void song_init ()
{
  TMOD = 0x11;
  note = 0;
  song_index = 0;
  song_setup ();
  TH0 = VELOCITIES_TH;
  TL0 = VELOCITIES_TL;
  ET0 = 1;
  ET1 = 1;
  song_set_note ();
  EA = 0;
  TR0 = 0;
  TR1 = 0;
  song_status = 0;
  buzz_stop ();
}

void song_play (void)
{
  TR0 = 1;
  TR1 = 1;
  EA = 1;
  song_status = 1;
}

void song_replay (void)
{
  song_setup ();
  song_play ();

}

void song_switch (void)
{
  if (song_status == 1)
  {
    song_pause ();
    song_status = 0;
  }
  else
  {
    song_play ();
    song_status =  1;
  }
}
