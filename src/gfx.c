/* gfx -- image file loading.
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
// Images / Graphics resources
#include "gfx_arrowsheet_png.h"
#include "gfx_ball_png.h"
#include "gfx_logo_png.h"
#include "gfx_wis_chilirun_png.h"
#include "gfx_wis_confusion_png.h"
#include "gfx_wis_frostwave_png.h"
#include "gfx_wis_ghost_png.h"
#include "gfx_wis_mole_png.h"
#include "gfx_wis_rocketlauncher_png.h"
#include "gfx_wis_sharpturn_png.h"
#include "gfx_wis_lightningspeed_png.h"
#include "gfx_wis_timestep_png.h"
#include "gfx_wis_tron_png.h"
#include "gfx_wis_warp_png.h"
#include "gfx_wi_bg_png.h"
#include "gfx_wi_chilirun_png.h"
#include "gfx_wi_confusion_png.h"
#include "gfx_wi_frostwave_png.h"
#include "gfx_wi_ghost_png.h"
#include "gfx_wi_mole_png.h"
#include "gfx_wi_rocketlauncher_png.h"
#include "gfx_wi_sharpturn_png.h"
#include "gfx_wi_lightningspeed_png.h"
#include "gfx_wi_timestep_png.h"
#include "gfx_wi_tron_png.h"
#include "gfx_wi_warp_png.h"
#endif

#include "gfx.h"

SDL_Color colors[N_COLORS];

SDL_Surface *images[N_IMAGES];

/**
 * Fill a surface with black pixels.
 *
 * Return 0 on success, -1 on error.
 */
int clearSurface(SDL_Surface *s)
{
    Uint32 color = SDL_MapRGB(s->format, 0x00, 0x00, 0x00);
    return SDL_FillRect(s, &s->clip_rect, color);
}

#ifndef GEKKO
/**
 * Load an icon file named `filename`. Return the loaded image, or
 * NULL if it wasn't loaded.
 */
SDL_Surface *loadIcon(const char *filename)
{
  // TODO: should probably use SDL_Creatergbsurfacefrom here as well? So we don't have to load a file system
    char *file = dataFile("gfx", filename);
    SDL_Surface *icon = SDL_LoadBMP(file);

    if (icon == NULL) {
        fileNotFound(file);
    }

    free(file);
    return icon;
}
#endif

/**
 * Load an image file named `filename` and identify it as `i`. Return
 * true on success, otherwise false.
 */
#ifdef GEKKO
bool loadImage(Image i, const uint8_t* imageData, size_t imageSize)
#else
bool loadImage(Image i, const char *filename)
#endif
{
    #ifdef GEKKO
    SDL_Surface *loadedImage = IMG_Load_RW(SDL_RWFromMem(imageData, imageSize), 0);
    #else
    char *file = dataFile("gfx", filename);
    SDL_Surface *loadedImage = IMG_Load(file);
    #endif

    if (loadedImage == NULL) {
        #ifndef GEKKO
        fileNotFound(file);
        free(file);
        #endif
        return false;
    }

    images[i] = SDL_DisplayFormatAlpha(loadedImage);
    #ifndef GEKKO
    if (olvl >= O_DEBUG) {
        printf("Loaded: %s\t(w:%d h:%d bpp:%d)\n", filename, images[i]->w,
               images[i]->h, images[i]->format->BitsPerPixel);
    }
    #endif
    SDL_FreeSurface(loadedImage);

    #ifndef GEKKO
    free(file);
    #endif
    return true;
}

/**
 * Load every needed image file. Return true if every file loaded
 * successfully, otherwise false.
 */
