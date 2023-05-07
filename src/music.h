#include "song.h"
static const Freq *freq_tables[] = {freq_table0, freq_table1, freq_table2};
static const Song *songs[] = {song0, song1, song2};
static const unsigned int song_length[] = {32, 172, 227};
static const Freq freq_table0[] =
{
  {0, 0},
  {252, 239},
  {253, 69},
  {253, 108},
  {253, 180},
  {253, 244},
  {254, 45},
  {251, 232},
};

const static Song song0[] =
{
  {1, 2},{2, 2},{3, 2},{1, 2},{1, 2},{2, 2},{3, 2},{1, 2},{3, 2}, /* 1 */ 
  {4, 2},{5, 4},{3, 2},{4, 2},{5, 4},{5, 1}, /* 2 */ 
  {6, 1},{5, 1},{4, 1},{3, 2},{1, 2},{5, 1},{6, 1},{5, 1},{4, 1},{3, 2},{1, 2},{3, 2}, /* 3 */ 
  {7, 2},{1, 4},{3, 2},{7, 2},{1, 4},
};

static const Freq freq_table1[] =
{
  {0, 0},
  {252, 239},
  {252, 90},
  {253, 69},
  {253, 108},
  {253, 180},
  {253, 244},
  {254, 45},
};

const static Song song1[] =
{
  {0, 13},{1, 1},{1, 1},{2, 1},{1, 2}, /* 1 */ 
  {2, 1},{1, 1},{1, 2},{1, 1},{3, 1},{3, 1},{3, 1},{3, 1},{3, 1},{3, 1},{4, 1},{1, 2},{1, 2}, /* 2 */ 
  {2, 1},{1, 3},{1, 1},{3, 1},{3, 1},{3, 1},{3, 1},{3, 1},{3, 1},{4, 1},{1, 2},{1, 2}, /* 3 */ 
  {2, 1},{1, 3},{1, 1},{1, 1},{3, 2},{3, 1},{3, 1},{3, 1},{1, 2},{3, 1},{4, 1}, /* 4 */ 
  {3, 1},{4, 1},{3, 2},{0, 3},{1, 2},{1, 1},{1, 1},{2, 1},{1, 1},{2, 1},{1, 1},{2, 1}, /* 5 */ 
  {1, 2},{2, 1},{1, 3},{1, 1},{3, 1},{3, 1},{3, 1},{3, 1},{3, 1},{3, 1},{4, 1},{1, 1},{1, 1}, /* 6 */ 
  {1, 2},{2, 1},{1, 1},{1, 2},{1, 1},{3, 1},{3, 1},{3, 1},{3, 1},{3, 1},{3, 1},{4, 1},{1, 2}, /* 7 */ 
  {0, 3},{1, 1},{4, 1},{5, 2},{4, 3},{3, 1},{3, 1},{1, 1},{3, 1},{1, 1},{3, 1}, /* 8 */ 
  {4, 1},{1, 8},{0, 4},{4, 2},{5, 1}, /* 9 */ 
  {6, 1},{6, 2},{6, 1},{6, 2},{6, 2},{6, 2},{6, 1},{6, 1},{6, 1},{3, 1},{4, 1},{3, 1}, /* 10 */ 
  {1, 1},{1, 2},{3, 1},{4, 2},{4, 2},{4, 2},{4, 1},{4, 1},{4, 1},{3, 1},{4, 1},{1, 1}, /* 11 */ 
  {2, 1},{2, 2},{1, 1},{1, 3},{1, 1},{1, 1},{1, 1},{3, 1},{3, 1},{3, 1},{1, 2},{3, 1}, /* 12 */ 
  {4, 1},{4, 8},{0, 4},{4, 2},{4, 1}, /* 13 */ 
  {5, 1},{6, 2},{6, 1},{6, 2},{6, 2},{6, 2},{6, 1},{6, 1},{6, 1},{3, 1},{4, 1},{3, 1}, /* 14 */ 
  {1, 1},{1, 2},{3, 1},{4, 2},{4, 2},{4, 2},{4, 1},{4, 1},{4, 1},{3, 1},{4, 1},{1, 1}, /* 15 */ 
  {7, 1},{2, 2},{1, 1},{1, 3},{1, 1},{1, 1},{3, 2},{3, 1},{3, 2},{1, 1},{1, 2}, /* 16 */ 
  {1, 16},
};

