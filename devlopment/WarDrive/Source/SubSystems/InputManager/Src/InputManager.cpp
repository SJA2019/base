#include <iostream>
#include "SDL.h"
#include "InputManager.h"

InputManager::InputManager(InputDeviceSelection::DeviceSet inputDeviceSet) {
	std::cout<<"InputManager() ++"<<std::endl;

    Uint32 inputSelection = 0;
    if(inputDeviceSet[InputDeviceSelection::joyInputDevice])
    {
        inputSelection |= SDL_INIT_JOYSTICK;
        SDL_JoystickEventState(SDL_ENABLE);
        
        SDL_Joystick *joystick = nullptr;
        joystick = SDL_JoystickOpen(0);
    }
    if(inputDeviceSet[InputDeviceSelection::mouseInputDevice] || inputDeviceSet[InputDeviceSelection::keyboardDevice])
    {
        inputSelection |= SDL_INIT_EVENTS | SDL_INIT_VIDEO;
        SDL_EventState( SDL_MOUSEMOTION | SDL_MOUSEBUTTONDOWN | SDL_MOUSEBUTTONUP | SDL_MOUSEWHEEL | SDL_KEYDOWN | SDL_KEYUP, SDL_ENABLE );
    
    }

    if( SDL_Init ( inputSelection ) != 0 )
	{
		std::cout<<"InputManager(): SDL_Init failed with:"<<inputSelection<<std::endl;	
	}
    
	std::cout<<"InputManager(): Number of joysticks found: "<<SDL_NumJoysticks()<<std::endl;
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
        if (sdlEvent.type == SDL_QUIT) {
            std::cout<<"InputManager:QUIT."<<std::endl;
            eventOut.eventType = EIMJoyEventType::eIMEventBailOut;
        } else if( sdlEvent.type == SDL_MOUSEMOTION || sdlEvent.type == SDL_MOUSEBUTTONDOWN ) {
            std::cout<<"InputManager:MouseEvent: event.type="<<sdlEvent.type<<",move="<<sdlEvent.motion.xrel<<","<<sdlEvent.motion.yrel<<",btn="<<sdlEvent.button.button<<std::endl;
            eventOut.eventType = EIMJoyEventType::eIMEventAvailable;
        } else if(sdlEvent.type == SDL_MOUSEBUTTONUP || sdlEvent.type == SDL_MOUSEWHEEL) {
            std::cout<<"InputManager:MouseEvent: event.type="<<std::endl;
            eventOut.eventType = EIMJoyEventType::eIMEventAvailable;
        } else if(sdlEvent.type == SDL_KEYDOWN || sdlEvent.type == SDL_KEYUP) {
            std::cout<<"InputManager:KeyboardEvent: event.type="<<sdlEvent.type<<"key="<<sdlEvent.key.keysym.scancode<<","<<sdlEvent.key.keysym.sym<<std::endl;
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
