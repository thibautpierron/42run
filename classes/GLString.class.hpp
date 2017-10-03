/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   GLString.class.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpierron <tpierron@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/02 14:47:43 by tpierron          #+#    #+#             */
/*   Updated: 2017/10/03 09:55:45 by tpierron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GLSTRING_CLASS_H
# define GLSTRING_CLASS_H

# include <map>
# include "../Shader.class.hpp"
# include "../libs/glm/gtc/matrix_transform.hpp"
# include <OpenGL/gl3.h>
# include <ft2build.h>
# include FT_FREETYPE_H

struct Character {
    GLuint     textureID;  // ID handle of the glyph texture
    glm::ivec2 size;       // Size of glyph
    glm::ivec2 bearing;    // Offset from baseline to left/top of glyph
    GLuint     advance;    // Offset to advance to next glyph
};

class GLString {
	public:
		GLString();
		void		render();
		void		renderText(std::string str, float x, float y, glm::vec3 color) const;

	private:
		void		initFont(std::string fontPath);
		void		setupGl();

		Shader*		shader;
		static std::map<GLchar, Character> characters;
		GLuint		VAO;
		GLuint		VBO;
		
};

#endif

