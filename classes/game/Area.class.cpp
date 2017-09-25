/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Area.class.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpierron <tpierron@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/26 10:01:40 by thibautpier       #+#    #+#             */
/*   Updated: 2017/09/25 16:56:04 by tpierron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Area.class.hpp"

Area::Area(float startX, float startY,
            unsigned int length, unsigned int lineNbr,
			Orientation::Enum orientation)
			: startX(startX), startY(startY),
				length(length), lineNbr(lineNbr),
			 	orientation(orientation) {
	// std::cout << "AREA CONSTRUCTOR" << std::endl;
	setupGrid();
	generateObstacles();
	setupObstacleDebug();
	
	this->gridShader = new Shader("shaders/simple_grid.glvs",
									"shaders/simple_grid.glfs");
	this->obstacleDebugShader = new Shader("shaders/simple_grid.glvs",
											"shaders/geometry_shader.glgs",
											"shaders/simple_grid.glfs");
	this->obstacleShader = new Shader("shaders/static_model_instanced.glvs",
										"shaders/diffuse_texture.glfs");

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
			for (unsigned int i = 0; i < this->length; i++) {
				this->obstacles.push_back(glm::vec2(static_cast<float>(rand() % this->lineNbr) + this->startX, static_cast<float>(i) + this->startY));
			} break;
		case Orientation::SOUTH:
			for (unsigned int i = 0; i < this->length; i++) {
				this->obstacles.push_back(glm::vec2(this->startX - static_cast<float>(rand() % this->lineNbr) - 1, this->startY - static_cast<float>(i) - 1));
			} break;
		case Orientation::WEST:
			for (unsigned int i = 0; i < this->length; i++) {
				this->obstacles.push_back(glm::vec2(this->startX - static_cast<float>(i) - 1, static_cast<float>(rand() % this->lineNbr) + this->startY));
			} break;
		case Orientation::EAST:
			for (unsigned int i = 0; i < this->length; i++) {
				this->obstacles.push_back(glm::vec2(this->startX + static_cast<float>(i),  this->startY - static_cast<float>(rand() % this->lineNbr) - 1));
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
		model = glm::scale(model, glm::vec3(0.3f, 0.3f, 0.03f));
		data.push_back(model);
	}
	this->obstacle->setInstanceBuffer(data);
}