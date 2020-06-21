#include "SDL.h"
#include <SDL_opengl.h>
#include <OpenGL/glu.h>
#include <iostream>
#include "WarDrive.h"

SDL_Window* window = NULL;
WarDrive::WarDrive() {
	std::cout<<"WarDrive() ++"<<std::endl;
	InputDeviceSelection::DeviceSet inputDeviceSet;
	inputDeviceSet |= InputDeviceSelection::joyInputDevice;
	inputDeviceSet |= InputDeviceSelection::mouseInputDevice;
	inputDeviceSet |= InputDeviceSelection::keyboardDevice;
	shared_ptr<InputManager> t_sptrInputManager(new InputManager(inputDeviceSet));
	m_sptrInputManager = t_sptrInputManager;

	//SDL_Surface* screenSurface = NULL;
    window = SDL_CreateWindow("SampleRendering..", 
            SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 
            640, 480, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);

    if (window == NULL) {
        fprintf(stderr, "Window could not be created: %s\n", SDL_GetError());
        return;
    }
#if 0
        screenSurface = SDL_GetWindowSurface(window);

        if (!screenSurface) {
            fprintf(stderr, "Screen surface could not be created: %s\n", SDL_GetError());
            SDL_Quit();
            return;
        }
#endif

    SDL_GLContext context = SDL_GL_CreateContext( window );
    glClearColor( 1,0,0,1 );
    glClear(GL_COLOR_BUFFER_BIT);
    SDL_GL_SwapWindow( window );
    /* Enable Unicode translation */
    //SDL_EnableUNICODE( 1 );


	std::cout<<"WarDrive() --"<<std::endl;
}

WarDrive::~WarDrive() {
	std::cout<<"~WarDrive() ++"<<std::endl;
	m_sptrInputManager = nullptr;
	std::cout<<"~WarDrive() --"<<std::endl;
} 

void WarDrive::Run() {
	IMJoyEventTypes inputEvent = IMJoyEventTypes::eIMEventNotAvailable;
	static float red = 0.0;
    static float green = 0.5;
    static float blue = 1.0;
	while ( true ) {

		inputEvent = m_sptrInputManager->PollJoyEvents();

		if(IMJoyEventTypes::eIMEventBailOut == inputEvent ) {
			break;
		} else if (IMJoyEventTypes::eIMEventAvailable== inputEvent) {
			red+=0.1;
            green+=0.1;
            blue+=0.1;
            red=(red>1)?0.1:red;
            green=(green>1)?0.1:green;
            blue=(blue>1)?0.1:blue;
			glClearColor( red,green,blue,1 );
    		glClear(GL_COLOR_BUFFER_BIT);
    		SDL_GL_SwapWindow( window );
		}
	}

	
}
