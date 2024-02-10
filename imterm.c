/*
*   Hello! This is the imTerm source code 
*   This is a terminal based instant messenger
*
*   Author: Aidan Myers
*
*/

// MACROS
#include <curses.h>
#define REFRESH_RATE 500      // in miliseconds

// libraries
#include "nwrapper.c"
#include <unistd.h>

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
  struct window* chats = construct_window(global_padding_x, global_padding_y, (int)(max_x / 5), (int)(max_y - local_padding_y), 1);

  struct window messages;

  // create color pair
  start_color();
  init_pair(1, COLOR_WHITE, COLOR_BLACK);

  // === primary loop ===
  do {
    
    // === housekeeping ===
    // important data
    getmaxyx(stdscr, max_y, max_x);

    // update windows
    box(chats->pointer, 0, 0);
    update_window(chats, global_padding_x, global_padding_y, (int)(max_x / 5), max_y - local_padding_y, 1);

    // create text
    mvwaddnstr(chats->pointer, 1, 1, "hello color!", -1);

    // global updates
    move(0, 0);   // to move the cursor
    refresh();
    usleep(REFRESH_RATE);
    refresh();

  } while ((char)getch() != 'q'); // will have to be changed when a q is typed lol

  endwin();

  return 0;
}

