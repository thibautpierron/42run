/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AreaFactory.class.cpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpierron <tpierron@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/21 09:44:59 by tpierron          #+#    #+#             */
/*   Updated: 2017/09/21 13:29:30 by tpierron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./AreaFactory.class.hpp"

AreaFactory::~AreaFactory() {}

AreaFactory::AreaFactory() {
	this->stages.push_back(Stage(0));
	this->stages.push_back(Stage(1));
	this->currentStage = 0;
}

Area *	AreaFactory::createArea(Area * prev) const {
	Orientation::Enum lastOrientation = prev->getOrientation();	
	Orientation::Enum nextOrientation = getNextOrientationAfter(lastOrientation);
	float x = prev->getEndX();
	float y = prev->getEndY();
	int nextAreaLength = rand() % 10 + 3;
	if (nextOrientation == Orientation::NORTH || nextOrientation == Orientation::SOUTH)
		nextAreaLength *= this->stages[this->currentStage].getPatternLengthVertical();
	else
		nextAreaLength *= this->stages[this->currentStage].getPatternLengthHorizontal();

	switch(lastOrientation) {
		case Orientation::NORTH:
			if (nextOrientation == Orientation::EAST)
				return new Area(x, y, nextAreaLength, 5, nextOrientation);
			else if (nextOrientation == Orientation::WEST)
				return new Area(x - 5, y - 5, nextAreaLength, 5, nextOrientation);
			else
				return new Area(x - 5, y, nextAreaLength, 5, nextOrientation);
			break;
		case Orientation::SOUTH:
			if (nextOrientation == Orientation::EAST)
				return new Area(x + 5, y + 5, nextAreaLength, 5, nextOrientation);
			else if (nextOrientation == Orientation::WEST)
				return new Area(x, y, nextAreaLength, 5, nextOrientation);
			else
				return new Area(x + 5, y, nextAreaLength, 5, nextOrientation);
			break;
		case Orientation::WEST:
			if (nextOrientation == Orientation::NORTH)
				return new Area(x, y, nextAreaLength, 5, nextOrientation);
			else if (nextOrientation == Orientation::SOUTH)
				return new Area(x + 5, y - 5, nextAreaLength, 5, nextOrientation);
			else
				return new Area(x, y - 5, nextAreaLength, 5, nextOrientation);
			break;
		case Orientation::EAST:
			if (nextOrientation == Orientation::NORTH)
				return new Area(x - 5, y + 5, nextAreaLength, 5, nextOrientation);
			else if (nextOrientation == Orientation::SOUTH)
				return new Area(x, y, nextAreaLength, 5, nextOrientation);
			else
				return new Area(x, y + 5, nextAreaLength, 5, nextOrientation);
			break;
	}
}

void	AreaFactory::changeStage() {
	this->currentStage == 0 ? this->currentStage = 1 : this->currentStage = 1;
}

Orientation::Enum	AreaFactory::getNextOrientationAfter(Orientation::Enum orientation) const {
	Orientation::Enum nextOrientation = orientation;
	while(nextOrientation == orientation || nextOrientation == (orientation + 2) % 4) {
		nextOrientation = static_cast<Orientation::Enum>(rand() % 4);
	}
	return nextOrientation;
}