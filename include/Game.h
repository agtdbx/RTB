//
// Created by auguste on 31/01/2022.
//

#ifndef RTB_GAME_H
#define RTB_GAME_H

#include <SDL2/SDL.h>
#include "../include/Button.h"
#include "../include/Personnage.h"
#include "../include/Map.h"
#include "../include/Camera.h"
#include "../include/Background.h"

class Game {
private:
    SDL_Renderer *renderer;
    int winW, winH, fenetre, volumeMusique, volumeSon, toucheGauche, toucheDroite, toucheSaut, checkpointProgression;
    bool run, showFps, fpsUnlimited;
    Button butContinuer, butQuitter, butRetourMenu;
    Personnage perso;
    float lastTime, fps, gravity;
    Map map;
    Camera camera;
    Background background;

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
