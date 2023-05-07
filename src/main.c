#include <mcs51/8051.h>
#include "button.h"
#include "config.h"
#include "song.h"
#define BUTTON_ACTIVATE 0
void main()
{
  int button1_status = button_switch_status(0);
  int button2_status = button_switch_status(0);
  int button3_status = button_switch_status(0);

  song_init ();
  while (1)
    {
      check_button (BUTTON1, song_switch, button1_status);
      check_button (BUTTON2, song_next, button2_status);
      check_button (BUTTON3, song_replay, button3_status);
    }
}
