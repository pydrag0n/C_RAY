#ifndef _RAY_H
#define _RAY_H

#define PI 3.14159265358979323846

#include <Windows.h>
#include <gl/gl.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "bind.h"

#define WHITE         (Color){1.0f, 1.0f, 1.0f, 1.0f}
#define BLACK         (Color){0.0f, 0.0f, 0.0f, 1.0f}
#define RED           (Color){1.0f, 0.0f, 0.0f, 1.0f}
#define GREEN         (Color){0.0f, 1.0f, 0.0f, 1.0f}
#define BLUE          (Color){0.0f, 0.0f, 1.0f, 1.0f}
#define BROWN         (Color){0.6f, 0.4f, 0.2f, 1.0f}
#define YELLOW        (Color){1.0f, 1.0f, 0.0f, 1.0f}
#define MAGENTA       (Color){1.0f, 0.0f, 1.0f, 1.0f}
#define CYAN          (Color){0.0f, 1.0f, 1.0f, 1.0f}
#define ORANGE        (Color){1.0f, 0.5f, 0.0f, 1.0f}
#define PURPLE        (Color){0.5f, 0.0f, 0.5f, 1.0f}
#define PINK          (Color){1.0f, 0.75f, 0.8f, 1.0f}
#define GRAY          (Color){0.5f, 0.5f, 0.5f, 1.0f}
#define LIME          (Color){0.75f, 1.0f, 0.0f, 1.0f}
#define TEAL          (Color){0.0f, 0.5f, 0.5f, 1.0f}
#define NAVY          (Color){0.0f, 0.0f, 0.5f, 1.0f}


#define C_RAY_GROUND  (Color){0.0f, 0.5f, 0.0f, 1.0f}
#define C_RAY_SKY     (Color){0.5f, 0.8f, 1.0f, 1.0f}

#define C_RAY_WALL    (Color){0.56f, 0.51f, 0.44f, 1.0f}  // Grayish-brown
#define C_RAY_FLOOR   (Color){0.38f, 0.27f, 0.18f, 1.0f}  // Dark brown
#define C_RAY_CEILING (Color){0.07f, 0.07f, 0.14f, 1.0f}  // Very dark blue (almost black)

typedef enum {
	WALL,
	FLOOR,
	DOOR,
	TRIGGER
} EntityType;

// Данные специфичные для двери
typedef struct {
    char is_locked;     // Закрыта ли дверь
    int  key_id;        // Какой ключ нужен
} DoorData;

// Данные специфичные для триггера
typedef struct {
    int  target_entity; // ID связанной сущности
    void (*callback)(); // Функция-колбэк
} TriggerData;

typedef struct {
	float r;
	float g;
	float b;
	float alpha;
} Color;

typedef struct {
	float x;
	float y;
} Position;

typedef struct {
	Position pos;
	float width;
	float height;
} Rect;

typedef struct {
	Position pos;
	float radius;
} Circle;

typedef struct {
	EntityType type;
	union {
        DoorData    door_data;      // Данные двери (если type == DOOR)
        TriggerData trigger_data;   // Данные триггера (если type == TRIGGER)
		// WallData	wall_data;		// Данные стены	(если type == WALL)
		// FloorData	floor_data;		// Данные стены	(если type == FLOOR)
    };
} GameObject;


typedef struct {
	Position pos;
	float angle;
	float fov;
	float sensitivity;
	float speed;
	float width;
	float height;
} Player;

#define MAP_HEIGHT  30
#define MAP_WIDTH   10
#define BLOCK_SIZE 20

#define WW 1024
#define WH 512

#define NUM_RAYS 1024

// global vars declared in global.c
// keep in sync
extern GameObject map[MAP_HEIGHT][MAP_WIDTH];
extern HWND window;
extern HDC hdc;
extern HGLRC hrc;

extern int last_mouse_x;
extern char cursor_enabled;
extern KeyBind key_bindings[];
extern float e_flashbang_duration; // test_1234

extern Player player;

// input.c
void i_handle_keys_event(void);
void i_handle_mouse_movement(void);

// main.c
void HandleMouseClick(int x, int y);
void GL_Init(void);
void GL_Shutdown(void);

// map.c
void m_load_map(void);
void m_save_map(void);
void m_draw_mini_map(int x, int y, int map_width, int map_height, Color player_color, Color player_line);

// misc.c
int u_check_collision(float x, float y);
void u_move_player(float angle);

// renderer.c
void r_drawRect(Rect *rect, Color color);
void r_drawPoint(int x, int y, int size, Color color);
void r_drawLine(int start_x, int start_y, int end_x, int end_y, float line_size, Color color);
void r_drawMap(GameObject map[MAP_HEIGHT][MAP_WIDTH], Rect* mapArea);
void r_drawSky(int view_width, int view_height);
void r_drawGround(int view_width, int view_height);

void e_flashbang(float flash_duration); // test_1234

#endif /* _RAY_H */
