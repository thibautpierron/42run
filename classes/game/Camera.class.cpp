/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Camera.class.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpierron <tpierron@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/18 15:05:13 by tpierron          #+#    #+#             */
/*   Updated: 2017/09/18 15:40:29 by tpierron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"./Camera.class.hpp"

Camera::Camera() {
	this->distance = 5.f;
	this->height = 2.f;
}

void    Camera::setCamera(float targetX, float gameClock) {
    float posX;
    float posY;
    float lookX;
    float lookY;

    switch(this->orientation) {
        case Orientation::NORTH:
            posX = targetX;
            posY = gameClock - this->distance;
            lookX = targetX;
            lookY = gameClock + this->distance;
            break;
        case Orientation::SOUTH:
            posX = targetX;
            posY = gameClock + this->distance;
            lookX = targetX;
            lookY = gameClock - this->distance;
            break;
        case Orientation::WEST:
            posX = gameClock + this->distance;
            posY = targetX;
            lookX = gameClock - this->distance;
            lookY = targetX;
            break;
        case Orientation::EAST:
            posX = gameClock - this->distance;
            posY = targetX;
            lookX = gameClock + this->distance;
            lookY = targetX;
            break;
    }
    
    this->matrix = glm::lookAt(
        glm::vec3(posX, posY, this->height),
        glm::vec3(lookX, lookY, 0.f),
        glm::vec3(0.f, 0.f, 1.f)
    );
}

glm::mat4	Camera::getMatrix() const {
	return this->matrix;
}

void		Camera::setOrientation(Orientation::Enum orientation) {
	this->orientation = orientation;
}