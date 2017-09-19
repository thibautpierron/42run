/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Camera.class.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpierron <tpierron@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/18 15:01:19 by tpierron          #+#    #+#             */
/*   Updated: 2017/09/19 16:25:14 by tpierron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CAMERA_CLASS_HPP
# define CAMERA_CLASS_HPP

# include "../constants/constants.hpp"
# include "../libs/glm/gtc/matrix_transform.hpp"
# include "../libs/glm/gtx/rotate_vector.hpp"
# include "../libs/glm/gtx/matrix_interpolation.hpp"
# include <iostream>

class Camera {
	public:
		Camera();

		glm::mat4	getMatrix() const;
		void		setOrientation(Orientation::Enum);
		void		setCamera(float, float);
		void		startRotationAnimation(float distance, float gameSpeed, Orientation::Enum way);
		void		startGetCloserAnimation();
		bool		getAnimationState() const;

	private:
		void				computeRotationAnimation(float, float, float, float);
		void				computeGetCloserAnimation(glm::mat4);

		glm::mat4			matrix;
		float				lookingDistance;
		float				positionDistance;
		float				height;
		Orientation::Enum	orientation;

		bool				animationRotationStarted;
		bool				animationGetCloserStarted;
		bool				completeAnimationDone;
		Orientation::Enum	animationWay;
		float				animationStep;
};

#endif