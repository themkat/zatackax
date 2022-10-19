/* font -- font file loading.
 * Copyright (C) 2010-2021 Simen Heggestøyl <simenheg@runbox.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifdef GEKKO
// fonts as binary data
#include "fonts_JuraLight_ttf.h"
#include "fonts_JuraMedium_ttf.h"
#include "fonts_AnkaCoder-r_ttf.h"
#include "fonts_AnkaCoder-b_ttf.h"
#endif

#include "font.h"

TTF_Font *fonts[N_FONTS];

/**
 * Load a font file named `filename` and identify it as `f` with size
 * `size`. Return true on success, otherwise false.
 */
#ifdef GEKKO
bool loadFont(Font f, const uint8_t* fontData, size_t fontDataSize, FontSize size)
#else
bool loadFont(Font f, const char *filename, FontSize size)
#endif
{
    #ifdef GEKKO
    TTF_Font *loadedFont = TTF_OpenFontRW(SDL_RWFromMem(fontData, fontDataSize), 0, size);
    #else
    char *file = dataFile("fonts", filename);
    TTF_Font *loadedFont = TTF_OpenFont(file, size);
    #endif
    
    if (loadedFont == NULL) {
        #ifndef GEKKO
        fileNotFound(file);
        free(file);
        #endif
        return false;
    }

    fonts[f] = loadedFont;
    #ifndef GEKKO
    free(file);
    #endif
    return true;
}

/**
 * Load every needed font file. Return true if every file loaded
 * successfully, otherwise false.
 */
bool loadFonts(void)
{
     #ifdef GEKKO
     return loadFont(FONT_MENU, JuraLight_ttf, JuraLight_ttf_size, FONT_SIZE_MENU)
        && loadFont(FONT_MENU_BOLD, JuraMedium_ttf, JuraMedium_ttf_size, FONT_SIZE_MENU)
        && loadFont(FONT_BROADCAST, AnkaCoder_r_ttf, AnkaCoder_r_ttf_size, FONT_SIZE_BROADCAST)
        && loadFont(FONT_BROADCAST_BOLD, AnkaCoder_b_ttf, AnkaCoder_b_ttf_size, FONT_SIZE_BROADCAST)
        && loadFont(FONT_SCORE, JuraMedium_ttf, JuraMedium_ttf_size, FONT_SIZE_SCORE);
     #else
     return loadFont(FONT_MENU, "jura/JuraLight.ttf", FONT_SIZE_MENU)
        && loadFont(FONT_MENU_BOLD, "jura/JuraMedium.ttf", FONT_SIZE_MENU)
        && loadFont(FONT_BROADCAST, "ankacoder/AnkaCoder-r.ttf", FONT_SIZE_BROADCAST)
        && loadFont(FONT_BROADCAST_BOLD, "ankacoder/AnkaCoder-b.ttf", FONT_SIZE_BROADCAST)
        && loadFont(FONT_SCORE, "jura/JuraMedium.ttf", FONT_SIZE_SCORE);
     #endif
}
