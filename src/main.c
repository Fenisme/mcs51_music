#include <mcs51/8051.h>
#include "button.h"
#include "config.h"
#include "song.h"
#define BUTTON_ACTIVATE 0
void main()
{
  int button1_status = button_switch_status(0);
  song_init ();
  song_play ();
  while (1)
    {
      check_button (BUTTON1, song_pause, button1_status);
    }
}
