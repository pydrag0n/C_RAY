#include "ray.h"

// global vars externed in ray.h
// keep in sync

HWND window = 0;
HDC hdc = 0;
HGLRC hrc = 0;

int last_mouse_x = 0;
char cursor_enabled = 1;
GLuint fontOffset;
Player player = {0};
unsigned short player_walk = 0;
