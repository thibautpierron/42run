/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpierron <tpierron@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/21 11:25:21 by tpierron          #+#    #+#             */
/*   Updated: 2017/10/04 10:25:07 by tpierron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "42run.hpp"

void    glInit() {
    glClearColor(0.5f, 0.5f, 0.5f, 0.5f);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glFrontFace(GL_CCW);
}

int     main() {
    srand(time(NULL));

    SDL_Event		events;
    SDL_GLContext	ctx;
    SDL_Window		*win;
	bool			exitLoop = false;
    std::chrono::high_resolution_clock::time_point  start, end;

    win = initSDL(&ctx);
    glInit();

    float gameSpeed = 6.f / 60.f;
    float gameTick = 0.f;
    Game game(gameSpeed);

	while (!exitLoop) {
        start = std::chrono::high_resolution_clock::now();
        if(gameTick >= 1.f)
            gameTick = 0.f;
        SDL_PollEvent(&events);
        eventManager(&events, &exitLoop, &game);
        
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        switch(game.getState()) {
            case 0: game.displayStartScreen(); break;
            case 1:
                game.compute(gameTick);
                game.render(gameSpeed);
                break;
            case 2: game.displayScoreScreen(); break;
            // default: game.displayStartScreen(); break;
        }
        
        SDL_GL_SwapWindow(win);
        end = std::chrono::high_resolution_clock::now();
        windowTitleUpdate(win, std::chrono::duration_cast<std::chrono::microseconds>( end - start ).count());
        gameTick += gameSpeed;
    }
    
    SDL_GL_DeleteContext(ctx);
    SDL_DestroyWindow(win);
    SDL_Quit();
    
    return 0;
}