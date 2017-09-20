/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Game.class.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpierron <tpierron@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/11 11:16:01 by tpierron          #+#    #+#             */
/*   Updated: 2017/09/20 15:35:39 by tpierron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./Game.class.hpp"

Game::Game(float gameSpeed) : gameSpeed(gameSpeed) {
	initAreas();
    this->obstacles = this->areas.front()->getObstacles();
    this->player = new Player(0, this->areas.front()->getLineNbr());
	this->camera = Camera();
	this->camera.setOrientation(Orientation::NORTH);
	this->movementDirection = Orientation::NORTH;
	this->gameClockRender = 0.f;
	this->areasUpdated = false;
	this->currentAreaInd = 0;
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

	// float plx = this->player->getX();
	// float ply = this->player->getY();
	// float ax = this->areas[this->currentAreaInd]->getEndX();
	// float ay = this->areas[this->currentAreaInd]->getEndY();

	// float a = 0;
	// float b = -5;

	// transcriptCrdToCameraRef(&plx, &ply, this->movementDirection);
	// transcriptCrdToCameraRef(&ax, &ay, this->movementDirection);
	// transcriptCrdToCameraRef(&a, &b, this->movementDirection);
	// std::cout << a << " : " << b << std::endl;

	// cameraX += this->areas[this->currentAreaInd]->getEndX() + a + b;
	// if (ay - ply < 15 &&
	// 	ay - ply > 0 &&
	// 	this->areas[this->currentAreaInd + 1]->getOrientation() != this->movementDirection &&
	// 	this->camera.getAnimationState() == false) {
	// 	this->camera.startRotationAnimation(15 - 2.5, this->gameSpeed, this->areas[this->currentAreaInd + 1]->getOrientation());
	// }

	switch(this->movementDirection) {
		case Orientation::NORTH:
			cameraX += this->areas[this->currentAreaInd]->getEndX() - 5;
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
			cameraX += this->areas[this->currentAreaInd]->getEndY() - 5;
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
	}

	player->draw(gameClockRender);
	player->drawDebug(gameClockRender);

}

void	Game::checkObstaclesCollision() {
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

bool	Game::checkWallCollision() {

	float plx = this->player->getX();
	float ply = this->player->getY();
	float arx = this->areas[this->currentAreaInd]->getEndX();
	float ary = this->areas[this->currentAreaInd]->getEndY();

	transcriptCrdToCameraRef(&plx, &ply, this->movementDirection);
	transcriptCrdToCameraRef(&arx, &ary, this->movementDirection);

	if (ply > ary)
		return true;
	// switch(this->movementDirection) {
	// 	case Orientation::NORTH:
	// 		if (this->player->getY() > this->areas[this->currentAreaInd]->getEndY())
	// 			return true;
	// 		break;
	// 	case Orientation::SOUTH:
	// 		if (this->player->getY() < this->areas[this->currentAreaInd]->getEndY())
	// 			return true;
	// 		break;
	// 	case Orientation::EAST:
	// 		if (this->player->getX() > this->areas[this->currentAreaInd]->getEndX())
	// 			return true;
	// 		break;
	// 	case Orientation::WEST:
	// 		if (this->player->getX() < this->areas[this->currentAreaInd]->getEndX())
	// 			return true;
	// 		break;
	// }
	return false;
}

void	Game::movePlayerRight() {
	switch (this->movementDirection) {
		case Orientation::NORTH:
			// std::cout << "NORTH" << std::endl;
			if (this->player->getX() < this->areas[currentAreaInd]->getEndX() - 1)
				this->player->move(1.0f, 0.f);
			break;
		case Orientation::SOUTH:
			// std::cout << "SOUTH" << std::endl;
			if (this->player->getX() > this->areas[currentAreaInd]->getEndX())
				this->player->move(-1.f, 0.f);
			break;
		case Orientation::EAST:
			// std::cout << "EAST" << std::endl;
			if (this->player->getY() > this->areas[currentAreaInd]->getEndY())
				this->player->move(0.f, -1.f);
			break;
		case Orientation::WEST:
			// std::cout << "WEST" << std::endl;
			if (this->player->getY() < this->areas[currentAreaInd]->getEndY() - 1)
				this->player->move(0.f, 1.f);
			break;
	}
}

void	Game::movePlayerLeft() {
	// std::cout << "x: " << this->player->getX() << " y: " << this->player->getY() << std::endl;
	switch (this->movementDirection) {
		case Orientation::NORTH:
			if (this->player->getX() > this->areas[currentAreaInd]->getEndX() - 5)
				this->player->move(-1.f, 0.f);
			break;
		case Orientation::SOUTH:
			if (this->player->getX() < this->areas[currentAreaInd]->getEndX() + 4)
				this->player->move(1.f, 0.f);
			break;
		case Orientation::EAST:
			if (this->player->getY() < this->areas[currentAreaInd]->getEndY() + 4)
				this->player->move(0.f, 1.f);
			break;
		case Orientation::WEST:
			if (this->player->getY() > this->areas[currentAreaInd]->getEndY() - 5)
				this->player->move(0.f, -1.f);
			break;
	}
}

bool	Game::playerCanTurn() {
	if (this->movementDirection == this->areas[this->currentAreaInd + 1]->getOrientation()) {
		switch(this->movementDirection) {
			case Orientation::NORTH:
				if (this->player->getY() > this->areas[this->currentAreaInd]->getEndY())
					this->currentAreaInd++; break;
			case Orientation::SOUTH:
				if (this->player->getY() < this->areas[this->currentAreaInd]->getEndY())
					this->currentAreaInd++; break;
			case Orientation::EAST:
				if (this->player->getX() > this->areas[this->currentAreaInd]->getEndX())
					this->currentAreaInd++; break;
			case Orientation::WEST:
				if (this->player->getX() < this->areas[this->currentAreaInd]->getEndX())
					this->currentAreaInd++; break;
		}
		return false;
	}
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
	// std::cout << "space PRESSED" << std::endl;
	if (!playerCanTurn())
		return;
	// std::cout << "Player can turn" << std::endl;
	// std::cout << this->player->getX() << " : " << this->player->getY() << std::endl;
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
	for (unsigned int i = 0; i < this->areas[currentAreaInd]->getObstacles().size(); i++) {
		// std::cout << this->areas[currentAreaInd]->getObstacles()[i].x << 
		// " : " <<
		// this->areas[currentAreaInd]->getObstacles()[i].y << std::endl;
		this->obstacles.push_back(this->areas[currentAreaInd]->getObstacles()[i]);
		this->obstacles.erase(this->obstacles.begin());
	}
	// std::cout << this->player->getX() << " : " << this->player->getY() << std::endl;
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
	
	this->areas.push_back(new Area(0.f, 0.f, Orientation::NORTH));

	Orientation::Enum randOrientation = getRandOrientationDifferentFrom(Orientation::SOUTH);
	addArea(randOrientation);
	addArea(getRandOrientationDifferentFrom(static_cast<Orientation::Enum>((randOrientation + 2) % 4)));
}

void	Game::manageAreas() {

	delArea();
	
	if (this->areasUpdated)
		return;
	Orientation::Enum lastOrientationInv = static_cast<Orientation::Enum>((this->areas.back()->getOrientation() + 2) % 4);
	switch (this->movementDirection) {
		case Orientation::NORTH:
			if (this->player->getY() > this->areas[0]->getEndY() - 20) {
				addArea(getRandOrientationDifferentFrom(lastOrientationInv));
				this->areasUpdated = true;
			} break;
		case Orientation::SOUTH:
			if (this->player->getY() < this->areas[0]->getEndY() + 20) {
				addArea(getRandOrientationDifferentFrom(lastOrientationInv));
				this->areasUpdated = true;
			} break;
		case Orientation::EAST:
			if (this->player->getX() > this->areas[0]->getEndX() - 20) {
				addArea(getRandOrientationDifferentFrom(lastOrientationInv));
				this->areasUpdated = true;
			} break;
		case Orientation::WEST:
			if (this->player->getX() < this->areas[0]->getEndX() + 20) {
				addArea(getRandOrientationDifferentFrom(lastOrientationInv));
				this->areasUpdated = true;
			} break;
	}
}

Orientation::Enum	Game::getRandOrientationDifferentFrom(Orientation::Enum orientation) const {
	Orientation::Enum randOrientation = orientation;
	while(randOrientation == orientation) {
		randOrientation = static_cast<Orientation::Enum>(rand() % 4);
	}
	return randOrientation;
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

	// switch(this->orientation) {
	// 	case Orientation::NORTH:
			switch(orientation) {
				case Orientation::NORTH: break;
				case Orientation::SOUTH: *x = -xx; *y = -yy;break;
				case Orientation::WEST: *x = -yy; *y = -xx;break;
				case Orientation::EAST: *x = yy; *y = xx;break;
			} 
}