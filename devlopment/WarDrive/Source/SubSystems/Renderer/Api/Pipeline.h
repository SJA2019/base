#pragma once
#include <memory>
#include <iostream>

// Include GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#ifdef __APPLE__
#include <OpenGL/gl3.h>
#include <OpenGL/gl3ext.h>
#else
#include <SDL_opengl.h>
#endif
#include <OpenGL/glu.h>

class Pipeline {

    public:
    GLuint GetProgramId();
    GLuint updateMVPMatrix(glm::mat4 MVPIn);
    void submitMVPMatrix();
    Pipeline(char *vertexShaderFileName = nullptr, char *fragmentShaderFileName = nullptr);
    
    private:
	GLuint m_programID;
    char shaderInfoLog[256];
    //Pipeline.
    GLuint MatrixID;
    glm::mat4 MVP;
	GLuint CreateProgramFromShaderText(const GLchar *vertexShader, const GLchar *fragmentShader);
	GLuint CreateProgramFromShaderFiles(const char *vertexShaderFileName, const char *fragmentShaderFileName);
	GLuint LoadShaders(const char * vertex_file_path,const char * fragment_file_path);

};

typedef std::shared_ptr<class Pipeline> PipelineSPTR;