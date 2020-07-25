#pragma once
#include <memory>
#include <vector>

#ifdef __APPLE__
#include <OpenGL/gl3.h>
#include <OpenGL/gl3ext.h>
#else
#include <SDL_opengl.h>
#endif
#include <OpenGL/glu.h>

#include "Object.h"
#include "Camera.h"
#include "Pipeline.h"

using namespace std;



typedef struct OBJPIPPAIR {
	ObjectSPTR objectInstance = nullptr;
	PipelineSPTR pipelineInstance = nullptr;
} ObjPipePair;
typedef shared_ptr<ObjPipePair> ObjPipePairSPTR;

class Renderer {

	public:
	Renderer();
	~Renderer();
	void HandleInput(SDL_Keycode input);
	void Render();

	private:
	void PerformRender();
	unsigned int currentRenderingIdx;
	std::vector<ObjPipePairSPTR> renderList;
	CameraSPTR cameraInstance;
};
typedef shared_ptr<Renderer> RendererSPTR;