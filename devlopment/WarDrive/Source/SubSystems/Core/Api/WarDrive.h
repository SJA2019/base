#pragma once
#include <memory>

#ifdef __APPLE__
#include <OpenGL/gl3.h>
#include <OpenGL/gl3ext.h>
#else
#include <SDL_opengl.h>
#endif
#include <OpenGL/glu.h>

#include "InputManager.h"
using namespace std;
class WarDrive {

	shared_ptr<InputManager> m_sptrInputManager;
	public:
	WarDrive();
	~WarDrive();
	void Run();
	private:

	GLuint programID;

	void PerformRender();
	GLuint CreateProgramFromShaderText(const GLchar *vertexShader, const GLchar *fragmentShader);
	GLuint CreateProgramFromShaderFiles(const char *vertexShaderFileName, const char *fragmentShaderFileName);
	GLuint LoadShaders(const char * vertex_file_path,const char * fragment_file_path);
};
