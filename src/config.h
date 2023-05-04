#define F_CPU 11059200
#ifdef STC89C52RC
#define switch_buzz() P2_5 = !P2_5
#endif
#ifdef IAP15F2K61S2
#define switch_buzz() \
  do \
  {  \
    P2_5 = 1; \
    P2_6 = 0; \
    P2_7 = 1; \
    P0_6 = !P0_6; \
  } while (0)
#endif

