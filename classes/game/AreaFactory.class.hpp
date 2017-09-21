/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AreaFactory.class.hpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpierron <tpierron@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/21 09:44:39 by tpierron          #+#    #+#             */
/*   Updated: 2017/09/21 14:19:52 by tpierron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AREAFACTORY_CLASS_HPP
# define AREAFACTORY_CLASS_HPP

# include "./Area.class.hpp"
# include "./Stage.class.hpp"
# include "../../constants/constants.hpp"

// struct stage {
// 	const int lineNbrHorizontal;
// 	const int lineNbrVertical;
// 	const int patternLengthHorizontal;	
// 	const int patternLengthVertical;
// 	Model	*scenery;
// 	std::vector<Model*>	obstacleFull;	
// 	std::vector<Model*>	obstacleBot;	
// 	std::vector<Model*>	obstacleTop;	
// };

class AreaFactory {
	public:
		AreaFactory();
		~AreaFactory();

		Area * 	createArea(Area *) const;
		void	changeStage();

	private:
		Orientation::Enum	getNextOrientationAfter(Orientation::Enum) const;

		std::vector<Stage*>	stages;
		unsigned int		currentStage;
};

#endif