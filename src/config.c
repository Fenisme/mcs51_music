#include "config.h"
#ifdef STC89C52RC
const static int *led_index = 
{
  0b00000000,
  0b00000100,
  0b00001000,
  0b00001100,
  0b00010000,
  0b00010100,
  0b00011000,
  0b00011100
};

/*void led_choose (int index)*/
/*{*/
  /*if (index >= 0 && index <=7)*/
  /*{*/
    /*P2 = P2 & 0b11100011;*/
    /*P2 = P2 | *(led_index + index);*/
  /*}*/
  /*else*/
  /*{*/
    /*P2 = P2 & 0b11100011;*/
    /*P2 = P2 | *(led_index + 2);*/
  /*}*/
/*}*/
void led_choose (int index)
{
  switch (index)
  {
    case 0:
      P2_4 = 0; P2_3 = 0; P2_2 = 0; break;
    case 1:
      P2_4 = 0; P2_3 = 0; P2_2 = 1; break;
    case 2:
      P2_4 = 0; P2_3 = 1; P2_2 = 0; break;
    case 3:
      P2_4 = 0; P2_3 = 1; P2_2 = 1; break;
    case 4:
      P2_4 = 1; P2_3 = 0; P2_2 = 0; break;
    case 5:
      P2_4 = 1; P2_3 = 0; P2_2 = 1; break;
    case 6:
      P2_4 = 1; P2_3 = 1; P2_2 = 0; break;
    case 7:
      P2_4 = 1; P2_3 = 1; P2_2 = 1; break;
    default:
      break;
  }
}
#endif

