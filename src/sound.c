/* sound -- sound handling.
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
// sound resources packed into binary data
#include "sound_theme1_ogg.h"
#include "sound_bep_ogg.h"
#include "sound_beep_ogg.h"
#include "sound_beeep_ogg.h"
#include "sound_beeeep_ogg.h"
#include "sound_beeeeep_ogg.h"
#include "sound_beeeeeep_ogg.h"
#include "sound_beeeeeeep_ogg.h"
#include "sound_beeeeeeeep_ogg.h"
#include "sound_round_begin_ogg.h"
#include "sound_crash_ogg.h"
#include "sound_explosion_ogg.h"
#include "sound_speed_ogg.h"
#include "sound_freeze_ogg.h"
#include "sound_confusion_ogg.h"
#include "sound_sharpturn_ogg.h"
#include "sound_timestep_ogg.h"
#include "sound_mole_ogg.h"
#include "sound_warp_ogg.h"
#include "sound_ghost_ogg.h"
#include "sound_tronmode_ogg.h"
#include "sound_chilirun_ogg.h"
#include "sound_rocketlauncher_ogg.h"
#endif

#include "sound.h"

Mix_Music *bgm = NULL;
Mix_Chunk *sounds[N_SOUNDS];

/**
 * Initialize the mixer. Return -1 on failure, 0 else.
 */
int initSound(void)
{
    return Mix_OpenAudio(MIX_DEFAULT_FREQUENCY * 2, MIX_DEFAULT_FORMAT, 2,
                         512);
}

/**
 * Load a sound file `filename` and identify it as `s`. Return true on
 * success, otherwise false.
 */
#ifdef GEKKO
bool loadSound(Sound s, const uint8_t* soundData, size_t soundSize)
#else
bool loadSound(Sound s, const char *filename)
#endif
{
    #ifdef GEKKO
    Mix_Chunk *sound = Mix_LoadWAV_RW(SDL_RWFromMem(soundData, soundSize), 0);
    #else
    char *file = dataFile("sound", filename);
    Mix_Chunk *sound = Mix_LoadWAV(file);
    #endif
    
    if (sound == NULL) {
        #ifndef GEKKO
        fileNotFound(file);
        free(file);
        #endif
        return false;
    }

    sounds[s] = sound;
    #ifndef GEKKO
    free(file);
    #endif
    return true;
}

/**
 * Load the background music from `filename`. Return true on success,
 * otherwise false.
 */
#ifdef GEKKO
bool loadBGM(const uint8_t* soundData, size_t soundSize)
#else
bool loadBGM(const char *filename)
#endif
{
    #ifdef GEKKO
    bgm = Mix_LoadMUS_RW(SDL_RWFromMem(soundData, soundSize));
    #else
    char *file = dataFile("sound", filename);
    bgm = Mix_LoadMUS(file);
    #endif
    
    if (bgm == NULL) {
        #ifndef GEKKO
        fileNotFound(file);
        free(file);
        #endif
        return false;
    }

    #ifndef GEKKO
    free(file);
    #endif
    return true;
}

/**
 * Load every needed sound file. Return true if every file loaded
 * successfully, otherwise false.
 */
