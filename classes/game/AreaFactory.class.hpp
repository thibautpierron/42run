/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AreaFactory.class.hpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpierron <tpierron@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/21 09:44:39 by tpierron          #+#    #+#             */
/*   Updated: 2017/09/28 13:30:03 by tpierron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AREAFACTORY_CLASS_HPP
# define AREAFACTORY_CLASS_HPP

# include "./Area.class.hpp"
# include "./Stage.class.hpp"
# include "../../constants/constants.hpp"

class AreaFactory {
	public:
		AreaFactory();
		~AreaFactory();

		Area * 	createArea(Area *);
		Area * 	createArea();
		void	changeStage();
		Model *	getGroundModel() const;
		Model *	getCeilingModel() const;

	private:
		Orientation::Enum	getNextOrientationAfter(Orientation::Enum) const;

		std::vector<Stage*>	stages;
		unsigned int		currentStage;
};

#endif