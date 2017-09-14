/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Area.class.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpierron <tpierron@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/26 10:01:40 by thibautpier       #+#    #+#             */
/*   Updated: 2017/09/14 12:06:07 by tpierron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Area.class.hpp"

Area::Area(float x, float y, eOrientation orientation) : startX(x), startY(y), orientation(orientation) {
	this->length = 30;
	this->lineNbr = 5;
	setupGrid();
	generateObstacles();
	setupObstacleDebug();
	this->gridShader = new Shader("shaders/simple_grid.glvs", "shaders/simple_grid.glfs");
	this->obstacleDebugShader = new Shader("shaders/simple_grid.glvs", "shaders/geometry_shader.glgs", "shaders/simple_grid.glfs");
}

Area::~Area() {
	delete this->gridShader;
	// std::cout << "Area destroyed" << std::endl;
}

void    Area::setupGrid() {

	switch (this->orientation) {
		case NORTH:
			for(float i = 0.f; i <= this->length; i++) {
				vertices.push_back(glm::vec3(this->startX, i + this->startY, 0.f));
				vertices.push_back(glm::vec3(static_cast<float>(this->lineNbr) + startX, i + this->startY, 0.f));
			} break;

		case SOUTH:
			for(float i = 0.f; i <= this->length; i++) {
				vertices.push_back(glm::vec3(this->startX, i - this->startY, 0.f));
				vertices.push_back(glm::vec3(static_cast<float>(this->lineNbr) - startX, i - this->startY, 0.f));
			} break;
		case WEST:
			for(float i = this->length * -1.f; i <= 0.f; i++) {
				// std::cout << i + this->startX << " : " << this->startY << std::endl;
				vertices.push_back(glm::vec3(i - this->startX, this->startY, 0.f));
				vertices.push_back(glm::vec3(i - this->startX, static_cast<float>(this->lineNbr) + this->startY, 0.f));
			} break;
		case EAST:
			for(float i = 0.f; i <= this->length; i++) {
				// std::cout << i - this->startX << " : " << this->startY << std::endl;
				vertices.push_back(glm::vec3(i - this->startX, this->startY, 0.f));
				vertices.push_back(glm::vec3(i - this->startX, static_cast<float>(this->lineNbr) + this->startY, 0.f));
			} break;
	}

	// for(float i = 0.f; i <= this->length; i++) {
	// 	vertices.push_back(glm::vec3(0.f + this->startX, i + startY, 0.f));
	// 	vertices.push_back(glm::vec3(static_cast<float>(this->lineNbr) + startX, i + this->startY, 0.f));
	// }
	
	for(unsigned int i = 0; i <= this->length * 2; i += 2) {
		indices.push_back(static_cast<int>(i));
		indices.push_back(static_cast<int>(i) + 1);
	}

	indices.push_back(0);
	indices.push_back(this->length * 2);
	indices.push_back(1);
	indices.push_back(this->length * 2 + 1);

	switch (this->orientation) {
		case NORTH:
			for(float i = 1.f; i < this->lineNbr; i++) {
				vertices.push_back(glm::vec3(i + this->startX, this->startY, 0.f));
				vertices.push_back(glm::vec3(i + this->startX, static_cast<float>(this->length) + this->startY, 0.f));
				indices.push_back(this->vertices.size() - 2);
				indices.push_back(this->vertices.size() - 1);
			} break;
		case SOUTH:
			for(float i = 1.f; i < this->lineNbr; i++) {
				vertices.push_back(glm::vec3(i - this->startX, this->startY, 0.f));
				vertices.push_back(glm::vec3(i - this->startX, static_cast<float>(this->length) - this->startY, 0.f));
				indices.push_back(this->vertices.size() - 2);
				indices.push_back(this->vertices.size() - 1);
			} break;
		case EAST:
			for(float i = 1.f; i < this->lineNbr; i++) {
				vertices.push_back(glm::vec3(this->startX, i + this->startY, 0.f));
				vertices.push_back(glm::vec3(static_cast<float>(this->length) + this->startX, i + this->startY, 0.f));
				indices.push_back(this->vertices.size() - 2);
				indices.push_back(this->vertices.size() - 1);
			} break;
		case WEST:
			for(float i = 1.f; i < this->lineNbr; i++) {
				vertices.push_back(glm::vec3(this->startX, i + this->startY, 0.f));
				vertices.push_back(glm::vec3(this->startX - static_cast<float>(this->length), i + this->startY, 0.f));
				indices.push_back(this->vertices.size() - 2);
				indices.push_back(this->vertices.size() - 1);
			} break;
	}

	// for(float i = 1.f; i < this->lineNbr; i++) {
	// 	vertices.push_back(glm::vec3(i + startX, 0.f + startY, 0.f));
	// 	vertices.push_back(glm::vec3(i + startX, static_cast<float>(this->length) + startY, 0.f));
	// 	indices.push_back(this->vertices.size() - 2);
	// 	indices.push_back(this->vertices.size() - 1);
	// }

	// for (unsigned int i = 0; i < vertices.size(); i++) {
	// 	vertices[i].x -= (this->lineNbr / 2) + 0.5f;
	// }

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

	// for (unsigned int i = 0; i < data.size(); i++) {
	// 	data[i].x -= (this->lineNbr / 2) + 0.5f;
	// }

	glGenVertexArrays(1, &this->obstacleDebugVao);
	glGenBuffers(1, &this->obstacleDebugVbo);

	glBindVertexArray(this->obstacleDebugVao);
	glBindBuffer(GL_ARRAY_BUFFER, this->obstacleDebugVbo);
	glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(glm::vec2), &data[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);

	glBindVertexArray(0);
}

void    Area::drawGrid(float playerX, float playerY) {
	gridShader->use();

	glm::mat4 model = glm::mat4();
	//////
	// model = glm::rotate(model,-90.f, glm::vec3(1.f, 0.f, 0.f));
	// model = glm::translate(model, glm::vec3(this->xOffset, -progress + this->yOffset, 0.f));
	// model = glm::rotate(model,glm::radians(this->orientationOffset), glm::vec3(0.f, 0.f, 1.f));
	////
	this->gridShader->setModel(model);
	this->gridShader->setPerspective(playerX, playerY);

    glBindVertexArray(this->vao);
	glDrawElements(GL_LINES, indices.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

void	Area::drawObstacleDebug(float cameraX, float playerY) {
	this->obstacleDebugShader->use();

	glm::mat4 model = glm::mat4();
	//////
	// model = glm::rotate(model,-90.f, glm::vec3(1.f, 0.f, 0.f));
	// model = glm::translate(model, glm::vec3(this->xOffset, -progress + this->yOffset, 0.f));
	// model = glm::rotate(model,glm::radians(this->orientationOffset), glm::vec3(0.f, 0.f, 1.f));
	////
	this->obstacleDebugShader->setModel(model);
	this->obstacleDebugShader->setPerspective(cameraX, playerY);

    glBindVertexArray(this->obstacleDebugVao);
	glDrawArrays(GL_POINTS, 0, obstacles.size());
	glBindVertexArray(0);
}

void	Area::generateObstacles() {
	switch(orientation) {
		case NORTH:
			for (unsigned int i = 1; i < this->length; i++) {
				this->obstacles.push_back(glm::vec2(static_cast<float>(rand() % 5) + this->startX, static_cast<float>(i) + this->startY));
			} break;
		case SOUTH:
			for (unsigned int i = 1; i < this->length; i++) {
				this->obstacles.push_back(glm::vec2(static_cast<float>(rand() % 5) + this->startX, static_cast<float>(i) + this->startY));
			} break;
		case WEST:
			for (unsigned int i = 1; i < this->length; i++) {
				this->obstacles.push_back(glm::vec2(this->startX - static_cast<float>(i), static_cast<float>(rand() % 5) + this->startY));
			} break;
		case EAST:
			for (unsigned int i = 1; i < this->length; i++) {
				this->obstacles.push_back(glm::vec2(this->startX + static_cast<float>(i), static_cast<float>(rand() % 5) + this->startY));
			} break;
	}
}

unsigned int	Area::getLineNbr() const {
	return this->lineNbr;
}

unsigned int 	Area::getLength() const {
	return this->length;
}

std::vector<glm::vec2> Area::getObstacles() {
	return this->obstacles;
}

// void	Area::orientate(Area *area, eOrientation orientation) {
// 	switch (orientation) {
// 		case EAST:
// 			this->orientationOffset = -90.f;
// 			this->xOffset = area->getLineNbr() / 2 + (area->getLineNbr() / 2) - 1.5;
// 			this->yOffset = area->getLength() - this->lineNbr + 2.5; break;
// 		case WEST:
// 			this->orientationOffset = 90.f;
// 			this->xOffset = area->getLineNbr() / 2 - (area->getLineNbr() / 2) - 1.5;
// 			this->yOffset = area->getLength() - this->lineNbr + 2.5; break;
// 		case NORTH: break;
// 		case SOUTH: break;
// 	}
// }