/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Shader.class.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpierron <tpierron@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/16 14:11:32 by thibautpier       #+#    #+#             */
/*   Updated: 2017/09/14 15:50:39 by tpierron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHADER_CLASS_HPP
# define SHADER_CLASS_HPP

# include <iostream>
# include <fstream>
# include <OpenGL/gl3.h>
# include "../math3d.hpp"
# include "../libs/glm/gtc/matrix_transform.hpp"
# include "../libs/glm/gtc/type_ptr.hpp"
# include "./game/Area.class.hpp"

class Shader {

    public:
        Shader(std::string vertexSrc, std::string fragmentSrc);
        Shader(std::string vertexSrc, std::string geometrySrc, std::string fragmentSrc);
        ~Shader();
        
        void    use() const;
        void    setModel(glm::mat4 model) const;
        void    setFloat(const std::string &name, float value) const;
        void    setInt(const std::string &name, float value) const;
        GLuint  getProgramID() const;
        static void    setPerspective(float, float, eOrientation);
        void    setView();
        
        Shader();
    private:
        GLuint      load(GLenum , std::string);
        void        compile();

        bool        checkShaderCompilation(GLuint, GLenum);
        bool        checkProgramCompilation(GLuint);

        static glm::mat4    camera;
        static glm::mat4    perspective;
        GLuint          vertexID;
        GLuint          fragmentID;
        GLuint          geometryID;
        GLuint          programID;
        std::string     vertexSrc;
        std::string     fragmentSrc;
        std::string     geometrySrc;
};

#endif
