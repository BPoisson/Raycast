#include "game.h"

int main() {
	Game game;
	if (!game.Init("RayCaster", 2560, 1080)) {
		return -1;
	}
	game.Run();

	return 0;
}