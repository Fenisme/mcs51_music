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
  int tmp_index;
  song_init ();
  while (1)
    {
#ifdef LED
#ifdef BUTTON_MATRIX
      if (tmp_index = button_get_index ())
      {
        led_print_song ();
        led_putnum (0, button_get_index_l ());
        led_putnum (1, button_get_index_h ());
      }
      else
      {
        led_print_status ();
        led_print_index ();
      }
      button_map_index(button_scan());
#endif
#endif
      check_button (BUTTON1, song_switch, button1_status);
      check_button (BUTTON2, song_next, button2_status);
      check_button (BUTTON3, song_replay, button3_status);
    }
}
