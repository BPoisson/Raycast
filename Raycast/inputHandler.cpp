#include "inputHandler.h"
#include <SDL3/SDL.h>

InputHandler::InputHandler() : quitRequested(false) {
    mouseState = {};
    keyState = {};
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
            case SDL_EVENT_KEY_DOWN:
                switch (event.key.scancode) {
                    case SDL_SCANCODE_W:
                        keyState.wDown = true;
                        break;
                    case SDL_SCANCODE_A:
                        keyState.aDown = true;
                        break;
                    case SDL_SCANCODE_S:
                        keyState.sDown = true;
                        break;
                    case SDL_SCANCODE_D:
                        keyState.dDown = true;
                        break;
                    case SDL_SCANCODE_UP:
                        keyState.upDown = true;
                        break;
                    case SDL_SCANCODE_DOWN:
                        keyState.downDown = true;
                        break;
                    case SDL_SCANCODE_LEFT:
                        keyState.leftDown = true;
                        break;
                    case SDL_SCANCODE_RIGHT:
                        keyState.rightDown = true;
                        break;
                    default:
                        break;
                }
                break;
            case SDL_EVENT_KEY_UP:
                switch (event.key.scancode) {
                    case SDL_SCANCODE_W:
                        keyState.wDown = false;
                        break;
                    case SDL_SCANCODE_A:
                        keyState.aDown = false;
                        break;
                    case SDL_SCANCODE_S:
                        keyState.sDown = false;
                        break;
                    case SDL_SCANCODE_D:
                        keyState.dDown = false;
                        break;
                    case SDL_SCANCODE_UP:
                        keyState.upDown = false;
                        break;
                    case SDL_SCANCODE_DOWN:
                        keyState.downDown = false;
                        break;
                    case SDL_SCANCODE_LEFT:
                        keyState.leftDown = false;
                        break;
                    case SDL_SCANCODE_RIGHT:
                        keyState.rightDown = false;
                        break;
                    default:
                        break;
                }
                break;
            default:
                break;
        }
    }
    mouseState.prevLeftDown = prevLeftDown;
    mouseState.prevRightDown = prevRightDown;
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

bool InputHandler::GetWKeyDown() {
    return keyState.wDown;
}

bool InputHandler::GetAKeyDown() {
    return keyState.aDown;
}

bool InputHandler::GetSKeyDown() {
    return keyState.sDown;
}

bool InputHandler::GetDKeyDown() {
    return keyState.dDown;
}

bool InputHandler::GetUpKeyDown() {
    return keyState.upDown;
}

bool InputHandler::GetDownKeyDown() {
    return keyState.downDown;
}

bool InputHandler::GetLeftKeyDown() {
    return keyState.leftDown;
}

bool InputHandler::GetRightKeyDown() {
    return keyState.rightDown;
}