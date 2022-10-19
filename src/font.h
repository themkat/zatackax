#ifndef FONT_H
#define FONT_H

#include <SDL/SDL_ttf.h>
#include <stdbool.h>

#include "data.h"
#include "error.h"

typedef enum font {
    FONT_MENU = 0,
    FONT_MENU_BOLD,
    FONT_BROADCAST,
    FONT_BROADCAST_BOLD,
    FONT_SCORE,
    N_FONTS
} Font;

typedef enum font_size {
    FONT_SIZE_BROADCAST = 13,
    FONT_SIZE_MENU      = 22,
    FONT_SIZE_SCORE     = 22
} FontSize;

extern TTF_Font *fonts[N_FONTS];

#ifdef GEKKO
bool loadFont(Font f, const uint8_t* fontData, size_t fontDataSize, FontSize size);
#else
bool loadFont(Font f, const char *filename, FontSize size);
#endif

bool loadFonts(void);

#endif
