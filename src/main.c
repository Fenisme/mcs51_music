#include <mcs51/8051.h>
#include "button.h"
#include "config.h"
#include "song.h"
#include "music.h"
#ifdef LED
#include "led.h"
#endif
#define BUTTON_ACTIVATE 0
void main()
{
  int button1_status = button_switch_status(0);
  int button2_status = button_switch_status(0);
  int button3_status = button_switch_status(0);

  song_init ();
  while (1)
    {
#ifdef LED
      led_print_status ();
      led_print_index ();
      led_putnum (1, SONG_INDEX_MAX);
#endif
#ifdef BUTTON_MATRIX
      if (button_scan())
        P2_1 = !P2_1;
#endif
      check_button (BUTTON1, song_switch, button1_status);
      check_button (BUTTON2, song_next, button2_status);
      check_button (BUTTON3, song_replay, button3_status);
    }
}
