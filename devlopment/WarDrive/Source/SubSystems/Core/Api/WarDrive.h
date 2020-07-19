#pragma once
#include <memory>

#include "InputManager.h"
#include "Renderer.h"
using namespace std;
class WarDrive {

	shared_ptr<InputManager> m_sptrInputManager;
	public:
	WarDrive();
	~WarDrive();
	void Run();

	private:
	RendererSPTR rendererInstance;
};
