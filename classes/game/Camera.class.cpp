/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Camera.class.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpierron <tpierron@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/18 15:05:13 by tpierron          #+#    #+#             */
/*   Updated: 2017/09/19 14:30:02 by tpierron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"./Camera.class.hpp"

Camera::Camera() {
	this->lookingDistance = 5.f;
	this->positionDistance = 5.f;
	this->height = 2.f;
    this->animationRotationStarted = false;
    this->animationGetCloserStarted = false;
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
    
    if (this->animationRotationStarted)
        computeRotationAnimation(posX, posY, lookX, lookY);
    else if (this->animationGetCloserStarted)
        computeGetCloserAnimation();
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
    this->animationRotationStarted = true;
    this->animationStep = 90.f / (distance / gameSpeed);
    this->animationWay = way;
}

void        Camera::computeRotationAnimation(float posX, float posY, float lookX, float lookY) {
    static float step = 0.f;

    float stepRad = glm::radians(step - 90);
    float stepRad2 = glm::radians(step + 180 - 90);

    float px = 5.f * cos(stepRad) + posX;
    float py = 5.f * sin(stepRad) + posY + 5.f;

    float lx = 5.f * cos(stepRad2) + lookX;
    float ly = 5.f * sin(stepRad2) + lookY - 5.f;

    this->matrix = glm::lookAt(
        glm::vec3(px, py, this->height),
        glm::vec3(lx, ly, 0.f),
        glm::vec3(0.f, 0.f, 1.f)
    );

    if (this->animationWay == Orientation::SOUTH || this->animationWay == Orientation::WEST)
        step += this->animationStep;
    else
        step -= this->animationStep;

    if (step >= 90.f || step <= -90.f) {
        this->animationRotationStarted = false;
    }

std::cout << step << std::endl;
        
}

void    Camera::startGetCloserAnimation() {
    this->animationRotationStarted = false;
    this->animationGetCloserStarted = true;
}

void    Camera::computeGetCloserAnimation() {}

bool    Camera::getAnimationState() const {
    if(this->animationRotationStarted || this->animationGetCloserStarted)
        return true;
    return false;
}