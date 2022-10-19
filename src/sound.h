#ifndef SOUND_H
#define SOUND_H

#include <SDL/SDL_mixer.h>
#include <stdbool.h>

#include "common.h"
#include "data.h"
#include "error.h"

typedef enum sound {
    SOUND_BEP = 0,
    SOUND_BEEP,
    SOUND_BEEEP,
    SOUND_BEEEEP,
    SOUND_BEEEEEP,
    SOUND_BEEEEEEP,
    SOUND_BEEEEEEEP,
    SOUND_BEEEEEEEEP,
    SOUND_ROUND_BEGIN,
    SOUND_CRASH,
    SOUND_EXPLOSION,
    SOUND_SPEED,
    SOUND_FREEZE,
    SOUND_CONFUSION,
    SOUND_SHARPTURN,
    SOUND_TIMESTEP,
    SOUND_MOLE,
    SOUND_WARP,
    SOUND_GHOST,
    SOUND_TRON,
    SOUND_CHILIRUN,
    SOUND_ROCKETLAUNCHER,
    N_SOUNDS
} Sound;

extern Mix_Music *bgm;

int initSound(void);

#ifdef GEKKO
bool loadSound(Sound s, const uint8_t* soundData, size_t soundSize);
#else
bool loadSound(Sound s, const char *filename);
#endif

bool loadSounds(void);
void playSound(unsigned int sound, int play);
void playBGM(void);
void stopBGM(void);

#endif
