/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Game.class.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpierron <tpierron@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/11 11:15:50 by tpierron          #+#    #+#             */
/*   Updated: 2017/09/18 10:52:37 by tpierron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GAME_CLASS_HPP
# define GAME_CLASS_HPP

# include <deque>
# include "./Area.class.hpp"
# include "./Player.class.hpp"
# include "../../constants/constants.hpp"

class Game {
	
	public:
		Game();
		~Game();
		void	compute(float gameTime);
		void	render(float gameTime);
		Player	*getPlayer();
		void	orientatePlayer();
		void	orientatePlayer(Orientation::Enum);
		void	movePlayerRight();
		void	movePlayerLeft();
		void	setCamera();
		
	private:
		void	initAreas();
		void	checkCollision();
		void	addArea(Orientation::Enum);
		void	delArea();
		void	manageAreas();
		bool	playerCanTurn() const;
		Orientation::Enum	getRandOrientationDifferentFrom(Orientation::Enum) const;
		
		Player	*player;
		std::vector<glm::vec2> obstacles;
		Orientation::Enum	movementDirection;
		float	gameClockRender;
		bool	areasUpdated;

		std::deque<Area*>	areas;
		unsigned int		currentAreaInd;
};

#endif