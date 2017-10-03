/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Area.class.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpierron <tpierron@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/26 10:01:40 by thibautpier       #+#    #+#             */
/*   Updated: 2017/10/03 14:11:39 by tpierron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Area.class.hpp"

Area::Area(float startX, float startY,
            unsigned int length, Stage *stage,
			Orientation::Enum orientation)
			: startX(startX), startY(startY),
				length(length - 2), orientation(orientation) {
	this->lineNbr = stage->getLineNbr(orientation);
	this->patternLength = stage->getPatternLength(orientation);
	setupGrid();
	generateObstacles();
	setBonus();
	setupObstacleDebug();
	
	this->gridShader = new Shader("shaders/simple_grid.glvs",
									"shaders/simple_grid.glfs");
	this->obstacleDebugShader = new Shader("shaders/simple_grid.glvs",
											"shaders/geometry_shader.glgs",
											"shaders/simple_grid.glfs");
	this->obstacleShader = new Shader("shaders/static_model_instanced.glvs",
										"shaders/simple_diffuse.glfs");
}

Area::~Area() {
	delete this->gridShader;
	delete this->obstacleDebugShader;
	delete this->obstacleShader;
	delete this->obstacle;
}

void    Area::setupGrid() {

	switch (this->orientation) {
		case Orientation::NORTH:
			for(float i = 0.f; i <= this->length; i++) {
				vertices.push_back(glm::vec3(this->startX, i + this->startY, 0.f));
				vertices.push_back(glm::vec3(static_cast<float>(this->lineNbr) + startX, i + this->startY, 0.f));
			} break;
		case Orientation::SOUTH:
			for(float i = 0.f; i <= this->length; i++) {
				vertices.push_back(glm::vec3(this->startX, this->startY - i, 0.f));
				vertices.push_back(glm::vec3(this->startX - static_cast<float>(this->lineNbr), this->startY - i, 0.f));
			} break;
		case Orientation::WEST:
			for(float i = 0.f; i <= this->length; i++) {
				vertices.push_back(glm::vec3(this->startX - i, this->startY, 0.f));
				vertices.push_back(glm::vec3(this->startX - i, static_cast<float>(this->lineNbr) + this->startY, 0.f));
			} break;
		case Orientation::EAST:
			for(float i = 0.f; i <= this->length; i++) {
				vertices.push_back(glm::vec3(this->startX + i, this->startY, 0.f));
				vertices.push_back(glm::vec3(this->startX + i, this->startY - static_cast<float>(this->lineNbr), 0.f));
			} break;
	}
	
	for(unsigned int i = 0; i <= this->length * 2; i += 2) {
		indices.push_back(static_cast<int>(i));
		indices.push_back(static_cast<int>(i) + 1);
	}

	indices.push_back(0);
	indices.push_back(this->length * 2);
	indices.push_back(1);
	indices.push_back(this->length * 2 + 1);

	switch (this->orientation) {
		case Orientation::NORTH:
			for(float i = 1.f; i < this->lineNbr; i++) {
				vertices.push_back(glm::vec3(i + this->startX, this->startY, 0.f));
				vertices.push_back(glm::vec3(i + this->startX, static_cast<float>(this->length) + this->startY, 0.f));
				indices.push_back(this->vertices.size() - 2);
				indices.push_back(this->vertices.size() - 1);
			} break;
		case Orientation::SOUTH:
			for(float i = 1.f; i < this->lineNbr; i++) {
				vertices.push_back(glm::vec3(this->startX - i, this->startY, 0.f));
				vertices.push_back(glm::vec3(this->startX - i, this->startY - static_cast<float>(this->length), 0.f));
				indices.push_back(this->vertices.size() - 2);
				indices.push_back(this->vertices.size() - 1);
			} break;
		case Orientation::EAST:
			for(float i = 1.f; i < this->lineNbr; i++) {
				vertices.push_back(glm::vec3(this->startX, this->startY - i, 0.f));
				vertices.push_back(glm::vec3(static_cast<float>(this->length) + this->startX, this->startY - i, 0.f));
				indices.push_back(this->vertices.size() - 2);
				indices.push_back(this->vertices.size() - 1);
			} break;
		case Orientation::WEST:
			for(float i = 1.f; i < this->lineNbr; i++) {
				vertices.push_back(glm::vec3(this->startX, i + this->startY, 0.f));
				vertices.push_back(glm::vec3(this->startX - static_cast<float>(this->length), i + this->startY, 0.f));
				indices.push_back(this->vertices.size() - 2);
				indices.push_back(this->vertices.size() - 1);
			} break;
	}

    glGenVertexArrays(1, &this->vao);
	glGenBuffers(1, &this->vbo);
	glGenBuffers(1, &this->ebo);

	glBindVertexArray(this->vao);
	glBindBuffer(GL_ARRAY_BUFFER, this->vbo);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindVertexArray(0);
}

void	Area::setupObstacleDebug() {
	std::vector<glm::vec2>      data = this->obstacles;

	glGenVertexArrays(1, &this->obstacleDebugVao);
	glGenBuffers(1, &this->obstacleDebugVbo);

	glBindVertexArray(this->obstacleDebugVao);
	glBindBuffer(GL_ARRAY_BUFFER, this->obstacleDebugVbo);
	glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(glm::vec2), &data[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);

	glBindVertexArray(0);
}

void    Area::drawGrid() const {
	glm::mat4 model = glm::mat4();

	this->gridShader->use();
	this->gridShader->setModel(model);
	this->gridShader->setView();

    glBindVertexArray(this->vao);
	glDrawElements(GL_LINES, indices.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

void    Area::drawObstacles() const {
    this->obstacleShader->use();
    this->obstacleShader->setView();
    this->obstacle->draw(this->obstacleShader, this->obstacles.size());
}

void	Area::drawScenery() const {
    this->obstacleShader->use();
    this->obstacleShader->setView();
	if ((this->orientation == Orientation::EAST || this->orientation == Orientation::WEST)
			&& ((this->length / this->patternLength) * 2) <= 4)
		return;
	int n;
	(this->orientation == Orientation::NORTH || this->orientation == Orientation::SOUTH) ? n = 4 : n = 0;
    this->scenery->draw(this->obstacleShader, (this->length / this->patternLength) * 2 + n);
}

void	Area::drawObstacleDebug() const {
	glm::mat4 model = glm::mat4();

	this->obstacleDebugShader->use();
	this->obstacleDebugShader->setModel(model);
	this->gridShader->setView();

    glBindVertexArray(this->obstacleDebugVao);
	glDrawArrays(GL_POINTS, 0, obstacles.size());
	glBindVertexArray(0);
}

void	Area::generateObstacles() {
	switch(orientation) {
		case Orientation::NORTH:
			for (unsigned int i = 0; i < this->length; i+=4) {
				this->obstacles.push_back(glm::vec2(static_cast<float>(rand() % this->lineNbr) + this->startX, static_cast<float>(i) + this->startY));
			}
			for (unsigned int i = 0; i < this->lineNbr; i++) {
				this->obstacles.push_back(glm::vec2(this->getEndX() + i - this->lineNbr, this->getEndY()));
			} break;
		case Orientation::SOUTH:
			for (unsigned int i = 0; i < this->length; i+=4) {
				this->obstacles.push_back(glm::vec2(this->startX - static_cast<float>(rand() % this->lineNbr) - 1, this->startY - static_cast<float>(i) - 1));
			}
			for (unsigned int i = 0; i < this->lineNbr; i++) {
				this->obstacles.push_back(glm::vec2(this->getEndX() + i, this->getEndY() - 1));
			} break;
		case Orientation::WEST:
			for (unsigned int i = 0; i < this->length; i+=4) {
				this->obstacles.push_back(glm::vec2(this->startX - static_cast<float>(i) - 1, static_cast<float>(rand() % this->lineNbr) + this->startY));
			}
			for (unsigned int i = 0; i < this->lineNbr; i++) {
				this->obstacles.push_back(glm::vec2(this->getEndX() - 1, this->getEndY() - this->lineNbr + i));
			} break;
		case Orientation::EAST:
			for (unsigned int i = 0; i < this->length; i+=4) {
				this->obstacles.push_back(glm::vec2(this->startX + static_cast<float>(i),  this->startY - static_cast<float>(rand() % this->lineNbr) - 1));
			}
			for (unsigned int i = 0; i < this->lineNbr; i++) {
				this->obstacles.push_back(glm::vec2(this->getEndX(), this->getEndY() + i));
			} break;
	}	
}

unsigned int	Area::getLineNbr() const {
	return this->lineNbr;
}

unsigned int 	Area::getLength() const {
	return this->length;
}

std::vector<glm::vec2> Area::getObstacles() const {
	return this->obstacles;
}

Orientation::Enum	Area::getOrientation() const {
	return this->orientation;
}

float		Area::getEndX() const {
	switch(this->orientation) {
		case Orientation::NORTH:
			return this->startX + this->lineNbr; break;
		case Orientation::SOUTH:
			return this->startX - this->lineNbr; break;
		case Orientation::WEST:
			return this->startX - this->length; break;
		case Orientation::EAST:
			return this->startX + this->length; break;
	}
}

float		Area::getEndY() const {
	switch(this->orientation) {
		case Orientation::NORTH:
			return this->startY + this->length; break;
		case Orientation::SOUTH:
			return this->startY - this->length; break;
		case Orientation::WEST:
			return this->startY + this->lineNbr; break;
		case Orientation::EAST:
			return this->startY - this->lineNbr; break;
	}
}

void		Area::setObstacleModel(Model * model) {
	this->obstacle = model;
	std::vector<glm::mat4> data;
	for (unsigned int i = 0; i < this->obstacles.size(); i++) {
    	glm::mat4 model = glm::mat4();
    	model = glm::translate(model, glm::vec3(this->obstacles[i].x + 0.5f, this->obstacles[i].y + 0.5f, 0.f));
		model = glm::scale(model, glm::vec3(0.25f, 0.25f, 0.025f));
		float angle = 90.f;
		int n = rand() % 4;

		model = glm::rotate(model, glm::radians(angle * n), glm::vec3(0.f, 0.f, 1.f));
		data.push_back(model);
	}
	this->obstacle->setInstanceBuffer(data);
}

void		Area::setSceneryModel(Model * model) {
	this->scenery = model;
	std::vector<glm::mat4> data;
	unsigned int limit = this->length / this->patternLength;

	switch (this->orientation) {
		case Orientation::NORTH:
			// std::cout << "N" << std::endl;
			for (unsigned int i = 0; i <= limit + 1; i++) {
				glm::mat4 model = glm::mat4();
				model = glm::translate(model, glm::vec3(this->startX, this->startY + i * this->patternLength - 2, 0.f));
				model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
				model = glm::rotate(model, glm::radians(90.f), glm::vec3(1.f, 0.f, 0.f));
				model = glm::rotate(model, glm::radians(180.f), glm::vec3(0.f, 1.f, 0.f));
				data.push_back(model);

				glm::mat4 model2 = glm::mat4();
				model2 = glm::translate(model2, glm::vec3(this->startX + 3 + 8, this->startY + i * this->patternLength - 2, 0.f));
				model2 = glm::scale(model2, glm::vec3(0.5f, 0.5f, 0.5f));
				model2 = glm::rotate(model2, glm::radians(90.f), glm::vec3(1.f, 0.f, 0.f));
				model2 = glm::rotate(model2, glm::radians(180.f), glm::vec3(0.f, 1.f, 0.f));
				data.push_back(model2);
			} break;
		case Orientation::SOUTH:
			// std::cout << "S" << std::endl;
			for (unsigned int i = 0; i < limit + 2; i++) {
				glm::mat4 model = glm::mat4();
				model = glm::translate(model, glm::vec3(this->startX - 3, this->startY - i * 9 + 9, 0.f));
				model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
				model = glm::rotate(model, glm::radians(90.f), glm::vec3(1.f, 0.f, 0.f));
				model = glm::rotate(model, glm::radians(180.f), glm::vec3(0.f, 1.f, 0.f));
				data.push_back(model);

				glm::mat4 model2 = glm::mat4();
				model2 = glm::translate(model2, glm::vec3(this->startX + 8, this->startY - i * 9 + 9, 0.f));
				model2 = glm::scale(model2, glm::vec3(0.5f, 0.5f, 0.5f));
				model2 = glm::rotate(model2, glm::radians(90.f), glm::vec3(1.f, 0.f, 0.f));
				model2 = glm::rotate(model2, glm::radians(180.f), glm::vec3(0.f, 1.f, 0.f));
				data.push_back(model2);
			} break;
		case Orientation::EAST:
			// std::cout << "E" << std::endl;
			for (unsigned int i = 1; i < limit - 1; i++) {
				glm::mat4 model = glm::mat4();
				model = glm::translate(model, glm::vec3(i * 8 + this->startX + 8, this->startY - 2, 0.f));
				model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
				model = glm::rotate(model, glm::radians(90.f), glm::vec3(1.f, 0.f, 0.f));
				model = glm::rotate(model, glm::radians(180.f), glm::vec3(0.f, 1.f, 0.f));
				data.push_back(model);

				glm::mat4 model2 = glm::mat4();
				model2 = glm::translate(model2, glm::vec3(i * 8 + this->startX + 8, this->startY + 9 - 2, 0.f));
				model2 = glm::scale(model2, glm::vec3(0.5f, 0.5f, 0.5f));
				model2 = glm::rotate(model2, glm::radians(90.f), glm::vec3(1.f, 0.f, 0.f));
				model2 = glm::rotate(model2, glm::radians(180.f), glm::vec3(0.f, 1.f, 0.f));
				data.push_back(model2);
			} break;
		case Orientation::WEST:
			// std::cout << "W" << std::endl;
			for (unsigned int i = 1; i < limit - 1; i++) {
				glm::mat4 model = glm::mat4();
				model = glm::translate(model, glm::vec3((this->startX - 1) - (i * 8), this->startY, 0.f));
				model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
				model = glm::rotate(model, glm::radians(90.f), glm::vec3(1.f, 0.f, 0.f));
				model = glm::rotate(model, glm::radians(180.f), glm::vec3(0.f, 1.f, 0.f));
				data.push_back(model);

				glm::mat4 model2 = glm::mat4();
				model2 = glm::translate(model2, glm::vec3((this->startX - 1) - (i * 8), this->startY + 9, 0.f));
				model2 = glm::scale(model2, glm::vec3(0.5f, 0.5f, 0.5f));
				model2 = glm::rotate(model2, glm::radians(90.f), glm::vec3(1.f, 0.f, 0.f));
				model2 = glm::rotate(model2, glm::radians(180.f), glm::vec3(0.f, 1.f, 0.f));
				data.push_back(model2);
			} break;
	}
	this->scenery->setInstanceBuffer(data);
}

void	Area::setBonus() {
	this->bonusShader = new Shader("shaders/static_model_instanced.glvs",
										"shaders/simple_diffuse.glfs");
	this->bonus = new Model("./models/scenery/card.obj", false);

	glm::vec2 crd;
	switch(orientation) {
		case Orientation::NORTH:
				crd = glm::vec2((rand() % this->lineNbr) + this->startX, (rand() % this->length) + this->startY); break;
		case Orientation::SOUTH:
				crd = glm::vec2(this->startX - (rand() % this->lineNbr), this->startY - (rand() % this->length)); break;
		case Orientation::WEST:
				crd = glm::vec2(this->startX - (rand() % this->length), (rand() % this->lineNbr) + this->startY); break;
		case Orientation::EAST:
				crd = glm::vec2((rand() % this->length) + this->startX, this->startY - (rand() % this->lineNbr)); break;
	}	

	bool flag = true;
	while (flag) {
		flag = false;
		for (unsigned int i = 0; i < obstacles.size(); i++) {
			// std::cout << "crdx:" << obstacles[i].x << " crdy: " << obstacles[i].y << std::endl;
			if (crd.x == obstacles[i].x && crd.y == obstacles[i].y) {
				std::cout << "BAD RAND" << std::endl;
				switch(orientation) {
					case Orientation::NORTH:
							crd = glm::vec2((rand() % this->lineNbr) + this->startX, (rand() % this->length) + this->startY); break;
					case Orientation::SOUTH:
							crd = glm::vec2(this->startX - (rand() % this->lineNbr), this->startY - (rand() % this->length)); break;
					case Orientation::WEST:
							crd = glm::vec2(this->startX - (rand() % this->length), (rand() % this->lineNbr) + this->startY); break;
					case Orientation::EAST:
							crd = glm::vec2((rand() % this->length) + this->startX, this->startY - (rand() % this->lineNbr)); break;
				}	
				flag = true;
				break;
			}
		}
	}
	this->bonusCrd = crd;
}

void	Area::drawBonus() const {
	std::vector<glm::mat4> data;
	static float angle = 0.f;

	glm::mat4 model = glm::mat4();
	model = glm::translate(model, glm::vec3(this->bonusCrd.x + 0.5f, this->bonusCrd.y + 0.5f, 0.2f));
	model = glm::rotate(model, glm::radians(angle) , glm::vec3(0.f, 0.f, 1.f));
	model = glm::translate(model, glm::vec3(- 0.2f, - 0.2f, 0.f));
	data.push_back(model);
	this->bonus->setInstanceBuffer(data);
	this->bonusShader->use();
    this->bonusShader->setView();
	this->bonusShader->setModel(model);
    this->bonus->draw(this->bonusShader, 1);
	angle += 1.f;
	if (angle > 360.f)
		angle = 0.f;
}

glm::vec2	Area::getBonus() const {
	return this->bonusCrd;
}