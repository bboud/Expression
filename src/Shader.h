#ifndef PHY_GRAPHICS_SHADER_H
#define PHY_GRAPHICS_SHADER_H

#include <iostream>
#include <fstream>
#include <sstream>
#include "glad.h"
#include "glm/mat4x4.hpp"
#include "glm/gtc/type_ptr.hpp"

namespace Expression{
    class Shader {
    public:
        Shader( std::string vertex_path, std::string fragment_path );
        ~Shader();
        void Use();

        void SetCameraUniforms(glm::mat4 m, glm::mat4 v, glm::mat4 p);

        void SetUniform4f(std::string name, GLfloat v1, GLfloat v2, GLfloat v3, GLfloat v4 );

    private:
        int program_id;
    };
}

#endif //PHY_GRAPHICS_SHADER_H
