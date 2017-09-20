/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Game.class.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpierron <tpierron@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/11 11:15:50 by tpierron          #+#    #+#             */
/*   Updated: 2017/09/20 13:40:12 by tpierron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GAME_CLASS_HPP
# define GAME_CLASS_HPP

# include <deque>
# include "./Area.class.hpp"
# include "./Player.class.hpp"
# include "./Camera.class.hpp"
# include "../../constants/constants.hpp"

class Game {
	
	public:
		Game();
		Game(float);
		~Game();
		void				compute(float gameTime);
		void				render(float gameTime);
		Player				*getPlayer();
		void				orientatePlayer();
		void				orientatePlayer(Orientation::Enum);
		void				movePlayerRight();
		void				movePlayerLeft();
		void				setCamera();
		
	private:
		void				initAreas();
		void				checkObstaclesCollision();
		bool				checkWallCollision();
		void				addArea(Orientation::Enum);
		void				delArea();
		void				manageAreas();
		bool				playerCanTurn();
		Orientation::Enum	getRandOrientationDifferentFrom(Orientation::Enum) const;
		void				transcriptCrdToCameraRef(float *, float *, Orientation::Enum);
		
		Player	*player;
		Camera	camera;
		float	gameSpeed;
		std::vector<glm::vec2>	obstacles;
		Orientation::Enum		movementDirection;
		float					gameClockRender;

		bool					areasUpdated;
		std::deque<Area*>		areas;
		unsigned int			currentAreaInd;
};

#endif