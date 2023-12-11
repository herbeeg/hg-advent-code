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
  int id;
  int x_pos;
  int y_pos;
};

struct bridge {
  int start_x;
  int start_y;
  struct visited visited_ids[5000];
};

typedef struct bridge Data;

extern bool Is_New_Tail_Position(int x, int y, Data d);

#endif
