#ifndef __NINE_DOT_H__
#define __NINE_DOT_H__

typedef enum {
  up,
  right,
  down,
  left
} facing;

typedef enum {
  false,
  true
} bool;

struct visited {
  int x_pos;
  int y_pos;
};

extern bool Tail_Should_Move(int hX, int hY, int tX, int tY, facing dir);
extern bool Chain_Should_Move(int hX, int hY, int tX, int tY);
extern bool Is_New_Tail_Position(int x, int y, int size, int length);

#endif
