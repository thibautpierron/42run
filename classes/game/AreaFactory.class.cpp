/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AreaFactory.class.cpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpierron <tpierron@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/21 09:44:59 by tpierron          #+#    #+#             */
/*   Updated: 2017/09/21 17:19:47 by tpierron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./AreaFactory.class.hpp"

AreaFactory::~AreaFactory() {}

AreaFactory::AreaFactory() {
	// std::cout << "AREA FACTO CONSTRUCTOR" << std::endl;
	this->stages.push_back(new Stage(0));
	this->stages.push_back(new Stage(1));
	this->currentStage = 0;
}

Area *	AreaFactory::createArea(Area * prev) {
	static int areaCounter = 0;
	if (areaCounter >= 5) {
		this->changeStage();
		areaCounter = 0;
	}
	areaCounter++;
	
	Orientation::Enum lastOrientation = prev->getOrientation();	
	Orientation::Enum nextOrientation = getNextOrientationAfter(lastOrientation);
	float prevX = prev->getEndX();
	float prevY = prev->getEndY();
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

	float areaX;
	float areaY;

	switch(lastOrientation) {
		case Orientation::NORTH:
			if (nextOrientation == Orientation::EAST)
				{areaX = prevX; areaY = prevY;}
			else
				{areaX = prevX - nextAreaLineNbr; areaY = prevY - nextAreaLineNbr;}
			break;
		case Orientation::SOUTH:
			if (nextOrientation == Orientation::EAST)
				{areaX = prevX + nextAreaLineNbr; areaY =  prevY + nextAreaLineNbr;}
			else
				{areaX = prevX; areaY = prevY;}
			break;
		case Orientation::WEST:
			if (nextOrientation == Orientation::NORTH)
				{areaX = prevX; areaY = prevY;}
			else
				{areaX = prevX + nextAreaLineNbr; areaY = prevY - prev->getLineNbr();}
			break;
		case Orientation::EAST:
			if (nextOrientation == Orientation::NORTH)
				{areaX = prevX - nextAreaLineNbr; areaY = prevY + prev->getLineNbr();}
			else
				{areaX = prevX; areaY = prevY;}
			break;
	}

	Area *area = new Area(areaX, areaY, nextAreaLength, nextAreaLineNbr, nextOrientation);
	area->setObstacleModel(this->stages[this->currentStage]->getObstacleModel());

	return area;
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