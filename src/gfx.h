#ifndef GFX_H
#define GFX_H

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <stdbool.h>

#include "common.h"
#include "data.h"
#include "error.h"

#define N_COLORS 8 /* Number of available player colors */

extern SDL_Color colors[N_COLORS];

typedef enum image {
    IMG_ARROWS = 0,
    IMG_BALL,
    IMG_LOGO,
    IMG_WIS_CHILIRUN,
    IMG_WIS_CONFUSION,
    IMG_WIS_FROST,
    IMG_WIS_GHOST,
    IMG_WIS_MOLE,
    IMG_WIS_ROCKETLAUNCHER,
    IMG_WIS_SHARPTURN,
    IMG_WIS_SPEED,
    IMG_WIS_TIMESTEP,
    IMG_WIS_TRON,
    IMG_WIS_WARP,
    IMG_WI_BG,
    IMG_WI_CHILIRUN,
    IMG_WI_CONFUSION,
    IMG_WI_FROST,
    IMG_WI_GHOST,
    IMG_WI_MOLE,
    IMG_WI_ROCKETLAUNCHER,
    IMG_WI_SHARPTURN,
    IMG_WI_SPEED,
    IMG_WI_TIMESTEP,
    IMG_WI_TRON,
    IMG_WI_WARP,
    N_IMAGES
} Image;

extern SDL_Surface *images[N_IMAGES];

int clearSurface(SDL_Surface *s);

#ifndef GEKKO
// icons only makes sense in windowing systems
SDL_Surface *loadIcon(const char *filename);
#endif

#ifdef GEKKO
bool loadImage(Image i, const uint8_t* imageData, size_t imageSize);
#else
bool loadImage(Image i, const char *filename);
#endif

bool loadImages(void);
void initColors(void);

#endif
