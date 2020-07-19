#pragma once
#include <memory>

#ifdef __APPLE__
#include <OpenGL/gl3.h>
#include <OpenGL/gl3ext.h>
#else
#include <SDL_opengl.h>
#endif
#include <OpenGL/glu.h>

#include "Object.h"
#include "Pipeline.h"

using namespace std;

class Renderer {

	public:
	Renderer();
	~Renderer();

	void HandleInput(SDL_Keycode input);
	void Render();

	private:
	ObjectSPTR objectInstance;
	PipelinePTR pipelineInstance;
	void PerformRender();
};

typedef shared_ptr<Renderer> RendererSPTR;