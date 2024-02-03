/*
*   Hello! This is the imTerm source code 
*   This is a terminal based instant messenger
*
*   Author: Aidan Myers
*
*/

// MACROS
#define PADDING_DIVISOR 20
#define REFRESH_RATE 500      // in miliseconds

// libraries
#include <curses.h>
#include <unistd.h>

// structs
struct window{
  int pos_x;
  int pos_y;
  int size_x;
  int size_y;
  WINDOW* pointer;
};

// prototypes
void update_window(struct window*, int, int, int, int);

// main
int main() {
  
  initscr();
  nodelay(stdscr, 1);

  // === key variables === 
  // sizings
  int max_x, max_y;
  getmaxyx(stdscr, max_y, max_x);

  int global_padding_x = (int)(max_x / (2 * PADDING_DIVISOR));
  int local_padding_x = 2 * global_padding_x;
  int global_padding_y = (int)(max_y / PADDING_DIVISOR);
  int local_padding_y = 2 * global_padding_y;

  // chats WINDOW*
  struct window chats;
  chats.pos_x = global_padding_x;
  chats.pos_y = global_padding_y;
  chats.size_x = (int)(max_x / 5);
  chats.size_y = max_y - local_padding_y;
  chats.pointer = newwin(chats.pos_y, chats.pos_x, chats.size_y, chats.size_x);

  struct window messages;


  // === primary loop ===
  do {
    
    // === housekeeping ===
    // important data
    getmaxyx(stdscr, max_y, max_x);

    // chats window
    update_window(&chats, global_padding_x, global_padding_y, (int)(max_x / 5), max_y - local_padding_y);
    box(chats.pointer, 0, 0);

    // global updates
    move(0, 0);   // to move the cursor
    refresh();
    usleep(REFRESH_RATE);
    refresh();

  } while ((char)getch() != 'q'); // will have to be changed when a q is typed lol

  endwin();

  return 0;
}

void update_window(struct window* win, int pos_x, int pos_y, int size_x, int size_y) {
  win->pos_x = pos_x;
  win->pos_y = pos_y;
  win->size_x = size_x;
  win->size_y = size_y;
  mvwin(win->pointer, win->pos_y, win->pos_x);
  wresize(win->pointer, win->size_y, win->size_x);
  wrefresh(win->pointer);
}

