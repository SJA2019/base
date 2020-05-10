#include <iostream>
#include "SDL.h"
#include "InputManager.h"
//#include <gl\glew.h>
#include <SDL_opengl.h>
//#include <gl\glu.h>
//#include <GL3/gl3.h>
#include <OpenGL/glu.h>

SDL_Window* window = NULL;
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

        static float red = 0.0;
        static float green = 0.5;
        static float blue = 1.0;
        red+=0.1;
        green+=0.1;
        blue+=0.1;
        red=(red>1)?0.1:red;
        green=(green>1)?0.1:green;
        blue=(blue>1)?0.1:blue;



        glClearColor( red,green,blue,1 );
        glClear(GL_COLOR_BUFFER_BIT);
        /*if(nullptr != window) {
            SDL_GL_SwapWindow( window );
        }*/
        SDL_GL_SwapWindow( window );
    }
    /* End loop here */
}
