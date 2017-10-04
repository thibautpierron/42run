/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Game.class.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpierron <tpierron@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/11 11:16:01 by tpierron          #+#    #+#             */
/*   Updated: 2017/10/04 10:26:28 by tpierron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./Game.class.hpp"

Game::Game(float gameSpeed) : gameSpeed(gameSpeed) {
	this->camera = Camera();
	this->camera.setOrientation(Orientation::NORTH);

	initAreas();
	this->ground = this->areaFactory.getGroundModel();
	this->ceiling = this->areaFactory.getCeilingModel();
	this->groundShader = new Shader("shaders/simple_grid.glvs",
										"shaders/simple_color.glfs");
	this->ceilingShader = new Shader("shaders/static_model_instanced.glvs",
										"shaders/simple_diffuse.glfs");
	this->logoShader = new Shader("shaders/static_model_instanced.glvs",
										"shaders/simple_diffuse.glfs");
	this->logo = new Model("./models/scenery/logo_42run.obj", false);

	this->areasUpdated = false;
	this->currentAreaInd = 0;
    this->obstacles = this->areas[this->currentAreaInd]->getObstacles();
    // this->obstacles = this->areas.front()->getObstacles();

    this->player = new Player(0, this->areas.front()->getLineNbr());
	this->movementDirection = Orientation::NORTH;
	this->gameClockRender = 0.f;

	this->glString = new GLString();
	this->score = 0.f;
	this->distance = 0.f;
	this->bonusFactor = 1.f;
	this->bonusCaught = false;

	this->state = 0;
}

Game::~Game() {
	delete this->player;
}

void	Game::compute(float gameTick) {
	
	if (gameTick == 0) {
		player->goAhead();
		this->distance += 1;
		this->score = distance * bonusFactor;
	}

	if (!this->bonusCaught) {
		if (checkBonusCollision())
			this->bonusCaught = true;
	}
	checkObstaclesCollision();
	if (checkWallCollision()) {
		// std::cout << "WALL" << std::endl;
		// this->currentAreaInd++;
		this->state = 2;
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

	this->drawGround();
	this->drawCeiling();

	for(unsigned int i = 0; i < this->areas.size(); i++) {
		this->areas[i]->drawGrid();
		this->areas[i]->drawObstacleDebug();
		this->areas[i]->drawObstacles();
		this->areas[i]->drawScenery();
		if (!this->bonusCaught)
			this->areas[i]->drawBonus();
	}

	player->draw(gameClockRender);
	player->drawDebug(gameClockRender);

	this->drawScore();
	this->drawBonus();
}

void	Game::checkObstaclesCollision() {
	glm::vec2 playerPosition = this->player->getPosition();
	for (unsigned int i = 0; i < obstacles.size(); i++) {
        if (obstacles[i].x == playerPosition.x && 
            ((obstacles[i].y + 1) == playerPosition.y ||
			 (obstacles[i].y ) == playerPosition.y) ) {
			player->setState(1);
			this->state = 2;
            return;
        }
    }
	player->setState(0);
    return;
}

bool	Game::checkBonusCollision() {
	glm::vec2 playerPosition = this->player->getPosition();
	glm::vec2 bonusPosition = this->areas[this->currentAreaInd]->getBonus();
	if (playerPosition == bonusPosition) {
		this->bonusFactor++;
		player->setState(1);
		return true;
	}
	player->setState(0);
	return false;
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
			if (this->player->getY() >= this->areas[this->currentAreaInd]->getEndY() - this->areas[this->currentAreaInd + 1]->getLineNbr())
				return true; break;
		case Orientation::SOUTH:
			if (this->player->getY() < this->areas[this->currentAreaInd]->getEndY() + this->areas[this->currentAreaInd + 1]->getLineNbr())
				return true; break;
		case Orientation::EAST:
			if (this->player->getX() >= this->areas[this->currentAreaInd]->getEndX() - this->areas[this->currentAreaInd + 1]->getLineNbr())
				return true; break;
		case Orientation::WEST:
			if (this->player->getX() < this->areas[this->currentAreaInd]->getEndX() + this->areas[this->currentAreaInd + 1]->getLineNbr())
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
	this->bonusCaught = false;
	this->obstacles = this->areas[currentAreaInd]->getObstacles();

}

void	Game::orientatePlayer(Orientation::Enum orientation) {
	this->movementDirection = orientation;
	this->player->setOrientation(orientation);
}

void	Game::initAreas() {	
	this->areas.erase(this->areas.begin(), this->areas.end());
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
			if (this->player->getY() > this->areas[0]->getEndY() - 5) flag = true; break;
		case Orientation::SOUTH:
			if (this->player->getY() < this->areas[0]->getEndY() + 5) flag = true; break;
		case Orientation::EAST:
			if (this->player->getX() > this->areas[0]->getEndX() - 5) flag = true; break;
		case Orientation::WEST:
			if (this->player->getX() < this->areas[0]->getEndX() + 5) flag = true; break;
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

void		Game::drawGround() const{
	glm::mat4 model = glm::mat4();
	model = glm::rotate(model, glm::radians(90.f), glm::vec3(1.f, 0.f, 0.f));

	this->groundShader->use();
    this->groundShader->setView();
	this->groundShader->setModel(model);
    this->ground->draw(this->groundShader, 1);

}

void		Game::drawCeiling() const {
	std::vector<glm::mat4> data;
	int plx = static_cast<int>(this->player->getX()) / 8;
	int ply = static_cast<int>(this->player->getY()) / 8;

	for (int j = plx - 6; j < plx + 6; j++) {
		for (int i = ply - 6; i < ply + 6; i++) {
			glm::mat4 model = glm::mat4();
			model = glm::translate(model, glm::vec3(j * 8, i * 8, 3.5f));
			model = glm::rotate(model, glm::radians(90.f), glm::vec3(1.f, 0.f, 0.f));
			model = glm::rotate(model, glm::radians(180.f), glm::vec3(1.f, 0.f, 0.f));
			data.push_back(model);
		}
	}
	this->ceiling->setInstanceBuffer(data);

	this->ceilingShader->use();
    this->ceilingShader->setView();
    this->ceiling->draw(this->ceilingShader, 144);

}

void		Game::drawScore() const {
	this->glString->renderText("Score:", 50.f, 950.f, glm::vec3(0.2f, 0.4f, 1.f));	
	this->glString->renderText(std::to_string(this->score), 50.f, 880.f, glm::vec3(0.2f, 0.4f, 1.f));	
}

void		Game::drawBonus() const {
	std::string str = std::to_string(this->bonusFactor);
	str.append("x");
	this->glString->renderText(str, 900.f, 950.f, glm::vec3(0.2f, 0.4f, 1.f));	
}

void		Game::displayStartScreen() const {
	static int t = 0;
	static float r = 0.f;
	t++;
	r++;
	if (t > 100)
		t = 0;
	if (t < 50)
		this->glString->renderText("press space to start", 70.f, 100.f, glm::vec3(1.f, 1.f, 1.f));

	if(r > 360)
		r = 0;
	std::vector<glm::mat4> data;

	glm::mat4 model = glm::mat4();
	model = glm::translate(model, glm::vec3(0.f, 5.f, 0.f));
	model = glm::rotate(model, glm::radians(90.f), glm::vec3(1.f, 0.f, 0.f));
	model = glm::rotate(model, glm::radians(r), glm::vec3(0.f, 1.f, 0.f));
	data.push_back(model);

	this->logo->setInstanceBuffer(data);

	this->logoShader->use();
    this->logoShader->setView();
    this->logo->draw(this->logoShader, 1);
}

void		Game::displayScoreScreen() const {
	static int t = 0;
	t++;
	if (t > 100)
		t = 0;
	if (t < 50)
		this->glString->renderText("you lose!", 300.f, 750.f, glm::vec3(1.f, 1.f, 1.f));	
	
	this->glString->renderText("your score is:", 200.f, 550.f, glm::vec3(1.f, 1.f, 1.f));	
	this->glString->renderText(std::to_string(this->score), 400.f, 450.f, glm::vec3(1.f, 1.f, 1.f));
}

int		Game::getState() const {
	return this->state;
}

void	Game::start() {
	this->camera = Camera();
	this->camera.setOrientation(Orientation::NORTH);

	initAreas();
	this->areasUpdated = false;
	this->currentAreaInd = 0;
    this->obstacles = this->areas[this->currentAreaInd]->getObstacles();

	delete this->player;
    this->player = new Player(0, this->areas[this->currentAreaInd]->getLineNbr());
	this->movementDirection = Orientation::NORTH;
	this->gameClockRender = 0.f;

	this->score = 0.f;
	this->distance = 0.f;
	this->bonusFactor = 1.f;
	this->bonusCaught = false;

	this->state = 1;
}