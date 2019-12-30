#include <iostream>
#include "WarDrive.h"

WarDrive::WarDrive() {
	std::cout<<"WarDrive() ++";
	shared_ptr<InputManager> t_sptrInputManager(new InputManager());
	m_sptrInputManager = t_sptrInputManager;
	std::cout<<"WarDrive() --";
}

WarDrive::~WarDrive() {
	std::cout<<"~WarDrive() ++";
	m_sptrInputManager = nullptr;
	std::cout<<"~WarDrive() --";
}

