/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Stage.class.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpierron <tpierron@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/21 11:33:21 by tpierron          #+#    #+#             */
/*   Updated: 2017/09/25 11:18:51 by tpierron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./Stage.class.hpp"

Stage::Stage(int n) {
	// std::cout << "STAGE CONSTRUCTOR" << std::endl;
	switch (n) {
		case 0: initClusterStage(); break;
		case 1: initOutsideStage(); break;
		default: initClusterStage(); break;
	}
	obstacleFull.push_back(new Model("./models/obstacles/chair.dae", false));
}

void	Stage::initClusterStage() {
	this->lineNbrHorizontal = 2;
	this->lineNbrVertical = 3;
	this->patternLengthHorizontal = 5;
	this->patternLengthVertical = 5;
	
	// std::cout << "B" << std::endl;
	// std::vector<Model*>	scenery;
	// std::vector<Model*>	obstacleFull;	
	// std::vector<Model*>	obstacleBot;	
	// std::vector<Model*>	obstacleTop;	
}

void	Stage::initOutsideStage() {
	this->lineNbrHorizontal = 1;
	this->lineNbrVertical = 5;
	this->patternLengthHorizontal = 5;
	this->patternLengthVertical = 5;

	// std::vector<Model*>	scenery;
	// std::vector<Model*>	obstacleFull;	
	// std::vector<Model*>	obstacleBot;	
	// std::vector<Model*>	obstacleTop;	
}

int Stage::getLineNbrHorizontal() const {
	return this->lineNbrHorizontal;
}

int Stage::getLineNbrVertical() const {
	return this->lineNbrVertical;
}

int Stage::getPatternLengthHorizontal() const {
	return this->patternLengthHorizontal;
}

int Stage::getPatternLengthVertical() const {
	return this->patternLengthVertical;
}

Model*	Stage::getObstacleModel() const {
	return this->obstacleFull[0];
}