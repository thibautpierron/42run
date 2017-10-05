/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Stage.class.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpierron <tpierron@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/21 11:33:26 by tpierron          #+#    #+#             */
/*   Updated: 2017/10/05 11:27:30 by tpierron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STAGE_CLASS_HPP
# define STAGE_CLASS_HPP

# include <vector>
# include "../../constants/constants.hpp"
# include "../model/Model.class.hpp"

class Stage {
	public:
		Stage(int);
		
		int getLineNbr(Orientation::Enum) const;
		int getPatternLength(Orientation::Enum) const;
		Model* getObstacleModel() const;
		Model* getSceneryModel() const;
		Model* getGroundModel() const;
		Model* getCeilingModel() const;

	private:
		Stage();
		void	initClusterStage();
		void	initOutsideStage();

		int lineNbrHorizontal;
		int lineNbrVertical;
		int patternLengthHorizontal;	
		int patternLengthVertical;
		
		std::vector<std::string>	scenery;	
		std::vector<std::string>	obstacleFull;	
		std::vector<std::string>	obstacleBot;	
		std::vector<std::string>	obstacleTop;
		std::string					ground;
		std::string					ceiling;
};

#endif