#include "led.h"
#include "config.h"
#include "button.h"
#ifdef LED
const static unsigned char led_num_table[] =
{
  0b00111111,
  0b00000110,
  0b01011011,
  0b01001111,
  0b01100110,
  0b01101101,
  0b01111101,
  0b00000111,
  0b01111111,
  0b01101111
};

void led_putchar (int index, unsigned char out)
{
  LED = LED_CHAR_NULL;
  led_choose (index);
  LED = out;
  delay(1);
}

static void led_print_play (void)
{
  led_putchar (7, LED_CHAR_P);
  led_putchar (6, LED_CHAR_L);
  led_putchar (5, LED_CHAR_A);
  led_putchar (4, LED_CHAR_Y);
  led_putchar (3, LED_CHAR_NULL);
  led_choose (2);
}

static void led_print_pause (void)
{
  led_putchar (7, LED_CHAR_P);
  led_putchar (6, LED_CHAR_A);
  led_putchar (5, LED_CHAR_U);
  led_putchar (4, LED_CHAR_S);
  led_putchar (3, LED_CHAR_E);
  led_choose (2);
}

void led_putnum (int index, int num)
{
  LED = LED_CHAR_NULL;
  if (num >= 0 && num < 10)
  {
    led_choose (index);
    LED = led_num_table[num];
  }
}

void led_print_status (void)
{
  if (song_get_status ())
    led_print_play ();
  else
    led_print_pause ();

}

void led_print_index (void)
{
  int index = song_get_index () + 1;
  led_putnum (0, index);
}
#endif
