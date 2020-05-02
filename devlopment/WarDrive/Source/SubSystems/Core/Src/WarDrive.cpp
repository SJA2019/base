#include <iostream>
#include "WarDrive.h"

WarDrive::WarDrive() {
	std::cout<<"WarDrive() ++"<<std::endl;
	InputDeviceSelection::DeviceSet inputDeviceSet;
	inputDeviceSet |= InputDeviceSelection::joyInputDevice;
	inputDeviceSet |= InputDeviceSelection::mouseInputDevice;
	inputDeviceSet |= InputDeviceSelection::keyboardDevice;
	shared_ptr<InputManager> t_sptrInputManager(new InputManager(inputDeviceSet));
	m_sptrInputManager = t_sptrInputManager;
	std::cout<<"WarDrive() --"<<std::endl;
}

WarDrive::~WarDrive() {
	std::cout<<"~WarDrive() ++"<<std::endl;
	m_sptrInputManager = nullptr;
	std::cout<<"~WarDrive() --"<<std::endl;
} 

void WarDrive::HandleInput() {
	m_sptrInputManager->PollJoyEvents();
}
