/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Player.class.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpierron <tpierron@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/05 16:23:51 by thibautpier       #+#    #+#             */
/*   Updated: 2017/09/13 11:33:17 by tpierron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLAYER_CLASS_HPP
# define PLAYER_CLASS_HPP

# include "../model/Model.class.hpp"
# include "../game/Area.class.hpp"
# include "../Shader.class.hpp"


class Player {
    public:
        Player(unsigned int x, unsigned int areaLineNbr);
        ~Player();
        
        void    moveLeft();
        void    moveRight();
        void    goAhead(float);
        void    setAreaLineNbr(unsigned int);
        void    setState(unsigned int);
        void    setOrientation(eOrientation);
        glm::vec2    getPosition();
        void    drawDebug(float, float);
        void    draw(float, float);
        float   getX() const;
        float   getY() const;

    private:
        Player();
        void    setupDebug();

        unsigned int    x;
        unsigned int    y;
        eOrientation    orientation;
        unsigned int    state;
        unsigned int    areaLineNbr;

        Shader          *shader;
        Model           *model;

        Shader                  *debugShader;
        unsigned int            debugVao;
        unsigned int            debugVbo;
};

#endif