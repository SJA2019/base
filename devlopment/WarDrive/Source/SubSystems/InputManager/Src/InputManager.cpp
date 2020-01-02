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
