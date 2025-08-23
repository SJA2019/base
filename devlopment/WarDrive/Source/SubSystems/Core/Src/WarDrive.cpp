#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "SDL.h"
#include "WarDrive.h"

WarDrive::WarDrive()
{
    InputDeviceSelection::DeviceSet inputDeviceSet;
    inputDeviceSet |= InputDeviceSelection::joyInputDevice;
    inputDeviceSet |= InputDeviceSelection::mouseInputDevice;
    inputDeviceSet |= InputDeviceSelection::keyboardDevice;
    shared_ptr<InputManager> t_sptrInputManager(new InputManager(inputDeviceSet));
    m_sptrInputManager = t_sptrInputManager;

    rendererInstance = make_shared<Renderer>();
}

WarDrive::~WarDrive() {
    m_sptrInputManager = nullptr;
}

void WarDrive::Run()
{
    IMEvent inputEvent = {eIMEventNotAvailable, SDL_EventType()};
    while (true)
    {
        inputEvent = m_sptrInputManager->PollJoyEvents();
        if (EIMJoyEventType::eIMEventBailOut == inputEvent.eventType)
        {
            break;
        }
        else if (EIMJoyEventType::eIMEventAvailable == inputEvent.eventType)
        {
            if(nullptr != rendererInstance && inputEvent.sdlEvent.key.type != SDL_EVENT_KEY_UP) {
                rendererInstance->HandleInput(inputEvent.sdlEvent.key.key);
                rendererInstance->Render();
            }
            
        }  /*else {
            rendererInstance->HandleInput(SDLK_1);
            rendererInstance->Render();
        }*/
    }
}
