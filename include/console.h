#include "stdint.h"
#include "portmap.h"
#include "stdlib.h"
#ifndef H_CONSOLE
#define H_CONSOLE

static char* const VGA_BUFFER = (char*) 0xb8000;
extern int terminal_position;

#define VGA_WIDTH 80
#define VGA_HEIGHT 25
#define VGA_BYTES_PER_CHARACTER 2

#define VGA_BYTES_PER_ROW (VGA_WIDTH*VGA_BYTES_PER_CHARACTER)
#define VGA_TOTAL_BYTES (VGA_WIDTH*VGA_HEIGHT*VGA_BYTES_PER_CHARACTER)

#define VGA_INDEX_REGISTER 0x3D4
#define VGA_DATA_REGISTER 0x3D5

#define VGA_LOW_REGISTER 0x0F
#define VGA_HIGH_REGISTER 0x0E

void clear_terminal();
void print_character(char c);
void print_string(char* str);
void print_line(char* str);

void update_cursor();
uint16_t get_cursor_position();

void print_integer(int toPrint);

#endif
