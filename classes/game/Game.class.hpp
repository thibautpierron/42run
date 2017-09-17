/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Game.class.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibautpierron <thibautpierron@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/11 11:15:50 by tpierron          #+#    #+#             */
/*   Updated: 2017/09/17 17:41:37 by thibautpier      ###   ########.fr       */
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
		
		// Area	*area;
		// Area	*area2;
	private:
		void	initAreas();
		void	checkCollision();
		void	addArea(Orientation::Enum);
		void	delArea();
		void	manageAreas();
		Orientation::Enum	getRandOrientationDifferentFrom(Orientation::Enum) const;
		
		Player	*player;
		std::vector<glm::vec2> obstacles;
		Orientation::Enum	movementDirection;
		float	gameClockRender;
		bool	areasUpdated;

		std::deque<Area*>	areas;
};

#endif