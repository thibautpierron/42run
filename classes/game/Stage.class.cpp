/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Stage.class.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpierron <tpierron@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/21 11:33:21 by tpierron          #+#    #+#             */
/*   Updated: 2017/09/21 14:17:44 by tpierron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./Stage.class.hpp"

Stage::Stage(int n) {
	std::cout << "STAGE CONSTRUCTOR" << std::endl;
	switch (n) {
		case 0: initClusterStage();
		case 1: initOutsideStage();
		default: initClusterStage();
	}
}

void	Stage::initClusterStage() {
	std::cout << "cluster" << std::endl;
	this->lineNbrHorizontal = 2;
	this->lineNbrVertical = 3;
	this->patternLengthHorizontal = 5;
	this->patternLengthVertical = 5;
	
	// std::vector<Model*>	scenery;
	// std::vector<Model*>	obstacleFull;	
	// std::vector<Model*>	obstacleBot;	
	// std::vector<Model*>	obstacleTop;	
}

void	Stage::initOutsideStage() {
	std::cout << "out" << std::endl;
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