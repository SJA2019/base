#include <iostream>
#include "SDL.h"
#include "InputManager.h"

InputManager::InputManager(InputDeviceSelection::DeviceSet inputDeviceSet) {
	std::cout<<"InputManager() ++"<<std::endl;

    Uint32 inputSelection = 0;
    if(inputDeviceSet[InputDeviceSelection::joyInputDevice])
    {
        inputSelection |= SDL_INIT_JOYSTICK;
        SDL_SetJoystickEventsEnabled(true);
        
        SDL_Joystick *joystick = nullptr;
        joystick = SDL_OpenJoystick(0);
    }
    if(inputDeviceSet[InputDeviceSelection::mouseInputDevice] || inputDeviceSet[InputDeviceSelection::keyboardDevice])
    {
        inputSelection |= SDL_INIT_EVENTS | SDL_INIT_VIDEO;
        SDL_SetEventEnabled( SDL_EVENT_MOUSE_MOTION | SDL_EVENT_MOUSE_BUTTON_DOWN | SDL_EVENT_MOUSE_BUTTON_UP | SDL_EVENT_MOUSE_WHEEL | SDL_EVENT_KEY_DOWN | SDL_EVENT_KEY_UP, true );
    
    }

    if( SDL_Init ( inputSelection ) != 0 )
	{
		std::cout<<"InputManager(): SDL_Init failed with:"<<inputSelection<<std::endl;	
	}
    int count = 0;
    SDL_GetJoysticks(&count);
	std::cout<<"InputManager(): Number of joysticks found: "<<count<<std::endl;
	std::cout<<"InputManager() ++"<<std::endl;
}

InputManager::~InputManager() {
	std::cout<<"~InputManager() ++"<<std::endl;
	SDL_Quit();
	std::cout<<"~InputManager() --"<<std::endl;
}

IMEvent InputManager::PollJoyEvents() {
    IMEvent eventOut = {eIMEventNotAvailable, SDL_EventType()};
#if 0
	if(SDL_NumJoysticks() <= 0)
	{
		return IMJoyEventType::EIMBailout;
	}
#endif
    SDL_Event sdlEvent;
    bool hasEvent;
    /* Other initializtion code goes here */   
    /* Start main game loop here */
    hasEvent=SDL_PollEvent(&sdlEvent);
    if(hasEvent==true) {
        if (sdlEvent.type == SDL_EVENT_QUIT) {
            std::cout<<"InputManager:QUIT."<<std::endl;
            eventOut.eventType = EIMJoyEventType::eIMEventBailOut;
        } else if( sdlEvent.type == SDL_EVENT_MOUSE_MOTION || sdlEvent.type == SDL_EVENT_MOUSE_BUTTON_DOWN ) {
            std::cout<<"InputManager:MouseEvent: event.type="<<sdlEvent.type<<",move="<<sdlEvent.motion.xrel<<","<<sdlEvent.motion.yrel<<",btn="<<sdlEvent.button.button<<std::endl;
            eventOut.eventType = EIMJoyEventType::eIMEventAvailable;
        } else if(sdlEvent.type == SDL_EVENT_MOUSE_BUTTON_UP || sdlEvent.type == SDL_EVENT_MOUSE_WHEEL) {
            std::cout<<"InputManager:MouseEvent: event.type="<<std::endl;
            eventOut.eventType = EIMJoyEventType::eIMEventAvailable;
        } else if(sdlEvent.type == SDL_EVENT_KEY_DOWN || sdlEvent.type == SDL_EVENT_KEY_UP) {
            std::cout<<"InputManager:KeyboardEvent: event.type="<<sdlEvent.type<<"key="<<sdlEvent.key.scancode<<","<<sdlEvent.key.key<<std::endl;
            eventOut.eventType = EIMJoyEventType::eIMEventAvailable;
        } else {
            std::cout<<"InputManager:PollJoyEvents: event.type="<<sdlEvent.type<<"|event.jbutton.button="<<(Uint32)sdlEvent.jbutton.button<<"|event.jaxis.value="<<sdlEvent.jaxis.value<<"|event.jaxis.axis="<<(Uint32)sdlEvent.jaxis.axis<<std::endl;
            eventOut.eventType = EIMJoyEventType::eIMEventAvailable;
        }
    } else {
        eventOut.eventType = EIMJoyEventType::eIMEventNotAvailable;
    }
    eventOut.sdlEvent = sdlEvent;
    return eventOut;
}
