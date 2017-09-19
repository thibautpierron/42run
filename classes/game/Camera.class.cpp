/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Camera.class.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpierron <tpierron@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/18 15:05:13 by tpierron          #+#    #+#             */
/*   Updated: 2017/09/19 16:58:35 by tpierron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"./Camera.class.hpp"

Camera::Camera() {
	this->lookingDistance = 5.f;
	this->positionDistance = 5.f;
	this->height = 2.f;
    this->animationRotationStarted = false;
    this->animationGetCloserStarted = false;
    this->completeAnimationDone = true;
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
        computeGetCloserAnimation(glm::lookAt(
            glm::vec3(posX, posY, this->height),
            glm::vec3(lookX, lookY, 0.f),
            glm::vec3(0.f, 0.f, 1.f)
        ));
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

    if(this->completeAnimationDone) {
        step = 0.f;
        this->completeAnimationDone = false;
    }
    
    float stepRad;
    float stepRad2;
    float px;
    float py;
    float lx;
    float ly;

    switch(this->orientation) {
        case Orientation::NORTH:
            stepRad = glm::radians(-90 + step);
            stepRad2 = glm::radians(-270 + step);
            px = 5.f * cos(stepRad) + posX;
            py = 5.f * sin(stepRad) + posY + 5.f;
            lx = 5.f * cos(stepRad2) + lookX;
            ly = 5.f * sin(stepRad2) + lookY - 5.f;
            break;
        case Orientation::SOUTH:
            stepRad = glm::radians(-270 + step);
            stepRad2 = glm::radians(-90 + step);
            px = 5.f * cos(stepRad) + posX;
            py = 5.f * sin(stepRad) + posY - 5.f;
            lx = 5.f * cos(stepRad2) + lookX;
            ly = 5.f * sin(stepRad2) + lookY + 5.f;
            break;
        case Orientation::EAST:
            stepRad = glm::radians(-180 + step);
            stepRad2 = glm::radians(step);
            px = 5.f * cos(stepRad) + posX + 5.f;
            py = 5.f * sin(stepRad) + posY;
            lx = 5.f * cos(stepRad2) + lookX - 5.f;
            ly = 5.f * sin(stepRad2) + lookY;
            break;
        case Orientation::WEST:
            stepRad = glm::radians(step);
            stepRad2 = glm::radians(-180 + step);
            px = 5.f * cos(stepRad) + posX - 5.f;
            py = 5.f * sin(stepRad) + posY;
            lx = 5.f * cos(stepRad2) + lookX + 5.f;
            ly = 5.f * sin(stepRad2) + lookY;
            break;
    }

    this->matrix = glm::lookAt(
        glm::vec3(px, py, this->height),
        glm::vec3(lx, ly, 0.f),
        glm::vec3(0.f, 0.f, 1.f)
    );

    switch (this->orientation) {
        case Orientation::NORTH: this->animationWay == Orientation::EAST ? step -= this->animationStep : step += this->animationStep; break;
        case Orientation::SOUTH: this->animationWay == Orientation::WEST ? step -= this->animationStep : step += this->animationStep; break;
        case Orientation::WEST: this->animationWay == Orientation::NORTH ? step -= this->animationStep : step += this->animationStep; break;
        case Orientation::EAST: this->animationWay == Orientation::SOUTH ? step -= this->animationStep : step += this->animationStep; break;
    }
}

void    Camera::startGetCloserAnimation() {
    this->animationRotationStarted = false;
    this->animationGetCloserStarted = true;
}

void    Camera::computeGetCloserAnimation(glm::mat4 targetMat) {
    static glm::mat4 prevMat = this->matrix;
    static float step = 0.f;

    if (step == 0.f)
        prevMat = this->matrix;
    this->matrix = glm::interpolate(prevMat, targetMat, step);
    step += 0.02f;
    if (step >= 1.f) {
        step = 0.f;
        this->animationGetCloserStarted = false;
        this->completeAnimationDone = true;
    }
}

bool    Camera::getAnimationState() const {
    if(this->animationRotationStarted || this->animationGetCloserStarted)
        return true;
    return false;
}