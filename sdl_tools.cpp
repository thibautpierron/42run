/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl_tools.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpierron <tpierron@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/20 14:18:32 by tpierron          #+#    #+#             */
/*   Updated: 2017/10/03 16:49:49 by tpierron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "42run.hpp"

SDL_Window *initSDL(SDL_GLContext ctx) {
    SDL_Init(SDL_INIT_VIDEO);

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    SDL_Window *win = SDL_CreateWindow("42Run",
                            SDL_WINDOWPOS_UNDEFINED,
                            SDL_WINDOWPOS_UNDEFINED,
                            WIN_WIDTH, WIN_HEIGHT,
                            SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);
    ctx = SDL_GL_CreateContext(win);
    if(ctx == 0) {
        std::cout << SDL_GetError() << std::endl;
        exit(0);
    }

    return win;
}

void    windowTitleUpdate(SDL_Window *win, int frameDuration) {
    static int timeCounter = 0;
    std::string frameRate;
    std::string newTitle;

    timeCounter += frameDuration;
    if(timeCounter > 1000000) {
        frameRate = std::to_string(1000000 / frameDuration);
        newTitle = "42 run (" + frameRate + "fps)"; 
        SDL_SetWindowTitle(win, newTitle.c_str());
        timeCounter = 0;
    }
}

void    eventManager(SDL_Event *events, bool *exitLoop, Game *game) {
    static int repeatFlag = 0;
    if (events->window.event == SDL_WINDOWEVENT_CLOSE || events->key.keysym.sym == SDLK_ESCAPE) {
        *exitLoop = true;
        return;
    }
    if (events->type == SDL_KEYUP)
        repeatFlag = 0;
    if (events->type == SDL_KEYDOWN && repeatFlag == 0) {
        repeatFlag = 1;
        switch(events->key.keysym.sym) {
            case SDLK_SPACE:
                switch (game->getState()) {
                    case 0: game->start(); break;
                    case 1: game->orientatePlayer(); break;
                    case 2: game->start(); break;
                }
                
                break;
            case SDLK_w: game->orientatePlayer(Orientation::NORTH); break;
            case SDLK_s: game->orientatePlayer(Orientation::SOUTH); break;
            case SDLK_d: game->orientatePlayer(Orientation::EAST); break;
            case SDLK_a: game->orientatePlayer(Orientation::WEST); break;
            case SDLK_RIGHT: game->movePlayerRight(); break;
            case SDLK_LEFT: game->movePlayerLeft(); break;
            // case SDLK_UP: game->area->n++; break;
            // case SDLK_DOWN: game->area->n--; break;
            // case SDLK_KP_MINUS: cameraRotation->z -= 0.5; *pause = true; break;
            // case SDLK_KP_PLUS: cameraRotation->z += 0.5; *pause = true; break;
        }
    }
    // if (events->button.button == SDL_BUTTON_LEFT) {
    //     *pause = false;
    //     *mousePosition = getMousePosition(win);
    //     resetCamera(cameraRotation);
    // }
}