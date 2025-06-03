#include "engine.h"

int main() {
	Engine engine;

	if (!engine.Init("RayCaster", 2400, 1200)) {
		return -1;
	}
	engine.Run();

	return 0;
}