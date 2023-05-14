#include <mcs51/8051.h>
#ifdef STC89C52RC
#define buzz_switch() P2_5 = !P2_5
#define buzz_stop() TR1 = 0
#define buzz_resume() TR1 = 1
#define BUTTON1 P3_1
#define BUTTON2 P3_0
#define BUTTON3 P3_2
#define BUTTON_ACTIVATE 0
#define BUTTON_MATRIX P1
#define LED P0
void led_choose (int index);
#endif

#ifdef Generic8051
#define buzz_switch() P1_0 = !P1_0
#define buzz_stop() \
  do \
  {  \
    TR1 = 0; \
    P1_0 = 0; \
  } while (0)
#define buzz_resume() TR1 = 1
#define BUTTON1 P3_0
#define BUTTON2 P3_1
#define BUTTON3 P3_2
#define BUTTON_ACTIVATE 0
#endif

#ifdef IAP15F2K61S2
#define buzz_switch() \
  do \
  {  \
    P2_5 = 1; \
    P2_6 = 0; \
    P2_7 = 1; \
    P0_6 = !P0_6; \
  } while (0)
#define buzz_stop() \
  do \
  {  \
    P2_5 = 1; \
    P2_6 = 0; \
    P2_7 = 1; \
    P0_6 = 0; \
    TR1 = 1; \
  } while (0)
#define buzz_resume() \
  do \
  {  \
    P2_5 = 1; \
    P2_6 = 0; \
    P2_7 = 1; \
    P0_6 = 1; \
    TR1 = 1; \
  } while (0)
#define BUTTON1 P3_0
#define BUTTON2 P3_1
#define BUTTON3 P3_2
#define BUTTON_ACTIVATE 0
#endif

