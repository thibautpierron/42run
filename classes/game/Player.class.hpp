/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Player.class.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpierron <tpierron@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/05 16:23:51 by thibautpier       #+#    #+#             */
/*   Updated: 2017/09/18 12:46:38 by tpierron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLAYER_CLASS_HPP
# define PLAYER_CLASS_HPP

# include "../model/Model.class.hpp"
# include "../game/Area.class.hpp"
# include "../Shader.class.hpp"
# include "../../constants/constants.hpp"


class Player {
    public:
        Player(unsigned int x, unsigned int areaLineNbr);
        ~Player();
        
        void    move(float, float);
        void    goAhead();
        void    setAreaLineNbr(unsigned int);
        void    setState(unsigned int);
        void    setOrientation(Orientation::Enum);
        glm::vec2    getPosition();
        void    drawDebug(float);
        void    draw(float);
        float   getX() const;
        float   getY() const;

    private:
        Player();
        void    setupDebug();

        int    x;
        int    y;
        Orientation::Enum    orientation;
        unsigned int    state;
        unsigned int    areaLineNbr;

        Shader          *shader;
        Model           *model;

        Shader                  *debugShader;
        unsigned int            debugVao;
        unsigned int            debugVbo;
};

#endif