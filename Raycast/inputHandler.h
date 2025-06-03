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

class InputHandler {
public:
	InputHandler();
	~InputHandler();

	void HandleEvents();
	const MouseState& GetMouseState() const;
	bool GetQuitRequested();
	bool GetMouseButtonDown();
	bool GetPrevMouseButtonDown();
	float GetMouseX();
	float GetMouseY();

private:
	bool quitRequested;
	MouseState mouseState;
};

#endif
