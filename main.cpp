#define MINIAUDIO_IMPLEMENTATION
#include <iostream>
#include <ncurses.h>
#include "miniaudio.h"

using namespace std;

void printMenu();

int main(int argc, char *argv[]){
  ma_result result;
  ma_engine engine;

  if (argc < 2) {
    cout << "No file provided" << endl;
    return -1;
  }

  result = ma_engine_init(NULL, &engine);
  if (result != MA_SUCCESS) {
    cout << "Oops, something happened!" << endl;
    return -1;
  }

  initscr();

  ma_engine_play_sound(&engine, argv[1], NULL);

  bool running = true;
  bool paused = false;
  while (running) {
    printMenu();
    int pressedChar = getch();
    switch (pressedChar) {
      case 113:
        running = false;
        break;
      case 112:
        if (!paused) {
          ma_engine_stop(&engine);
        } else {
          result = ma_engine_init(NULL, &engine);
          ma_engine_play_sound(&engine, argv[1], NULL);
        }
        paused = !paused;
        break;
    }
  }

  endwin();

  ma_engine_uninit(&engine);

  return 0;
}

void printMenu() {
  printw("Player\n");
  printw("P - Pause; Q - Quit;\n");
  printw("----------------------\n");
  printw("Made by Locke\n");
  refresh();
}
