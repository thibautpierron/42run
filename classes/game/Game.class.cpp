/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Game.class.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpierron <tpierron@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/11 11:16:01 by tpierron          #+#    #+#             */
/*   Updated: 2017/09/15 15:52:54 by tpierron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./Game.class.hpp"

Game::Game() {

	initAreas();
    this->obstacles = this->areas.front()->getObstacles();
    this->player = new Player(0, this->areas.front()->getLineNbr());
	this->movementDirection = Orientation::NORTH;
	this->gameClockRender = 0.f;
}

Game::~Game() {
	delete this->player;
	// delete this->area;
	// delete this->area2;
}

void	Game::compute(float gameTick) {
	if (gameTick == 0)
		player->goAhead();

	checkCollision();
}

void	Game::render(float gameSpeed) {

	if(this->movementDirection == Orientation::NORTH || this->movementDirection == Orientation::EAST)
		gameClockRender += gameSpeed;
	else
		gameClockRender -= gameSpeed;
	float cameraX = this->areas.front()->getLineNbr() * 0.5f;

	Shader::setCamera(cameraX, gameClockRender, this->movementDirection);
	
	for(unsigned int i = 0; i < this->areas.size(); i++) {
		this->areas[i]->drawGrid();
		this->areas[i]->drawObstacleDebug();
	}

	player->draw(gameClockRender);
	player->drawDebug(gameClockRender);

}

void	Game::checkCollision() {
	glm::vec2 playerPosition = this->player->getPosition();
	for (unsigned int i = 0; i < obstacles.size(); i++) {
        if (obstacles[i].x == playerPosition.x && 
            ((obstacles[i].y + 1) == playerPosition.y || (obstacles[i].y ) == playerPosition.y) ) {
			player->setState(1);
            return;
        }
    }
	player->setState(0);
    return;
}

void	Game::movePlayerRight() {
	this->player->moveRight();
}

void	Game::movePlayerLeft() {
	this->player->moveLeft();
}

void	Game::orientatePlayer() {
	
	Orientation::Enum nextOrientation = this->areas[1]->getOrientation();
	
	this->movementDirection = nextOrientation;
	this->player->setOrientation(nextOrientation);
}

void	Game::orientatePlayer(Orientation::Enum orientation) {
	this->movementDirection = orientation;
	this->player->setOrientation(orientation);
}

void	Game::addArea(Orientation::Enum nextOrientation) {
	Orientation::Enum lastOrientation = this->areas.back()->getOrientation();	
	float x = this->areas.back()->getEndX();
	float y = this->areas.back()->getEndY();


	switch(lastOrientation) {
		case Orientation::NORTH:
			if (nextOrientation == Orientation::EAST)
				this->areas.push_back(new Area(x, y, nextOrientation));
			else if (nextOrientation == Orientation::WEST)
				this->areas.push_back(new Area(x - 5, y - 5, nextOrientation));
			else
				this->areas.push_back(new Area(x - 5, y, nextOrientation));
			break;
		case Orientation::SOUTH:
			if (nextOrientation == Orientation::EAST)
				this->areas.push_back(new Area(x + 5, y + 5, nextOrientation));
			else if (nextOrientation == Orientation::WEST)
				this->areas.push_back(new Area(x, y, nextOrientation));
			else
				this->areas.push_back(new Area(x + 5, y, nextOrientation));
			break;
		case Orientation::WEST:
			if (nextOrientation == Orientation::NORTH)
				this->areas.push_back(new Area(x, y, nextOrientation));
			else if (nextOrientation == Orientation::SOUTH)
				this->areas.push_back(new Area(x + 5, y - 5, nextOrientation));
			else
				this->areas.push_back(new Area(x, y - 5, nextOrientation));
			break;
		case Orientation::EAST:
			if (nextOrientation == Orientation::NORTH)
				this->areas.push_back(new Area(x - 5, y + 5, nextOrientation));
			else if (nextOrientation == Orientation::SOUTH)
				this->areas.push_back(new Area(x, y, nextOrientation));
			else
				this->areas.push_back(new Area(x, y + 5, nextOrientation));
			break;
	}
}

void	Game::initAreas() {
	Orientation::Enum randOrientation = Orientation::SOUTH;
	Orientation::Enum randOrientation2;
	
	this->areas.push_back(new Area(0.f, 0.f, Orientation::NORTH));
	while(randOrientation == Orientation::SOUTH) {
		randOrientation = static_cast<Orientation::Enum>(rand() % 4);
		std::cout << "First: " << randOrientation << std::endl;
	}
	addArea(randOrientation);

	randOrientation2 = static_cast<Orientation::Enum>((randOrientation + 2) % 4);
	while(randOrientation2 == ((randOrientation + 2) % 4)) {
		randOrientation2 = static_cast<Orientation::Enum>(rand() % 4);
		std::cout << "Seconde: " << randOrientation2 << std::endl;
	}
	addArea(randOrientation2);
}

void	Game::manageAreas() {

}