/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Game.class.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpierron <tpierron@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/11 11:16:01 by tpierron          #+#    #+#             */
/*   Updated: 2017/09/26 10:02:13 by tpierron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./Game.class.hpp"

Game::Game(float gameSpeed) : gameSpeed(gameSpeed) {
	this->camera = Camera();
	this->camera.setOrientation(Orientation::NORTH);

	initAreas();
	this->areasUpdated = false;
	this->currentAreaInd = 0;
    this->obstacles = this->areas.front()->getObstacles();

    this->player = new Player(0, this->areas.front()->getLineNbr());
	this->movementDirection = Orientation::NORTH;
	this->gameClockRender = 0.f;
}

Game::~Game() {
	delete this->player;
}

void	Game::compute(float gameTick) {
	
	if (gameTick == 0)
		player->goAhead();

	checkObstaclesCollision();
	if (checkWallCollision()) {
		std::cout << "WALL" << std::endl;
		this->currentAreaInd++;
	}
	manageAreas();
}

void	Game::setCamera() {
	float cameraX = this->areas[this->currentAreaInd]->getLineNbr() * 0.5f;

	switch(this->movementDirection) {
		case Orientation::NORTH:
			cameraX += this->areas[this->currentAreaInd]->getEndX() - this->areas[this->currentAreaInd]->getLineNbr();
			if (this->areas[this->currentAreaInd]->getEndY() - this->player->getY() < 15 &&
				this->areas[this->currentAreaInd]->getEndY() - this->player->getY() > 0 &&
				this->areas[this->currentAreaInd + 1]->getOrientation() != Orientation::NORTH &&
				this->camera.getAnimationState() == false) {
				this->camera.startRotationAnimation(15 - 2.5, this->gameSpeed, this->areas[this->currentAreaInd + 1]->getOrientation());
			}
			break;
		case Orientation::SOUTH:
			cameraX += this->areas[this->currentAreaInd]->getEndX();
			if (this->player->getY() - this->areas[this->currentAreaInd]->getEndY() < 15 &&
				this->player->getY() - this->areas[this->currentAreaInd]->getEndY() > 0 && 
				this->areas[this->currentAreaInd + 1]->getOrientation() != Orientation::SOUTH &&
				this->camera.getAnimationState() == false) {
				this->camera.startRotationAnimation(15 - 2.5, this->gameSpeed, this->areas[this->currentAreaInd + 1]->getOrientation());
			}
			break;
		case Orientation::EAST:
			cameraX += this->areas[this->currentAreaInd]->getEndY();
			if (this->areas[this->currentAreaInd]->getEndX() - this->player->getX() < 15 &&
				this->areas[this->currentAreaInd]->getEndX() - this->player->getX() > 0 &&
				this->areas[this->currentAreaInd + 1]->getOrientation() != Orientation::EAST &&
				this->camera.getAnimationState() == false) {
				this->camera.startRotationAnimation(15 - 2.5, this->gameSpeed, this->areas[this->currentAreaInd + 1]->getOrientation());
			}
			break;
		case Orientation::WEST:
			cameraX += this->areas[this->currentAreaInd]->getEndY() - this->areas[this->currentAreaInd]->getLineNbr();
			if (this->player->getX() - this->areas[this->currentAreaInd]->getEndX() < 15 &&
				this->player->getX() - this->areas[this->currentAreaInd]->getEndX() > 0 &&
				this->areas[this->currentAreaInd + 1]->getOrientation() != Orientation::WEST &&
				this->camera.getAnimationState() == false) {
				this->camera.startRotationAnimation(15 - 2.5, this->gameSpeed, this->areas[this->currentAreaInd + 1]->getOrientation());
			}
			break;
	}

	this->camera.setCamera(cameraX, this->gameClockRender);
	Shader::setCamera(this->camera.getMatrix());
}

void	Game::render(float gameSpeed) {

	if(this->movementDirection == Orientation::NORTH || this->movementDirection == Orientation::EAST)
		this->gameClockRender += gameSpeed;
	else
		this->gameClockRender -= gameSpeed;

	this->setCamera();

	for(unsigned int i = 0; i < this->areas.size(); i++) {
		this->areas[i]->drawGrid();
		this->areas[i]->drawObstacleDebug();
		this->areas[i]->drawObstacles();
		this->areas[i]->drawScenery();
	}

	player->draw(gameClockRender);
	player->drawDebug(gameClockRender);

}

void	Game::checkObstaclesCollision() {
	glm::vec2 playerPosition = this->player->getPosition();
	for (unsigned int i = 0; i < obstacles.size(); i++) {
        if (obstacles[i].x == playerPosition.x && 
            ((obstacles[i].y + 1) == playerPosition.y ||
			 (obstacles[i].y ) == playerPosition.y) ) {
			player->setState(1);
            return;
        }
    }
	player->setState(0);
    return;
}

bool	Game::checkWallCollision() {

	float plx = this->player->getX();
	float ply = this->player->getY();
	float arx = this->areas[this->currentAreaInd]->getEndX();
	float ary = this->areas[this->currentAreaInd]->getEndY();

	transcriptCrdToCameraRef(&plx, &ply, this->movementDirection);
	transcriptCrdToCameraRef(&arx, &ary, this->movementDirection);

	if (ply > ary)
		return true;
	return false;
}

void	Game::movePlayerRight() {
	switch (this->movementDirection) {
		case Orientation::NORTH:
			if (this->player->getX() < this->areas[currentAreaInd]->getEndX() - 1)
				this->player->move(1.0f, 0.f);
			break;
		case Orientation::SOUTH:
			if (this->player->getX() > this->areas[currentAreaInd]->getEndX())
				this->player->move(-1.f, 0.f);
			break;
		case Orientation::EAST:
			if (this->player->getY() > this->areas[currentAreaInd]->getEndY())
				this->player->move(0.f, -1.f);
			break;
		case Orientation::WEST:
			if (this->player->getY() < this->areas[currentAreaInd]->getEndY() - 1)
				this->player->move(0.f, 1.f);
			break;
	}
}

void	Game::movePlayerLeft() {
	switch (this->movementDirection) {
		case Orientation::NORTH:
			if (this->player->getX() > this->areas[currentAreaInd]->getEndX() - this->areas[currentAreaInd]->getLineNbr())
				this->player->move(-1.f, 0.f);
			break;
		case Orientation::SOUTH:
			if (this->player->getX() < this->areas[currentAreaInd]->getEndX() + this->areas[currentAreaInd]->getLineNbr() - 1)
				this->player->move(1.f, 0.f);
			break;
		case Orientation::EAST:
			if (this->player->getY() < this->areas[currentAreaInd]->getEndY() + this->areas[currentAreaInd]->getLineNbr() - 1)
				this->player->move(0.f, 1.f);
			break;
		case Orientation::WEST:
			if (this->player->getY() > this->areas[currentAreaInd]->getEndY() - this->areas[currentAreaInd]->getLineNbr())
				this->player->move(0.f, -1.f);
			break;
	}
}

bool	Game::playerCanTurn() {
	// if (this->movementDirection == this->areas[this->currentAreaInd + 1]->getOrientation()) {
	// 	switch(this->movementDirection) {
	// 		case Orientation::NORTH:
	// 			if (this->player->getY() > this->areas[this->currentAreaInd]->getEndY())
	// 				this->currentAreaInd++; break;
	// 		case Orientation::SOUTH:
	// 			if (this->player->getY() < this->areas[this->currentAreaInd]->getEndY())
	// 				this->currentAreaInd++; break;
	// 		case Orientation::EAST:
	// 			if (this->player->getX() > this->areas[this->currentAreaInd]->getEndX())
	// 				this->currentAreaInd++; break;
	// 		case Orientation::WEST:
	// 			if (this->player->getX() < this->areas[this->currentAreaInd]->getEndX())
	// 				this->currentAreaInd++; break;
	// 	}
	// 	return false;
	// }
	switch (this->movementDirection) {
		case Orientation::NORTH:
			if (this->player->getY() >= this->areas[this->currentAreaInd]->getEndY() - 5)
				return true; break;
		case Orientation::SOUTH:
			if (this->player->getY() < this->areas[this->currentAreaInd]->getEndY() + 5)
				return true; break;
		case Orientation::EAST:
			if (this->player->getX() >= this->areas[this->currentAreaInd]->getEndX() - 5)
				return true; break;
		case Orientation::WEST:
			if (this->player->getX() < this->areas[this->currentAreaInd]->getEndX() + 5)
				return true; break;
	}
	return false;
}

void	Game::orientatePlayer() {
	if (!playerCanTurn())
		return;
	Orientation::Enum nextOrientation = this->areas[this->currentAreaInd + 1]->getOrientation();

	if (this->movementDirection == Orientation::NORTH || this->movementDirection == Orientation::SOUTH)
		this->gameClockRender = static_cast<float>(this->player->getX());
	else
		this->gameClockRender = static_cast<float>(this->player->getY());

	this->movementDirection = nextOrientation;
	this->player->setOrientation(nextOrientation);
	this->camera.setOrientation(nextOrientation);
	this->currentAreaInd++;
	this->areasUpdated = false;
	this->camera.startGetCloserAnimation();
	// for (unsigned int i = 0; i < this->areas[currentAreaInd]->getObstacles().size(); i++) {
	// 	this->obstacles.push_back(this->areas[currentAreaInd]->getObstacles()[i]);
	// 	this->obstacles.erase(this->obstacles.begin());
	// }
}

void	Game::orientatePlayer(Orientation::Enum orientation) {
	this->movementDirection = orientation;
	this->player->setOrientation(orientation);
}

void	Game::initAreas() {
	
	this->areas.push_back(this->areaFactory.createArea());
	this->areas.push_back(this->areaFactory.createArea(this->areas.back()));
	this->areas.push_back(this->areaFactory.createArea(this->areas.back()));
}

void	Game::manageAreas() {

	delArea();
	
	if (this->areasUpdated)
		return;
		
	bool flag = false;
	switch (this->movementDirection) {
		case Orientation::NORTH:
			if (this->player->getY() > this->areas[0]->getEndY() - 20) flag = true; break;
		case Orientation::SOUTH:
			if (this->player->getY() < this->areas[0]->getEndY() + 20) flag = true; break;
		case Orientation::EAST:
			if (this->player->getX() > this->areas[0]->getEndX() - 20) flag = true; break;
		case Orientation::WEST:
			if (this->player->getX() < this->areas[0]->getEndX() + 20) flag = true; break;
	}
	
	if (flag) {
		this->areas.push_back(this->areaFactory.createArea(this->areas.back()));
		this->areasUpdated = true;
	}
}

void	Game::delArea() {
	if (this->areas.size() <= 5)
		return;

	this->currentAreaInd--;
	this->areas.pop_front();
}

void		Game::transcriptCrdToCameraRef(float *x, float *y, Orientation::Enum orientation) {

	float xx = *x;
	float yy = *y;

	switch(orientation) {
		case Orientation::NORTH: break;
		case Orientation::SOUTH: *x = -xx; *y = -yy;break;
		case Orientation::WEST: *x = -yy; *y = -xx;break;
		case Orientation::EAST: *x = yy; *y = xx;break;
	} 
}