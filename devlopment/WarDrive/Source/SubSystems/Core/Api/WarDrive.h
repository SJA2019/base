#pragma once
#include <memory>
#include "InputManager.h"
using namespace std;
class WarDrive {

	shared_ptr<InputManager> m_sptrInputManager;
	public:
	WarDrive();
	~WarDrive();
	void HandleInput();
};
