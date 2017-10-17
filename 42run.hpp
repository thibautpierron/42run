/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   42run.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpierron <tpierron@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/21 11:23:17 by tpierron          #+#    #+#             */
/*   Updated: 2017/10/17 13:45:02 by tpierron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RUN42
# define RUN42

# define WIN_WIDTH 1024
# define WIN_HEIGHT 1024

# include <SDL2/SDL.h>
# include <iostream>
# include "classes/game/Game.class.hpp"
# include "./constants/constants.hpp"


SDL_Window	*initSDL(SDL_GLContext ctx);
void    	eventManager(SDL_Event *events, bool *exitLoop, Game *game);
void    	windowTitleUpdate(SDL_Window *win, int frameDuration);

#endif