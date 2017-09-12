/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   42run.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibautpierron <thibautpierron@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/21 11:23:17 by tpierron          #+#    #+#             */
/*   Updated: 2017/09/11 23:12:20 by thibautpier      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RUN42
# define RUN42

# define WIN_WIDTH 1024
# define WIN_HEIGHT 1024
# define PARTICLE_NBR 10000

// # include "SDL.h"
# include <SDL2/SDL.h>
# include <iostream>
# include "classes/game/Game.class.hpp"


SDL_Window	*initSDL(SDL_GLContext ctx);
void    	eventManager(SDL_Event *events, bool *exitLoop, Game *game);
void    	windowTitleUpdate(SDL_Window *win, int frameDuration);
// Vec4    	getMousePosition(SDL_Window *win);
// void    	windowTitleUpdate(SDL_Window *win, int frameDuration);
// void    	resetCamera(Vec4 *cameraRotation);


#endif