/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Game.class.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpierron <tpierron@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/11 11:16:01 by tpierron          #+#    #+#             */
/*   Updated: 2017/09/15 10:19:27 by tpierron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./Game.class.hpp"

Game::Game() {
	this->area = new Area(0.f, 0.f, Orientation::NORTH);
	this->area2 = new Area(0.f, 25.f, Orientation::WEST);
    this->obstacles = area->getObstacles();
    this->player = new Player(0, area->getLineNbr());
	this->movementDirection = Orientation::NORTH;
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

	if (gameTime == 0)
		player->goAhead();
}

void	Game::render(float gameTime) {
	float cameraX = this->area->getLineNbr() * 0.5f;

	Shader::setPerspective(cameraX, gameTime, this->movementDirection);
	
	area->drawGrid();
	area->drawObstacleDebug();

	area2->drawGrid();
	area2->drawObstacleDebug();

	player->draw(gameTime);
	player->drawDebug(gameTime);
}

bool	Game::checkCollision() {
	glm::vec2 playerPosition = this->player->getPosition();
	for (unsigned int i = 0; i < obstacles.size(); i++) {
        if (obstacles[i].x == playerPosition.x && 
            ((obstacles[i].y + 1) == playerPosition.y || (obstacles[i].y ) == playerPosition.y) ) {
            return true;
        }
    }
    return false;
}

void	Game::movePlayerRight() {
	this->player->moveRight();
}

void	Game::movePlayerLeft() {
	this->player->moveLeft();
}

void	Game::orientatePlayer() {
	this->movementDirection = Orientation::WEST;
	this->player->setOrientation(Orientation::WEST);
}
