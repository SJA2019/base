#include <iostream>
#include "SDL.h"
#include "InputManager.h"


InputManager::InputManager() {
	std::cout<<"InputManager() ++"<<std::endl;


	if( SDL_Init ( SDL_INIT_JOYSTICK ) < 0 )
	{
		std::cout<<"InputManager(): SDL_INIT_JOYSTICK failed!!"<<std::endl;	
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

	if(SDL_NumJoysticks() <= 0)
	{
		return;
	}

	SDL_Joystick *joystick = nullptr;
    SDL_JoystickEventState(SDL_ENABLE);
    joystick = SDL_JoystickOpen(0);

    SDL_Event event;
    /* Other initializtion code goes here */   

    /* Start main game loop here */

    while(1)
    {  
        #if 0
        switch(event.type)
        {  
            case SDL_QUIT:
            /* Set whatever flags are necessary to */
            /* end the main game loop here */
            break;
        }
        #endif

        SDL_PollEvent(&event);
        std::cout<<"~InputManager:PollJoyEvents :"<<event.type<<std::endl;

		
    }
	
    /* End loop here */

}
