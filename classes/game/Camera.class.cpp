/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Camera.class.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpierron <tpierron@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/18 15:05:13 by tpierron          #+#    #+#             */
/*   Updated: 2017/09/18 15:16:34 by tpierron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"./Camera.class.hpp"

Camera::Camera() {}

void    Camera::setCamera(float targetX, float gameClock, Orientation::Enum orientation) {
    float posX;
    float posY;
    float lookX;
    float lookY;
    float horizontalOffset = 5.f;
    float cameraHeight = 2.f;

    switch(orientation) {
        case Orientation::NORTH:
            posX = targetX;
            posY = gameClock - horizontalOffset;
            lookX = targetX;
            lookY = gameClock + horizontalOffset;
            break;
        case Orientation::SOUTH:
            posX = targetX;
            posY = gameClock + horizontalOffset;
            lookX = targetX;
            lookY = gameClock - horizontalOffset;
            break;
        case Orientation::WEST:
            posX = gameClock + horizontalOffset;
            posY = targetX;
            lookX = gameClock - horizontalOffset;
            lookY = targetX;
            break;
        case Orientation::EAST:
            posX = gameClock - horizontalOffset;
            posY = targetX;
            lookX = gameClock + horizontalOffset;
            lookY = targetX;
            break;
    }
    
    this->matrix = glm::lookAt(
        glm::vec3(posX, posY, cameraHeight),
        glm::vec3(lookX, lookY, 0.f),
        glm::vec3(0.f, 0.f, 1.f)
    );
}

glm::mat4	Camera::getMatrix() const {
	return this->matrix;
}