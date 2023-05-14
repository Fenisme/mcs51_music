#ifndef __LED_H__
#define __LED_H__
#include "song.h"
#include "config.h"
#include <mcs51/8051.h>
#ifdef LED
#define LED_CHAR_P 0b01110011
#define LED_CHAR_L 0b00111000
#define LED_CHAR_A 0b01110111
#define LED_CHAR_Y 0b01101110
#define LED_CHAR_U 0b00111110
#define LED_CHAR_S 0b01101101
#define LED_CHAR_E 0b01111001
#define LED_CHAR_C 0b00111001
#define LED_CHAR_H 0b01110110
#define LED_CHAR_g 0b01101111
#define LED_CHAR_o 0b01011100
#define LED_CHAR_n 0b01010100
#define LED_CHAR_NULL 0
void led_putchar (int index, unsigned char out);
void led_print_song (void);
void led_print_status (void);
void led_print_index (void);
void led_putnum (int index, int num);
#endif
#endif
