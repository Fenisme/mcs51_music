#include "button.h"
#include "config.h"
#include "song.h"
#include "music.h"

void delay (int count)
{
  unsigned int i, j;
  for (i = 0; i < count; i++)
    for (j = 0; j < 200; j++);
}
int button_switch_status (int status)
{
    if (status == 1)
      return 0;
    else
      return 1;
}
#ifdef BUTTON_MATRIX
/*static enum _ButtonStatus*/
/*{*/
  /*DEFAULT = 0,*/
  /*CUSTOM = 1*/
/*} button_status = DEFAULT;*/

static int button_custom_index = 0;
static int button_custom_index_h = 0;
static int button_custom_index_l = 0;

int button_get_index (void)
{
  return button_custom_index;
}

int button_get_index_h (void)
{
  return button_custom_index_h;
}

int button_get_index_l (void)
{
  return button_custom_index_l;
}

static void button_index_increase (int num)
{
  if (button_custom_index_h)
    return;
  button_custom_index_h = button_custom_index_l;
  button_custom_index_l = num;
  button_custom_index = button_custom_index_h * 10 + button_custom_index_l;
}

static void button_index_decrease (void)
{
  button_custom_index_l = button_custom_index_h;
  button_custom_index_h = 0;
  button_custom_index = button_custom_index_l;
}

static void button_confirm (void)
{
  int song_index = button_custom_index - 1;
  if (song_index >= 0 && song_index <= SONG_INDEX_MAX )
    song_choose (song_index);
  button_custom_index = 0;
  button_custom_index_h = 0;
  button_custom_index_l = 0;
}

void button_map_index (unsigned short key)
{
  switch (key)
  {
    case 16: button_index_increase (7); break;
    case 12: button_index_increase (8); break;
    case 18: button_index_increase (9); break;
    case 15: button_index_increase (4); break;
    case 11: button_index_increase (5); break;
    case 7: button_index_increase (6); break;
    case 14: button_index_increase (1); break;
    case 10: button_index_increase (2); break;
    case 6: button_index_increase (3); break;
    case 13: button_index_increase (0); break;
    case 1: button_confirm (); break;
    case 5: button_index_decrease (); break;
    default: break;
  }
}

unsigned short button_scan (void)
{
  unsigned short key = 0; 
  unsigned short row = 0;
  unsigned short col = 0;
  BUTTON_MATRIX = 0x0f;
  if (BUTTON_MATRIX != 0x0f)
  {
    delay(BUTTON_WAIT_TIME);
    if (BUTTON_MATRIX != 0x0f)
    {
      row = BUTTON_MATRIX & 0x0f;
      BUTTON_MATRIX = 0xf0;
      col = BUTTON_MATRIX & 0xf0;
    }
    while ((BUTTON_MATRIX & 0xf0) != 0xf0)
      BUTTON_MATRIX = 0xf0;
    switch (row + col)
    {
      case 0xee:
        key = 1;
        break;
      case 0xde:
        key = 2;
        break;
      case 0xbe:
        key = 3;
        break;
      case 0x7e:
        key = 4;
        break;

      case 0xed:
        key = 5;
        break;
      case 0xdd:
        key = 6;
        break;
      case 0xbd:
        key = 7;
        break;
      case 0x7d:
        key = 8;
        break;

      case 0xeb:
        key = 9;
        break;
      case 0xdb:
        key = 10;
        break;
      case 0xbb:
        key = 11;
        break;
      case 0x7b:
        key = 12;
        break;

      case 0xe7:
        key = 13;
        break;
      case 0xd7:
        key = 14;
        break;
      case 0xb7:
        key = 15;
        break;
      case 0x77:
        key = 16;
        break;
      default:
        key = 0;
        break;
    }
    return key;
  }
  else
    return 0;
}

#endif
