#ifndef __EIGHT_DOT_H__
#define __EIGHT_DOT_H__

typedef enum { 
  false, 
  true 
} bool;

typedef enum {
  left,
  right,
  up,
  down
} direction;

extern bool Check_Visibility(direction d, int start_x, int start_y);

#endif
