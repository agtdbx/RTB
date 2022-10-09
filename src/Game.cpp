//
// Created by auguste on 31/01/2022.
//

#include "../include/Game.h"
#include "../include/Functions.h"
#include <SDL2/SDL.h>
#include <string>
#include <ostream>
#include <fstream>
#include <sstream>
#include <jsoncpp/json/json.h>
#include <jsoncpp/json/value.h>
#include <jsoncpp/json/writer.h>
#include <jsoncpp/json/reader.h>
#include <dirent.h>

//Private methods
void Game::initButton() {
    SDL_Color colorOff = {255, 255, 255, 0};
    SDL_Color colorOn = {100, 100, 100, 100};
    this->butContinuer = Button("Continuer", 40, 1, this->textColor, this->winW/2 - 100, this->winH/2 - 75, 200, 50, colorOff, colorOn,2, this->color);
    this->butQuitter = Button("Quitter", 40, 1, this->textColor, this->winW/2 - 100, this->winH/2 + 25, 200, 50, colorOff, colorOn,2, this->color);
    this->butRetourMenu = Button("Retour au menu", 40, 1, this->textColor, this->winW/2 - 150, this->winH/2 - 75, 300, 50, colorOff, colorOn,2, this->color);
}

void Game::input() {
    SDL_Event event;
    while(SDL_PollEvent(&event)){
        switch (event.type) {
            case SDL_QUIT:
                this->run = false;
                break;

            case SDL_KEYDOWN:
                if (event.key.keysym.sym == SDLK_ESCAPE && this->fenetre != 2){
                    if (this->fenetre == 0){
                        this->fenetre = 1;
                    }
                    else{
                        this->fenetre = 0;
                    }
                }
                break;
        }
    }
}


void Game::tick() {
    float delta = ((float)SDL_GetTicks()/1000.0f) - this->lastTime;
    if (this->perso.atFin(&this->map)){
        this->fenetre = 2;
    }
    if (this->fenetre == 0){
        int keylen;
        const unsigned char *keyboard = SDL_GetKeyboardState(&keylen);

        if (keyboard[SDL_SCANCODE_F3]) {
            this->showFps = !this->showFps;
        }
        if (this->showFps && (int)SDL_GetTicks()%100 == 0){
            this->fps = 1.0f / delta;
        }

        if (!this->perso.isMort(&this->map)){
            if (keyboard[this->toucheGauche]) {
                this->perso.deplacementX('g', &this->map);
            }
            else if (keyboard[this->toucheDroite]) {
                this->perso.deplacementX('d', &this->map);
            }
            else{
                this->perso.deplacementX('n', &this->map);
            }

            if (this->perso.saut(&this->map, keyboard[this->toucheSaut]))
                Mix_PlayChannel(-1, this->jump_sound, 0);
            if (this->perso.walljump(&this->map, keyboard[this->toucheSaut]))
                Mix_PlayChannel(-1, this->walljump_sound, 0);

            this->perso.addVy(this->gravity);
            this->perso.move(delta, this->camera, &this->map);
        }
        else if (SDL_GetTicks()/1000.0f - this->lastRespawnTime >= 1.0f && this->canRespawn){
            this->perso.respawn();
            this->canRespawn = false;
        }
        else if (!this->canRespawn){
            this->lastRespawnTime = SDL_GetTicks()/1000.0f;
            this->canRespawn = true;
        }

        Zone *checkpoint = this->map.testCheckpoint(this->perso.getX(), this->perso.getY(), this->perso.getWidth(), this->perso.getHeight());

        if (checkpoint != NULL && checkpoint->getId() > this->checkpointProgression){
            this->checkpointProgression = checkpoint->getId();
            this->perso.setRespawn(checkpoint->getX() * this->map.getSquarreSize(), checkpoint->getY() * this->map.getSquarreSize());
        }
        this->camera.tick(this->perso.getX(), this->perso.getY(), this->perso.getVx(), this->perso.getVy(), this->perso.getWidth(), this->perso.getHeight(), &this->background, delta);
    }
    else if (this->fenetre == 1) {
        if (this->butContinuer.clicOnButton()){
            this->fenetre = 0;
        }
        else if (this->butQuitter.clicOnButton()){
            this->levelInGame = 0;
            this->run = false;
        }
    }
    else{
        this->perso.deplacementX('n', &this->map);
        this->perso.addVy(this->gravity);
        this->perso.move(delta, this->camera, &this->map);
        if (this->butRetourMenu.clicOnButton()){
            this->run = false;
        }
    }
    this->lastTime = ((float)SDL_GetTicks()/1000.0f);
}


void Game::render() {
    SDL_SetRenderDrawColor(this->renderer, 255, 255, 255, 255);
    SDL_RenderClear(this->renderer);

    this->background.draw(this->renderer);

    this->map.draw(this->renderer, this->camera, this->winW, this->winH);

    if (!this->perso.isMort(&map))
        this->perso.draw(this->renderer, this->camera);
    switch (this->fenetre) {
        case 0:

            if (this->showFps){
                SDL_Color green = {0, 200, 0, 255};
                char strfps[10] = "000000000";
                snprintf(strfps, sizeof(strfps), "%f", this->fps);
                drawText(this->renderer, strfps, 20, this->winW, 0, 3, green);
            }

            break;

        case 1:
            this->butContinuer.draw(this->renderer);
            this->butQuitter.draw(this->renderer);
            break;

        case 2:
            this->butRetourMenu.draw(this->renderer);
    }

    SDL_RenderPresent(this->renderer);
}


