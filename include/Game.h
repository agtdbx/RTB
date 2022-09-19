//
// Created by auguste on 31/01/2022.
//

#ifndef RTB_GAME_H
#define RTB_GAME_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include "../include/Button.h"
#include "../include/Personnage.h"
#include "../include/Map.h"
#include "../include/Camera.h"
#include "../include/Background.h"

class Game {
private:
    SDL_Renderer *renderer;
    int winW, winH, fenetre, volumeMusique, volumeSon, toucheGauche, toucheDroite, toucheSaut, checkpointProgression;
    bool run, showFps, fpsUnlimited, canRespawn;
    Button butContinuer, butQuitter, butRetourMenu;
    Personnage perso;
    float lastTime, fps, gravity, lastRespawnTime;
    Map map;
    Camera camera;
    Background background;
    SDL_Color color, textColor;
    Mix_Music *game_theme;
    Mix_Chunk *jump_sound, *walljump_sound;

    void initButton();
    void input();
    void tick();
    void render();
    void loadMap(std::string filename);

public:
    Game(SDL_Renderer *renderer, int winW, int winH);
    ~Game();

    void start();
    void initLevel(int levelNum);
    void setVariables(int volumeSon, int volumeMusique, int toucheGauche, int toucheDroite, int toucheSaut, int winWidth, int winHeight);
};


#endif //RTB_GAME_H
