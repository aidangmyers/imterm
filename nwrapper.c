/* 
* This is my curses wrapper for c
*/

// Macros
#define PADDING_DIVISOR 20

// libraries
#include <curses.h>
#include <stdlib.h>

// structs
struct window{
  int pos_x;
  int pos_y;
  int size_x;
  int size_y;
  int color_id;
  WINDOW* pointer;
};

// Methods
struct window* construct_window (int pos_x, int pos_y, int size_x, int size_y, int color_id) {
  
  struct window* object = malloc(sizeof(struct window));

  object->pos_x = pos_x;
  object->pos_y = pos_y;
  object->size_x = size_x;
  object->size_y = size_y;
  object->color_id = color_id;
  object->pointer = newwin(pos_y, pos_x, size_y, size_x);

  return object;

}

void update_window(struct window* win, int pos_x, int pos_y, int size_x, int size_y, int color_id) {
  win->pos_x = pos_x;
  win->pos_y = pos_y;
  win->size_x = size_x;
  win->size_y = size_y;
  win->color_id = color_id;
  wattron(win->pointer, COLOR_PAIR(win->color_id));
  mvwin(win->pointer, win->pos_y, win->pos_x);
  wresize(win->pointer, win->size_y, win->size_x);
  wrefresh(win->pointer);
}

