#ifndef __BUTTON_H__
#define __BUTTON_H__
#define BUTTON_WAIT_TIME 10
#include "config.h"
#define check_button(button, callback, status) \
  do \
  {  \
    if (status != ((button)))  \
    {  \
      delay(BUTTON_WAIT_TIME); \
      if (status != ((button))) \
      { \
        status = button_switch_status (status); \
        if (status == 0) \
          callback (); \
      } \
    } \
  }while(0)

#ifdef BUTTON_MATRIX
unsigned short button_scan (void);
#endif
void delay (int count);
int button_switch_status (int status);
#endif

