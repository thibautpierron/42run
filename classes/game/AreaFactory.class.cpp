/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AreaFactory.class.cpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpierron <tpierron@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/21 09:44:59 by tpierron          #+#    #+#             */
/*   Updated: 2017/09/26 15:08:02 by tpierron         ###   ########.fr       */
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
	int nextAreaLength = rand() % 3 + 2;
	// int nextAreaLength = 1;
	int nextAreaLineNbr;
	if (nextOrientation == Orientation::NORTH || nextOrientation == Orientation::SOUTH) {
		nextAreaLength *= this->stages[this->currentStage]->getPatternLengthVertical();
		nextAreaLength += this->stages[this->currentStage]->getLineNbrHorizontal();
		nextAreaLineNbr = this->stages[this->currentStage]->getLineNbrVertical();
	}
	else {
		nextAreaLength *= this->stages[this->currentStage]->getPatternLengthHorizontal();
		nextAreaLength += this->stages[this->currentStage]->getLineNbrVertical();
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
	area->setSceneryModel(this->stages[this->currentStage]->getSceneryModel());

	return area;
}

Area *	AreaFactory::createArea() {
	int nextAreaLength = (rand() % 3 + 2) * this->stages[this->currentStage]->getPatternLengthVertical()
							+ this->stages[this->currentStage]->getLineNbrHorizontal();
	int nextAreaLineNbr = this->stages[this->currentStage]->getLineNbrVertical();

	Area *area = new Area(0, 0, nextAreaLength, nextAreaLineNbr, Orientation::NORTH);
	area->setObstacleModel(this->stages[this->currentStage]->getObstacleModel());
	area->setSceneryModel(this->stages[this->currentStage]->getSceneryModel());

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