void Game::loadMap(std::string filename) {
    std::string file = "";
    file.append(filename);
    file.append(".json");

    bool test = false;
    DIR *d;
    struct dirent *dir;
    d = opendir("./data/levels/");
    if (d){
        while ((dir = readdir(d)) != NULL){
            std::string file_name = dir->d_name;
            if (file_name != "." && file_name != ".."){
                if (file_name == file){
                    test = true;
                }
            }
        }
        closedir(d);
    }

    if (test){
        Json::Value json;

        std::string filepath = "./data/levels/";
        filepath.append(file);

        std::ifstream myfile(filepath);

        myfile >> json; // Récupération du fichier
        std::string fname = json["filename"].asString();
        std::string mname = json["name"].asString();
//        this->filename = json["filename"].asString();
//        this->mapname = json["name"].asString();

        int w = json["width"].asInt();
        int h = json["heigth"].asInt();
        //int size = json["square_size"].asInt();
        int size = 24;
        this->map = Map(w, h, size, this->renderer);

        // Chargement du debut
        Json::Value debut = json["start"];
        Zone start = Zone(debut["x"].asInt(), debut["y"].asInt(), "start", size, this->renderer);
        this->map.setStart(start, this->renderer);

        // Chargement de la fin
        Json::Value fin = json["end"];
        Zone end = Zone(fin["x"].asInt(), fin["y"].asInt(), "end", size, this->renderer);
        this->map.setEnd(end, this->renderer);

        // Chargement des checkpoints
        Json::Value checkpoints = json["checkpoints"];
        if (checkpoints.isArray()){
            for (int i = 0; i < checkpoints.size(); i++){
                Json::Value check = checkpoints[i];

                int x = check["x"].asInt();
                int y = check["y"].asInt();
                int id = check["id"].asInt();

                Zone checkpoint = Zone(x, y, id, size, this->renderer);
                this->map.addCheckpoint(checkpoint);
            }      }

        Json::Value tuiles = json["map"];
        for (int i = 0; i < tuiles.size(); i++){
            Json::Value t = tuiles[i];

            int x = t["x"].asInt();
            int y = t["y"].asInt();
            std::string type = t["type"].asString();

            Tuile tuile = Tuile(x, y, size, const_cast<char*>(type.c_str()), this->renderer);
            this->map.set(x, y, tuile);
        }
    }
}



//Public methods
Game::Game(SDL_Renderer *renderer, int winW, int winH) {
    this->winW = winW;
    this->winH = winH;
    this->renderer = renderer;
    this->run = true;
    this->fenetre = 0;
    this->volumeSon = 100;
    this->volumeMusique = 100;
    this->toucheGauche = 20;
    this->toucheDroite = 7;
    this->toucheSaut = 44;
    this->lastTime = ((float)SDL_GetTicks()/1000.0f);
    this->camera = Camera();
    this->showFps = false;
    this->fps = 0.0f;
    this->gravity = 40.0f * (20.0f / 24.0f);
    this->fpsUnlimited = false;
    this->background = Background(this->renderer, this->winW, this->winH);
    this->color = {100, 100, 100, 255};
    this->textColor = {150, 150, 150, 255};
    this->lastRespawnTime = 0.0f;
    this->canRespawn = false;
    this->game_theme = Mix_LoadMUS("./data/sounds/game_theme.wav");
    this->jump_sound = Mix_LoadWAV("./data/sounds/jump.wav");
    this->walljump_sound = Mix_LoadWAV("./data/sounds/walljump.wav");
    this->levelInGame = 0;

    this->initButton();
}


Game::~Game() {
    Mix_FreeMusic(this->game_theme);
    Mix_FreeChunk(this->jump_sound);
    Mix_FreeChunk(this->walljump_sound);
}


int Game::start() {
    this->run = true;
    this->fenetre = 0;
    Mix_PlayMusic(this->game_theme, -1);
    Mix_VolumeMusic(this->volumeMusique);
    Mix_Volume(-1, this->volumeSon);
    while(this->run){
        if (((float)SDL_GetTicks()/1000) - this->lastTime >= 1.0f/60.0f || this->fpsUnlimited){
            this->input();
            this->tick();
            this->render();
        }
    }
    Mix_HaltMusic();
    float wait = (float)SDL_GetTicks()/1000.0f;
    while ((float)SDL_GetTicks()/1000.0f - wait < 0.2);
    return this->levelInGame;
}


void Game::initLevel(int levelNum) {
    switch (levelNum) {
        case 1:
            this->loadMap("test1");
            break;

        case 2:
            this->loadMap("test2");
            break;

        case 3:
            this->loadMap("test3");
            break;

        case 4:
            this->loadMap("test4");
            break;
    }
    this->levelInGame = levelNum;
    this->perso = Personnage(this->map.getStart().getX() * this->map.getSquarreSize(), this->map.getStart().getY() * this->map.getSquarreSize(), this->map.getSquarreSize(), this->renderer);
    this->camera.setWindowSize(this->winW, this->winH);
    this->camera.setMapSize(this->map.getWidth(), this->map.getHeigth(), this->map.getSquarreSize());
    this->checkpointProgression = -1;
    this->background = Background(this->renderer, this->winW, this->winH);
}


void Game::setVariables(int volumeSon, int volumeMusique, int toucheGauche, int toucheDroite, int toucheSaut, int winWidth, int winHeight) {
    this->volumeSon = volumeSon;
    this->volumeMusique = volumeMusique;
    this->toucheGauche = toucheGauche;
    this->toucheDroite = toucheDroite;
    this->toucheSaut = toucheSaut;
    this->winW = winWidth;
    this->winH = winHeight;

    this->butContinuer.setX(this->winW/2 - 100);
    this->butContinuer.setY(this->winH/2 - 75);
    this->butQuitter.setX(this->winW/2 - 100);
    this->butQuitter.setY(this->winH/2 + 25);
}