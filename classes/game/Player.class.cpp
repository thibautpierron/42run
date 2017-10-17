/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Player.class.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpierron <tpierron@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/05 16:29:37 by thibautpier       #+#    #+#             */
/*   Updated: 2017/10/17 13:35:36 by tpierron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Player.class.hpp"

Player::Player(unsigned int x, unsigned int areaLineNbr) : x(x), areaLineNbr(areaLineNbr) {
    this->shader = new Shader("shaders/static_model_instanced.glvs", "shaders/player_diffuse.glfs");
    this->debugShader = new Shader("shaders/simple_grid.glvs", "shaders/geometry_shader.glgs", "shaders/simple_grid.glfs");

    this->model = new Model("./models/marvin/marvin.obj", false);

    this->y = 0;
    this->z = 0;
    this->state = 0;
    this->orientation = Orientation::NORTH;
    setupDebug();
}

Player::~Player() {
    delete this->shader;
    delete this->debugShader;
    delete this->model;
    glDeleteBuffers(1, &this->debugVbo);
	glDeleteVertexArrays(1, &this->debugVao);
}

void    Player::setAreaLineNbr(unsigned int n) {
    this->areaLineNbr = n;
}

void    Player::move(float x, float y) {
        this->x += x;
        this->y += y;
}

void    Player::goAhead() {
    switch(this->orientation) {
        case Orientation::NORTH: this->y++; break;
        case Orientation::SOUTH: this->y--; break;
        case Orientation::EAST: this->x++; break;
        case Orientation::WEST: this->x--; break;
    }
}

void     Player::setupDebug() {

    std::vector<glm::vec2> crd;
    crd.push_back(glm::vec2(this->x, this->y));

	glGenVertexArrays(1, &this->debugVao);
	glGenBuffers(1, &this->debugVbo);

	glBindVertexArray(this->debugVao);
	glBindBuffer(GL_ARRAY_BUFFER, this->debugVbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec2), &crd[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);

	glBindVertexArray(0);
}

void    Player::draw(float gameClock) {
    float scalingRate = 0.5f;
    float xScaled;
    float yScaled;
    float angle;

    switch (this->orientation) {
        case Orientation::NORTH:
            xScaled = this->x * scalingRate + scalingRate * 0.5f;
            yScaled = gameClock * scalingRate + scalingRate * 0.5f;
            angle = 180.f; break;
        case Orientation::SOUTH:
            xScaled = this->x * scalingRate + scalingRate * 0.5f;
            yScaled = gameClock * scalingRate + scalingRate * 0.5f;
            angle = 0.f; break;
        case Orientation::EAST:
            xScaled = gameClock * scalingRate + scalingRate * 0.5f;
            yScaled = this->y * scalingRate + scalingRate * 0.5f;
            angle = 90.f; break;
        case Orientation::WEST:
            xScaled = gameClock * scalingRate + scalingRate * 0.5f;
            yScaled = this->y * scalingRate + scalingRate * 0.5f;
            angle = -90.f; break;
    }

    this->computeHeigth();

    std::vector<glm::mat4> data;
    glm::mat4 model;
    model = glm::scale(model, glm::vec3(1.f / scalingRate, 1.f / scalingRate, 1.f / scalingRate));
    model = glm::translate(model, glm::vec3(xScaled, yScaled, this->z));
    model = glm::rotate(model, glm::radians(90.f), glm::vec3(1.f, 0.f, 0.f));
    model = glm::rotate(model, glm::radians(angle), glm::vec3(0.f, 1.f, 0.f));
    data.push_back(model);
    
    this->shader->use();
	this->shader->setModel(model);
    this->model->setInstanceBuffer(data);

    glUniform3f(glGetUniformLocation(this->shader->getProgramID(), "lightOffset"), static_cast<float>(this->x), static_cast<float>(this->y), gameClock);
    this->shader->setView();
    this->model->draw(this->shader, 1);
}

void    Player::drawDebug(float gameClock) const {
    float xScaled;
    float yScaled;

    switch (this->orientation) {
        case Orientation::NORTH:
            xScaled = static_cast<float>(this->x);
            yScaled = gameClock; break;
        case Orientation::SOUTH:
            xScaled = static_cast<float>(this->x);
            yScaled = gameClock; break;
        case Orientation::EAST:
            xScaled = gameClock;
            yScaled = static_cast<float>(this->y); break;
        case Orientation::WEST:
            xScaled = gameClock;
            yScaled = static_cast<float>(this->y); break;
    }

    glm::mat4 model = glm::mat4();
    model = glm::translate(model, glm::vec3(xScaled, yScaled, 0.01f));
    
    this->debugShader->use();
    this->debugShader->setModel(model);
    this->debugShader->setView();
    glUniform1i(glGetUniformLocation(debugShader->getProgramID(), "playerState"), this->state);

    glBindVertexArray(this->debugVao);
    glDrawArrays(GL_POINTS, 0, 1);
    glBindVertexArray(0);
}

void    Player::setState(unsigned int newState) {
    this->state = newState;
}

glm::vec2   Player::getPosition() const {
    return glm::vec2(static_cast<float>(this->x), static_cast<float>(this->y));
}

void        Player::setOrientation(Orientation::Enum orientation) {
    this->orientation = orientation;
}

float   Player::getX() const {
    return this->x;
}

float   Player::getY() const {
    return this->y;
}

void    Player::computeHeigth() {
    
    static float i = 1;
    
    if (this->state != 2)
        return;

    i += 0.1;
    this->z = -0.02857143 + 0.8571429 * i - 0.2142857 * i * i;
    if (i > 4) {
        i = 1;
        this->z = 0;
        this->state = 0;
    }
}

bool    Player::isJumping() const {
    return (this->state == 2) ? true : false;
}