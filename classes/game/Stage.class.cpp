/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Stage.class.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpierron <tpierron@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/21 11:33:21 by tpierron          #+#    #+#             */
/*   Updated: 2017/09/21 12:36:10 by tpierron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./Stage.class.hpp"

Stage::Stage(int n) {
	switch (n) {
		case 0: initClusterStage();
		case 1: initOutsideStage();
		default: initClusterStage();
	}
}

void	Stage::initClusterStage() {
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
	this->lineNbrHorizontal = 1;
	this->lineNbrVertical = 5;
	this->patternLengthHorizontal = 5;
	this->patternLengthVertical = 5;

	// std::vector<Model*>	scenery;
	// std::vector<Model*>	obstacleFull;	
	// std::vector<Model*>	obstacleBot;	
	// std::vector<Model*>	obstacleTop;	
}