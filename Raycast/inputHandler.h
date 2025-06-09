#ifndef INPUT_HANDLER_H
#define INPUT_HANDLER_H

struct MouseState {
	bool leftDown = false;
	bool rightDown = false;
	bool prevLeftDown = false;
	bool prevRightDown = false;
	float x = 0;
	float y = 0;
	float deltaX = 0;
	float deltaY = 0;
};

struct KeyState {
	// WASD keys.
	bool wDown = false;
	bool aDown = false;
	bool sDown = false;
	bool dDown = false;

	// Arrow keys.
	bool upDown = false;
	bool downDown = false;
	bool leftDown = false;
	bool rightDown = false;
};

class InputHandler {
public:
	InputHandler();
	~InputHandler();

	void HandleEvents();
	bool GetQuitRequested();
	bool GetLeftMouseButtonDown();
	bool GetRightMouseButtonDown();
	bool GetLeftPrevMouseButtonDown();
	bool GetRightPrevMouseButtonDown();
	float GetMouseX();
	float GetMouseY();

	bool GetWKeyDown();
	bool GetAKeyDown();
	bool GetSKeyDown();
	bool GetDKeyDown();
	bool GetUpKeyDown();
	bool GetDownKeyDown();
	bool GetLeftKeyDown();
	bool GetRightKeyDown();

private:
	bool quitRequested;
	MouseState mouseState;
	KeyState keyState;
};

#endif
