/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Stage.class.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpierron <tpierron@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/21 11:33:21 by tpierron          #+#    #+#             */
/*   Updated: 2017/09/27 09:26:45 by tpierron         ###   ########.fr       */
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
}

void	Stage::initClusterStage() {
	this->lineNbrHorizontal = 2;
	this->lineNbrVertical = 3;
	this->patternLengthHorizontal = 8;
	this->patternLengthVertical = 9;
	
	obstacleFull.push_back("./models/obstacles/chair.dae");
	scenery.push_back("./models/scenery/cluster.obj");
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
	return new Model(this->obstacleFull[0], false);
}

Model*	Stage::getSceneryModel() const {
	return new Model(this->scenery[0], false);
}