#ifndef __NINE_DOT_H__
#define __NINE_DOT_H__

struct visited {
  int id;
  int x_pos;
  int y_pos;
};

struct bridge {
  int start_x;
  int start_y;
  int visited_ids[5000];
};

#endif
