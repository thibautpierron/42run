/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpierron <tpierron@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/21 11:25:21 by tpierron          #+#    #+#             */
/*   Updated: 2017/09/15 12:43:28 by tpierron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "42run.hpp"

void    glInit() {
    glClearColor(0.5f, 0.5f, 0.5f, 1.0f);

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

    Game game;
    float gameSpeed = 2.f / 60.f;
    float gameTick = 0.f;


	while (!exitLoop) {
        start = std::chrono::high_resolution_clock::now();
        if(gameTick > 1.f)
            gameTick = 0.f;
        SDL_PollEvent(&events);
        eventManager(&events, &exitLoop, &game);
        
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        game.compute(gameTick);
        game.render(gameSpeed);
        
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