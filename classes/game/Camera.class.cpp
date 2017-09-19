/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Camera.class.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpierron <tpierron@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/18 15:05:13 by tpierron          #+#    #+#             */
/*   Updated: 2017/09/19 11:11:17 by tpierron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"./Camera.class.hpp"

Camera::Camera() {
	this->lookingDistance = 5.f;
	this->positionDistance = 5.f;
	this->height = 2.f;
    this->animationStarted = false;
}

void    Camera::setCamera(float targetX, float gameClock) {
    float posX;
    float posY;
    float lookX;
    float lookY;

    switch(this->orientation) {
        case Orientation::NORTH:
            posX = targetX;
            posY = gameClock - this->positionDistance;
            lookX = targetX;
            lookY = gameClock + this->lookingDistance;
            break;
        case Orientation::SOUTH:
            posX = targetX;
            posY = gameClock + this->positionDistance;
            lookX = targetX;
            lookY = gameClock - this->lookingDistance;
            break;
        case Orientation::WEST:
            posX = gameClock + this->positionDistance;
            posY = targetX;
            lookX = gameClock - this->lookingDistance;
            lookY = targetX;
            break;
        case Orientation::EAST:
            posX = gameClock - this->positionDistance;
            posY = targetX;
            lookX = gameClock + this->lookingDistance;
            lookY = targetX;
            break;
    }
    
    if (this->animationStarted)
        computeAnimation(posX, posY, lookX, lookY);
    else {
        this->matrix = glm::lookAt(
            glm::vec3(posX, posY, this->height),
            glm::vec3(lookX, lookY, 0.f),
            glm::vec3(0.f, 0.f, 1.f)
        );
    }
}

glm::mat4	Camera::getMatrix() const {
	return this->matrix;
}

void		Camera::setOrientation(Orientation::Enum orientation) {
	this->orientation = orientation;
}

void        Camera::startRotationAnimation(float distance, float gameSpeed, Orientation::Enum way) {
    this->animationStarted = true;
    this->animationStep = distance / gameSpeed;
    this->animationWay = way;
}

void        Camera::computeAnimation(float posX, float posY, float lookX, float lookY) {
        this->matrix = glm::lookAt(
            glm::vec3(posX, posY, this->height),
            glm::vec3(lookX, lookY, 0.f),
            glm::vec3(0.f, 0.f, 1.f)
        );
}