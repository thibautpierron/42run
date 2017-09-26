/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Stage.class.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpierron <tpierron@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/21 11:33:26 by tpierron          #+#    #+#             */
/*   Updated: 2017/09/26 09:45:15 by tpierron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AreaFactory.class.hpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpierron <tpierron@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/21 09:44:39 by tpierron          #+#    #+#             */
/*   Updated: 2017/09/21 11:31:52 by tpierron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STAGE_CLASS_HPP
# define STAGE_CLASS_HPP

# include <vector>
# include "../model/Model.class.hpp"

class Stage {
	public:
		Stage(int);
		
		int getLineNbrHorizontal() const;
		int getLineNbrVertical() const;
		int getPatternLengthHorizontal() const;
		int getPatternLengthVertical() const;
		Model* getObstacleModel() const;
		Model* getSceneryModel() const;

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
};

#endif