#include "button.h"

void delay (int count)
{
  unsigned char i, j;
  for (i = 0; i < count; i++)
    for (j = 0; j < 250; j++);
}
int button_switch_status (int status)
{
    if (status == 1)
      return 0;
    else
      return 1;
}
