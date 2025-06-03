#include "inputHandler.h"
#include <SDL3/SDL.h>

InputHandler::InputHandler() : quitRequested(false) {
    mouseState = {};
}

InputHandler::~InputHandler() {}

//struct MouseState {
//    bool leftDown = false;
//    bool rightDown = false;
//    int x = 0;
//    int y = 0;
//    int deltaX = 0;
//    int deltaY = 0;
//};

void InputHandler::HandleEvents() {
    SDL_Event event;
    bool prevLeftDown = mouseState.leftDown;

    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_EVENT_QUIT:
                quitRequested = true;
                break;
            case SDL_EVENT_MOUSE_BUTTON_DOWN:
                if (event.button.button == SDL_BUTTON_LEFT) {
                    
                    mouseState.leftDown = true;
                }
                break;
            case SDL_EVENT_MOUSE_BUTTON_UP:
                if (event.button.button == SDL_BUTTON_LEFT) {

                    mouseState.leftDown = false;
                }
                break;
            case SDL_EVENT_MOUSE_MOTION:
                mouseState.x = event.motion.x;
                mouseState.y = event.motion.y;
                mouseState.deltaX = event.motion.xrel;
                mouseState.deltaY = event.motion.yrel;
                break;
            default:
                break;
        }
    }
    mouseState.prevLeftDown = prevLeftDown;
}

const MouseState& InputHandler::GetMouseState() const {
    return mouseState;
}

bool InputHandler::GetQuitRequested() {
    return quitRequested;
}

bool InputHandler::GetMouseButtonDown() {
    return mouseState.leftDown;
}

bool InputHandler::GetPrevMouseButtonDown() {
    return mouseState.prevLeftDown;
}

float InputHandler::GetMouseX() {
    return mouseState.x;
}

float InputHandler::GetMouseY() {
    return mouseState.y;
}