/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Camera.class.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpierron <tpierron@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/18 15:01:19 by tpierron          #+#    #+#             */
/*   Updated: 2017/09/18 15:15:16 by tpierron         ###   ########.fr       */
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
		void		setCamera(float, float, Orientation::Enum);

	private:
		glm::mat4	matrix;
};

#endif