bool loadImages(void)
{
    #ifdef GEKKO
    return loadImage(IMG_ARROWS, arrowsheet_png, arrowsheet_png_size)
        && loadImage(IMG_BALL, ball_png, ball_png_size)
        && loadImage(IMG_LOGO, logo_png, logo_png_size)
        && loadImage(IMG_WIS_CHILIRUN, wis_chilirun_png, wis_chilirun_png_size)
        && loadImage(IMG_WIS_CONFUSION, wis_confusion_png, wis_confusion_png_size)
        && loadImage(IMG_WIS_FROST, wis_frostwave_png, wis_frostwave_png_size)
        && loadImage(IMG_WIS_GHOST, wis_ghost_png, wis_ghost_png_size)
        && loadImage(IMG_WIS_MOLE, wis_mole_png, wis_mole_png_size)
        && loadImage(IMG_WIS_ROCKETLAUNCHER, wis_rocketlauncher_png, wis_rocketlauncher_png_size)
        && loadImage(IMG_WIS_SHARPTURN, wis_sharpturn_png, wis_sharpturn_png_size)
        && loadImage(IMG_WIS_SPEED, wis_lightningspeed_png, wis_lightningspeed_png_size)
        && loadImage(IMG_WIS_TIMESTEP, wis_timestep_png, wis_timestep_png_size)
        && loadImage(IMG_WIS_TRON, wis_tron_png, wis_tron_png_size)
        && loadImage(IMG_WIS_WARP, wis_warp_png, wis_warp_png_size)
        && loadImage(IMG_WI_BG, wi_bg_png, wi_bg_png_size)
        && loadImage(IMG_WI_CHILIRUN, wi_chilirun_png, wi_chilirun_png_size)
        && loadImage(IMG_WI_CONFUSION, wi_confusion_png, wi_confusion_png_size)
        && loadImage(IMG_WI_FROST, wi_frostwave_png, wi_frostwave_png_size)
        && loadImage(IMG_WI_GHOST, wi_ghost_png, wi_ghost_png_size)
        && loadImage(IMG_WI_MOLE, wi_mole_png, wi_mole_png_size)
        && loadImage(IMG_WI_ROCKETLAUNCHER, wi_rocketlauncher_png, wi_rocketlauncher_png_size)
        && loadImage(IMG_WI_SHARPTURN, wi_sharpturn_png, wi_sharpturn_png_size)
        && loadImage(IMG_WI_SPEED, wi_lightningspeed_png, wi_lightningspeed_png_size)
        && loadImage(IMG_WI_TIMESTEP, wi_timestep_png, wi_timestep_png_size)
        && loadImage(IMG_WI_TRON, wi_tron_png, wi_tron_png_size)
        && loadImage(IMG_WI_WARP, wi_warp_png, wi_warp_png_size);
    #else
    return loadImage(IMG_ARROWS, "arrowsheet.png")
        && loadImage(IMG_BALL, "ball.png")
        && loadImage(IMG_LOGO, "logo.png")
        && loadImage(IMG_WIS_CHILIRUN, "wis_chilirun.png")
        && loadImage(IMG_WIS_CONFUSION, "wis_confusion.png")
        && loadImage(IMG_WIS_FROST, "wis_frostwave.png")
        && loadImage(IMG_WIS_GHOST, "wis_ghost.png")
        && loadImage(IMG_WIS_MOLE, "wis_mole.png")
        && loadImage(IMG_WIS_ROCKETLAUNCHER, "wis_rocketlauncher.png")
        && loadImage(IMG_WIS_SHARPTURN, "wis_sharpturn.png")
        && loadImage(IMG_WIS_SPEED, "wis_lightningspeed.png")
        && loadImage(IMG_WIS_TIMESTEP, "wis_timestep.png")
        && loadImage(IMG_WIS_TRON, "wis_tron.png")
        && loadImage(IMG_WIS_WARP, "wis_warp.png")
        && loadImage(IMG_WI_BG, "wi_bg.png")
        && loadImage(IMG_WI_CHILIRUN, "wi_chilirun.png")
        && loadImage(IMG_WI_CONFUSION, "wi_confusion.png")
        && loadImage(IMG_WI_FROST, "wi_frostwave.png")
        && loadImage(IMG_WI_GHOST, "wi_ghost.png")
        && loadImage(IMG_WI_MOLE, "wi_mole.png")
        && loadImage(IMG_WI_ROCKETLAUNCHER, "wi_rocketlauncher.png")
        && loadImage(IMG_WI_SHARPTURN, "wi_sharpturn.png")
        && loadImage(IMG_WI_SPEED, "wi_lightningspeed.png")
        && loadImage(IMG_WI_TIMESTEP, "wi_timestep.png")
        && loadImage(IMG_WI_TRON, "wi_tron.png")
        && loadImage(IMG_WI_WARP, "wi_warp.png");
    #endif
}

/**
 * Initialize the player colors.
 */
void initColors(void)
{
    SDL_Color *c = &colors[0];
    c->r = 0xFF; c->g = 0x00; c->b = 0x00; ++c; /* Red */
    c->r = 0x00; c->g = 0x6F; c->b = 0xFF; ++c; /* Blue */
    c->r = 0x00; c->g = 0xFF; c->b = 0x00; ++c; /* Green */
    c->r = 0xFF; c->g = 0xFF; c->b = 0x00; ++c; /* Yellow */
    c->r = 0xFF; c->g = 0x00; c->b = 0xFF; ++c; /* Pink */
    c->r = 0x00; c->g = 0xFF; c->b = 0xFF; ++c; /* Cyan */
    c->r = 0xFF; c->g = 0xFF; c->b = 0xFF; ++c; /* White */
    c->r = 0xFF; c->g = 0x80; c->b = 0x00; ++c; /* Orange */
}
