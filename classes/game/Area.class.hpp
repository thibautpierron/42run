/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Area.class.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpierron <tpierron@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/26 09:56:41 by thibautpier       #+#    #+#             */
/*   Updated: 2017/09/13 09:41:32 by tpierron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AREA_CLASS_HPP
# define AREA_CLASS_HPP

# include <vector>
# include <OpenGL/gl3.h>
# include "../../libs/glm/vec3.hpp"
# include "../../libs/glm/gtx/quaternion.hpp"
# include "../Shader.class.hpp"

enum eOrientation { NORTH = 0, SOUTH = 1, EST = 2, WEST = 3 };

class Area {
    public:
        Area(unsigned int length, unsigned int lineNbr);
        ~Area();
        
        void            drawGrid(float, float);
        void            drawObstacleDebug(float, float);
        unsigned int	getLineNbr() const;
        unsigned int    getLength() const;
        std::vector<glm::vec2> getObstacles();
        void	        orientate(Area *previousArea, eOrientation orientation);

    private:
        Area();
        void    setupGrid();
        void    setupObstacleDebug();
        void    generateObstacles();

        unsigned int length;
        unsigned int lineNbr;
        eOrientation orientation;

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

        float                   orientationOffset;
        float                   xOffset;
        float                   yOffset;

};

#endif