#define F_CPU 11059200
#ifdef STC89C52RC
#define buzz_switch() P2_5 = !P2_5
#define buzz_stop() TR1 = 0
#define buzz_resume() TR1 = 1
#endif

#ifdef Generic8051
#define buzz_switch() P1_0 = !P1_0
#define buzz_stop() TR1 = 0
#define buzz_resume() TR1 = 1
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
#endif

