/*
*   Hello! This is the imTerm source code 
*   This is a terminal based instant messenger
*
*   Author: Aidan Myers
*
*/

// MACROS
#include <curses.h>
#define REFRESH_RATE 1000      // in miliseconds

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
  int chats_pos_x = global_padding_x;
  int chats_pos_y = global_padding_y;
  int chats_size_x = (int)((max_x - 3 * global_padding_x ) * .2);
  int chats_size_y = (int)(max_y - local_padding_y);
  struct window* chats = construct_window(chats_pos_x, chats_pos_y, chats_size_x, chats_size_y, 1);

  // messages WINDOW*
  int messages_pos_x = 2 * global_padding_x + chats_size_x;
  int messages_pos_y = global_padding_y;
  int messages_size_x = (int)((max_x - 3 * global_padding_x ) * .8);
  int messages_size_y = (int)(max_y - local_padding_y);
  struct window* messages = construct_window(messages_pos_x, messages_pos_y, messages_size_x, messages_size_y, 1);

  // create color pair
  start_color();
  init_pair(1, COLOR_WHITE, COLOR_BLACK);

  curs_set(0);

  // === primary loop ===
  do {
    
    // === housekeeping ===
    // important data
    getmaxyx(stdscr, max_y, max_x);

    // update windows
    chats_pos_x = global_padding_x;
    chats_pos_y = global_padding_y;
    chats_size_x = (int)((max_x - 3 * global_padding_x ) * .2);
    chats_size_y = (int)(max_y - local_padding_y);
    box(chats->pointer, 0, 0);
    update_window(chats, chats_pos_x, chats_pos_y, chats_size_x, chats_size_y, 1);

    messages_pos_x = 2 * global_padding_x + chats_size_x;
    messages_pos_y = global_padding_y;
    messages_size_x = (int)((max_x - 3 * global_padding_x ) * .8);
    messages_size_y = (int)(max_y - local_padding_y);
    box(messages->pointer, 0, 0);
    update_window(messages, messages_pos_x, messages_pos_y, messages_size_x, messages_size_y, 1);  

    // create text
    mvwaddnstr(chats->pointer, 1, 1, "hello color!", -1);

    // global updates
    refresh();
    usleep(REFRESH_RATE);

  } while ((char)getch() != 'q'); // will have to be changed when a q is typed lol

  free(chats);
  free(messages);

  endwin();

  return 0;
}

