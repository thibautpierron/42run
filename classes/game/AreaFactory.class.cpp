/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AreaFactory.class.cpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpierron <tpierron@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/21 09:44:59 by tpierron          #+#    #+#             */
/*   Updated: 2017/09/27 10:38:13 by tpierron         ###   ########.fr       */
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
		nextAreaLength *= this->stages[this->currentStage]->getPatternLength(Orientation::NORTH);
		nextAreaLength += this->stages[this->currentStage]->getLineNbr(Orientation::WEST);
		nextAreaLineNbr = this->stages[this->currentStage]->getLineNbr(Orientation::NORTH);
	}
	else {
		nextAreaLength *= this->stages[this->currentStage]->getPatternLength(Orientation::WEST);
		nextAreaLength += this->stages[this->currentStage]->getLineNbr(Orientation::NORTH);
		nextAreaLineNbr = this->stages[this->currentStage]->getLineNbr(Orientation::WEST);
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

	Area *area = new Area(areaX, areaY, nextAreaLength, this->stages[currentStage], nextOrientation);
	area->setObstacleModel(this->stages[this->currentStage]->getObstacleModel());
	area->setSceneryModel(this->stages[this->currentStage]->getSceneryModel());

	return area;
}

Area *	AreaFactory::createArea() {
	int nextAreaLength = (rand() % 3 + 2) * this->stages[this->currentStage]->getPatternLength(Orientation::NORTH)
							+ this->stages[this->currentStage]->getLineNbr(Orientation::WEST);
	// int nextAreaLineNbr = this->stages[this->currentStage]->getLineNbr(Orientation::NORTH);

	Area *area = new Area(0, 0, nextAreaLength, this->stages[currentStage], Orientation::NORTH);
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