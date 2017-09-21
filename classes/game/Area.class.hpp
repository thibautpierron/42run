/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Area.class.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpierron <tpierron@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/26 09:56:41 by thibautpier       #+#    #+#             */
/*   Updated: 2017/09/21 12:40:34 by tpierron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AREA_CLASS_HPP
# define AREA_CLASS_HPP

# include <vector>
# include <OpenGL/gl3.h>
# include "../../libs/glm/vec3.hpp"
# include "../../libs/glm/gtx/quaternion.hpp"
# include "../Shader.class.hpp"
# include "../../constants/constants.hpp"
# include "../model/Model.class.hpp"

class Area {
    public:
        Area(float startX, float startY,
                unsigned int length, unsigned int lineNbr,
                Orientation::Enum orientation);
        ~Area();
        
        void                    drawGrid() const;
        void                    drawObstacles() const;
        void                    drawObstacleDebug() const;
        unsigned int	        getLineNbr() const;
        unsigned int            getLength() const;
        float                   getEndX() const;
        float                   getEndY() const;
        std::vector<glm::vec2>  getObstacles() const;
        Orientation::Enum       getOrientation() const;

    private:
        Area();
        void    setupGrid();
        void    setupObstacleDebug();
        void    generateObstacles();

        float				startX;
        float				startY;
        unsigned int		length;
        unsigned int		lineNbr;
        Orientation::Enum	orientation;

        std::vector<unsigned int>	indices;
        std::vector<glm::vec3>		vertices;
        std::vector<glm::vec2>      obstacles;

        Shader                  *gridShader;
        unsigned int            vao;
        unsigned int            vbo;
        unsigned int            ebo;

        Shader                  *obstacleDebugShader;
        unsigned int            obstacleDebugVao;
        unsigned int            obstacleDebugVbo;

        Model                   *obstacle;
        Shader                  *obstacleShader;
        // unsigned int            obstacleVao;
        // unsigned int            obstacleVbo;
};

#endif