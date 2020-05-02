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
    
        SDL_Window* window = NULL;
        SDL_Surface* screenSurface = NULL;

        window = SDL_CreateWindow("Sphere Rendering", 
            SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 
            200, 200, SDL_WINDOW_SHOWN);

        if (window == NULL) {
            fprintf(stderr, "Window could not be created: %s\n", SDL_GetError());
            return;
        }

        screenSurface = SDL_GetWindowSurface(window);

        if (!screenSurface) {
            fprintf(stderr, "Screen surface could not be created: %s\n", SDL_GetError());
            SDL_Quit();
            return;
        }

        /* Enable Unicode translation */
       //SDL_EnableUNICODE( 1 );
    
    }
	if( SDL_Init ( inputSelection ) <= 0 )
	{
		std::cout<<"InputManager(): SDL_Init failed!!"<<std::endl;	
	}
	std::cout<<"InputManager(): Number of joysticks found: "<<SDL_NumJoysticks()<<std::endl;
	std::cout<<"InputManager() ++"<<std::endl;
}

InputManager::~InputManager() {
	std::cout<<"~InputManager() ++"<<std::endl;
	SDL_Quit();
	std::cout<<"~InputManager() --"<<std::endl;
}

void InputManager::PollJoyEvents() {
#if 0
	if(SDL_NumJoysticks() <= 0)
	{
		return;
	}
#endif
    SDL_Event event;
    bool hasEvent;
    /* Other initializtion code goes here */   
    /* Start main game loop here */
    while(1)
    {  
        hasEvent=SDL_PollEvent(&event);
        if (event.type == SDL_QUIT) {
            std::cout<<"InputManager:QUIT."<<std::endl;
            break;
        }
        if(hasEvent==true)
        {
            if( event.type == SDL_MOUSEMOTION || event.type == SDL_MOUSEBUTTONDOWN ) {
                std::cout<<"InputManager:MouseEvent: event.type="<<event.type<<",move="<<event.motion.xrel<<","<<event.motion.yrel<<",btn="<<event.button.button<<std::endl;
            } else if(event.type == SDL_MOUSEBUTTONUP || event.type == SDL_MOUSEWHEEL) {
                std::cout<<"InputManager:MouseEvent: event.type="<<std::endl;
            } else if(event.type == SDL_KEYDOWN || event.type == SDL_KEYUP) {
                std::cout<<"InputManager:KeyboardEvent: event.type="<<event.type<<"key="<<event.key.keysym.scancode<<","<<event.key.keysym.sym<<std::endl;
            } else {
                std::cout<<"InputManager:PollJoyEvents: event.type="<<event.type<<"|event.jbutton.button="<<(Uint32)event.jbutton.button<<"|event.jaxis.value="<<event.jaxis.value<<"|event.jaxis.axis="<<(Uint32)event.jaxis.axis<<std::endl;
            }
        }		
    }
    /* End loop here */
}
