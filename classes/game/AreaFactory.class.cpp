/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AreaFactory.class.cpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpierron <tpierron@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/21 09:44:59 by tpierron          #+#    #+#             */
/*   Updated: 2017/09/21 14:22:04 by tpierron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./AreaFactory.class.hpp"

AreaFactory::~AreaFactory() {}

AreaFactory::AreaFactory() {
	// std::cout << "AREA FACTO CONSTRUCTOR" << std::endl;
	this->stages.push_back(new Stage(0));
	this->stages.push_back(new Stage(1));
	this->currentStage = 1;
}

Area *	AreaFactory::createArea(Area * prev) const {
	Orientation::Enum lastOrientation = prev->getOrientation();	
	Orientation::Enum nextOrientation = getNextOrientationAfter(lastOrientation);
	float x = prev->getEndX();
	float y = prev->getEndY();
	int nextAreaLength = rand() % 10 + 3;
	int nextAreaLineNbr;
	if (nextOrientation == Orientation::NORTH || nextOrientation == Orientation::SOUTH) {
		nextAreaLength *= this->stages[this->currentStage]->getPatternLengthVertical();
		nextAreaLineNbr = this->stages[this->currentStage]->getLineNbrVertical();
	}
	else {
		nextAreaLength *= this->stages[this->currentStage]->getPatternLengthHorizontal();
		nextAreaLineNbr = this->stages[this->currentStage]->getLineNbrHorizontal();
	}

	switch(lastOrientation) {
		case Orientation::NORTH:
			if (nextOrientation == Orientation::EAST)
				return new Area(x, y, nextAreaLength, nextAreaLineNbr, nextOrientation);
			else if (nextOrientation == Orientation::WEST)
				return new Area(x - nextAreaLineNbr, y - nextAreaLineNbr, nextAreaLength, nextAreaLineNbr, nextOrientation);
			else
				return new Area(x - nextAreaLineNbr, y, nextAreaLength, nextAreaLineNbr, nextOrientation);
			break;
		case Orientation::SOUTH:
			if (nextOrientation == Orientation::EAST)
				return new Area(x + nextAreaLineNbr, y + nextAreaLineNbr, nextAreaLength, nextAreaLineNbr, nextOrientation);
			else if (nextOrientation == Orientation::WEST)
				return new Area(x, y, nextAreaLength, nextAreaLineNbr, nextOrientation);
			else
				return new Area(x + nextAreaLineNbr, y, nextAreaLength, nextAreaLineNbr, nextOrientation);
			break;
		case Orientation::WEST:
			if (nextOrientation == Orientation::NORTH)
				return new Area(x, y, nextAreaLength, nextAreaLineNbr, nextOrientation);
			else if (nextOrientation == Orientation::SOUTH)
				return new Area(x + nextAreaLineNbr, y - nextAreaLineNbr, nextAreaLength, nextAreaLineNbr, nextOrientation);
			else
				return new Area(x, y - nextAreaLineNbr, nextAreaLength, nextAreaLineNbr, nextOrientation);
			break;
		case Orientation::EAST:
			if (nextOrientation == Orientation::NORTH)
				return new Area(x - nextAreaLineNbr, y + nextAreaLineNbr, nextAreaLength, nextAreaLineNbr, nextOrientation);
			else if (nextOrientation == Orientation::SOUTH)
				return new Area(x, y, nextAreaLength, nextAreaLineNbr, nextOrientation);
			else
				return new Area(x, y + nextAreaLineNbr, nextAreaLength, nextAreaLineNbr, nextOrientation);
			break;
	}
}

void	AreaFactory::changeStage() {
	this->currentStage == 0 ? this->currentStage = 1 : this->currentStage = 0;
}

Orientation::Enum	AreaFactory::getNextOrientationAfter(Orientation::Enum orientation) const {
	Orientation::Enum nextOrientation = orientation;
	while(nextOrientation == orientation || nextOrientation == (orientation + 2) % 4) {
		nextOrientation = static_cast<Orientation::Enum>(rand() % 4);
	}
	return nextOrientation;
}