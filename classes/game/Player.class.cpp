/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Player.class.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpierron <tpierron@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/05 16:29:37 by thibautpier       #+#    #+#             */
/*   Updated: 2017/09/14 12:06:06 by tpierron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Player.class.hpp"

Player::Player(unsigned int x, unsigned int areaLineNbr) : x(x), areaLineNbr(areaLineNbr) {
    this->shader = new Shader("shaders/static_model.glvs", "shaders/diffuse_texture.glfs");
    this->debugShader = new Shader("shaders/simple_grid.glvs", "shaders/geometry_shader.glgs", "shaders/simple_grid.glfs");

    this->model = new Model("./models/cowboy/model.dae", true);

    this->y = 0;
    this->state = 0;
    this->orientation = NORTH;
    setupDebug();
}

Player::~Player() {
    delete this->shader;
    delete this->debugShader;
    delete this->model;
    // std::cout << "Player destroyed" << std::endl;
}

void    Player::setAreaLineNbr(unsigned int n) {
    this->areaLineNbr = n;
}

void    Player::moveLeft() {
    if (this->x > 0)
        this->x -= 1;
}

void    Player::moveRight() {
    if (this->x < this->areaLineNbr - 1)
        this->x += 1;
}

void    Player::goAhead() {
        // std::cout << "YEP" << std::endl;
        switch(this->orientation) {
            case NORTH: this->y++; break;
            case SOUTH: this->y--; break;
            case WEST: this->x--; break;
            case EAST: this->x++; break;
        }
}

void     Player::setupDebug() {

    std::vector<glm::vec2> crd;
    crd.push_back(glm::vec2(this->x, this->y));
    // crd[0].x -= (5 / 2) + 0.5f;

	glGenVertexArrays(1, &this->debugVao);
	glGenBuffers(1, &this->debugVbo);

	glBindVertexArray(this->debugVao);
	glBindBuffer(GL_ARRAY_BUFFER, this->debugVbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec2), &crd[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);

	glBindVertexArray(0);
}

void    Player::draw(float cameraX, float playerY) {
    
    float scalingRate = 5.f;

    glm::mat4 model;
    model = glm::scale(model, glm::vec3(1.f / scalingRate, 1.f / scalingRate, 1.f / scalingRate));

    float xScaled = this->x * scalingRate + scalingRate * 0.5f;
    float yScaled = playerY * scalingRate + scalingRate * 0.5f;
    model = glm::translate(model, glm::vec3(xScaled, yScaled, 0.f));
    model = glm::rotate(model, glm::radians(180.f), glm::vec3(0.f, 0.f, 1.f));
    
    this->shader->use();
    
	this->shader->setModel(model);
    this->shader->setPerspective(cameraX, playerY);
    this->model->draw(this->shader);
}

void    Player::drawDebug(float cameraX, float playerY) {
    this->debugShader->use();
    
    glm::mat4 model = glm::mat4();
    // model = glm::rotate(model, -90.f, glm::vec3(1.f, 0.f, 0.f));
    model = glm::translate(model, glm::vec3(this->x, playerY, 0.01f));
    // model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));
    this->debugShader->setModel(model);
    this->debugShader->setPerspective(cameraX, playerY);
    glUniform1i(glGetUniformLocation(debugShader->getProgramID(), "playerState"), this->state);    

    glBindVertexArray(this->debugVao);
    glDrawArrays(GL_POINTS, 0, 1);
    glBindVertexArray(0);
}

void    Player::setState(unsigned int newState) {
    this->state = newState;
}

glm::vec2   Player::getPosition() {
    return glm::vec2(static_cast<float>(this->x), static_cast<float>(this->y));
}

void        Player::setOrientation(eOrientation orientation) {
    this->orientation = orientation;
}

float   Player::getX() const {
    return this->x;
}

float   Player::getY() const {
    return this->y;
}
