/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Game.class.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpierron <tpierron@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/11 11:15:50 by tpierron          #+#    #+#             */
/*   Updated: 2017/09/15 09:20:39 by tpierron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GAME_CLASS_HPP
# define GAME_CLASS_HPP

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
		void	movePlayerRight();
		void	movePlayerLeft();
		
		Area	*area;
		Area	*area2;
	private:
		bool	checkCollision();
		
		Player	*player;
		std::vector<glm::vec2> obstacles;
		Orientation::Enum	movementDirection;
};

#endif