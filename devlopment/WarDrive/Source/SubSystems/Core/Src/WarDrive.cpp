#include <iostream>
#include "WarDrive.h"

WarDrive::WarDrive() {
	std::cout<<"WarDrive() ++"<<std::endl;
	shared_ptr<InputManager> t_sptrInputManager(new InputManager());
	m_sptrInputManager = t_sptrInputManager;
	std::cout<<"WarDrive() --"<<std::endl;
}

WarDrive::~WarDrive() {
	std::cout<<"~WarDrive() ++"<<std::endl;
	m_sptrInputManager = nullptr;
	std::cout<<"~WarDrive() --"<<std::endl;
}

