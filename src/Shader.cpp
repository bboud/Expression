#include "Shader.h"

namespace PhyG{
    Shader::Shader( std::string vertex_path, std::string fragment_path ){
        // Load in the shader:
        std::ifstream vFile;
        std::ifstream fFile;
        std::stringstream vStream, fStream;

        vFile.exceptions( std::ifstream::failbit | std::ifstream::badbit );
        fFile.exceptions( std::ifstream::failbit | std::ifstream::badbit );

        try {
            vFile.open(vertex_path);
            fFile.open(fragment_path);

            vStream << vFile.rdbuf();
            fStream << fFile.rdbuf();

            fFile.close();
            vFile.close();
        }catch(std::ifstream::failure e){
            std::cout << "SHADER READ ERROR: " << e.what() << std::endl;
        }

        // This is stupid, or maybe just me
        const std::string vertex_code_str = vStream.str();
        const std::string fragment_code_str = fStream.str();

        const char* vertex_code = vertex_code_str.c_str();
        const char* fragment_code = fragment_code_str.c_str();

        // Compile the shaders
        unsigned int vertex, fragment;
        int success;
        char infoLog[512];

        vertex = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertex, 1, &vertex_code, NULL);
        glCompileShader(vertex);
        glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
        if(!success){
            glGetShaderInfoLog(vertex, 512, NULL, infoLog);
            std::cout << "There was a problem compiling the shader " << vertex_path << std::endl;
            std::cout << infoLog << std::endl;
        }

        fragment= glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragment, 1, &fragment_code, NULL);
        glCompileShader(fragment);
        glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
        if(!success){
            glGetShaderInfoLog(vertex, 512, NULL, infoLog);
            std::cout << "There was a problem compiling the shader " << fragment_path << std::endl;
            std::cout << infoLog << std::endl;
        }

        program_id = glCreateProgram();
        glAttachShader(program_id, vertex);
        glAttachShader(program_id, fragment );
        glLinkProgram(program_id);
        glGetProgramiv(program_id, GL_LINK_STATUS, &success);
        if(!success){
            glGetProgramInfoLog(program_id, 512, NULL, infoLog);
            std::cout << "There was a problem linking the shader program!" << std::endl;
            std::cout << infoLog << std::endl;
        }

        glDeleteShader(vertex);
        glDeleteShader(fragment);
    }

    Shader::~Shader(){
        glDeleteProgram(program_id);
    }

    void Shader::Use(){
        glUseProgram(program_id);
    }

    void Shader::SetUniform4f(std::string name, GLfloat v1, GLfloat v2, GLfloat v3, GLfloat v4) {
        GLuint attrib = glGetUniformLocation(program_id, name.c_str());
        Use();
        // GLint location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3
        glUniform4f(attrib, v1, v2, v3, v4);
    }

    void Shader::SetCameraUniforms(glm::mat4 m, glm::mat4 v, glm::mat4 p) {
        GLuint model, view, projection;
        model = glGetUniformLocation(program_id, "model");
        view = glGetUniformLocation(program_id, "view");
        projection = glGetUniformLocation(program_id, "projection");

        glUniformMatrix4fv(model, 1, GL_FALSE, glm::value_ptr(m));
        glUniformMatrix4fv(view, 1, GL_FALSE, glm::value_ptr(v));
        glUniformMatrix4fv(projection, 1, GL_FALSE, glm::value_ptr(p));

    }
}
