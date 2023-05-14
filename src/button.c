#include "button.h"
#include "config.h"

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
