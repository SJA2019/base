#pragma once

#include <bitset>

typedef class InputDeviceSelection {
	public:
	static const uint8_t mouseInputDevice = 0x1<<0;
	static const uint8_t joyInputDevice = 0x1<<1;
	static const uint8_t keyboardDevice = 0x1<<2;
	typedef std::bitset<sizeof(uint8_t)> DeviceSet;
};

typedef enum IMEventType {
	eIMEventNotAvailable = 0,
	eIMEventAvailable,
	eIMEventBailOut
} EIMJoyEventType;

struct IMEvent {
	EIMJoyEventType eventType;
	SDL_Event sdlEvent;
};

class InputManager {
	public:
	InputManager(InputDeviceSelection::DeviceSet inputDeviceSet);
	IMEvent PollJoyEvents();
	~InputManager();
};