bool loadSounds(void)
{
    #ifdef GEKKO
    return loadBGM(theme1_ogg, theme1_ogg_size)
        && loadSound(SOUND_BEP, bep_ogg, bep_ogg_size)
        && loadSound(SOUND_BEEP, beep_ogg, beep_ogg_size)
        && loadSound(SOUND_BEEEP, beeep_ogg, beeep_ogg_size)
        && loadSound(SOUND_BEEEEP, beeeep_ogg, beeeep_ogg_size)
        && loadSound(SOUND_BEEEEEP, beeeeep_ogg, beeeeep_ogg_size)
        && loadSound(SOUND_BEEEEEEP, beeeeeep_ogg, beeeeeep_ogg_size)
        && loadSound(SOUND_BEEEEEEEP, beeeeeeep_ogg, beeeeeeep_ogg_size)
        && loadSound(SOUND_BEEEEEEEEP, beeeeeeeep_ogg, beeeeeeeep_ogg_size)
        && loadSound(SOUND_ROUND_BEGIN, round_begin_ogg, round_begin_ogg_size)
        && loadSound(SOUND_CRASH, crash_ogg, crash_ogg_size)
        && loadSound(SOUND_EXPLOSION, explosion_ogg, explosion_ogg_size)
        && loadSound(SOUND_SPEED, speed_ogg, speed_ogg_size)
        && loadSound(SOUND_FREEZE, freeze_ogg, freeze_ogg_size)
        && loadSound(SOUND_CONFUSION, confusion_ogg, confusion_ogg_size)
        && loadSound(SOUND_SHARPTURN, sharpturn_ogg, sharpturn_ogg_size)
        && loadSound(SOUND_TIMESTEP, timestep_ogg, timestep_ogg_size)
        && loadSound(SOUND_MOLE, mole_ogg, mole_ogg_size)
        && loadSound(SOUND_WARP, warp_ogg, warp_ogg_size)
        && loadSound(SOUND_GHOST, ghost_ogg, ghost_ogg_size)
        && loadSound(SOUND_TRON, tronmode_ogg, tronmode_ogg_size)
        && loadSound(SOUND_CHILIRUN, chilirun_ogg, chilirun_ogg_size)
        && loadSound(SOUND_ROCKETLAUNCHER, rocketlauncher_ogg, rocketlauncher_ogg_size);
    #else
    return loadBGM("theme1.ogg")
        && loadSound(SOUND_BEP, "bep.ogg")
        && loadSound(SOUND_BEEP, "beep.ogg")
        && loadSound(SOUND_BEEEP, "beeep.ogg")
        && loadSound(SOUND_BEEEEP, "beeeep.ogg")
        && loadSound(SOUND_BEEEEEP, "beeeeep.ogg")
        && loadSound(SOUND_BEEEEEEP, "beeeeeep.ogg")
        && loadSound(SOUND_BEEEEEEEP, "beeeeeeep.ogg")
        && loadSound(SOUND_BEEEEEEEEP, "beeeeeeeep.ogg")
        && loadSound(SOUND_ROUND_BEGIN, "round_begin.ogg")
        && loadSound(SOUND_CRASH, "crash.ogg")
        && loadSound(SOUND_EXPLOSION, "explosion.ogg")
        && loadSound(SOUND_SPEED, "speed.ogg")
        && loadSound(SOUND_FREEZE, "freeze.ogg")
        && loadSound(SOUND_CONFUSION, "confusion.ogg")
        && loadSound(SOUND_SHARPTURN, "sharpturn.ogg")
        && loadSound(SOUND_TIMESTEP, "timestep.ogg")
        && loadSound(SOUND_MOLE, "mole.ogg")
        && loadSound(SOUND_WARP, "warp.ogg")
        && loadSound(SOUND_GHOST, "ghost.ogg")
        && loadSound(SOUND_TRON, "tronmode.ogg")
        && loadSound(SOUND_CHILIRUN, "chilirun.ogg")
        && loadSound(SOUND_ROCKETLAUNCHER, "rocketlauncher.ogg");
    #endif
}

/**
 * Plays a sound.
 *
 * @param sound One of the sounds stated in enum sounds (see sound.h).
 * @param play 1 if the sound is to be played, 0 else.
 */
void playSound(unsigned int sound, int play)
{
    if (play)
        Mix_PlayChannel(-1, sounds[sound], 0);
}

/**
 * Plays the background music.
 */
void playBGM(void)
{
    if (!Mix_PlayingMusic()) {
        if ((Mix_PlayMusic(bgm, -1) == -1)) {
            if (olvl >= O_NORMAL)
                fprintf(stderr, "Couldn't play music: %s\n", Mix_GetError());
        }
    }
}

/**
 * Stops the background music.
 */
void stopBGM(void)
{
    Mix_HaltMusic();
}
