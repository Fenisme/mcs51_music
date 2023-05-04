#include <mcs51/8051.h>
#include "config.h"
#include "song.h"

void main()
{
  song_init ();
  song_play ();
  while (1)
    {
    }
}