static const Freq freq_table2[] =
{
  {0, 0},
  {253, 69},
  {252, 143},
  {252, 239},
  {252, 90},
  {253, 108},
  {254, 45},
  {253, 244},
  {254, 71},
  {254, 119},
  {254, 162},
  {254, 182},
  {254, 250},
  {255, 22},
};

const static Song song2[] =
{
  {1, 2},{2, 2},{3, 2},{4, 2},{1, 2},{2, 2},{3, 2},{4, 2},{1, 2}, /* 1 */ 
  {2, 2},{3, 2},{4, 2},{1, 2},{2, 2},{3, 2},{4, 2},{1, 2}, /* 2 */ 
  {2, 2},{3, 2},{4, 2},{1, 2},{2, 2},{3, 2},{4, 2},{1, 2}, /* 3 */ 
  {2, 2},{3, 2},{4, 2},{1, 2},{2, 2},{3, 2},{4, 2},{1, 2}, /* 4 */ 
  {2, 2},{3, 2},{4, 2},{1, 2},{2, 2},{3, 2},{4, 2},{5, 8}, /* 5 */ 
  {0, 5},{3, 1},{1, 1},{3, 1},{5, 8}, /* 6 */ 
  {0, 3},{3, 1},{1, 1},{3, 1},{1, 1},{5, 1},{4, 3}, /* 7 */ 
  {3, 1},{4, 3},{3, 1},{4, 3},{3, 1},{1, 2},{3, 2},{2, 8}, /* 8 */ 
  {0, 8},{4, 1}, /* 9 */ 
  {3, 1},{6, 3},{6, 1},{6, 1},{7, 1},{6, 2},{6, 1},{7, 1},{6, 1},{7, 1},{6, 1},{7, 1},{5, 1}, /* 10 */ 
  {5, 7},{0, 6},{4, 1},{3, 1},{6, 3}, /* 11 */ 
  {6, 1},{6, 1},{7, 1},{6, 1},{7, 1},{8, 3},{8, 1},{8, 1},{6, 1},{8, 3}, /* 12 */ 
  {6, 2},{5, 9},{0, 1},{5, 1},{7, 1},{5, 1},{1, 3}, /* 13 */ 
  {5, 1},{1, 3},{5, 1},{1, 3},{5, 1},{7, 1},{5, 1},{7, 1},{5, 1},{1, 3}, /* 14 */ 
  {5, 1},{1, 3},{5, 1},{1, 4},{0, 2},{3, 1},{1, 1},{5, 2}, /* 15 */ 
  {4, 2},{3, 2},{5, 2},{1, 3},{5, 1},{1, 1},{3, 1},{3, 2},{4, 8}, /* 16 */ 
  {0, 6},{6, 1},{8, 1},{9, 1}, /* 17 */ 
  {10, 1},{8, 1},{9, 1},{9, 2},{9, 1},{8, 1},{9, 1},{10, 1},{8, 1},{9, 1},{9, 2},{9, 1},{10, 1},{11, 1}, /* 18 */ 
  {10, 1},{11, 1},{10, 1},{11, 2},{11, 1},{10, 1},{11, 2},{12, 2},{11, 2},{6, 1},{8, 1},{9, 1}, /* 19 */ 
  {10, 1},{8, 1},{9, 1},{9, 2},{9, 1},{8, 1},{9, 1},{10, 1},{8, 1},{9, 1},{9, 2},{9, 1},{10, 1},{11, 1}, /* 20 */ 
  {10, 1},{11, 1},{10, 1},{11, 2},{11, 1},{10, 1},{11, 2},{12, 2},{11, 2},{12, 2},{11, 3}, /* 21 */ 
  {12, 1},{11, 3},{12, 1},{11, 1},{12, 1},{13, 1},{11, 1},{12, 2},{12, 2},{11, 3}, /* 22 */ 
  {12, 1},{11, 3},{12, 1},{11, 1},{12, 1},{13, 1},{11, 1},{12, 2},{12, 1},{12, 1},{11, 1}, /* 23 */ 
  {10, 1},{10, 2},{10, 2},{9, 1},{11, 2},{10, 1},{10, 2},{10, 2},{9, 1},{9, 1},{6, 8}, /* 24 */ 
  {0, 6},{12, 1},{12, 1},{11, 1}, /* 25 */ 
  {10, 1},{10, 2},{10, 2},{9, 1},{11, 2},{10, 2},{10, 2},{9, 1},{9, 1},{6, 8}, /* 26 */ 
  {0, 8},
};
