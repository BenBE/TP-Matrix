#ifndef H_UTPLIB
#define H_UTPLIB

#include <stdint.h>

#include <avr/pgmspace.h>

#ifdef __cplusplus
extern "C" {
#endif

#define	DISPLAY_WIDTH	32
#define	DISPLAY_HEIGHT	8
#define DISPLAY_BUFFERS	2

#define FONT_WIDTH	5
#define FONT_HEIGHT	6

typedef int8_t coord_t;
typedef uint8_t color_t;
typedef uint8_t buffer_t;

typedef enum bufmod {
    bmEQU,
    bmXOR,
    bmAND,
    bmOR,
    bmMIN,
    bmMAX
} bufmod_t;

typedef color_t screen_t[DISPLAY_WIDTH][DISPLAY_HEIGHT];

typedef uint16_t timebase_t;

extern screen_t display[DISPLAY_BUFFERS];

extern screen_t* display_active;
extern screen_t* display_write;

extern const prog_uint8_t font[128][FONT_WIDTH];

extern volatile timebase_t time_frame;
extern volatile uint8_t time_vsynced;

void display_init(void);
void display_mode(char mode);

void display_interrupt(void);

void display_clear_black(void);
void display_clear_color(color_t color);

void display_pixel_set(coord_t x, coord_t y, color_t color);
color_t display_pixel_get(coord_t x, coord_t y);

static inline coord_t display_size_width(void)	{	return DISPLAY_WIDTH;	};
static inline coord_t display_size_height(void)	{	return DISPLAY_HEIGHT;	};

void display_buffer_active_set(buffer_t bufferid);
buffer_t display_buffer_active_get(void);
void display_buffer_write_set(buffer_t bufferid);
buffer_t display_buffer_write_get(void);
void display_buffer_active_write_swap(void);
void display_buffer_active_write_next(void);

void display_buffer_active_next(void);
void display_buffer_write_next(void);

void display_buffer_swap(uint8_t mode);
void display_buffer_copy(buffer_t from, buffer_t to);
void display_buffer_modify(buffer_t dest, buffer_t src, bufmod_t mode);

static inline color_t display_color_from_rgb(color_t r, color_t g, color_t b) {
    return (b & 0300) + ((g >> 2) & 0070) + ((r >> 5) & 007);
}

void font_char_print(coord_t x, coord_t y, color_t color, char c);
void font_string_printX(coord_t x, coord_t y, color_t color, char *s);
void font_string_printY(coord_t x, coord_t y, color_t color, char *s);

void font_string_printX_P(coord_t x, coord_t y, color_t color, const prog_uint8_t *s);
void font_string_printY_P(coord_t x, coord_t y, color_t color, const prog_uint8_t *s);

static inline coord_t font_char_width(void)	{	return FONT_WIDTH;	}
static inline coord_t font_char_height(void)	{	return FONT_HEIGHT;	}

void delay_s(timebase_t time);
void delay_ms(timebase_t time);
void delay_us(timebase_t time);

void time_sync(void);
timebase_t time_frame_get(void);
void time_frame_wait(timebase_t time);

void int_enable(void);
void int_disable(void);

static inline uint8_t rot_left(uint8_t v, uint8_t bits)
{
    return (v >> (8 - bits)) | (v << bits); // rotate left 
}
static inline uint8_t rot_right(uint8_t v, uint8_t bits)
{
    return rot_left(v, 8 - bits); // rotate right
}

int random_range(int min, int max);

#ifdef __cplusplus
}
#endif

#endif //H_UTPLIB
