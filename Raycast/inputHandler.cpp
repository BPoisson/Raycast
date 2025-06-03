#include "inputHandler.h"
#include <SDL3/SDL.h>

InputHandler::InputHandler() : quitRequested(false) {
    mouseState = {};
}

InputHandler::~InputHandler() {}

void InputHandler::HandleEvents() {
    SDL_Event event;
    bool prevLeftDown = mouseState.leftDown;
    bool prevRightDown = mouseState.rightDown;

    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_EVENT_QUIT:
                quitRequested = true;
                break;
            case SDL_EVENT_MOUSE_BUTTON_DOWN:
                if (event.button.button == SDL_BUTTON_LEFT) {
                    mouseState.leftDown = true;
                } else if (event.button.button == SDL_BUTTON_RIGHT) {
                    mouseState.rightDown = true;
                }
                break;
            case SDL_EVENT_MOUSE_BUTTON_UP:
                if (event.button.button == SDL_BUTTON_LEFT) {
                    mouseState.leftDown = false;
                } else if (event.button.button == SDL_BUTTON_RIGHT) {
                    mouseState.rightDown = false;
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
    mouseState.prevRightDown = prevRightDown;
}

const MouseState& InputHandler::GetMouseState() const {
    return mouseState;
}

bool InputHandler::GetQuitRequested() {
    return quitRequested;
}

bool InputHandler::GetLeftMouseButtonDown() {
    return mouseState.leftDown;
}

bool InputHandler::GetRightMouseButtonDown() {
    return mouseState.rightDown;
}

bool InputHandler::GetLeftPrevMouseButtonDown() {
    return mouseState.prevLeftDown;
}

bool InputHandler::GetRightPrevMouseButtonDown() {
    return mouseState.prevRightDown;
}

float InputHandler::GetMouseX() {
    return mouseState.x;
}

float InputHandler::GetMouseY() {
    return mouseState.y;
}