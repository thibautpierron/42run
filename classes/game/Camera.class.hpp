/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Camera.class.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpierron <tpierron@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/18 15:01:19 by tpierron          #+#    #+#             */
/*   Updated: 2017/09/19 11:11:31 by tpierron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CAMERA_CLASS_HPP
# define CAMERA_CLASS_HPP

# include "../constants/constants.hpp"
# include "../libs/glm/gtc/matrix_transform.hpp"

class Camera {
	public:
		Camera();

		glm::mat4	getMatrix() const;
		void		setOrientation(Orientation::Enum);
		void		setCamera(float, float);
		void		startRotationAnimation(float distance, float gameSpeed, Orientation::Enum way);

	private:
		void				computeAnimation(float, float, float, float);

		glm::mat4			matrix;
		float				lookingDistance;
		float				positionDistance;
		float				height;
		Orientation::Enum	orientation;

		bool				animationStarted;
		Orientation::Enum	animationWay;
		float				animationStep;
};

#endif