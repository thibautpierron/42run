/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Game.class.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpierron <tpierron@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/11 11:16:01 by tpierron          #+#    #+#             */
/*   Updated: 2017/09/13 15:50:08 by tpierron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./Game.class.hpp"

Game::Game() {
	this->area = new Area(0.f, 0.f, NORTH);
	this->area2 = new Area(0.f, 25.f, WEST);
	// this->area2->orientate(this->area, static_cast<eOrientation>((rand() % 2) + 2));
    this->obstacles = area->getObstacles();
    this->player = new Player(0, area->getLineNbr());
	this->movementDirection = NORTH;
}

Game::~Game() {
	delete this->player;
	delete this->area;
	delete this->area2;
}

void	Game::compute(float gameTime) {
	if (checkCollision())
		player->setState(1);
	else
		player->setState(0);
	
	player->goAhead(gameTime);
}

void	Game::render(float gameTime) {
	float cameraX = this->area->getLineNbr() * 0.5f;
	area->drawGrid(cameraX, gameTime);
	area->drawObstacleDebug(cameraX, gameTime);

	area2->drawGrid(cameraX, gameTime);
	area2->drawObstacleDebug(cameraX, gameTime);

	player->draw(cameraX, gameTime);
	player->drawDebug(cameraX, gameTime);
}

bool	Game::checkCollision() {
	glm::vec2 playerPosition = this->player->getPosition();
	for (unsigned int i = 0; i < obstacles.size(); i++) {
        if (obstacles[i].x == playerPosition.x && 
            ((obstacles[i].y - 1) == playerPosition.y || (obstacles[i].y ) == playerPosition.y) ) {
            return true;
        }
    }
    return false;
}

Player	*Game::getPlayer() {
	return this->player;
}